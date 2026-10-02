import type { Filters, RelationEdge, RelationGraphResponse, RelationNode } from './types';

function record(value: unknown): Record<string, unknown> | null {
  return value && typeof value === 'object' && !Array.isArray(value) ? value as Record<string, unknown> : null;
}
function items(value: unknown): unknown[] { return Array.isArray(value) ? value : []; }

export function normalizeGraphResponse(value: unknown): RelationGraphResponse {
  const input = record(value) || {};
  const nodes: RelationNode[] = [];
  const edges: RelationEdge[] = [];
  const ids = new Set<string>();
  const edgeIds = new Set<string>();
  let discarded = 0;
  for (const value of items(input.nodes)) {
    const n = record(value);
    if (!n || !n.id || !n.oj || !n.problem_id || ids.has(String(n.id))) { discarded++; continue; }
    const id = String(n.id);
    ids.add(id);
    nodes.push({
      id, oj: String(n.oj), problem_id: String(n.problem_id),
      label: String(n.label || `${n.oj} ${n.problem_id}`), title: String(n.title || ''),
      tags: items(n.tags).map(String).filter(Boolean), primaryTag: String(n.primaryTag || ''),
      difficulty: String(n.difficulty || '未知'), color: String(n.color || '#64748b'),
      url: String(n.url || ''), isolated: true, predecessorCount: 0, successorCount: 0, commonCount: 0,
    });
  }
  const byId = new Map(nodes.map(n => [n.id, n]));
  for (const value of items(input.edges)) {
    const e = record(value);
    if (!e || !e.id || (e.type !== 'pre' && e.type !== 'common') || !ids.has(String(e.source)) || !ids.has(String(e.target)) || edgeIds.has(String(e.id))) {
      discarded++; continue;
    }
    const edge: RelationEdge = { id: String(e.id), source: String(e.source), target: String(e.target), type: e.type, directed: e.type === 'pre', reason: String(e.reason || '') };
    edgeIds.add(edge.id);
    edges.push(edge);
    const source = byId.get(edge.source)!;
    const target = byId.get(edge.target)!;
    source.isolated = target.isolated = false;
    if (edge.type === 'pre') { source.successorCount++; target.predecessorCount++; }
    else { source.commonCount++; if (source !== target) target.commonCount++; }
  }
  const tagStats = items(input.tagStats).flatMap(value => {
    const t = record(value);
    return t && t.tag ? [{ tag: String(t.tag), count: Number(t.count) || 0, color: String(t.color || '#64748b') }] : [];
  });
  return { nodes, edges, tagStats, discarded, summary: {
    nodes: nodes.length, edges: edges.length, relationNodes: nodes.filter(n => !n.isolated).length,
    isolatedNodes: nodes.filter(n => n.isolated).length,
    preEdges: edges.filter(e => e.type === 'pre').length, commonEdges: edges.filter(e => e.type === 'common').length,
  } };
}

export function matchesQuery(node: RelationNode, query: string): boolean {
  return [node.oj, node.problem_id, node.label, node.title, node.difficulty, node.primaryTag, ...node.tags].join(' ').toLowerCase().includes(query.trim().toLowerCase());
}

export function buildVisibleGraph(data: RelationGraphResponse, filters: Filters, selectedId: string | null, matches: Set<string>) {
  const edges = data.edges.filter(e => e.type === 'pre' ? filters.showPre : filters.showCommon);
  const valid = new Set(data.nodes.map(n => n.id));
  const nodeIds = new Set<string>();
  edges.forEach(e => { nodeIds.add(e.source); nodeIds.add(e.target); });
  if (filters.showIsolated) data.nodes.forEach(n => nodeIds.add(n.id));
  if (selectedId && valid.has(selectedId)) nodeIds.add(selectedId);
  for (const id of matches) if (valid.has(id)) nodeIds.add(id);
  return { nodeIds, edgeIds: new Set(edges.map(e => e.id)), edges };
}

export function hashString(source: string): number {
  let hash = 2166136261;
  for (let i = 0; i < source.length; i++) { hash ^= source.charCodeAt(i); hash = Math.imul(hash, 16777619); }
  return hash >>> 0;
}
export function relationFingerprint(data: RelationGraphResponse): string {
  return hashString(JSON.stringify([
    data.nodes.map(n => n.id).sort(),
    data.edges.map(e => [e.id, e.source, e.target, e.type].join(':')).sort(),
  ])).toString(16);
}
