import type {
  PositionMap,
  RelationEdge,
  RelationGraphResponse,
  RelationNode,
  RelationType,
  VisibleGraph,
} from './types';

const TAG_COLORS = [
  '#2563eb', '#0f766e', '#c2410c', '#be123c', '#7c3aed', '#15803d',
  '#0369a1', '#a16207', '#475569', '#9333ea', '#b45309', '#1d4ed8',
];

export function normalizeGraphResponse(value: unknown): RelationGraphResponse {
  const input = value && typeof value === 'object' ? value as Record<string, unknown> : {};
  const rawNodes = Array.isArray(input.nodes) ? input.nodes : [];
  const rawEdges = Array.isArray(input.edges) ? input.edges : [];
  const nodes = rawNodes
    .filter((node): node is Record<string, unknown> => Boolean(node && typeof node === 'object'))
    .map((node) => ({
      id: String(node.id || ''),
      oj: String(node.oj || ''),
      problem_id: String(node.problem_id || ''),
      label: String(node.label || `${node.oj || ''} ${node.problem_id || ''}`).trim(),
      title: String(node.title || ''),
      tags: Array.isArray(node.tags) ? node.tags.map(String).filter(Boolean) : [],
      primaryTag: String(node.primaryTag || ''),
      difficulty: String(node.difficulty || '未知'),
      color: String(node.color || '#64748b'),
      url: String(node.url || ''),
      isolated: node.isolated === true,
      predecessorCount: 0,
      successorCount: 0,
      commonCount: 0,
    }))
    .filter((node) => node.id && node.oj && node.problem_id);

  const nodeIds = new Set(nodes.map((node) => node.id));
  const edges = rawEdges
    .filter((edge): edge is Record<string, unknown> => Boolean(edge && typeof edge === 'object'))
    .map((edge) => ({
      id: String(edge.id || ''),
      source: String(edge.source || ''),
      target: String(edge.target || ''),
      type: edge.type === 'common' ? 'common' as const : 'pre' as const,
      directed: edge.type !== 'common' && edge.directed !== false,
      reason: String(edge.reason || ''),
    }))
    .filter((edge) => edge.id && nodeIds.has(edge.source) && nodeIds.has(edge.target));

  const withCounts = addRelationCounts({ nodes, edges, tagStats: [], summary: emptySummary(nodes.length, edges.length) });
  const tagStats = buildTagStats(withCounts.nodes);

  return {
    nodes: withCounts.nodes,
    edges,
    tagStats,
    summary: {
      nodes: nodes.length,
      edges: edges.length,
      relationNodes: nodes.filter((node) => !node.isolated).length,
      isolatedNodes: nodes.filter((node) => node.isolated).length,
      preEdges: edges.filter((edge) => edge.type === 'pre').length,
      commonEdges: edges.filter((edge) => edge.type === 'common').length,
    },
  };
}

export function addRelationCounts(data: RelationGraphResponse): RelationGraphResponse {
  const counts = new Map<string, { predecessorCount: number; successorCount: number; commonCount: number }>();
  data.nodes.forEach((node) => counts.set(node.id, { predecessorCount: 0, successorCount: 0, commonCount: 0 }));

  data.edges.forEach((edge) => {
    const source = counts.get(edge.source);
    const target = counts.get(edge.target);
    if (edge.type === 'pre') {
      if (source) source.successorCount += 1;
      if (target) target.predecessorCount += 1;
    } else {
      if (source) source.commonCount += 1;
      if (target) target.commonCount += 1;
    }
  });

  return {
    ...data,
    nodes: data.nodes.map((node) => ({ ...node, ...counts.get(node.id) })),
  };
}

export function buildVisibleGraph(
  data: RelationGraphResponse,
  options: {
    query: string;
    selectedId: string;
    showPre: boolean;
    showCommon: boolean;
    showIsolated: boolean;
  },
): VisibleGraph {
  const types = new Set<RelationType>();
  if (options.showPre) types.add('pre');
  if (options.showCommon) types.add('common');

  const visibleEdges = data.edges.filter((edge) => types.has(edge.type));
  const incident = new Set<string>();
  visibleEdges.forEach((edge) => {
    incident.add(edge.source);
    incident.add(edge.target);
  });

  const query = options.query.trim().toLowerCase();
  const matches = new Set(
    query
      ? data.nodes.filter((node) => matchesQuery(node, query)).map((node) => node.id)
      : [],
  );

  const visibleIds = new Set(
    data.nodes
      .filter((node) => options.showIsolated || incident.has(node.id))
      .map((node) => node.id),
  );
  if (options.selectedId) visibleIds.add(options.selectedId);
  matches.forEach((id) => visibleIds.add(id));

  const nodes = data.nodes.filter((node) => visibleIds.has(node.id));
  const nodeIds = new Set(nodes.map((node) => node.id));

  return {
    nodes,
    edges: visibleEdges.filter((edge) => nodeIds.has(edge.source) && nodeIds.has(edge.target)),
  };
}

export function matchesQuery(node: RelationNode, query: string): boolean {
  return [node.oj, node.problem_id, node.label, node.title, node.difficulty, node.primaryTag, ...node.tags]
    .join(' ')
    .toLowerCase()
    .includes(query);
}

export function relationFingerprint(data: RelationGraphResponse): string {
  const source = [
    ...data.nodes.map((node) => node.id).sort(),
    ...data.edges.map((edge) => `${edge.id}:${edge.source}:${edge.target}`).sort(),
  ].join('|');
  let hash = 2166136261;
  for (let index = 0; index < source.length; index += 1) {
    hash ^= source.charCodeAt(index);
    hash = Math.imul(hash, 16777619);
  }
  return (hash >>> 0).toString(16);
}

export function positionForNode(id: string, index: number, positions: PositionMap): { x: number; y: number } {
  if (positions[id]) return positions[id];
  const angle = index * 2.399963229728653;
  const radius = 90 + Math.sqrt(index + 1) * 26;
  return { x: Math.cos(angle) * radius, y: Math.sin(angle) * radius };
}

function buildTagStats(nodes: RelationNode[]) {
  const counts = new Map<string, number>();
  nodes.forEach((node) => node.tags.forEach((tag) => counts.set(tag, (counts.get(tag) || 0) + 1)));
  return Array.from(counts.entries())
    .sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0]))
    .map(([tag, count], index) => ({ tag, count, color: TAG_COLORS[index % TAG_COLORS.length] }));
}

function emptySummary(nodes: number, edges: number) {
  return { nodes, edges, relationNodes: 0, isolatedNodes: nodes, preEdges: 0, commonEdges: 0 };
}
