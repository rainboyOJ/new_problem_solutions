import {
  Application,
  Circle,
  Container,
  FederatedPointerEvent,
  Graphics,
  Point,
  Text,
  type TextStyleOptions,
} from 'pixi.js';
import type { Position, PositionMap, RelationEdge, RelationNode } from './types';

export interface PixiGraphHandlers {
  onNodeSelect: (node: RelationNode) => void;
  onNodeOpen: (node: RelationNode) => void;
  onNodeHover: (node: RelationNode | null) => void;
  onEdgeHover: (edge: RelationEdge | null, x: number, y: number) => void;
  onNodePosition: (id: string, position: Position) => void;
}

export interface PixiGraphOptions {
  dark: boolean;
  selectedId: string;
  hoveredId: string;
  matchedIds: Set<string>;
}

interface NodeVisual {
  node: RelationNode;
  hit: Graphics;
  ring: Graphics;
  label: Text;
  radius: number;
}

interface PointerPosition {
  x: number;
  y: number;
  type: string;
}

const MIN_ZOOM = 0.08;
const MAX_ZOOM = 6;

export class PixiGraphRenderer {
  private app: Application | null = null;
  private host: HTMLElement | null = null;
  private world = new Container();
  private edgeLayer = new Graphics();
  private nodeLayer = new Container();
  private nodeVisuals = new Map<string, NodeVisual>();
  private nodes: RelationNode[] = [];
  private edges: RelationEdge[] = [];
  private positions: PositionMap = {};
  private handlers: PixiGraphHandlers;
  private options: PixiGraphOptions = { dark: false, selectedId: '', hoveredId: '', matchedIds: new Set() };
  private pointerPositions = new Map<number, PointerPosition>();
  private panPointerId: number | null = null;
  private panLast: Point | null = null;
  private dragId = '';
  private dragPointerId: number | null = null;
  private dragMoved = false;
  private dragCandidate: { id: string; pointerId: number; x: number; y: number; type: string } | null = null;
  private longPressTimer: number | null = null;
  private pinchDistance = 0;
  private pinchCenter: Point | null = null;
  private lastTapAt = 0;
  private lastTapId = '';
  private initializedViewport = false;
  private resizeObserver: ResizeObserver | null = null;
  private wheelHandler: ((event: WheelEvent) => void) | null = null;

  constructor(handlers: PixiGraphHandlers) {
    this.handlers = handlers;
  }

  static canRenderWebGL(): boolean {
    try {
      const canvas = document.createElement('canvas');
      return Boolean(canvas.getContext('webgl2') || canvas.getContext('webgl'));
    } catch {
      return false;
    }
  }

  async mount(host: HTMLElement, options: PixiGraphOptions): Promise<void> {
    if (!PixiGraphRenderer.canRenderWebGL()) {
      throw new Error('当前浏览器不支持 WebGL');
    }

    this.host = host;
    this.options = options;
    const app = new Application();
    await app.init({
      resizeTo: host,
      preference: 'webgl',
      antialias: true,
      autoDensity: true,
      resolution: Math.min(window.devicePixelRatio || 1, 2),
      backgroundAlpha: 0,
    });
    this.app = app;
    host.replaceChildren(app.canvas);
    app.canvas.className = 'relations2-canvas';
    app.canvas.setAttribute('role', 'img');
    app.canvas.setAttribute('aria-label', '题目关系图 Canvas');
    app.stage.eventMode = 'static';
    app.stage.hitArea = app.screen;
    app.stage.addChild(this.world);
    this.world.addChild(this.edgeLayer);
    this.world.addChild(this.nodeLayer);
    this.world.position.set(app.screen.width / 2, app.screen.height / 2);
    this.bindEvents();
    this.resizeObserver = new ResizeObserver(() => this.syncStageBounds());
    this.resizeObserver.observe(host);
  }

