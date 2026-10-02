import type { Filters, FocusNeighborhood, RelationEntry, RelationNode } from './types';

interface Props {
  node?: RelationNode; nodes: Map<string, RelationNode>; focus: FocusNeighborhood; filters: Filters;
  open: boolean; onOpen(value: boolean): void; onSelect(id: string): void; onHover(id: string): void;
}
export default function DetailsPanel(p: Props) {
  const group = (title: string, name: string, entries: RelationEntry[], enabled: boolean) => <section className="relations3-relation-group" data-relation-group={name}>
    <h3>{title}<span>{entries.length}</span></h3>
    {!enabled ? <p className="r3-muted">当前筛选已隐藏这类关系</p> : !entries.length ? <p className="r3-muted">暂无{title}</p> :
      <ul>{entries.map(e => {
        const n = p.nodes.get(e.nodeId);
        return n && <li key={e.edgeId} onMouseEnter={() => p.onHover(e.nodeId)} onMouseLeave={() => p.onHover('')}>
          <div className="relations3-relation-entry">
            <button type="button" data-node-id={n.id} onClick={() => p.onSelect(n.id)} onFocus={() => p.onHover(n.id)} onBlur={() => p.onHover('')}>
              <strong>{n.label}</strong><span>{n.title}</span>
            </button>
            <a href={n.url} title={`打开 ${n.label} 的题解`} aria-label={`打开 ${n.label} 的题解`}>↗</a>
          </div>
          {e.reason && <details className="relations3-reason"><summary>关系说明</summary><p>{e.reason}</p></details>}
        </li>;
      })}</ul>}
  </section>;
  return <aside className={`relations3-details${p.open ? ' is-open' : ''}`} aria-label="题目详情与关系清单">
    <button type="button" className="relations3-drawer-toggle" onClick={() => p.onOpen(!p.open)} aria-expanded={p.open}>
      <span>{p.node ? p.node.label : '题目关系清单'}</span><span>{p.open ? '收起 ↓' : '展开 ↑'}</span>
    </button>
    <div className="relations3-details-scroll">
      {p.node ? <>
        <div className="relations3-detail-heading">
          <p className="relations3-kicker">当前中心题目</p>
          <div className="relations3-detail-code">{p.node.label}</div>
          <h2>{p.node.title || p.node.label}</h2>
          <div className="relations3-tags">{p.node.tags.map(tag => <span key={tag}>{tag}</span>)}<span className="r3-difficulty">{p.node.difficulty}</span></div>
          <a className="r3-button r3-primary relations3-open-solution" href={p.node.url}>打开题解 ↗</a>
          <p className="r3-muted">点击关联题目切换中心，使用“上一题”返回。</p>
        </div>
        {group('前置题', 'predecessors', p.focus.predecessors, p.filters.showPre)}
        {group('后续题', 'successors', p.focus.successors, p.filters.showPre)}
        {group('相似题', 'commons', p.focus.commons, p.filters.showCommon)}
        {p.node.isolated && <p className="relations3-isolated-note">这是一道孤立题目，尚未维护前置或相似关系。</p>}
      </> : <div className="relations3-detail-empty">
        <div className="relations3-empty-symbol" aria-hidden="true">◎</div>
        <p className="relations3-kicker">从一道题开始探索</p>
        <h2>看清下一步，<br />也看清来路。</h2>
        <p>点击图中的题目，或搜索一个题号。这里会列出它的直接前置、后续与相似题。</p>
        <ol><li>选择一个题目作为中心</li><li>查看一层关系和关系说明</li><li>沿邻居继续探索，随时返回</li></ol>
      </div>}
    </div>
  </aside>;
}
