import { GRAPH_THEME } from './graph-theme';
import type { SimLink } from './types';
// 只依赖边的类型与目标端，RelationEdge 与 SimLink 都可直接传入
// 总览（无中心题）按类型着色：pre=黄，common=青；
// 聚焦时保留方向色：direct 且指向中心的 pre=黄，direct 且指出的 pre=蓝，common=青。
export function edgeVisual(edge: Pick<SimLink, 'type' | 'target'>, centerId: string | null, direct: boolean, hovered: boolean) {
  const focused = direct || hovered;
  const color = edge.type === 'common' ? GRAPH_THEME.common
    : centerId ? (direct && edge.target === centerId ? GRAPH_THEME.pre : GRAPH_THEME.next)
    : GRAPH_THEME.pre;
  return { color, opacity: centerId && !focused ? 0.05 : focused ? 1 : 0.22, dashed: edge.type === 'common', arrow: edge.type === 'pre' };
}
