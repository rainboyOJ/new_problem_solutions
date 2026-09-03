import { useCallback, useEffect, useMemo, useRef, useState } from 'react';
import PixiCanvas, { type PixiCanvasHandle } from './PixiCanvas';
import { LayoutRunner } from './layout-runner';
import {
  buildVisibleGraph,
  matchesQuery,
  normalizeGraphResponse,
  positionForNode,
  relationFingerprint,
} from './graph-data';
import type { Position, PositionMap, RelationEdge, RelationGraphResponse, RelationNode } from './types';

const POSITION_PREFIX = 'rbook.relations2.positions';

interface SavedLayout {
  positions: PositionMap;
  fixedIds: string[];
}

interface InitialState {
  selectedId: string;
  showPre: boolean;
  showCommon: boolean;
  showIsolated: boolean;
}

export default function App() {
  const initialState = useMemo(readInitialState, []);
  const [data, setData] = useState<RelationGraphResponse | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');
  const [canvasError, setCanvasError] = useState('');
  const [canvasReady, setCanvasReady] = useState(false);
  const [query, setQuery] = useState('');
  const [selectedId, setSelectedId] = useState(initialState.selectedId);
  const [hoveredId, setHoveredId] = useState('');
  const [hoveredEdge, setHoveredEdge] = useState<{ edge: RelationEdge; x: number; y: number } | null>(null);
  const [showPre, setShowPre] = useState(initialState.showPre);
  const [showCommon, setShowCommon] = useState(initialState.showCommon);
  const [showIsolated, setShowIsolated] = useState(initialState.showIsolated);
  const [positions, setPositions] = useState<PositionMap>({});
  const [fixedIds, setFixedIds] = useState<Set<string>>(new Set());
  const [isLayouting, setIsLayouting] = useState(false);
  const [refreshing, setRefreshing] = useState(false);
  const [dark, setDark] = useState(() => document.documentElement.dataset.bsTheme === 'dark');
  const positionsRef = useRef<PositionMap>({});
  const fixedIdsRef = useRef<Set<string>>(new Set());
  const layoutSignatureRef = useRef('');
  const layoutRunnerRef = useRef(new LayoutRunner());
  const saveTimerRef = useRef<number | null>(null);
  const graphRef = useRef<PixiCanvasHandle | null>(null);

  const selectedNode = useMemo(
    () => data?.nodes.find((node) => node.id === selectedId) || null,
    [data, selectedId],
  );
  const visibleGraph = useMemo(() => data ? buildVisibleGraph(data, {
    query,
    selectedId,
    showPre,
    showCommon,
    showIsolated,
  }) : { nodes: [], edges: [] }, [data, query, selectedId, showCommon, showIsolated, showPre]);
  const layoutGraph = useMemo(() => data ? buildVisibleGraph(data, {
    query: '',
    selectedId: '',
    showPre,
    showCommon,
    showIsolated,
  }) : { nodes: [], edges: [] }, [data, showCommon, showIsolated, showPre]);
  const matchedIds = useMemo(() => new Set(
    query.trim() ? (data?.nodes || []).filter((node) => matchesQuery(node, query.trim().toLowerCase())).map((node) => node.id) : [],
  ), [data, query]);
  const renderPositions = useMemo(() => {
    const next = { ...positions };
    visibleGraph.nodes.forEach((node, index) => {
      if (!next[node.id]) next[node.id] = positionForNode(node.id, index, positions);
    });
    return next;
  }, [positions, visibleGraph.nodes]);
  const summaryText = data
    ? `${visibleGraph.nodes.length}/${data.summary.nodes} 个节点 · ${visibleGraph.edges.length} 条可见关系 · ${data.summary.preEdges} pre · ${data.summary.commonEdges} common`
    : '正在读取关系数据...';

  const persist = useCallback((nextPositions: PositionMap, nextFixedIds = fixedIdsRef.current) => {
    if (!data) return;
    const key = `${POSITION_PREFIX}.${relationFingerprint(data)}`;
    const payload: SavedLayout = { positions: nextPositions, fixedIds: Array.from(nextFixedIds) };
    try {
      window.localStorage.setItem(key, JSON.stringify(payload));
    } catch {
      // Local storage is optional; the current tab still keeps its layout.
    }
  }, [data]);

  const schedulePersist = useCallback((nextPositions: PositionMap, nextFixedIds = fixedIdsRef.current) => {
    if (saveTimerRef.current !== null) window.clearTimeout(saveTimerRef.current);
    saveTimerRef.current = window.setTimeout(() => persist(nextPositions, nextFixedIds), 250);
  }, [persist]);

  const runLayout = useCallback((force = false) => {
    if (!data) return;
    const signature = JSON.stringify({
      nodes: layoutGraph.nodes.map((node) => node.id).sort(),
      edges: layoutGraph.edges.map((edge) => edge.id).sort(),
    });
    if (!force && signature === layoutSignatureRef.current) return;
    layoutSignatureRef.current = signature;
    layoutRunnerRef.current.cancel();
    if (layoutGraph.nodes.length === 0) {
      setIsLayouting(false);
      return;
    }
    setIsLayouting(true);
    const input = {
      nodes: layoutGraph.nodes.map((node) => ({ id: node.id })),
      edges: layoutGraph.edges.map((edge) => ({ source: edge.source, target: edge.target })),
      initialPositions: positionsRef.current,
      fixedIds: Array.from(fixedIdsRef.current).filter((id) => layoutGraph.nodes.some((node) => node.id === id)),
      seed: Number.parseInt(relationFingerprint(data), 16) || 1,
      edgeLength: 160,
      chargeStrength: layoutGraph.nodes.length > 600 ? 400 : 620,
      collisionRadius: 24,
      ticks: layoutGraph.nodes.length > 900 ? 190 : 240,
    };
    layoutRunnerRef.current.run(
      input,
      (next) => {
        positionsRef.current = { ...positionsRef.current, ...next };
        setPositions(positionsRef.current);
      },
      (next) => {
        positionsRef.current = { ...positionsRef.current, ...next };
        setPositions(positionsRef.current);
        setIsLayouting(false);
        persist(positionsRef.current);
      },
      (message) => {
        setIsLayouting(false);
        setError(`布局计算失败：${message}`);
      },
    );
  }, [data, layoutGraph, persist]);

  const fetchGraph = useCallback(async (isRefresh = false) => {
    if (isRefresh) setRefreshing(true);
    else setLoading(true);
    setError('');
    try {
      const response = await fetch('/api/relations', { headers: { Accept: 'application/json' } });
      if (!response.ok) throw new Error(`HTTP ${response.status}`);
      const next = normalizeGraphResponse(await response.json());
      setData(next);
    } catch (fetchError) {
      setError(`关系图加载失败：${fetchError instanceof Error ? fetchError.message : '未知错误'}`);
    } finally {
      setLoading(false);
      setRefreshing(false);
    }
  }, []);

  useEffect(() => {
    fetchGraph();
    return () => layoutRunnerRef.current.cancel();
  }, [fetchGraph]);

  useEffect(() => {
    if (!data) return;
    const fingerprint = relationFingerprint(data);
    const key = `${POSITION_PREFIX}.${fingerprint}`;
    let saved: SavedLayout = { positions: {}, fixedIds: [] };
    try {
      const raw = window.localStorage.getItem(key);
      if (raw) saved = JSON.parse(raw) as SavedLayout;
    } catch {
      saved = { positions: {}, fixedIds: [] };
    }
    const nextPositions = saved.positions && typeof saved.positions === 'object' ? saved.positions : {};
    const nextFixedIds = new Set(Array.isArray(saved.fixedIds) ? saved.fixedIds : []);
    positionsRef.current = nextPositions;
    fixedIdsRef.current = nextFixedIds;
    setPositions(nextPositions);
    setFixedIds(nextFixedIds);
    layoutSignatureRef.current = '';
  }, [data]);

  const layoutSignature = useMemo(() => JSON.stringify({
    nodes: layoutGraph.nodes.map((node) => node.id).sort(),
    edges: layoutGraph.edges.map((edge) => edge.id).sort(),
  }), [layoutGraph]);

  useEffect(() => {
    if (data && layoutSignature) runLayout();
  }, [data, layoutSignature, runLayout]);

  useEffect(() => {
    const observer = new MutationObserver(() => setDark(document.documentElement.dataset.bsTheme === 'dark'));
    observer.observe(document.documentElement, { attributes: true, attributeFilter: ['data-bs-theme'] });
    return () => observer.disconnect();
  }, []);

  useEffect(() => {
    const next = new URL(window.location.href);
    next.searchParams.set('edges', [showPre ? 'pre' : '', showCommon ? 'common' : ''].filter(Boolean).join(',') || 'none');
    if (showIsolated) next.searchParams.set('isolated', '1');
    else next.searchParams.delete('isolated');
    if (selectedId.includes('/')) {
      const [oj, pid] = selectedId.split('/');
      next.searchParams.set('oj', oj);
      next.searchParams.set('pid', pid);
    } else {
      next.searchParams.delete('oj');
      next.searchParams.delete('pid');
    }
    window.history.replaceState({}, '', next);
  }, [selectedId, showCommon, showIsolated, showPre]);

  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      if (event.target instanceof HTMLInputElement || event.target instanceof HTMLTextAreaElement || event.target instanceof HTMLSelectElement) return;
      if (event.key === '+' || event.key === '=') { event.preventDefault(); graphRef.current?.zoomIn(); }
      if (event.key === '-') { event.preventDefault(); graphRef.current?.zoomOut(); }
      if (event.key === '0') { event.preventDefault(); graphRef.current?.fitToNodes(); }
      if (event.key.toLowerCase() === 'r') { event.preventDefault(); runLayout(true); }
    };
    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, [runLayout]);

  const selectNode = useCallback((node: RelationNode) => {
    setSelectedId(node.id);
    window.requestAnimationFrame(() => graphRef.current?.focusNode(node.id));
  }, []);

  const pinNode = useCallback((id: string, position: Position) => {
    positionsRef.current = { ...positionsRef.current, [id]: position };
    setPositions(positionsRef.current);
    const nextFixed = new Set(fixedIdsRef.current);
    nextFixed.add(id);
    fixedIdsRef.current = nextFixed;
    setFixedIds(nextFixed);
    schedulePersist(positionsRef.current, nextFixed);
  }, [schedulePersist]);

  const resetLayout = useCallback(() => {
    if (!data) return;
    const key = `${POSITION_PREFIX}.${relationFingerprint(data)}`;
    try { window.localStorage.removeItem(key); } catch { /* optional */ }
    positionsRef.current = {};
    fixedIdsRef.current = new Set();
    setPositions({});
    setFixedIds(new Set());
    runLayout(true);
  }, [data, runLayout]);

  const searchMatches = useMemo(() => {
    const normalized = query.trim().toLowerCase();
    if (!normalized || !data) return [];
    return data.nodes.filter((node) => matchesQuery(node, normalized)).slice(0, 20);
  }, [data, query]);

  return (
    <main className="relations2-app" aria-label="Canvas 题目关系图应用">
      <header className="relations2-toolbar">
        <div className="relations2-heading">
          <p className="relations2-eyebrow">CANVAS RELATIONS</p>
          <h1>题目关系图</h1>
          <p className="relations2-summary" aria-live="polite">{summaryText}</p>
        </div>
        <div className="relations2-actions">
          <button type="button" className="r2-button r2-button-primary" onClick={() => fetchGraph(true)} disabled={refreshing}>
            {refreshing ? '刷新中...' : '刷新数据'}
          </button>
          <button type="button" className="r2-button" onClick={() => graphRef.current?.fitToNodes()} aria-label="适应视图">适应视图</button>
          <button type="button" className="r2-button" onClick={resetLayout} disabled={isLayouting} aria-label="重新布局">重新布局</button>
          <a className="r2-button r2-button-muted" href="/relations">旧版关系图</a>
        </div>
        <div className="relations2-filters">
          <label className="r2-search">
            <span className="visually-hidden">搜索题目</span>
            <input value={query} onChange={(event) => setQuery(event.target.value)} placeholder="搜索题号、标题、标签..." aria-label="搜索题号、标题、标签" />
            {query && <button type="button" onClick={() => setQuery('')} aria-label="清除搜索">×</button>}
          </label>
          <label><input type="checkbox" checked={showPre} onChange={(event) => setShowPre(event.target.checked)} /> <span className="r2-swatch r2-swatch-pre" /> pre</label>
          <label><input type="checkbox" checked={showCommon} onChange={(event) => setShowCommon(event.target.checked)} /> <span className="r2-swatch r2-swatch-common" /> common</label>
          <label><input type="checkbox" checked={showIsolated} onChange={(event) => setShowIsolated(event.target.checked)} /> 显示孤立题目</label>
        </div>
      </header>

      <div className="relations2-zoom-actions" aria-label="缩放控制">
        <button type="button" onClick={() => graphRef.current?.zoomOut()} aria-label="缩小">-</button>
        <button type="button" onClick={() => graphRef.current?.zoomIn()} aria-label="放大">+</button>
        <button type="button" onClick={() => graphRef.current?.resetViewport()} aria-label="重置视图">重置</button>
      </div>

      <section className="relations2-stage" aria-busy={loading || isLayouting}>
        <PixiCanvas
          ref={graphRef}
          nodes={visibleGraph.nodes}
          edges={visibleGraph.edges}
          positions={renderPositions}
          options={{ dark, selectedId, hoveredId, matchedIds }}
          onReady={() => { setCanvasReady(true); setCanvasError(''); }}
          onError={(message) => { setCanvasReady(false); setCanvasError(message); }}
          onNodeSelect={selectNode}
          onNodeOpen={(node) => { window.location.href = node.url; }}
          onNodeHover={(node) => { setHoveredId(node?.id || ''); if (node) setHoveredEdge(null); }}
          onEdgeHover={(edge, x, y) => setHoveredEdge(edge ? { edge, x, y } : null)}
          onNodePosition={pinNode}
        />
        <div className="relations2-grid" aria-hidden="true" />
        {(loading || isLayouting) && <div className="r2-status" role="status">{loading ? '正在加载关系数据...' : '正在计算布局...'}</div>}
        {error && (
          <div className="r2-error" role="alert">
            <strong>{error}</strong>
            <div><button type="button" className="r2-button" onClick={() => fetchGraph(true)}>重试</button> <a className="r2-button r2-button-muted" href="/relations">返回旧版关系图</a></div>
          </div>
        )}
        {canvasError && !loading && (
          <div className="r2-error r2-webgl-error" role="alert">
            <strong>{canvasError}</strong>
            <p>当前使用键盘可操作的关系列表。请检查浏览器图形能力或返回旧版关系图。</p>
            <div><button type="button" className="r2-button" onClick={() => { setCanvasError(''); setCanvasReady(false); }}>重试图形渲染</button> <a className="r2-button r2-button-muted" href="/relations">返回旧版关系图</a></div>
          </div>
        )}
        {!loading && !error && !canvasReady && !canvasError && <div className="r2-status">正在准备画布...</div>}
        {hoveredEdge && (
          <div className="r2-edge-tooltip" style={{ left: `${Math.min(82, Math.max(4, hoveredEdge.x / Math.max(1, window.innerWidth) * 100))}%`, top: `${Math.min(86, Math.max(12, hoveredEdge.y / Math.max(1, window.innerHeight) * 100))}%` }}>
            <strong>{hoveredEdge.edge.type}</strong>
            {hoveredEdge.edge.reason && <span>{hoveredEdge.edge.reason}</span>}
          </div>
        )}
        {query && searchMatches.length > 0 && (
          <div className="r2-search-results" aria-label="搜索结果">
            {searchMatches.map((node) => <button type="button" key={node.id} onClick={() => selectNode(node)}><strong>{node.label}</strong><span>{node.title || '无标题'}</span></button>)}
          </div>
        )}
        {query && searchMatches.length === 0 && <div className="r2-search-results r2-search-empty">没有匹配的题目</div>}
      </section>

      <aside className="relations2-details" aria-live="polite">
        {selectedNode ? (
          <>
            <div className="r2-detail-code">{selectedNode.oj} {selectedNode.problem_id}</div>
            <h2>{selectedNode.title || selectedNode.label}</h2>
            <div className="r2-detail-tags">{selectedNode.tags.length ? selectedNode.tags.map((tag) => <span key={tag}>{tag}</span>) : <span>无标签</span>}</div>
            <dl><div><dt>前置</dt><dd>{selectedNode.predecessorCount}</dd></div><div><dt>后置</dt><dd>{selectedNode.successorCount}</dd></div><div><dt>相似</dt><dd>{selectedNode.commonCount}</dd></div></dl>
            <a className="r2-detail-link" href={selectedNode.url}>打开题解</a>
          </>
        ) : <div className="r2-detail-empty">选择一个题目节点查看关系</div>}
      </aside>

      <div className="relations2-legend" aria-label="关系图图例">
        <span><i className="r2-legend-node" />题目节点</span>
        <span><i className="r2-legend-line r2-legend-pre" />pre 前置</span>
        <span><i className="r2-legend-line r2-legend-common" />common 相似</span>
      </div>

      {(!canvasReady || canvasError) && !loading && !error && (
        <section className="relations2-fallback-list" aria-label="题目关系列表">
          <h2>题目关系列表</h2>
          <p>图形渲染不可用时仍可通过列表选择题目。</p>
          <div>{visibleGraph.nodes.slice(0, 120).map((node) => <button type="button" key={node.id} onClick={() => selectNode(node)}><strong>{node.label}</strong><span>{node.title || '无标题'}</span></button>)}</div>
        </section>
      )}
    </main>
  );
}

function readInitialState(): InitialState {
  const url = new URL(window.location.href);
  const oj = url.searchParams.get('oj');
  const pid = url.searchParams.get('pid');
  const rawEdges = url.searchParams.get('edges');
  const edges = rawEdges === null ? new Set(['pre', 'common']) : new Set(rawEdges.split(','));
  return {
    selectedId: oj && pid ? `${oj}/${pid}` : '',
    showPre: edges.has('pre'),
    showCommon: edges.has('common'),
    showIsolated: url.searchParams.get('isolated') === '1',
  };
}
