import { BufferAttribute, BufferGeometry, ConeGeometry, Group, Line, LineBasicMaterial, LineDashedMaterial, Mesh, MeshBasicMaterial, MeshLambertMaterial, RingGeometry, SphereGeometry, Vector3 } from 'three';
import type { FocusNeighborhood, Position3D, RelationGraphResponse, SimLink, SimNode } from './types';
import { GRAPH_THEME, getGraphCategoryColor } from './graph-theme';
import { edgeVisual } from './graph-visual-style';

export interface VisualState {
  data: RelationGraphResponse; visibleNodes: Set<string>; visibleEdges: Set<string>;
  focus: FocusNeighborhood; matched: Set<string>; query: string; hovered: string; hoveredEdge: string; dark?: boolean;
}
export interface NodeObject { group: Group; sphere: Mesh<SphereGeometry, MeshLambertMaterial>; halo: Mesh<RingGeometry, MeshBasicMaterial> }
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
    const sphere = new Mesh(new SphereGeometry(BASE_RADIUS, 12, 8), new MeshLambertMaterial({ color: '#64748b', transparent: true }));
    sphere.userData.nodeId = node.id;
    const halo = new Mesh(new RingGeometry(BASE_RADIUS * 1.16, BASE_RADIUS * 1.32, 32), new MeshBasicMaterial({ color: GRAPH_THEME.hoverRing, transparent: true, depthWrite: false, side: 2 }));
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
    const ra = this.nodes.get(this.visual?.data.edges.find(e => e.id === id)?.source || '')?.sphere.scale.x ? BASE_RADIUS * (this.visual?.focus.centerId === this.visual?.data.edges.find(e => e.id === id)?.source ? 1.3 : 1) : BASE_RADIUS;
    const rb = this.nodes.get(this.visual?.data.edges.find(e => e.id === id)?.target || '')?.sphere.scale.x ? BASE_RADIUS * (this.visual?.focus.centerId === this.visual?.data.edges.find(e => e.id === id)?.target ? 1.3 : 1) : BASE_RADIUS;
    const key = `${start.x},${start.y},${start.z},${end.x},${end.y},${end.z},${ra},${rb}`;
    if (object.last === key) return true;
    object.last = key;
    const a = new Vector3(start.x, start.y, start.z);
    const b = new Vector3(end.x, end.y, end.z);
    const direction = b.clone().sub(a);
    const length = direction.length();
    if (length < 1e-6) { object.line.visible = false; if (object.arrow) object.arrow.visible = false; return true; }
    direction.normalize();
    a.addScaledVector(direction, ra + 2);
    b.addScaledVector(direction, -rb - 2);
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
    n.sphere.material.color.set(getGraphCategoryColor(data.color));
    n.sphere.material.opacity = dim ? 0.15 : 0.95;
    n.sphere.material.depthWrite = !dim;
    n.sphere.scale.setScalar(center ? 1.3 : 1);
    n.halo.visible = center || v.hovered === id;
    n.halo.material.color.set(center ? GRAPH_THEME.centerRing : GRAPH_THEME.hoverRing);
    n.halo.quaternion.copy((this.visual as any)?.cameraQuaternion || n.halo.quaternion);
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
    const style = edgeVisual(data, v.focus.centerId, direct, !!highlighted);
    e.line.material.color.set(style.color);
    e.line.material.opacity = dim ? 0.05 : style.opacity;
    if (e.arrow) { e.arrow.material.color.set(style.color); e.arrow.material.opacity = e.line.material.opacity; e.arrow.scale.setScalar(highlighted ? 1.25 : 1); }
  }
}
