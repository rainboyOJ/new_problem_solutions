import { hashString, relationFingerprint } from './graph-data';
import { finitePosition, LAYOUT_VERSION } from './layout-store';
import type { SavedLayout3D } from './layout-store';
import type { Position3D, RelationGraphResponse, SimLink, SimNode } from './types';

export function initialPosition(id: string, isolated: boolean, seed = 0): Position3D {
  const h = hashString(`${seed}:${id}`);
  const z = (h / 0xffffffff) * 2 - 1;
  const angle = (hashString(`${id}:${seed}:angle`) / 0xffffffff) * Math.PI * 2;
  const radius = isolated ? 1300 + (h % 1300) : 180 + (h % 240);
  const planar = Math.sqrt(Math.max(0, 1 - z * z));
  return { x: Math.cos(angle) * planar * radius, y: Math.sin(angle) * planar * radius, z: z * radius };
}
export class GraphModel {
  nodes = new Map<string, SimNode>();
  links = new Map<string, SimLink>();
  pinned = new Set<string>();
  fingerprint = '';
  graphData: { nodes: SimNode[]; links: SimLink[] } = { nodes: [], links: [] };

  reconcile(data: RelationGraphResponse, saved?: SavedLayout3D | null) {
    const fingerprint = relationFingerprint(data);
    const first = !this.fingerprint;
    const changed = this.fingerprint !== fingerprint;
    if (first && saved) this.pinned = new Set(saved.userPinnedIds);
    const valid = new Set(data.nodes.map(n => n.id));
    for (const id of this.nodes.keys()) if (!valid.has(id)) { this.nodes.delete(id); this.pinned.delete(id); }
    for (const n of data.nodes) if (!this.nodes.has(n.id)) {
      const position = saved?.positions[n.id];
      const node: SimNode = { id: n.id, ...(finitePosition(position) ? position : initialPosition(n.id, n.isolated)) };
      this.nodes.set(n.id, node);
      this.freezeNode(node);
    }
    const validEdges = new Set(data.edges.map(e => e.id));
    for (const id of this.links.keys()) if (!validEdges.has(id)) this.links.delete(id);
    for (const e of data.edges) {
      const previous = this.links.get(e.id);
      if (!previous || previous.sourceId !== e.source || previous.targetId !== e.target || previous.type !== e.type) this.links.set(e.id, { id: e.id, source: e.source, target: e.target, sourceId: e.source, targetId: e.target, type: e.type });
    }
    if (changed) this.graphData = { nodes: data.nodes.map(n => this.nodes.get(n.id)!), links: data.edges.map(e => this.links.get(e.id)!) };
    this.fingerprint = fingerprint;
    return { changed, needsLayout: changed && !(first && saved?.fingerprint === fingerprint && data.nodes.every(n => !!saved.positions[n.id])) };
  }
  freezeNode(node: SimNode) {
    node.fx = node.x; node.fy = node.y; node.fz = node.z;
    node.vx = node.vy = node.vz = 0;
  }
  freeze() { this.nodes.forEach(n => this.freezeNode(n)); }
  release(ids: Set<string>) {
    this.freeze();
    for (const id of ids) {
      const n = this.nodes.get(id);
      if (n && !this.pinned.has(id)) { delete n.fx; delete n.fy; delete n.fz; }
    }
  }
  pin(id: string) { const n = this.nodes.get(id); if (n) { this.pinned.add(id); this.freezeNode(n); } }
  reset(data: RelationGraphResponse, ids: Set<string>, seed: number) {
    this.pinned.clear();
    for (const n of data.nodes) if (ids.has(n.id)) Object.assign(this.nodes.get(n.id)!, initialPosition(n.id, n.isolated, seed));
    this.release(ids);
  }
  snapshot(): SavedLayout3D {
    return { version: 1, layoutVersion: LAYOUT_VERSION, fingerprint: this.fingerprint, updatedAt: Date.now(), positions: Object.fromEntries([...this.nodes].filter(([, n]) => finitePosition(n)).map(([id, n]) => [id, { x: n.x, y: n.y, z: n.z }])), userPinnedIds: [...this.pinned] };
  }
}
