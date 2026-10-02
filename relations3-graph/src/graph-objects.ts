import { BufferAttribute, BufferGeometry, Color, ConeGeometry, Group, Line, LineBasicMaterial, LineDashedMaterial, Mesh, MeshBasicMaterial, SphereGeometry, Vector3 } from 'three';
import SpriteText from 'three-spritetext';
import type { FocusNeighborhood, Position3D, RelationGraphResponse, SimLink, SimNode } from './types';

export interface VisualState {
  data: RelationGraphResponse; visibleNodes: Set<string>; visibleEdges: Set<string>;
  focus: FocusNeighborhood; matched: Set<string>; query: string; hovered: string; hoveredEdge: string; dark: boolean;
}
export interface NodeObject { group: Group; sphere: Mesh<SphereGeometry, MeshBasicMaterial>; halo: Mesh<SphereGeometry, MeshBasicMaterial>; label?: SpriteText }
interface EdgeObject { group: Group; line: Line<BufferGeometry, LineBasicMaterial | LineDashedMaterial>; arrow?: Mesh<ConeGeometry, MeshBasicMaterial>; last: string }
const Y_AXIS = new Vector3(0, 1, 0);
const BASE_RADIUS = 6;

export function shortTitle(title: string, limit = 14): string {
  const chars = Array.from(title);
  return chars.length > limit ? `${chars.slice(0, limit).join('')}…` : title;
}

// The graph library owns disposal of objects handed to it (including custom objects).
// Geometry is per node so removing a node never disposes another node's geometry.
export class GraphObjects {
  nodes = new Map<string, NodeObject>();
  edges = new Map<string, EdgeObject>();
  private nodeData = new Map<string, RelationGraphResponse['nodes'][number]>();
  private visual: VisualState | null = null;
  private parallel = new Map<string, number>();

  node(node: SimNode): Group {
    const cached = this.nodes.get(node.id);
    if (cached) return cached.group;
    const group = new Group();
    const sphere = new Mesh(new SphereGeometry(BASE_RADIUS, 12, 8), new MeshBasicMaterial({ color: '#64748b', transparent: true }));
    sphere.userData.nodeId = node.id;
    const halo = new Mesh(new SphereGeometry(BASE_RADIUS * 1.4, 12, 8), new MeshBasicMaterial({ color: '#2563eb', wireframe: true, transparent: true, depthWrite: false }));
    halo.visible = false;
    halo.raycast = () => {};
    const raycast = sphere.raycast.bind(sphere);
    sphere.raycast = (raycaster, intersects) => { if (group.visible) raycast(raycaster, intersects); };
    group.add(sphere, halo);
    group.position.set(node.x, node.y, node.z);
    this.nodes.set(node.id, { group, sphere, halo });
    if (this.visual) this.styleNode(node.id);
    return group;
  }

  edge(edge: SimLink): Group {
    const cached = this.edges.get(edge.id);
    if (cached) return cached.group;
    const group = new Group();
    const geometry = new BufferGeometry();
    geometry.setAttribute('position', new BufferAttribute(new Float32Array(33 * 3), 3));
    const material = edge.type === 'common'
      ? new LineDashedMaterial({ color: '#0f766e', dashSize: 7, gapSize: 5, transparent: true, depthWrite: false })
      : new LineBasicMaterial({ color: '#2563eb', transparent: true, depthWrite: false });
    const line = new Line(geometry, material);
    const raycast = line.raycast.bind(line);
    line.raycast = (r, hits) => { if (group.visible) raycast(r, hits); };
    group.add(line);
    let arrow: EdgeObject['arrow'];
    if (edge.type === 'pre') {
      arrow = new Mesh(new ConeGeometry(3, 9, 8), new MeshBasicMaterial({ color: '#2563eb', transparent: true, depthWrite: false }));
      arrow.raycast = () => {};
      group.add(arrow);
    }
    this.edges.set(edge.id, { group, line, arrow, last: '' });
    if (this.visual) this.styleEdge(edge.id);
    return group;
  }

  updateEdge(id: string, start: Position3D, end: Position3D): boolean {
    const object = this.edges.get(id);
    if (!object) return true;
    const key = `${start.x},${start.y},${start.z},${end.x},${end.y},${end.z}`;
    if (object.last === key) return true;
    object.last = key;
    const a = new Vector3(start.x, start.y, start.z);
    const b = new Vector3(end.x, end.y, end.z);
    const direction = b.clone().sub(a);
    const length = direction.length();
    if (length < 1e-6) { object.line.visible = false; if (object.arrow) object.arrow.visible = false; return true; }
    direction.normalize();
    a.addScaledVector(direction, BASE_RADIUS + 2);
    b.addScaledVector(direction, -BASE_RADIUS - 2);
    const normal = new Vector3().crossVectors(direction, Math.abs(direction.y) < 0.9 ? Y_AXIS : new Vector3(1, 0, 0)).normalize();
    const offset = this.parallel.get(id) || 0;
    // A quadratic arc separates parallel types/reverse edges without changing endpoints.
    const control = a.clone().add(b).multiplyScalar(0.5).addScaledVector(normal, offset);
    const point = (t: number) => a.clone().multiplyScalar((1 - t) ** 2).addScaledVector(control, 2 * t * (1 - t)).addScaledVector(b, t * t);
    const positions = object.line.geometry.getAttribute('position') as BufferAttribute;
    for (let i = 0; i < 33; i++) { const p = point(i / 32); positions.setXYZ(i, p.x, p.y, p.z); }
    positions.needsUpdate = true;
    object.line.geometry.computeBoundingSphere();
    object.line.visible = true;
    if (object.line.material instanceof LineDashedMaterial) object.line.computeLineDistances();
    if (object.arrow) {
      const t = 0.77;
      object.arrow.position.copy(point(t));
      const tangent = control.clone().sub(a).multiplyScalar(1 - t).add(b.clone().sub(control).multiplyScalar(t)).normalize();
      object.arrow.quaternion.setFromUnitVectors(Y_AXIS, tangent);
      object.arrow.visible = true;
    }
    return true;
  }

