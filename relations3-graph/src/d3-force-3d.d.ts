declare module 'd3-force-3d' {
  export interface Force3D<N> {
    (alpha: number): void;
    initialize(nodes: N[], ...args: unknown[]): void;
  }
  export function forceCenter<N>(x?: number, y?: number, z?: number): Force3D<N>;
  export function forceManyBody<N>(): Force3D<N> & { strength(value: number): Force3D<N> };
  export function forceCollide<N>(radius: number): Force3D<N> & { iterations(value: number): Force3D<N> };
}
