import type { CameraView, Position3D } from './types';

export function distance(a: Position3D, b: Position3D): number { return Math.hypot(a.x - b.x, a.y - b.y, a.z - b.z); }
export function focusCamera(center: Position3D, points: Position3D[], current: CameraView, aspect: number, effectiveFov = 50, near = 0.1): CameraView {
  const length = distance(current.position, current.target);
  const direction = length > 1e-8 ? { x: (current.position.x - current.target.x) / length, y: (current.position.y - current.target.y) / length, z: (current.position.z - current.target.z) / length } : { x: 0, y: 0, z: 1 };
  const radius = Math.max(50, ...points.map(p => distance(center, p) + 10));
  const halfFov = Math.min(85, Math.max(5, effectiveFov / 2)) * Math.PI / 180;
  const horizontal = Math.atan(Math.tan(halfFov) * (Number.isFinite(aspect) && aspect > 0 ? aspect : 1));
  const d = Math.max(radius / Math.sin(Math.max(0.01, Math.min(halfFov, horizontal))) * 1.2, radius + near + 10);
  return { position: { x: center.x + direction.x * d, y: center.y + direction.y * d, z: center.z + direction.z * d }, target: { ...center } };
}
export function overviewCenter(points: Position3D[]): Position3D {
  if (!points.length) return { x: 0, y: 0, z: 0 };
  const axis = (key: keyof Position3D) => (Math.min(...points.map(p => p[key])) + Math.max(...points.map(p => p[key]))) / 2;
  return { x: axis('x'), y: axis('y'), z: axis('z') };
}
