import { edgeRole, effectiveFocus, focusNeighborhood, writeStored, readStored, type Point, type Camera, type RelationNode, type RelationEdge } from './model';

export interface Scene {
  nodes: RelationNode[]; edges: RelationEdge[]; index: Map<string, RelationEdge[]>;
  visible: Set<string>; edgeIds: Set<string>; matches: Set<string>; searching: boolean;
  selected: string | null; hover: string; dark: boolean;
}
interface Label extends Point { width: number; height: number; id: string; text: string; focus: boolean }
const PALETTES = {
  light: { background: '#f8faf9', text: '#243e49', muted: '#6f858b', edge: '#7d9196', before: '#278a7a', after: '#c17a37', similar: '#8070b2', current: '#205f75' },
  dark: { background: '#101d29', text: '#e0ebee', muted: '#95abb6', edge: '#728ba0', before: '#62c4ad', after: '#e7ae6e', similar: '#b6a0e8', current: '#86c9e1' },
};
const FONT = 'system-ui, -apple-system, "PingFang SC", sans-serif';
export class CanvasGraph {
  camera: Camera = { x: 0, y: 0, k: 1 };
  width = 0; height = 0;
  labels: Label[] = [];
  private cells = new Map<string, { id: string; x: number; y: number }[]>();
  private frame = 0;
  private observer: ResizeObserver;
  private abort = new AbortController();
  private pointers = new Map<number, Point>();
  private drag: { id: string; start: Point; last: Point; moved: boolean } | null = null;
  private pinching = false;
  private hasCamera = false;
  private hoverStart = 0;
  private context: CanvasRenderingContext2D;
  private saveTimer = 0;
  constructor(
    readonly canvas: HTMLCanvasElement,
    public scene: Scene,
    readonly positions: Record<string, Point>,
    private storageKey: string,
    private onHover: (id: string) => void,
    private onSelect: (id: string | null) => void,
  ) {
    const context = canvas.getContext('2d');
    if (!context) throw new Error('当前浏览器无法使用二维画布，请通过搜索和关系清单浏览。');
    this.context = context;
    const saved = readStored<Camera>(`${storageKey}.camera`);
    if (saved && Number.isFinite(saved.x) && Number.isFinite(saved.y) && saved.k >= .04 && saved.k <= 8) {
      this.camera = saved; this.hasCamera = true;
    }
    this.observer = new ResizeObserver(entries => {
      const { width, height } = entries[0].contentRect;
      if (width < 1 || height < 1) return; // Hidden mode must not reset the overview camera.
      const oldWidth = this.width, oldHeight = this.height;
      this.width = width; this.height = height;
      const dpr = Math.min(window.devicePixelRatio || 1, 2);
      canvas.width = Math.round(width * dpr); canvas.height = Math.round(height * dpr);
      if (!this.hasCamera) { this.fit(); if (this.scene.selected) this.locate(this.scene.selected); }
      else if (oldWidth && oldHeight) {
        this.camera.x += (width - oldWidth) / 2; this.camera.y += (height - oldHeight) / 2;
      }
      this.requestDraw();
    });
    this.observer.observe(canvas);
    const opts = { signal: this.abort.signal };
    canvas.addEventListener('pointermove', this.pointerMove, opts);
    canvas.addEventListener('pointerdown', this.pointerDown, opts);
    canvas.addEventListener('pointerup', this.pointerUp, opts);
    canvas.addEventListener('pointercancel', this.pointerCancel, opts);
    canvas.addEventListener('pointerleave', () => { if (!this.drag) this.hover(''); }, opts);
    canvas.addEventListener('wheel', this.wheel, { ...opts, passive: false });
    canvas.addEventListener('keydown', this.keyDown, opts);
    window.addEventListener('pagehide', () => this.save(), opts);
  }
  update(scene: Scene) { this.scene = scene; this.requestDraw(); }
  destroy() {
    clearTimeout(this.saveTimer); this.save(); this.observer.disconnect(); this.abort.abort(); cancelAnimationFrame(this.frame);
  }
  save() {
    if (this.hasCamera) writeStored(`${this.storageKey}.camera`, this.camera);
    writeStored(this.storageKey, this.positions);
  }
  private saveSoon() {
    clearTimeout(this.saveTimer);
    this.saveTimer = window.setTimeout(() => this.save(), 200);
  }
  project(p: Point): Point { return { x: p.x * this.camera.k + this.camera.x, y: p.y * this.camera.k + this.camera.y }; }
  private local(event: PointerEvent | WheelEvent): Point {
    const rect = this.canvas.getBoundingClientRect(); return { x: event.clientX - rect.left, y: event.clientY - rect.top };
  }
  fit() {
    const points = [...this.scene.visible].map(id => this.positions[id]).filter(Boolean);
    if (!points.length || !this.width || !this.height) return;
    let minX = Infinity, maxX = -Infinity, minY = Infinity, maxY = -Infinity;
    for (const p of points) { minX = Math.min(minX, p.x); maxX = Math.max(maxX, p.x); minY = Math.min(minY, p.y); maxY = Math.max(maxY, p.y); }
    const k = Math.max(.04, Math.min(2, (this.width - 100) / Math.max(100, maxX - minX), (this.height - 120) / Math.max(100, maxY - minY)));
    this.camera = { x: this.width / 2 - (minX + maxX) / 2 * k, y: this.height / 2 - (minY + maxY) / 2 * k, k };
    this.hasCamera = true; this.requestDraw(); this.save();
  }
  locate(id: string) {
    const p = this.positions[id]; if (!p) return;
    const k = Math.max(.85, this.camera.k);
    this.camera = { k, x: this.width / 2 - p.x * k, y: this.height / 2 - p.y * k };
    this.hasCamera = true; this.requestDraw(); this.save();
  }
  zoom(factor: number, point: Point = { x: this.width / 2, y: this.height / 2 }) {
    const old = this.camera.k, k = Math.min(8, Math.max(.04, old * factor));
    this.camera = { k, x: point.x - (point.x - this.camera.x) / old * k, y: point.y - (point.y - this.camera.y) / old * k };
    this.requestDraw(); this.saveSoon();
  }
  private hover(id: string) {
    if (id === this.scene.hover) return;
    this.hoverStart = performance.now();
    this.scene = { ...this.scene, hover: id }; this.requestDraw(); this.onHover(id);
  }
  private hit(point: Point): string {
    const x = Math.floor(point.x / 28), y = Math.floor(point.y / 28);
    let nearest = '', distance = 12;
    for (let i = x - 1; i <= x + 1; i++) for (let j = y - 1; j <= y + 1; j++) {
      for (const n of this.cells.get(`${i},${j}`) || []) {
        const d = Math.hypot(point.x - n.x, point.y - n.y);
        if (d < distance) { nearest = n.id; distance = d; }
      }
    }
    if (nearest) return nearest;
    return this.labels.find(l => point.x >= l.x && point.x <= l.x + l.width && point.y >= l.y && point.y <= l.y + l.height)?.id || '';
  }
  private pointerDown = (event: PointerEvent) => {
    if (event.button !== 0) return;
    const p = this.local(event); this.pointers.set(event.pointerId, p);
    this.canvas.setPointerCapture(event.pointerId); this.canvas.focus({ preventScroll: true });
    if (this.pointers.size === 2) { this.pinching = true; if (this.drag) this.drag.moved = true; this.hover(''); return; }
    this.pinching = false; this.drag = { id: this.hit(p), start: p, last: p, moved: false };
  };
  private pointerMove = (event: PointerEvent) => {
    const p = this.local(event);
    if (this.pointers.has(event.pointerId)) {
      const previous = [...this.pointers.values()]; this.pointers.set(event.pointerId, p);
      if (this.pointers.size === 2) {
        const next = [...this.pointers.values()];
        const oldDistance = Math.hypot(previous[0].x - previous[1].x, previous[0].y - previous[1].y);
        const distance = Math.hypot(next[0].x - next[1].x, next[0].y - next[1].y);
        const center = { x: (next[0].x + next[1].x) / 2, y: (next[0].y + next[1].y) / 2 };
        this.camera.x += center.x - (previous[0].x + previous[1].x) / 2;
        this.camera.y += center.y - (previous[0].y + previous[1].y) / 2;
        if (oldDistance > 0) this.zoom(distance / oldDistance, center);
        return;
      }
      if (this.pinching || !this.drag) return;
      const drag = this.drag;
      if (Math.hypot(p.x - drag.start.x, p.y - drag.start.y) > 4) drag.moved = true;
      if (drag.moved) {
        const dx = p.x - drag.last.x, dy = p.y - drag.last.y;
        if (drag.id) {
          const node = this.positions[drag.id]; node.x += dx / this.camera.k; node.y += dy / this.camera.k;
        } else { this.camera.x += dx; this.camera.y += dy; }
        drag.last = p; this.hover(''); this.requestDraw();
      }
      return;
    }
    const id = this.hit(p); this.canvas.style.cursor = id ? 'pointer' : 'grab'; this.hover(id);
  };
  private pointerUp = (event: PointerEvent) => {
    const drag = this.drag;
    if (!this.pinching && drag && !drag.moved) {
      this.onSelect(drag.id || null);
      if (event.pointerType === 'touch') this.hover('');
    }
    this.pointers.delete(event.pointerId);
    if (!this.pointers.size) { this.drag = null; this.pinching = false; }
    this.save();
  };
  private pointerCancel = (event: PointerEvent) => {
    this.pointers.delete(event.pointerId); this.drag = null; this.pinching = false; this.hover('');
  };
  private wheel = (event: WheelEvent) => {
    event.preventDefault(); this.hover(''); this.zoom(Math.exp(-Math.max(-200, Math.min(200, event.deltaY)) * .002), this.local(event));
  };
  private keyDown = (event: KeyboardEvent) => {
    if (['+', '=', '-', 'ArrowLeft', 'ArrowRight', 'ArrowUp', 'ArrowDown', 'Escape', '0'].includes(event.key)) event.preventDefault();
    if (event.key === '+' || event.key === '=') this.zoom(1.25);
    else if (event.key === '-') this.zoom(.8);
    else if (event.key === '0') this.fit();
    else if (event.key === 'Escape') { this.hover(''); this.onSelect(null); }
    else if (event.key.startsWith('Arrow')) {
      this.camera.x += event.key === 'ArrowLeft' ? 50 : event.key === 'ArrowRight' ? -50 : 0;
      this.camera.y += event.key === 'ArrowUp' ? 50 : event.key === 'ArrowDown' ? -50 : 0;
      this.hover(''); this.requestDraw(); this.save();
    }
  };
  requestDraw() { if (!this.frame) this.frame = requestAnimationFrame(() => { this.frame = 0; this.draw(); }); }
  private draw() {
    if (!this.width || !this.height) return;
    const c = this.context, s = this.scene, theme = PALETTES[s.dark ? 'dark' : 'light'];
    const dpr = this.canvas.width / this.width;
    c.setTransform(dpr, 0, 0, dpr, 0, 0); c.globalAlpha = 1; c.fillStyle = theme.background; c.fillRect(0, 0, this.width, this.height);
    const center = effectiveFocus(s.hover, s.selected), focus = focusNeighborhood(s.index, center, s.edgeIds);
    const screen = new Map<string, Point>();
    for (const id of s.visible) { const p = this.positions[id]; if (p) screen.set(id, this.project(p)); }
    const paintEdge = (e: RelationEdge, active: boolean) => {
      const a = screen.get(e.source), b = screen.get(e.target); if (!a || !b) return;
      if ((a.x < -20 && b.x < -20) || (a.x > this.width + 20 && b.x > this.width + 20) || (a.y < -20 && b.y < -20) || (a.y > this.height + 20 && b.y > this.height + 20)) return;
      const role = edgeRole(e, center);
      c.strokeStyle = active && role ? theme[role] : theme.edge;
      c.globalAlpha = active ? .9 : center ? .045 : .13; c.lineWidth = active ? 1.65 : .65;
      c.setLineDash(e.type === 'common' ? [4, 4] : []);
      const dx = b.x - a.x, dy = b.y - a.y, mx = (a.x + b.x) / 2 - dy * .07, my = (a.y + b.y) / 2 + dx * .07;
      c.beginPath(); c.moveTo(a.x, a.y); c.quadraticCurveTo(mx, my, b.x, b.y); c.stroke(); c.setLineDash([]);
      if (active && e.type === 'pre') {
        const distance = Math.hypot(b.x - mx, b.y - my) || 1, ux = (b.x - mx) / distance, uy = (b.y - my) / distance;
        const x = b.x - ux * 9, y = b.y - uy * 9;
        c.fillStyle = c.strokeStyle; c.beginPath(); c.moveTo(x, y); c.lineTo(x - ux * 7 - uy * 3, y - uy * 7 + ux * 3); c.lineTo(x - ux * 7 + uy * 3, y - uy * 7 - ux * 3); c.closePath(); c.fill();
      }
    };
    // Draw muted lines first; highlighted lines never disappear underneath them.
    for (const e of s.edges) if (!focus.edgeIds.has(e.id)) paintEdge(e, false);
    for (const e of s.index.get(center) || []) if (s.edgeIds.has(e.id)) paintEdge(e, true);
    this.cells.clear();
    const candidates: { n: RelationNode; p: Point; radius: number; priority: number }[] = [];
    for (const n of s.nodes) {
      const p = screen.get(n.id); if (!p || p.x < -15 || p.x > this.width + 15 || p.y < -15 || p.y > this.height + 15) continue;
      const key = `${Math.floor(p.x / 28)},${Math.floor(p.y / 28)}`;
      if (!this.cells.has(key)) this.cells.set(key, []); this.cells.get(key)!.push({ id: n.id, ...p });
      const degree = s.index.get(n.id)?.length || 0, current = n.id === center, near = focus.nodeIds.has(n.id);
      const radius = Math.max(2.2, Math.min(6, 2 + Math.sqrt(degree) * .65)) * Math.min(1.5, Math.max(.85, Math.sqrt(this.camera.k)));
      c.globalAlpha = center ? near ? 1 : .16 : s.searching && !s.matches.has(n.id) ? .16 : .85;
      if (current || n.id === s.selected) {
        c.fillStyle = theme.current; c.globalAlpha = .09; c.beginPath(); c.arc(p.x, p.y, radius + 11, 0, Math.PI * 2); c.fill(); c.globalAlpha = 1;
        c.strokeStyle = theme.current; c.lineWidth = 1.5; c.beginPath(); c.arc(p.x, p.y, radius + 4, 0, Math.PI * 2); c.stroke();
      }
      c.fillStyle = n.color || theme.current; c.beginPath(); c.arc(p.x, p.y, radius, 0, Math.PI * 2); c.fill();
      const priority = current ? 10000 : near ? 1000 + degree : s.matches.has(n.id) ? 500 + degree : degree;
      if (!center || near || n.id === s.selected) candidates.push({ n, p, radius, priority });
    }
    candidates.sort((a, b) => b.priority - a.priority || a.n.id.localeCompare(b.n.id));
    this.labels = []; c.textAlign = 'left'; c.textBaseline = 'middle';
    const limit = center ? 80 : Math.min(120, Math.round(24 + this.camera.k * 42));
    for (const { n, p, radius } of candidates) {
      if (this.labels.length >= limit) break;
      const current = n.id === center;
      const text = `${n.label} · ${current ? n.title : n.title.length > 12 ? n.title.slice(0, 12) + '…' : n.title}`;
      c.font = `${current ? '600 13' : '400 11'}px ${FONT}`;
      const width = Math.min(this.width - 16, c.measureText(text).width + 12), height = current ? 26 : 21;
      const variants = [
        { x: p.x + radius + 6, y: p.y - height / 2 },
        { x: p.x - width / 2, y: p.y + radius + 7 },
        { x: p.x - width - radius - 6, y: p.y - height / 2 },
        { x: p.x - width / 2, y: p.y - height - radius - 7 },
      ];
      for (const v of variants) {
        const x = Math.max(8, Math.min(this.width - width - 8, v.x)), y = v.y;
        if (y < 8 || y + height > this.height - 8) continue;
        if (this.labels.some(l => x < l.x + l.width + 5 && x + width + 5 > l.x && y < l.y + l.height + 3 && y + height + 3 > l.y)) continue;
        this.labels.push({ x, y, width, height, id: n.id, text, focus: current });
        c.globalAlpha = current || focus.nodeIds.has(n.id) || !s.searching || s.matches.has(n.id) ? 1 : .2;
        if (current) { c.fillStyle = theme.background; c.fillRect(x, y, width, height); }
        c.strokeStyle = theme.background; c.lineWidth = 4; c.lineJoin = 'round'; c.strokeText(text, x + 6, y + height / 2, width - 12);
        c.fillStyle = current || focus.nodeIds.has(n.id) ? theme.text : theme.muted; c.fillText(text, x + 6, y + height / 2, width - 12); break;
      }
    }
    c.globalAlpha = 1;
    this.canvas.dataset.renderReady = 'true';
    this.canvas.dataset.focusId = center;
    this.canvas.dataset.highlightedEdges = String(focus.edgeIds.size);
    if (this.hoverStart) { this.canvas.dataset.hoverFrameMs = (performance.now() - this.hoverStart).toFixed(1); this.hoverStart = 0; }
  }
}
