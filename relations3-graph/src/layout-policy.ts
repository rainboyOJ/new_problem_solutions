import type { Force3D } from 'd3-force-3d';
import type { SimNode } from './types';

// Original indices are intentionally retained: d3 forces index their arrays by node.index.
export function scopedForce(force: Force3D<SimNode>, ids: Set<string>): Force3D<SimNode> {
  const result = (alpha: number) => force(alpha);
  result.initialize = (nodes: SimNode[], ...args: unknown[]) => force.initialize(nodes.filter(n => ids.has(n.id)), ...args);
  return result;
}
