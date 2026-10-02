import type { Filters, RelationNode } from './types';

interface Props {
  filters: Filters; query: string; results: RelationNode[]; shown: number; refreshing: boolean; layoutRunning: boolean;
  canBack: boolean; selectedId: string | null;
  onQuery(value: string): void; onFilters(value: Filters): void; onSelect(id: string): void;
  onMore(): void; onBack(): void; onOverview(): void; onRefresh(): void; onFit(): void; onReset(): void; onRelayout(): void;
}
export default function Toolbar(p: Props) {
  return <div className="relations3-tools">
    <div className="relations3-search">
      <label htmlFor="r3-search">查找题目</label>
      <div className="relations3-search-field">
        <span aria-hidden="true">⌕</span>
        <input id="r3-search" type="search" value={p.query} onChange={e => p.onQuery(e.target.value)} placeholder="题号、标题、标签或难度" autoComplete="off" />
        {p.query && <button type="button" onClick={() => p.onQuery('')} aria-label="清除搜索">×</button>}
      </div>
      {p.query.trim() && <div className="relations3-search-results" aria-label="搜索结果">
        <p role="status">{p.results.length ? `找到 ${p.results.length} 道题目` : '没有匹配的题目'}</p>
        <div className="relations3-result-list">{p.results.slice(0, p.shown).map(n => <button type="button" key={n.id} onClick={() => p.onSelect(n.id)}>
          <strong>{n.label}</strong><span>{n.title}</span>
        </button>)}</div>
        {p.shown < p.results.length && <button type="button" className="r3-button" onClick={p.onMore}>再显示 20 项</button>}
      </div>}
    </div>
    <div className="relations3-filter-row" aria-label="关系筛选">
      <label><input type="checkbox" checked={p.filters.showPre} onChange={e => p.onFilters({ ...p.filters, showPre: e.target.checked })} /><i className="r3-line pre" aria-hidden="true" />前置关系</label>
      <label><input type="checkbox" checked={p.filters.showCommon} onChange={e => p.onFilters({ ...p.filters, showCommon: e.target.checked })} /><i className="r3-line common" aria-hidden="true" />相似关系</label>
      <label><input type="checkbox" checked={p.filters.showIsolated} onChange={e => p.onFilters({ ...p.filters, showIsolated: e.target.checked })} />显示孤立题目</label>
    </div>
    <details className="relations3-controls" open>
      <summary>浏览与布局控制</summary>
      <div className="relations3-buttons">
        <button type="button" className="r3-button" disabled={!p.canBack} onClick={p.onBack}>← 上一题</button>
        <button type="button" className="r3-button" disabled={!p.selectedId} onClick={p.onOverview}>返回总览</button>
        <button type="button" className="r3-button" onClick={p.onFit}>适应视图</button>
        <button type="button" className="r3-button" onClick={p.onReset}>重置视角</button>
        <button type="button" className="r3-button" disabled={p.layoutRunning} onClick={p.onRelayout}>重新布局</button>
        <button type="button" className="r3-button" disabled={p.refreshing} onClick={p.onRefresh}>{p.refreshing ? '刷新中…' : '刷新数据'}</button>
      </div>
    </details>
  </div>;
}
