import { useId, useLayoutEffect, useRef, useState } from 'react';
import { layerGroups, edgeRole, type FocusNeighborhood, type RelationNode, type RelationEdge, type Filters } from './model';

interface Props {
  active: boolean; focus: FocusNeighborhood; nodes: Map<string, RelationNode>; edges: Map<string, RelationEdge>;
  relationMode: Filters['relationMode'];
  hover: string; onHover(id: string): void; onSelect(id: string): void; onOverview(): void;
}
interface Path { id: string; d: string; role: string; source: string; target: string }
export default function Layers(p: Props) {
  const root = useRef<HTMLDivElement>(null), board = useRef<HTMLDivElement>(null);
  const [paths, setPaths] = useState<Path[]>([]);
  const marker = useId().replaceAll(':', '');
  // The component stays mounted while hidden, preserving horizontal and column scroll.
  useLayoutEffect(() => {
    if (!p.active || !board.current || !root.current) return;
    let frame = 0;
    const measure = () => {
      frame = 0;
      const element = board.current!;
      const bounds = element.getBoundingClientRect();
      const center = element.querySelector<HTMLElement>('[data-layer="current"] [data-node-id]');
      if (!center) { setPaths([]); return; }
      const c = center.getBoundingClientRect();
      const result: Path[] = [];
      element.querySelectorAll<HTMLElement>('[data-edge-id]').forEach(card => {
        const edge = p.edges.get(card.dataset.edgeId!); if (!edge) return;
        const rect = card.getBoundingClientRect(), list = card.parentElement!.getBoundingClientRect();
        if (rect.bottom < list.top || rect.top > list.bottom) return;
        const role = edgeRole(edge, p.focus.centerId)!;
        let x1: number, y1: number, x2: number, y2: number;
        if (role === 'before') { x1 = rect.right; y1 = rect.top + rect.height / 2; x2 = c.left; y2 = c.top + c.height / 2; }
        else if (role === 'after') { x1 = c.right; y1 = c.top + c.height / 2; x2 = rect.left; y2 = rect.top + rect.height / 2; }
        else { x1 = c.left + c.width / 2; y1 = c.bottom; x2 = rect.left + rect.width / 2; y2 = rect.top; }
        x1 -= bounds.left; x2 -= bounds.left; y1 -= bounds.top; y2 -= bounds.top;
        const d = role === 'similar'
          ? `M ${x1} ${y1} C ${x1} ${y1 + 40}, ${x2} ${y2 - 40}, ${x2} ${y2}`
          : `M ${x1} ${y1} C ${(x1 + x2) / 2} ${y1}, ${(x1 + x2) / 2} ${y2}, ${x2} ${y2}`;
        result.push({ id: edge.id, d, role, source: edge.source, target: edge.target });
      });
      setPaths(result);
    };
    const schedule = () => { if (!frame) frame = requestAnimationFrame(measure); };
    const observer = new ResizeObserver(schedule); observer.observe(board.current);
    root.current.addEventListener('scroll', schedule, true); measure();
    const container = root.current;
    return () => { observer.disconnect(); container.removeEventListener('scroll', schedule, true); cancelAnimationFrame(frame); };
  }, [p.active, p.focus, p.edges]);
  const card = (id: string, edgeId = '', role = 'current') => {
    const node = p.nodes.get(id); if (!node) return null;
    return <button key={edgeId || id} className={`r4-layer-card r4-role-${role}${p.hover === id ? ' is-hovered' : ''}`}
      data-node-id={id} data-edge-id={edgeId || undefined} onClick={() => p.onSelect(id)}
      onPointerEnter={() => p.onHover(id)} onPointerLeave={() => p.onHover('')}
      onFocus={() => p.onHover(id)} onBlur={() => p.onHover('')}>
      <span className="r4-card-code">{node.label}<span>{node.difficulty}</span></span>
      <strong>{node.title || node.label}</strong>
      <small>{node.primaryTag || '题目'}{edgeId && p.edges.get(edgeId)?.reason ? ' · 有关系说明' : ''}</small>
    </button>;
  };
  return <div className="r4-layers" ref={root}>
    {!p.focus.centerId ? <div className="r4-stage-message"><span className="r4-empty-orbit">◎</span><h2>从一道题，看清来路与去向</h2><p>搜索题号或题名，或先在全景中选择一个节点。</p><button onClick={p.onOverview}>去全景选题 →</button></div> :
      <div className="r4-layer-board" ref={board}>
        <svg className="r4-layer-edges" aria-hidden="true">
          <defs>{['before', 'after'].map(role => <marker key={role} id={`${marker}-${role}`} markerWidth="7" markerHeight="7" refX="6" refY="3.5" orient="auto"><path d="M0 0 L7 3.5 L0 7" className={`r4-fill-${role}`} /></marker>)}</defs>
          {paths.map(path => <path key={path.id} data-relation-edge={path.id} d={path.d} className={`r4-edge-${path.role}`}
            opacity={!p.hover || path.source === p.hover || path.target === p.hover ? .75 : .06}
            markerEnd={path.role === 'similar' ? undefined : `url(#${marker}-${path.role})`} />)}
        </svg>
        <div className="r4-layer-columns">
          {layerGroups(p.focus).map(group => <section key={group.key} className={`r4-layer-column r4-role-${group.key}`} data-layer={group.key}>
            <header><div><span>{group.hint}</span><h2>{group.title}</h2></div><b>{group.entries.length}</b></header>
            <div className="r4-layer-list">{group.entries.length ? group.entries.map(e => card(e.nodeId, e.edgeId, group.key)) : <p className="r4-layer-empty">{p.relationMode === 'common' && group.key !== 'current' ? '前置关系已隐藏' : `暂无直接${group.title}`}</p>}</div>
          </section>)}
        </div>
        <section className="r4-similar-group" data-layer="similar"><header><h2>相似题 <b>{p.focus.commons.length}</b></h2><span>相近的解题模型，不表示学习先后</span></header>
          <div className="r4-similar-cards">{p.focus.commons.length ? p.focus.commons.map(e => card(e.nodeId, e.edgeId, 'similar')) : <p className="r4-layer-empty">{p.relationMode === 'pre' ? '相似关系已隐藏' : '暂无直接相似关系'}</p>}</div>
        </section>
        <p className="r4-layer-footnote">只展示已维护的直接关系 · 点击卡片继续探索 · 完整说明见关系清单</p>
      </div>}
  </div>;
}
