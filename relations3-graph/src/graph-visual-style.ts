import { GRAPH_THEME } from './graph-theme';
import type { SimLink } from './types';
// 只依赖边的类型与目标端，RelationEdge 与 SimLink 都可直接传入
export function edgeVisual(edge: Pick<SimLink, 'type' | 'target'>, centerId: string | null, direct: boolean, hovered: boolean) {
  const focused = direct || hovered;
  const color = edge.type === 'common' ? GRAPH_THEME.common : direct && edge.target === centerId ? GRAPH_THEME.pre : GRAPH_THEME.next;
  return { color: centerId && !focused ? GRAPH_THEME.overviewEdge : color, opacity: centerId && !focused ? 0.05 : focused ? 1 : 0.22, dashed: edge.type === 'common', arrow: edge.type === 'pre' };
}
