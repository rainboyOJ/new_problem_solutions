// Shared catalog semantics have no dependency on the 3D renderer or camera.
export { normalizeGraphResponse, matchesQuery, buildVisibleGraph, relationFingerprint } from '../../relations3-graph/src/graph-data';
export { buildRelationIndex, focusNeighborhood } from '../../relations3-graph/src/relation-index';
export type { RelationNode, RelationEdge, RelationGraphResponse, Filters, FocusNeighborhood, RelationEntry } from '../../relations3-graph/src/types';
import type { RelationEdge, FocusNeighborhood } from '../../relations3-graph/src/types';
import { readUrlState, writeUrlState } from '../../relations3-graph/src/url-state';

export interface Point { x: number; y: number }
export interface Camera extends Point { k: number }
export type ViewMode = 'overview' | 'layers';
export function readState(url: URL) {
  return { ...readUrlState(url), view: url.searchParams.get('view') === 'layers' ? 'layers' as const : 'overview' as const };
}
export function writeState(url: URL, state: ReturnType<typeof readState>) {
  const next = writeUrlState(url, state);
  if (state.view === 'layers') next.searchParams.set('view', 'layers'); else next.searchParams.delete('view');
  return next;
}
export type EdgeRole = 'before' | 'after' | 'similar';
export function edgeRole(edge: RelationEdge, center: string): EdgeRole | null {
  if (edge.source !== center && edge.target !== center) return null;
  return edge.type === 'common' ? 'similar' : edge.target === center ? 'before' : 'after';
}
export function effectiveFocus(hover: string, selected: string | null): string { return hover || selected || ''; }

// No topological sort: a node may appear in multiple groups when the data has
// cycles or both pre/common relations. Every real relation remains accessible.
export function layerGroups(focus: FocusNeighborhood) {
  return [
    { key: 'before', title: '前置题', hint: '从这里准备', entries: focus.predecessors },
    { key: 'current', title: '当前题', hint: '正在探索', entries: focus.centerId ? [{ nodeId: focus.centerId, edgeId: '', reason: '' }] : [] },
    { key: 'after', title: '后续题', hint: '接着去尝试', entries: focus.successors },
  ] as const;
}
export function safeStorage(): Storage | undefined {
  try { return window.localStorage; } catch { return undefined; }
}
export function readStored<T>(key: string): T | undefined {
  try { return JSON.parse(safeStorage()?.getItem(key) || 'null') ?? undefined; } catch { return undefined; }
}
export function writeStored(key: string, value: unknown) {
  try { safeStorage()?.setItem(key, JSON.stringify(value)); } catch { /* Private mode and quota must not prevent browsing. */ }
}
