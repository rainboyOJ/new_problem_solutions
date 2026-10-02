import type { Filters } from './types';
export interface UrlState extends Filters { selectedId: string | null }
export function readUrlState(url: URL): UrlState {
  const p = url.searchParams;
  const edges = p.get('edges');
  const types = new Set(edges === null ? ['pre', 'common'] : edges.split(','));
  return { selectedId: p.get('oj') && p.get('pid') ? `${p.get('oj')}/${p.get('pid')}` : null, showPre: types.has('pre'), showCommon: types.has('common'), showIsolated: p.get('isolated') === '1' };
}
export function writeUrlState(url: URL, state: UrlState): URL {
  const result = new URL(url);
  const p = result.searchParams;
  const slash = state.selectedId?.indexOf('/') ?? -1;
  if (state.selectedId && slash > 0) {
    p.set('oj', state.selectedId.slice(0, slash)); p.set('pid', state.selectedId.slice(slash + 1));
  } else { p.delete('oj'); p.delete('pid'); }
  p.set('edges', [state.showPre ? 'pre' : '', state.showCommon ? 'common' : ''].filter(Boolean).join(',') || 'none');
  if (state.showIsolated) p.set('isolated', '1'); else p.delete('isolated');
  return result;
}
