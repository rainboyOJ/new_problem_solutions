export type RelationType = 'pre' | 'common';
export interface RelationNode {
  id: string; oj: string; problem_id: string; label: string; title: string;
  tags: string[]; primaryTag: string; difficulty: string; color: string; url: string;
  isolated: boolean; predecessorCount: number; successorCount: number; commonCount: number;
}
export interface RelationEdge {
  id: string; source: string; target: string; type: RelationType; directed: boolean; reason: string;
}
export interface RelationGraphResponse {
  nodes: RelationNode[]; edges: RelationEdge[];
  tagStats: { tag: string; count: number; color: string }[];
  summary: { nodes: number; edges: number; relationNodes: number; isolatedNodes: number; preEdges: number; commonEdges: number };
  discarded: number;
}
export interface Filters { showPre: boolean; showCommon: boolean; showIsolated: boolean }
// 节点标签显示内容：full=题号·标题（默认），title=仅标题，pi=仅题号（OJ+编号），off=不显示标签
export type LabelMode = 'full' | 'title' | 'pi' | 'off';
export const LABEL_MODES: readonly { value: LabelMode; label: string }[] = [
  { value: 'full', label: '完整' }, { value: 'title', label: '标题' }, { value: 'pi', label: '题号' }, { value: 'off', label: '关闭' },
];
export interface Position3D { x: number; y: number; z: number }
export interface SimNode extends Position3D {
  id: string; vx?: number; vy?: number; vz?: number; fx?: number; fy?: number; fz?: number;
}
export interface SimLink {
  id: string; source: string | SimNode; target: string | SimNode;
  sourceId: string; targetId: string; type: RelationType;
}
export interface RelationEntry { nodeId: string; edgeId: string; reason: string }
export interface FocusNeighborhood {
  centerId: string; nodeIds: Set<string>; edgeIds: Set<string>;
  predecessors: RelationEntry[]; successors: RelationEntry[]; commons: RelationEntry[];
}
export interface CameraView { position: Position3D; target: Position3D }
export interface Graph3DHandle {
  fitVisible(): void; resetView(): void; relayout(): void; zoom(factor: number): void;
  getCameraView(): CameraView | undefined;
}
