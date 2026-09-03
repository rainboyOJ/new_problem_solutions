import { forceCenter, forceCollide, forceLink, forceManyBody, forceSimulation } from 'd3-force';
import type { LayoutInput, PositionMap } from './types';

interface SimNode {
  id: string;
  x: number;
  y: number;
  fx?: number;
  fy?: number;
}

export function runLayoutSync(
  input: LayoutInput,
  onTick?: (positions: PositionMap) => void,
): PositionMap {
  const fixedIds = new Set(input.fixedIds);
  const nodes: SimNode[] = input.nodes.map((node, index) => {
    const saved = input.initialPositions[node.id];
    const angle = index * 2.399963229728653;
    const radius = 100 + Math.sqrt(index + 1) * 32;
    const position = saved || { x: Math.cos(angle) * radius, y: Math.sin(angle) * radius };
    return {
      id: node.id,
      x: position.x,
      y: position.y,
      ...(fixedIds.has(node.id) ? { fx: position.x, fy: position.y } : {}),
    };
  });

  const links = input.edges.map((edge) => ({ source: edge.source, target: edge.target }));
  const simulation = forceSimulation(nodes)
    .randomSource(seedRandom(input.seed))
    .force('link', forceLink<SimNode, { source: string; target: string }>(links)
      .id((node) => node.id)
      .distance(input.edgeLength)
      .strength(0.7))
    .force('charge', forceManyBody<SimNode>().strength(-input.chargeStrength).distanceMax(2600))
    .force('collide', forceCollide<SimNode>(input.collisionRadius).iterations(3).strength(1))
    .force('center', forceCenter(0, 0))
    .alpha(1)
    .alphaDecay(0.035)
    .velocityDecay(0.42)
    .stop();

  for (let tick = 0; tick < input.ticks; tick += 1) {
    simulation.tick();
    if (onTick && (tick % 8 === 0 || tick === input.ticks - 1)) {
      onTick(toPositions(nodes));
    }
  }

  simulation.stop();
  return toPositions(nodes);
}

function toPositions(nodes: SimNode[]): PositionMap {
  return Object.fromEntries(nodes.map((node) => [node.id, { x: node.x, y: node.y }]));
}

function seedRandom(seed: number): () => number {
  let state = (seed || 1) >>> 0;
  return () => {
    state = Math.imul(1664525, state) + 1013904223;
    return ((state >>> 0) + 1) / 4294967297;
  };
}