  update(nodes: RelationNode[], edges: RelationEdge[], positions: PositionMap, options: PixiGraphOptions): void {
    this.nodes = nodes;
    this.edges = edges;
    this.positions = positions;
    this.options = options;
    if (!this.app) return;

    const nextIds = new Set(nodes.map((node) => node.id));
    this.nodeVisuals.forEach((visual, id) => {
      if (!nextIds.has(id)) {
        visual.hit.destroy();
        visual.ring.destroy();
        visual.label.destroy();
        this.nodeVisuals.delete(id);
      }
    });

    nodes.forEach((node) => {
      let visual = this.nodeVisuals.get(node.id);
      if (!visual) {
        visual = this.createNodeVisual(node);
        this.nodeVisuals.set(node.id, visual);
        this.nodeLayer.addChild(visual.ring, visual.hit, visual.label);
      }
      visual.node = node;
      this.updateNodeVisual(visual);
    });

    this.drawEdges();
    this.syncStageBounds();
    if (!this.initializedViewport && nodes.length > 0) {
      this.fitToNodes();
      this.initializedViewport = true;
    }
  }

  fitToNodes(): void {
    if (!this.app || this.nodes.length === 0) return;
    const points = this.nodes
      .map((node, index) => this.positions[node.id] || fallbackPosition(index))
      .filter((position): position is Position => Number.isFinite(position.x) && Number.isFinite(position.y));
    if (!points.length) return;
    const xs = points.map((point) => point.x);
    const ys = points.map((point) => point.y);
    const width = Math.max(260, Math.max(...xs) - Math.min(...xs) + 100);
    const height = Math.max(220, Math.max(...ys) - Math.min(...ys) + 100);
    const scale = clamp(Math.min(this.app.screen.width / width, this.app.screen.height / height), MIN_ZOOM, 1.6);
    this.world.scale.set(scale);
    this.world.position.set(this.app.screen.width / 2 - ((Math.max(...xs) + Math.min(...xs)) / 2) * scale, this.app.screen.height / 2 - ((Math.max(...ys) + Math.min(...ys)) / 2) * scale);
    this.updateLabelVisibility();
  }

  focusNode(id: string): void {
    const position = this.positions[id];
    if (!this.app || !position) return;
    const scale = Math.max(this.world.scale.x, 1);
    this.world.scale.set(scale);
    this.world.position.set(this.app.screen.width / 2 - position.x * scale, this.app.screen.height / 2 - position.y * scale);
    this.updateLabelVisibility();
  }

  zoomIn(): void {
    this.zoomAt(1.3, this.app ? this.app.screen.width / 2 : 0, this.app ? this.app.screen.height / 2 : 0);
  }

  zoomOut(): void {
    this.zoomAt(1 / 1.3, this.app ? this.app.screen.width / 2 : 0, this.app ? this.app.screen.height / 2 : 0);
  }

  resetViewport(): void {
    if (!this.app) return;
    this.world.scale.set(1);
    this.world.position.set(this.app.screen.width / 2, this.app.screen.height / 2);
    this.updateLabelVisibility();
  }

  destroy(): void {
    this.resizeObserver?.disconnect();
    this.resizeObserver = null;
    if (this.app?.canvas && this.wheelHandler) this.app.canvas.removeEventListener('wheel', this.wheelHandler);
    this.app?.stage.removeAllListeners();
    this.nodeVisuals.clear();
    this.app?.destroy(true, { children: true, texture: true, textureSource: true });
    this.app = null;
    this.host = null;
  }

  private createNodeVisual(node: RelationNode): NodeVisual {
    const radius = Math.min(15, 8 + Math.sqrt(node.predecessorCount + node.successorCount + node.commonCount) * 1.4);
    const hit = new Graphics().circle(0, 0, radius + 7).fill({ color: 0xffffff, alpha: 0.001 });
    const ring = new Graphics();
    const labelStyle: TextStyleOptions = {
      fontFamily: 'Inter, system-ui, sans-serif',
      fontSize: 12,
      fontWeight: '600',
      fill: this.options.dark ? 0xe2e8f0 : 0x1e293b,
      align: 'center',
      stroke: { color: this.options.dark ? 0x0f172a : 0xffffff, width: 3 },
    };
    const label = new Text({ text: node.label, style: labelStyle });
    label.anchor.set(0.5, 0);
    hit.eventMode = 'static';
    hit.cursor = 'pointer';
    hit.on('pointerdown', (event) => this.handleNodeDown(event, node.id));
    hit.on('pointertap', (event) => this.handleNodeTap(event, node.id));
    hit.on('pointerover', () => this.handlers.onNodeHover(this.nodes.find((item) => item.id === node.id) || null));
    hit.on('pointerout', () => this.handlers.onNodeHover(null));
    return { node, hit, ring, label, radius };
  }

