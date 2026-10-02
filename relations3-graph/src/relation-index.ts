import type { FocusNeighborhood, RelationEdge, RelationGraphResponse } from './types';

export function buildRelationIndex(data: RelationGraphResponse): Map<string, RelationEdge[]> {
  const result = new Map(data.nodes.map(n => [n.id, [] as RelationEdge[]]));
  for (const e of data.edges) {
    result.get(e.source)?.push(e);
    if (e.source !== e.target) result.get(e.target)?.push(e);
  }
  return result;
}
export function focusNeighborhood(index: Map<string, RelationEdge[]>, centerId: string | null, edgeIds: Set<string>): FocusNeighborhood {
  const result: FocusNeighborhood = { centerId: centerId || '', nodeIds: new Set(centerId ? [centerId] : []), edgeIds: new Set(), predecessors: [], successors: [], commons: [] };
  for (const e of centerId ? index.get(centerId) || [] : []) {
    if (!edgeIds.has(e.id)) continue;
    const entry = { nodeId: e.source === centerId ? e.target : e.source, edgeId: e.id, reason: e.reason };
    result.nodeIds.add(entry.nodeId);
    result.edgeIds.add(e.id);
    if (e.type === 'common') result.commons.push(entry);
    else if (e.target === centerId) result.predecessors.push(entry);
    else result.successors.push(entry);
  }
  return result;
}
