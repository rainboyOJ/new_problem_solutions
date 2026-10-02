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