  private updateNodeVisual(visual: NodeVisual): void {
    const node = visual.node;
    const position = this.positions[node.id] || { x: 0, y: 0 };
    visual.hit.position.set(position.x, position.y);
    visual.ring.position.set(position.x, position.y);
    visual.label.position.set(position.x, position.y + visual.radius + 4);
    visual.ring.clear().circle(0, 0, visual.radius).fill({ color: toColor(node.color), alpha: node.isolated ? 0.55 : 0.92 }).stroke({ color: this.options.dark ? 0x0f172a : 0xffffff, width: 1.5, alpha: 0.9 });
    if (node.id === this.options.selectedId || node.id === this.options.hoveredId) {
      visual.ring.circle(0, 0, visual.radius + 5).stroke({ color: 0xf59e0b, width: 2.5, alpha: 1 });
    } else if (this.options.matchedIds.has(node.id)) {
      visual.ring.circle(0, 0, visual.radius + 4).stroke({ color: 0xf59e0b, width: 2, alpha: 0.95 });
    }
    visual.label.style.fill = this.options.dark ? 0xe2e8f0 : 0x1e293b;
    visual.label.style.stroke = { color: this.options.dark ? 0x0f172a : 0xffffff, width: 3 };
    visual.label.visible = this.shouldShowLabel(node);
    visual.hit.alpha = node.isolated ? 0.6 : 1;
    visual.label.alpha = node.isolated ? 0.65 : 1;
  }

  private shouldShowLabel(node: RelationNode): boolean {
    const zoom = this.world.scale.x;
    return zoom >= 1.12 || node.id === this.options.selectedId || node.id === this.options.hoveredId || this.options.matchedIds.has(node.id);
  }

  private updateLabelVisibility(): void {
    this.nodeVisuals.forEach((visual) => {
      visual.label.visible = this.shouldShowLabel(visual.node);
    });
  }

  private drawEdges(): void {
    const graphics = this.edgeLayer;
    graphics.clear();
    const byId = new Map(this.nodes.map((node) => [node.id, this.positions[node.id]]));
    const edgeColor = this.options.dark ? 0x94a3b8 : 0x64748b;
    this.edges.forEach((edge) => {
      const source = byId.get(edge.source);
      const target = byId.get(edge.target);
      if (!source || !target) return;
      if (edge.type === 'common') {
        drawDashedLine(graphics, source.x, source.y, target.x, target.y, this.options.dark ? 0x4ade80 : 0x15803d, 2, 9, 7);
      } else {
        graphics.moveTo(source.x, source.y).lineTo(target.x, target.y).stroke({ color: this.options.dark ? 0x60a5fa : 0x2563eb, width: 2.2, alpha: 0.82 });
        drawArrow(graphics, source, target, this.options.dark ? 0x60a5fa : 0x2563eb);
      }
    });
    if (this.edges.length === 0) {
      graphics.moveTo(0, 0).lineTo(0, 0).stroke({ color: edgeColor, width: 1, alpha: 0 });
    }
  }

  private bindEvents(): void {
    if (!this.app) return;
    this.app.stage.on('pointerdown', (event: FederatedPointerEvent) => {
      if (event.target !== this.app?.stage) return;
      this.pointerPositions.set(event.pointerId, { x: event.global.x, y: event.global.y, type: event.pointerType });
      if (this.pointerPositions.size === 1) {
        this.panPointerId = event.pointerId;
        this.panLast = new Point(event.global.x, event.global.y);
      }
      this.updatePinchState();
    });
    this.app.stage.on('globalpointermove', (event: FederatedPointerEvent) => {
      this.pointerPositions.set(event.pointerId, { x: event.global.x, y: event.global.y, type: event.pointerType });
      this.handlePointerMove(event);
      if (!this.dragId && !this.panPointerId && this.pointerPositions.size < 2) {
        const edge = this.findEdgeAt(event.global.x, event.global.y);
        this.handlers.onEdgeHover(edge, event.global.x, event.global.y);
      }
      this.updatePinchState();
    });
    this.app.stage.on('pointerup', (event: FederatedPointerEvent) => this.endPointer(event.pointerId));
    this.app.stage.on('pointerupoutside', (event: FederatedPointerEvent) => this.endPointer(event.pointerId));
    this.app.stage.on('pointercancel', (event: FederatedPointerEvent) => this.endPointer(event.pointerId));
    this.wheelHandler = (event: WheelEvent) => {
      event.preventDefault();
      if (!this.app) return;
      const bounds = this.app.canvas.getBoundingClientRect();
      const x = event.clientX - bounds.left;
      const y = event.clientY - bounds.top;
      this.zoomAt(Math.exp(-event.deltaY * 0.0018), x, y);
    };
    this.app.canvas.addEventListener('wheel', this.wheelHandler, { passive: false });
  }

