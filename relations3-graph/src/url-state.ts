import type { RelationMode } from './types';
import type { Filters } from './types';
export interface UrlState extends Filters { selectedId: string | null }
// edges 严格三档：pre / common / pre,common；缺省或非法旧值（如 none）一律回退 both
export function readRelationMode(edges: string | null): RelationMode {
  if (edges === 'pre' || edges === 'common') return edges;
  if (edges === 'pre,common') return 'both';
  return 'both';
}
export function writeRelationMode(mode: RelationMode): string {
  return mode === 'both' ? 'pre,common' : mode;
}
export function readUrlState(url: URL): UrlState {
  const p = url.searchParams;
  return { selectedId: p.get('oj') && p.get('pid') ? `${p.get('oj')}/${p.get('pid')}` : null, relationMode: readRelationMode(p.get('edges')), showIsolated: p.get('isolated') === '1' };
}
export function writeUrlState(url: URL, state: UrlState): URL {
  const result = new URL(url);
  const p = result.searchParams;
  const slash = state.selectedId?.indexOf('/') ?? -1;
  if (state.selectedId && slash > 0) {
    p.set('oj', state.selectedId.slice(0, slash)); p.set('pid', state.selectedId.slice(slash + 1));
  } else { p.delete('oj'); p.delete('pid'); }
  p.set('edges', writeRelationMode(state.relationMode));
  if (state.showIsolated) p.set('isolated', '1'); else p.delete('isolated');
  return result;
}
