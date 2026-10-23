import { useCallback, useEffect, useMemo, useRef, useState } from 'react';
import Overview, { type OverviewHandle } from './Overview';
import Layers from './Layers';
import {
  normalizeGraphResponse, buildRelationIndex, focusNeighborhood, matchesQuery, buildVisibleGraph,
  effectiveFocus, readState, writeState, type Filters, type RelationGraphResponse, type RelationEntry, type ViewMode,
} from './model';

export default function App() {
  const initial = useMemo(() => readState(new URL(window.location.href)), []);
  const [data, setData] = useState<RelationGraphResponse | null>(null);
  const [loading, setLoading] = useState(true), [error, setError] = useState('');
  const [filters, setFilters] = useState<Filters>(initial);
  const [view, setView] = useState<ViewMode>(initial.view);
  const [history, setHistory] = useState<(string | null)[]>([initial.selectedId]);
  const selected = history.at(-1) || null;
  const [hover, setHover] = useState(''), [query, setQuery] = useState('');
  const [resultLimit, setResultLimit] = useState(20), [drawer, setDrawer] = useState(false);
  const [layoutVersion, setLayoutVersion] = useState(0), [notice, setNotice] = useState('');
  const [dark, setDark] = useState(document.documentElement.dataset.bsTheme === 'dark');
  const overview = useRef<OverviewHandle>(null);
  const request = useRef<AbortController | null>(null);
  const searchInput = useRef<HTMLInputElement>(null);
  const fetchData = useCallback(async () => {
    request.current?.abort();
    const controller = new AbortController(); request.current = controller;
    setLoading(true); setError('');
    try {
      const response = await fetch('/api/relations', { signal: controller.signal });
      if (!response.ok) throw new Error(`题目关系读取失败（${response.status}）`);
      const next = normalizeGraphResponse(await response.json());
      if (!controller.signal.aborted) { setData(next); setNotice(next.discarded ? `已忽略 ${next.discarded} 条不完整数据` : ''); }
    } catch (error) {
      if (!controller.signal.aborted) setError(error instanceof Error ? error.message : '题目关系读取失败，请重试');
    } finally { if (!controller.signal.aborted) setLoading(false); }
  }, []);
  useEffect(() => { fetchData(); return () => request.current?.abort(); }, [fetchData]);
  useEffect(() => {
    const observer = new MutationObserver(() => setDark(document.documentElement.dataset.bsTheme === 'dark'));
    observer.observe(document.documentElement, { attributes: true, attributeFilter: ['data-bs-theme'] });
    return () => observer.disconnect();
  }, []);
  useEffect(() => {
    const read = () => {
      const state = readState(new URL(window.location.href));
      setFilters(state); setView(state.view); setHistory([state.selectedId]); setHover('');
    };
    window.addEventListener('popstate', read); return () => window.removeEventListener('popstate', read);
  }, []);
  useEffect(() => {
    const url = writeState(new URL(window.location.href), { ...filters, selectedId: selected, view });
    window.history.replaceState(null, '', url);
  }, [filters, selected, view]);
  const nodes = useMemo(() => new Map(data?.nodes.map(n => [n.id, n]) || []), [data]);
  const edges = useMemo(() => new Map(data?.edges.map(e => [e.id, e]) || []), [data]);
  const index = useMemo(() => data ? buildRelationIndex(data) : new Map(), [data]);
  const results = useMemo(() => {
    if (!query.trim() || !data) return [];
    const q = query.trim().toLowerCase();
    return data.nodes.filter(n => matchesQuery(n, query)).sort((a, b) =>
      Number(b.problem_id.toLowerCase() === q) - Number(a.problem_id.toLowerCase() === q) || a.label.localeCompare(b.label));
  }, [data, query]);
  const matches = useMemo(() => new Set(results.map(n => n.id)), [results]);
  const visible = useMemo(() => data ? buildVisibleGraph(data, filters, selected, matches) : { nodeIds: new Set<string>(), edgeIds: new Set<string>(), edges: [] }, [data, filters, selected, matches]);
  const focus = useMemo(() => focusNeighborhood(index, selected, visible.edgeIds), [index, selected, visible.edgeIds]);
  const scene = useMemo(() => ({
    nodes: data?.nodes || [], edges: visible.edges, index, visible: visible.nodeIds, edgeIds: visible.edgeIds,
    matches, searching: !!query.trim(), selected, hover, dark,
  }), [data, visible, index, matches, query, selected, hover, dark]);
  useEffect(() => {
    if (data && selected && !nodes.has(selected)) {
      setHistory([null]); setNotice('当前题目不在有效目录中，请重新选择。');
    }
  }, [data, selected, nodes]);
  const select = useCallback((id: string | null) => {
    setHistory(previous => previous.at(-1) === id ? previous : [...previous, id]);
    setHover('');
  }, []);
  const searchSelect = (id: string) => {
    select(id); setQuery(''); setDrawer(false); overview.current?.locate(id);
  };
  const switchView = (next: ViewMode) => { setHover(''); setView(next); };
  const node = selected ? nodes.get(selected) : undefined;
  const preview = nodes.get(effectiveFocus(hover, selected));
  const group = (title: string, key: string, entries: RelationEntry[], enabled: boolean) => <section className={`r4-detail-group r4-role-${key}`} data-relation-group={key}>
    <h3>{title}<b>{entries.length}</b></h3>
    {!enabled ? <p className="r4-muted">当前筛选已隐藏此类关系</p> : !entries.length ? <p className="r4-muted">暂无直接{title}</p> : <ul>{entries.map(entry => {
      const related = nodes.get(entry.nodeId); if (!related) return null;
      return <li key={entry.edgeId}>
        <div className="r4-detail-entry"><button data-node-id={related.id} onClick={() => select(related.id)} onPointerEnter={() => setHover(related.id)} onPointerLeave={() => setHover('')} onFocus={() => setHover(related.id)} onBlur={() => setHover('')}>
          <strong>{related.label}</strong><span>{related.title}</span>
        </button><a href={related.url} aria-label={`打开 ${related.label} 的题解`} title="打开题解">↗</a></div>
        {entry.reason && <details><summary>关系说明</summary><p>{entry.reason}</p></details>}
      </li>;
    })}</ul>}
  </section>;
  return <div className="r4-app">
    <header className="r4-topbar">
      <div className="r4-brand"><span aria-hidden="true">✣</span><div><h1>题目关系</h1><p>连接所学，发现下一步</p></div></div>
      <div className="r4-top-actions"><a href="/relations/3" title="打开原有 3D 关系图">3D 视图 ↗</a><button onClick={fetchData} disabled={loading} aria-label="刷新关系数据">{loading ? '读取中…' : '刷新'}</button></div>
    </header>
    <div className="r4-toolbar">
      <div className="r4-mode-switch" role="group" aria-label="关系图模式">
        <button aria-pressed={view === 'overview'} onClick={() => switchView('overview')}><span aria-hidden="true">◌</span> 全景</button>
        <button aria-pressed={view === 'layers'} onClick={() => switchView('layers')}><span aria-hidden="true">▥</span> 分层</button>
      </div>
      <div className="r4-filters">
        <label>关系<select aria-label="关系类型" value={filters.relationMode} onChange={e => { setHover(''); setFilters(f => ({ ...f, relationMode: e.target.value as Filters['relationMode'] })); }}>
          <option value="both">全部</option><option value="pre">前置</option><option value="common">相似</option>
        </select></label>
        <label className="r4-isolated"><input type="checkbox" checked={filters.showIsolated} onChange={e => setFilters(f => ({ ...f, showIsolated: e.target.checked }))} />孤立题</label>
        <button className="r4-relayout" onClick={() => setLayoutVersion(v => v + 1)} disabled={!data || loading} title="重新计算全景布局">重新布局</button>
      </div>
    </div>
    {error && <div className="r4-notice" role="alert">{error} <button onClick={fetchData}>重试</button>{data && ' · 当前保留上次读取的数据'}</div>}
    {notice && <p className="r4-notice" role="status">{notice}</p>}
    <div className="r4-workspace">
      <aside className={`r4-details${drawer ? ' is-open' : ''}`} aria-label="题目搜索与关系清单">
        <button className="r4-drawer-toggle" onClick={() => setDrawer(v => !v)} aria-expanded={drawer}><span>{node?.label || '搜索与关系清单'}</span><span>{drawer ? '收起 ↓' : '展开 ↑'}</span></button>
        <div className="r4-sidebar-scroll">
          <form role="search" className="r4-search" onSubmit={e => { e.preventDefault(); if (results[0]) searchSelect(results[0].id); }}>
            <label htmlFor="r4-query">找一道题</label><div><span aria-hidden="true">⌕</span><input id="r4-query" ref={searchInput} type="search" placeholder="题号、题名或算法标签" value={query} onChange={e => { setQuery(e.target.value); setResultLimit(20); }} onKeyDown={e => { if (e.key === 'Escape') setQuery(''); }} />{query && <button type="button" aria-label="清除搜索" onClick={() => { setQuery(''); searchInput.current?.focus(); }}>×</button>}</div>
          </form>
          {query.trim() ? <div className="r4-search-results"><p className="r4-muted">找到 {results.length} 道题目</p>{results.slice(0, resultLimit).map(result => <button key={result.id} data-node-id={result.id} onClick={() => searchSelect(result.id)}><strong>{result.label}</strong><span>{result.title}</span>{result.isolated && <small>暂无关系</small>}</button>)}{results.length > resultLimit && <button onClick={() => setResultLimit(v => v + 40)}>显示更多</button>}</div> : <>
            <p className="r4-stats"><strong>{visible.nodeIds.size}</strong> / {data?.nodes.length || 0} 道题目 <span>· {visible.edges.length} 条关系</span></p>
            <div className="r4-history"><button disabled={history.length < 2} onClick={() => { setHistory(h => h.slice(0, -1)); setHover(''); }}>← 上一题</button>{selected && <button onClick={() => select(null)}>取消选择</button>}</div>
            {node ? <>
              <div className="r4-detail-heading" aria-live="polite"><p className="r4-kicker">当前题目</p><div className="r4-detail-code">{node.label}</div><h2>{node.title || node.label}</h2><div className="r4-tags">{node.tags.map(tag => <span key={tag}>{tag}</span>)}<span>{node.difficulty}</span></div><a className="r4-open-solution" href={node.url}>打开题解 ↗</a>{node.isolated && <p className="r4-muted">这道题尚未维护题目关系，可通过题解了解内容。</p>}</div>
              {group('前置题', 'before', focus.predecessors, filters.relationMode !== 'common')}
              {group('后续题', 'after', focus.successors, filters.relationMode !== 'common')}
              {group('相似题', 'similar', focus.commons, filters.relationMode !== 'pre')}
            </> : <div className="r4-intro"><div className="r4-empty-orbit" aria-hidden="true">◎</div><p className="r4-kicker">从一个连接开始</p><h2>看清来路，<br />找到下一步。</h2><p>在全景中移动鼠标，立即看见一道题的直接关系。</p><p>点击锁定题目，再切换分层，按学习顺序继续探索。</p><div className="r4-mini-flow"><span>前置题</span><i>→</i><strong>当前题</strong><i>→</i><span>后续题</span></div></div>}
          </>}
        </div>
      </aside>
      <section className="r4-stage" aria-label="关系图画布">
        {data ? <>
          <div className="r4-view" hidden={view !== 'overview'}><Overview ref={overview} data={data} scene={scene} layoutVersion={layoutVersion} onHover={setHover} onSelect={select} /></div>
          <div className="r4-view" hidden={view !== 'layers'}><Layers active={view === 'layers'} focus={focus} nodes={nodes} edges={edges} relationMode={filters.relationMode} hover={hover} onHover={setHover} onSelect={select} onOverview={() => switchView('overview')} /></div>
          {view === 'overview' && preview && <div className="r4-preview"><strong>{preview.label}</strong><span>{preview.title}</span><small>{hover && hover !== selected ? '悬停预览 · 点击锁定' : '已锁定 · 移动鼠标继续探索'}</small></div>}
          {view === 'overview' && !visible.nodeIds.size && <div className="r4-stage-message">当前筛选下没有关系节点。试试搜索题目或显示孤立题。</div>}
        </> : <div className="r4-stage-message" role="status">{loading ? '正在读取题目关系…' : '暂时无法读取关系数据，请点击重试。'}</div>}
      </section>
    </div>
    <footer className="r4-bottom"><div className="r4-legend" aria-label="关系图例"><span className="r4-legend-before">前置题 → 当前题</span><span className="r4-legend-after">当前题 → 后续题</span><span className="r4-legend-similar">相似题</span></div><span>真实关系 · 自由探索</span></footer>
  </div>;
}
