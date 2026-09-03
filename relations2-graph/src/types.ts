export type RelationType = 'pre' | 'common';

export interface RelationNode {
  id: string;
  oj: string;
  problem_id: string;
  label: string;
  title: string;
  tags: string[];
  primaryTag: string;
  difficulty: string;
  color: string;
  url: string;
  isolated: boolean;
  predecessorCount: number;
  successorCount: number;
  commonCount: number;
}

export interface RelationEdge {
  id: string;
  source: string;
  target: string;
  type: RelationType;
  directed: boolean;
  reason: string;
}

export interface RelationSummary {
  nodes: number;
  edges: number;
  relationNodes: number;
  isolatedNodes: number;
  preEdges: number;
  commonEdges: number;
}

export interface TagStat {
  tag: string;
  count: number;
  color: string;
}

export interface RelationGraphResponse {
  nodes: RelationNode[];
  edges: RelationEdge[];
  tagStats: TagStat[];
  summary: RelationSummary;
}

export interface VisibleGraph {
  nodes: RelationNode[];
  edges: RelationEdge[];
}

export interface Position {
  x: number;
  y: number;
}

export type PositionMap = Record<string, Position>;

export interface LayoutInput {
  nodes: Array<{ id: string }>;
  edges: Array<{ source: string; target: string }>;
  initialPositions: PositionMap;
  fixedIds: string[];
  seed: number;
  edgeLength: number;
  chargeStrength: number;
  collisionRadius: number;
  ticks: number;
}

export interface LayoutMessage {
  type: 'tick' | 'done' | 'error';
  positions?: PositionMap;
  message?: string;
}
