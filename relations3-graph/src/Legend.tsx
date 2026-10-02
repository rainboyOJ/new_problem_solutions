import type { RelationGraphResponse, RelationMode } from './types';
export default function Legend({ data, focused, relationMode }: { data: RelationGraphResponse; focused: boolean; relationMode: RelationMode }) {
  const showPre = relationMode !== 'common';
  const showCommon = relationMode !== 'pre';
  return <div className="relations3-legend" aria-label="图例">
    <span><i className="r3-dot" />题目</span>
    {showPre && <span><i className="r3-line pre" />{focused ? '当前题 → 后续题' : '前置 → 后续'}</span>}
    {showPre && focused && <span><i className="r3-line incoming" />前置题 → 当前题</span>}
    {showCommon && <span><i className="r3-line common" />相似题 · 无方向</span>}
    <details><summary>节点颜色按主标签</summary><div className="relations3-tag-legend">{data.tagStats.map(t => <span key={t.tag}><i style={{ background: t.color }} />{t.tag}</span>)}</div></details>
  </div>;
}