  private handleNodeDown(event: FederatedPointerEvent, id: string): void {
    event.stopPropagation();
    const isTouch = event.pointerType === 'touch';
    this.dragCandidate = { id, pointerId: event.pointerId, x: event.global.x, y: event.global.y, type: event.pointerType };
    if (isTouch) {
      this.longPressTimer = window.setTimeout(() => this.activateDrag(), 300);
    } else {
      this.activateDrag();
    }
    this.pointerPositions.set(event.pointerId, { x: event.global.x, y: event.global.y, type: event.pointerType });
  }

  private activateDrag(): void {
    if (!this.dragCandidate) return;
    this.dragId = this.dragCandidate.id;
    this.dragPointerId = this.dragCandidate.pointerId;
    this.dragMoved = false;
    this.panPointerId = null;
    this.panLast = null;
    if (this.longPressTimer !== null) window.clearTimeout(this.longPressTimer);
    this.longPressTimer = null;
  }

  private handleNodeTap(event: FederatedPointerEvent, id: string): void {
    event.stopPropagation();
    if (this.dragMoved) return;
    const node = this.nodes.find((item) => item.id === id);
    if (!node) return;
    const now = performance.now();
    if (this.lastTapId === id && now - this.lastTapAt < 330) {
      this.handlers.onNodeOpen(node);
      this.lastTapAt = 0;
      this.lastTapId = '';
    } else {
      this.handlers.onNodeSelect(node);
      this.lastTapAt = now;
      this.lastTapId = id;
    }
  }

  private handlePointerMove(event: FederatedPointerEvent): void {
    if (this.dragId && this.dragPointerId === event.pointerId) {
      const local = this.toWorld(event.global.x, event.global.y);
      this.positions[this.dragId] = local;
      this.dragMoved = true;
      this.updateNodeVisual(this.nodeVisuals.get(this.dragId)!);
      this.drawEdges();
      this.handlers.onNodePosition(this.dragId, local);
      return;
    }
    if (this.dragCandidate && this.dragCandidate.pointerId === event.pointerId && !this.dragId) {
      const moved = Math.hypot(event.global.x - this.dragCandidate.x, event.global.y - this.dragCandidate.y);
      if (moved > 10) {
        if (this.longPressTimer !== null) window.clearTimeout(this.longPressTimer);
        this.longPressTimer = null;
        this.dragCandidate = null;
      }
    }
    if (this.panPointerId === event.pointerId && this.panLast && this.pointerPositions.size < 2) {
      const dx = event.global.x - this.panLast.x;
      const dy = event.global.y - this.panLast.y;
      this.world.position.x += dx;
      this.world.position.y += dy;
      this.panLast.set(event.global.x, event.global.y);
    }
  }

  private endPointer(pointerId: number): void {
    this.pointerPositions.delete(pointerId);
    if (this.longPressTimer !== null) window.clearTimeout(this.longPressTimer);
    this.longPressTimer = null;
    if (this.dragPointerId === pointerId && this.dragId) {
      this.handlers.onNodePosition(this.dragId, this.positions[this.dragId]);
    }
    this.dragId = '';
    this.dragPointerId = null;
    this.dragCandidate = null;
    this.dragMoved = false;
    if (this.panPointerId === pointerId) {
      this.panPointerId = null;
      this.panLast = null;
    }
    this.updatePinchState();
  }

  private updatePinchState(): void {
    if (this.pointerPositions.size < 2) {
      this.pinchDistance = 0;
      this.pinchCenter = null;
      return;
    }
    const [first, second] = Array.from(this.pointerPositions.values());
    const center = new Point((first.x + second.x) / 2, (first.y + second.y) / 2);
    const distance = Math.hypot(first.x - second.x, first.y - second.y);
    if (this.pinchDistance > 0 && this.pinchCenter) {
      this.zoomAt(distance / this.pinchDistance, this.pinchCenter.x, this.pinchCenter.y);
      this.world.position.x += center.x - this.pinchCenter.x;
      this.world.position.y += center.y - this.pinchCenter.y;
    }
    this.pinchDistance = distance;
    this.pinchCenter = center;
    this.panPointerId = null;
    this.panLast = null;
  }

