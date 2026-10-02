import { Component, lazy, Suspense, useCallback, useEffect, useMemo, useReducer, useRef, useState, type ReactNode } from 'react';
import { normalizeGraphResponse, matchesQuery, buildVisibleGraph } from './graph-data';
import { buildRelationIndex, focusNeighborhood } from './relation-index';
import { explorationReducer, initialExploration } from './exploration';
import { readUrlState, writeUrlState } from './url-state';
import type { Filters, Graph3DHandle, RelationGraphResponse } from './types';
import Toolbar from './Toolbar';
import DetailsPanel from './DetailsPanel';
import Legend from './Legend';

const Graph3D = lazy(() => import('./Graph3D'));
class GraphBoundary extends Component<{ children: ReactNode; onError(message: string): void }, { failed: boolean }> {
  state = { failed: false };
  static getDerivedStateFromError() { return { failed: true }; }
  componentDidCatch(error: Error) { this.props.onError(error.message || '浏览器无法启动 3D 画布'); }
  render() { return this.state.failed ? null : this.props.children; }
}

export default function App() {
  const initial = useMemo(() => readUrlState(new URL(window.location.href)), []);
  const [data, setData] = useState<RelationGraphResponse | null>(null);
  const [loading, setLoading] = useState(true);
  const [refreshing, setRefreshing] = useState(false);
  const [loadError, setLoadError] = useState('');
  const [notice, setNotice] = useState('');
  const [renderError, setRenderError] = useState('');
  const [renderReady, setRenderReady] = useState(false);
  const [renderKey, setRenderKey] = useState(0);
  const [layoutRunning, setLayoutRunning] = useState(false);
  const [filters, setFilters] = useState<Filters>(initial);
  const [query, setQuery] = useState('');
  const [shown, setShown] = useState(20);
  const [exploration, dispatch] = useReducer(explorationReducer, initial.selectedId, initialExploration);
  const entry = exploration.entries[exploration.cursor];
  const selectedId = entry.id;
  const [hovered, setHovered] = useState('');
  const [hoveredEdge, setHoveredEdge] = useState('');
  const [dark, setDark] = useState(document.documentElement.dataset.bsTheme === 'dark');
  const [drawerOpen, setDrawerOpen] = useState(false);
  const [size, setSize] = useState({ width: 0, height: 0 });
  const stage = useRef<HTMLDivElement>(null);
  const graph = useRef<Graph3DHandle>(null);
  const controller = useRef<AbortController | null>(null);
  const requestId = useRef(0);
  const stateRef = useRef({ selectedId, data });
  stateRef.current = { selectedId, data };

  const fetchGraph = useCallback(async (refresh = false) => {
    controller.current?.abort();
    const abort = new AbortController(); controller.current = abort;
    const id = ++requestId.current;
    if (refresh) setRefreshing(true); else setLoading(true);
    setLoadError('');
    try {
      const response = await fetch('/api/relations', { headers: { Accept: 'application/json' }, signal: abort.signal });
      if (!response.ok) throw new Error(`HTTP ${response.status}`);
      const next = normalizeGraphResponse(await response.json());
      if (id !== requestId.current) return;
      const valid = new Set(next.nodes.map(n => n.id));
      if (stateRef.current.selectedId && !valid.has(stateRef.current.selectedId)) setNotice('指定的题目不存在或已移除，已返回总览。');
      dispatch({ type: 'reconcile', validIds: valid });
      setData(next);
    } catch (e) {
      if (abort.signal.aborted || id !== requestId.current) return;
      setLoadError(`关系数据加载失败：${e instanceof Error ? e.message : '未知错误'}`);
    } finally { if (id === requestId.current && !abort.signal.aborted) { setLoading(false); setRefreshing(false); } }
  }, []);
  useEffect(() => { fetchGraph(); return () => { controller.current?.abort(); }; }, [fetchGraph]);
  useEffect(() => {
    const element = stage.current;
    if (!element) return;
    const observer = new ResizeObserver(entries => {
      const { width, height } = entries[0].contentRect;
      setSize({ width: Math.round(width), height: Math.round(height) });
    });
    observer.observe(element);
    return () => observer.disconnect();
  }, []);
  useEffect(() => {
    const observer = new MutationObserver(() => setDark(document.documentElement.dataset.bsTheme === 'dark'));
    observer.observe(document.documentElement, { attributes: true, attributeFilter: ['data-bs-theme'] });
    const nav = document.querySelector('body > nav');
    const navObserver = new ResizeObserver(entries => { document.documentElement.style.setProperty('--r3-nav-height', `${entries[0].contentRect.height}px`); });
    if (nav) navObserver.observe(nav);
    return () => { observer.disconnect(); navObserver.disconnect(); document.documentElement.style.removeProperty('--r3-nav-height'); };
  }, []);
  useEffect(() => { setShown(20); }, [query]);
  useEffect(() => {
    if (!data) return;
    window.history.replaceState({}, '', writeUrlState(new URL(window.location.href), { ...filters, selectedId }));
  }, [filters, selectedId, data]);
  useEffect(() => {
    const read = () => {
      const next = readUrlState(new URL(window.location.href));
      setFilters(next);
      const id = !next.selectedId || stateRef.current.data?.nodes.some(n => n.id === next.selectedId) ? next.selectedId : null;
      dispatch({ type: 'url', id });
    };
    window.addEventListener('popstate', read);
    return () => window.removeEventListener('popstate', read);
  }, []);

  const nodes = useMemo(() => new Map(data?.nodes.map(n => [n.id, n]) || []), [data]);
  const index = useMemo(() => data ? buildRelationIndex(data) : new Map(), [data]);
  const results = useMemo(() => query.trim() ? data?.nodes.filter(n => matchesQuery(n, query)) || [] : [], [data, query]);
  const matched = useMemo(() => new Set(results.map(n => n.id)), [results]);
  const visible = useMemo(() => data ? buildVisibleGraph(data, filters, selectedId, matched) : { nodeIds: new Set<string>(), edgeIds: new Set<string>(), edges: [] }, [data, filters, selectedId, matched]);
  const focus = useMemo(() => focusNeighborhood(index, selectedId, visible.edgeIds), [index, selectedId, visible.edgeIds]);
  const visual = useMemo(() => data ? { data, visibleNodes: visible.nodeIds, visibleEdges: visible.edgeIds, focus, matched, query, hovered, hoveredEdge, dark } : null, [data, visible, focus, matched, query, hovered, hoveredEdge, dark]);

  const select = useCallback((id: string) => {
    if (!nodes.has(id)) return;
    setNotice(''); setHovered(''); setHoveredEdge('');
    dispatch({ type: 'select', id, camera: graph.current?.getCameraView() });
    setDrawerOpen(true);
  }, [nodes]);
  const back = useCallback(() => { setHovered(''); dispatch({ type: 'back', camera: graph.current?.getCameraView() }); }, []);
  const overview = useCallback(() => { setHovered(''); setDrawerOpen(false); dispatch({ type: 'select', id: null, camera: graph.current?.getCameraView() }); }, []);
  const renderFailure = useCallback((message: string) => { setRenderError(`3D 图形暂不可用：${message}`); setRenderReady(false); setLayoutRunning(false); }, []);
  const ready = useCallback(() => { setRenderReady(true); }, []);
  const retry = () => { setRenderError(''); setRenderReady(false); setRenderKey(k => k + 1); };
  useEffect(() => {
    const key = (event: KeyboardEvent) => {
      if (event.target instanceof HTMLElement && (event.target.matches('input, textarea, select') || event.target.isContentEditable)) return;
      if (event.key === '+' || event.key === '=') { event.preventDefault(); graph.current?.zoom(0.8); }
      if (event.key === '-') { event.preventDefault(); graph.current?.zoom(1.25); }
      if (event.key === '0') { event.preventDefault(); graph.current?.fitVisible(); }
      if (event.key === 'Escape') overview();
    };
    window.addEventListener('keydown', key);
    return () => window.removeEventListener('keydown', key);
  }, [overview]);
  const hoveredNode = nodes.get(hovered);
  const edgeTooltip = data?.edges.find(e => e.id === hoveredEdge);

  return <main className="relations3-app" aria-label="3D 题目关系图">
    <Toolbar filters={filters} query={query} results={results} shown={shown} refreshing={refreshing} layoutRunning={layoutRunning}
      canBack={exploration.cursor > 0} selectedId={selectedId} onQuery={setQuery} onFilters={setFilters} onSelect={select}
      onMore={() => setShown(n => n + 20)} onBack={back} onOverview={overview} onRefresh={() => fetchGraph(true)}
      onFit={() => graph.current?.fitVisible()} onReset={() => graph.current?.resetView()} onRelayout={() => graph.current?.relayout()} />
    <div className="relations3-workspace">
      <DetailsPanel node={selectedId ? nodes.get(selectedId) : undefined} nodes={nodes} focus={focus} filters={filters} open={drawerOpen} onOpen={setDrawerOpen} onSelect={select} onHover={setHovered}
        stats={data ? { visible: visible.nodeIds.size, total: data.summary.nodes, edges: visible.edgeIds.size } : undefined} />
      <section className="relations3-stage" ref={stage} aria-label="可旋转的题目关系网络" aria-busy={loading || layoutRunning} data-render-ready={renderReady} data-layout-running={layoutRunning}>
        {visual && size.width > 0 && size.height > 0 && !renderError && <GraphBoundary key={renderKey} onError={renderFailure}>
          <Suspense fallback={<div className="relations3-status" role="status">正在准备 3D 画布…</div>}>
            <Graph3D ref={graph} visual={visual} width={size.width} height={size.height} focusRevision={exploration.revision}
              restoreCamera={entry.camera} onSelect={select} onHover={setHovered} onEdgeHover={setHoveredEdge}
              onReady={ready} onError={renderFailure} onLayout={setLayoutRunning} />
          </Suspense>
        </GraphBoundary>}
        {(loading || layoutRunning) && <div className="relations3-status" role="status"><span className="relations3-spinner" />{loading ? '正在加载关系数据…' : '正在整理三维布局…'}</div>}
        {(notice || loadError) && <div className="relations3-message" role={loadError ? 'alert' : 'status'}><p>{loadError || notice}</p>{loadError ? <button type="button" className="r3-button" onClick={() => fetchGraph(true)}>重试加载</button> : <button type="button" className="r3-button" onClick={() => setNotice('')}>知道了</button>}</div>}
        {renderError && <div className="relations3-fallback" role="alert"><h2>继续通过清单探索</h2><p>{renderError}</p><div><button type="button" className="r3-button" onClick={retry}>重试 3D 图形</button></div>
          <p>搜索题号，或从下方选择题目；关系清单仍可使用。</p><div className="relations3-fallback-list">{(query.trim() ? results : data?.nodes.filter(n => !n.isolated) || []).slice(0, shown).map(n => <button type="button" key={n.id} onClick={() => select(n.id)}>{n.label} · {n.title}</button>)}</div>
        </div>}
        {data && !visible.nodeIds.size && !loading && <div className="relations3-message" role="status"><p>{data.nodes.length ? '当前筛选下没有可见题目。可开启关系类型，搜索题号，或显示孤立题目。' : '当前目录没有可浏览的有效题目。'}</p></div>}
        {hoveredNode && !renderError && <div className="relations3-tooltip" role="tooltip"><strong>{hoveredNode.label}</strong><span>{hoveredNode.title}</span><small>点击切换中心</small></div>}
        {edgeTooltip && !hoveredNode && <div className="relations3-tooltip" role="tooltip"><strong>{edgeTooltip.type === 'pre' ? '前置关系 →' : '相似关系'}</strong>{edgeTooltip.reason && <span>{edgeTooltip.reason}</span>}</div>}
        <div className="relations3-zoom"><button type="button" aria-label="放大" onClick={() => graph.current?.zoom(0.8)}>+</button><button type="button" aria-label="缩小" onClick={() => graph.current?.zoom(1.25)}>−</button></div>
        <div className="relations3-hint">拖动空白处旋转 · 滚轮缩放 · 点击题目聚焦</div>
      </section>
    </div>
    {data && <Legend data={data} focused={!!selectedId} />}
  </main>;
}
