import { forceSimulation, forceManyBody, forceLink, forceCenter, forceCollide, type SimulationNodeDatum } from 'd3-force';
import type { Point } from './model';

export interface LayoutInput { nodes: { id: string; isolated: boolean }[]; edges: { source: string; target: string }[] }
export function createLayout(input: LayoutInput): Record<string, Point> {
  const linked = input.nodes.filter(n => !n.isolated).map(n => ({ id: n.id } as SimulationNodeDatum & { id: string }));
  // d3's initial phyllotaxis and random source are deterministic. Only run in
  // the worker, then freeze: hovering never restarts this simulation.
  if (linked.length) {
    const simulation = forceSimulation(linked)
      .force('links', forceLink<(typeof linked)[number], { source: string; target: string }>(input.edges.map(e => ({ ...e }))).id(n => n.id).distance(48).strength(.42))
      .force('charge', forceManyBody().strength(-95))
      .force('collision', forceCollide(12))
      .force('center', forceCenter())
      .stop();
    simulation.tick(210);
  }
  const result: Record<string, Point> = {};
  let radius = 0;
  for (const n of linked) {
    result[n.id] = { x: n.x || 0, y: n.y || 0 };
    radius = Math.max(radius, Math.hypot(n.x || 0, n.y || 0));
  }
  const isolated = input.nodes.filter(n => n.isolated);
  isolated.forEach((n, i) => {
    const angle = i * Math.PI * (3 - Math.sqrt(5));
    const r = Math.sqrt((radius + 120) ** 2 + i * 1000);
    result[n.id] = { x: Math.cos(angle) * r, y: Math.sin(angle) * r };
  });
  return result;
}
export function validPositions(value: unknown, nodes: { id: string }[]): value is Record<string, Point> {
  if (!value || typeof value !== 'object' || Array.isArray(value)) return false;
  const positions = value as Record<string, Point>;
  return nodes.every(n => positions[n.id] && Number.isFinite(positions[n.id].x) && Number.isFinite(positions[n.id].y));
}