  update(visual: VisualState) {
    const dataChanged = this.visual?.data !== visual.data;
    this.visual = visual;
    this.nodeData = new Map(visual.data.nodes.map(n => [n.id, n]));
    if (dataChanged) {
      const pairs = new Map<string, SimLink['id'][]>();
      for (const e of visual.data.edges) {
        const key = [e.source, e.target].sort().join('|');
        pairs.set(key, [...(pairs.get(key) || []), e.id]);
      }
      this.parallel.clear();
      for (const ids of pairs.values()) if (ids.length > 1) ids.sort().forEach((id, i) => this.parallel.set(id, (i + 1) * 18));
      this.edges.forEach(e => { e.last = ''; });
      // Removed objects are disposed by the library's data mapper, not twice here.
      for (const id of this.nodes.keys()) if (!this.nodeData.has(id)) this.nodes.delete(id);
      const edgeIds = new Set(visual.data.edges.map(e => e.id));
      for (const id of this.edges.keys()) if (!edgeIds.has(id)) this.edges.delete(id);
    }
    this.nodes.forEach((_, id) => this.styleNode(id));
    this.edges.forEach((_, id) => this.styleEdge(id));
  }

  private styleNode(id: string) {
    const n = this.nodes.get(id);
    const data = this.nodeData.get(id);
    const v = this.visual;
    if (!n || !v || !data) return;
    n.group.visible = v.visibleNodes.has(id);
    const center = v.focus.centerId === id;
    const foreground = center || v.hovered === id || v.focus.nodeIds.has(id) || v.matched.has(id);
    const dim = (v.focus.centerId || v.query) && !foreground;
    n.sphere.material.color.set(data.color);
    n.sphere.material.opacity = dim ? 0.15 : 0.95;
    n.sphere.material.depthWrite = !dim;
    n.sphere.scale.setScalar(center ? 1.3 : 1);
    n.halo.visible = center || v.hovered === id;
    n.halo.material.color.set(center ? (v.dark ? '#f8fafc' : '#172554') : '#f59e0b');
    if (n.label) n.label.visible = false;
  }
  private styleEdge(id: string) {
    const e = this.edges.get(id);
    const data = this.visual?.data.edges.find(e => e.id === id);
    const v = this.visual;
    if (!e || !data || !v) return;
    e.group.visible = v.visibleEdges.has(id);
    const direct = v.focus.edgeIds.has(id);
    const highlighted = direct || v.hoveredEdge === id || (v.hovered && (data.source === v.hovered || data.target === v.hovered) && (!v.focus.centerId || direct));
    const dim = !!v.focus.centerId && !highlighted;
    const color = data.type === 'common' ? (v.dark ? '#5eead4' : '#0f766e')
      : direct && data.target === v.focus.centerId ? (v.dark ? '#fbbf24' : '#b45309') : (v.dark ? '#93c5fd' : '#2563eb');
    e.line.material.color.set(color);
    e.line.material.opacity = dim ? 0.06 : highlighted ? 1 : 0.65;
    if (e.arrow) { e.arrow.material.color.set(color); e.arrow.material.opacity = e.line.material.opacity; e.arrow.scale.setScalar(highlighted ? 1.25 : 1); }
  }

  label(id: string, full: boolean): SpriteText | undefined {
    const n = this.nodes.get(id);
    const data = this.nodeData.get(id);
    const v = this.visual;
    if (!n || !data || !v || !n.group.visible) return undefined;
    if (!n.label) {
      n.label = new SpriteText('', 10);
      n.label.fontFace = 'system-ui, sans-serif';
      n.label.fontSize = 40;
      n.label.padding = [5, 3];
      n.label.borderRadius = 4;
      n.label.material.depthTest = false;
      n.label.material.depthWrite = false;
      n.label.renderOrder = 10;
      n.label.raycast = () => {};
      n.group.add(n.label);
    }
    const text = `${data.label}\n${full ? data.title : shortTitle(data.title)}`;
    if (n.label.text !== text) n.label.text = text;
    const color = v.dark ? '#f1f5f9' : '#172033';
    const background = v.dark ? '#0f172a' : '#ffffff';
    if (n.label.color !== color) n.label.color = color;
    if (n.label.backgroundColor !== background) n.label.backgroundColor = background;
    return n.label;
  }
}