  private zoomAt(factor: number, x: number, y: number): void {
    if (!this.app) return;
    const oldScale = this.world.scale.x;
    const nextScale = clamp(oldScale * factor, MIN_ZOOM, MAX_ZOOM);
    const worldPoint = { x: (x - this.world.position.x) / oldScale, y: (y - this.world.position.y) / oldScale };
    this.world.scale.set(nextScale);
    this.world.position.set(x - worldPoint.x * nextScale, y - worldPoint.y * nextScale);
    this.updateLabelVisibility();
  }

  private toWorld(x: number, y: number): Position {
    return { x: (x - (this.world.position.x || 0)) / this.world.scale.x, y: (y - (this.world.position.y || 0)) / this.world.scale.y };
  }

  private findEdgeAt(screenX: number, screenY: number): RelationEdge | null {
    if (this.edges.length === 0) return null;
    const point = this.toWorld(screenX, screenY);
    const positions = this.positions;
    let closest: RelationEdge | null = null;
    let distance = Number.POSITIVE_INFINITY;
    this.edges.forEach((edge) => {
      const source = positions[edge.source];
      const target = positions[edge.target];
      if (!source || !target) return;
      const current = segmentDistance(point.x, point.y, source.x, source.y, target.x, target.y);
      if (current < distance) {
        distance = current;
        closest = edge;
      }
    });
    return distance <= Math.max(8 / this.world.scale.x, 10) ? closest : null;
  }

  private syncStageBounds(): void {
    if (!this.app) return;
    this.app.stage.hitArea = this.app.screen;
    if (!this.initializedViewport && this.nodes.length === 0) {
      this.world.position.set(this.app.screen.width / 2, this.app.screen.height / 2);
    }
  }
}

function drawDashedLine(graphics: Graphics, x1: number, y1: number, x2: number, y2: number, color: number, width: number, dash: number, gap: number): void {
  const length = Math.hypot(x2 - x1, y2 - y1);
  if (length === 0) return;
  const dx = (x2 - x1) / length;
  const dy = (y2 - y1) / length;
  for (let cursor = 0; cursor < length; cursor += dash + gap) {
    const end = Math.min(length, cursor + dash);
    graphics.moveTo(x1 + dx * cursor, y1 + dy * cursor).lineTo(x1 + dx * end, y1 + dy * end).stroke({ color, width, alpha: 0.72 });
  }
}

function drawArrow(graphics: Graphics, source: Position, target: Position, color: number): void {
  const angle = Math.atan2(target.y - source.y, target.x - source.x);
  const length = Math.hypot(target.x - source.x, target.y - source.y);
  const end = { x: target.x - Math.cos(angle) * 9, y: target.y - Math.sin(angle) * 9 };
  const size = 6;
  graphics
    .moveTo(end.x, end.y)
    .lineTo(end.x - Math.cos(angle - Math.PI / 6) * size, end.y - Math.sin(angle - Math.PI / 6) * size)
    .lineTo(end.x - Math.cos(angle + Math.PI / 6) * size, end.y - Math.sin(angle + Math.PI / 6) * size)
    .closePath()
    .fill({ color, alpha: 0.9 });
  if (length === 0) graphics.clear();
}

function fallbackPosition(index: number): Position {
  const angle = index * 2.399963229728653;
  const radius = 100 + Math.sqrt(index + 1) * 32;
  return { x: Math.cos(angle) * radius, y: Math.sin(angle) * radius };
}

function segmentDistance(px: number, py: number, x1: number, y1: number, x2: number, y2: number): number {
  const dx = x2 - x1;
  const dy = y2 - y1;
  if (dx === 0 && dy === 0) return Math.hypot(px - x1, py - y1);
  const t = clamp(((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy), 0, 1);
  return Math.hypot(px - (x1 + t * dx), py - (y1 + t * dy));
}

function toColor(value: string): number {
  const normalized = value.replace(/^#/, '');
  const parsed = Number.parseInt(normalized, 16);
  return Number.isFinite(parsed) ? parsed : 0x64748b;
}

function clamp(value: number, min: number, max: number): number {
  return Math.min(max, Math.max(min, value));
}
