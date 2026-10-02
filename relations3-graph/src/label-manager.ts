import { PerspectiveCamera, Vector3 } from 'three';
import type { GraphModel } from './graph-model';
import type { GraphObjects, VisualState } from './graph-objects';

interface Rect { left: number; top: number; right: number; bottom: number }
export interface LabelCandidate { id: string; label: string; title: string; priority: number; full: boolean }
export interface LabelAnchor extends LabelCandidate { x: number; y: number; behind?: boolean }
export interface LabelMeasurement { width: number; height: number }
export function selectLabelCandidates(items: LabelCandidate[], budget: number): LabelCandidate[] {
  return [...items].sort((a, b) => a.priority - b.priority || a.id.localeCompare(b.id)).slice(0, Math.max(0, budget));
}
export function placeLabels(anchors: LabelAnchor[], measurements: Record<string, LabelMeasurement>, reserved: Rect[] = []): Record<string, { left: number; top: number }> {
  const placed: Record<string, { left: number; top: number }> = {};
  const occupied = [...reserved];
  for (const a of anchors) {
    if (a.behind) continue;
    const m = measurements[a.id] || { width: 80, height: 24 };
    const options = [[a.x - m.width / 2, a.y - m.height - 8], [a.x - m.width / 2, a.y + 8], [a.x + 8, a.y - m.height / 2], [a.x - m.width - 8, a.y - m.height / 2]];
    const hit = options.find(([left, top]) => { const r = { left, top, right: left + m.width, bottom: top + m.height }; return !occupied.some(o => rectanglesOverlap(r, o)); });
    if (!hit && a.priority > 1) continue;
    const [left, top] = hit || options[0];
    placed[a.id] = { left, top }; occupied.push({ left, top, right: left + m.width, bottom: top + m.height });
  }
  return placed;
}
export function rectanglesOverlap(a: Rect, b: Rect): boolean {
  return a.left < b.right && a.right > b.left && a.top < b.bottom && a.bottom > b.top;
}

export function updateLabels(objects: GraphObjects, model: GraphModel, visual: VisualState, camera: PerspectiveCamera, width: number, height: number) {
  if (!width || !height) return;
  // Labels are rendered by the HTML overlay. Keep this hook for the render loop.
  return;
  /*
  const ids = new Set<string>();
  if (visual.focus.centerId) { ids.add(visual.focus.centerId); visual.focus.nodeIds.forEach(id => ids.add(id)); }
  if (visual.hovered) ids.add(visual.hovered);
  if (visual.query) [...visual.matched].slice(0, 30).forEach(id => ids.add(id));
  if (!visual.focus.centerId && !visual.query) {
    // Near overview nodes may carry labels; the distant catalog remains uncluttered.
    for (const id of visual.visibleNodes) {
      const n = model.nodes.get(id);
      if (n && camera.position.distanceTo(new Vector3(n.x, n.y, n.z)) < 700) ids.add(id);
      if (ids.size >= 45) break;
    }
  }
  const ordered = [...ids].sort((a, b) => {
    const rank = (id: string) => id === visual.focus.centerId ? 0 : id === visual.hovered ? 1 : visual.focus.nodeIds.has(id) ? 2 : 3;
    return rank(a) - rank(b);
  });
  const occupied: Rect[] = [];
  camera.updateMatrixWorld();
  for (const id of ordered) {
    const n = model.nodes.get(id);
    if (!n || !visual.visibleNodes.has(id)) continue;
    const world = new Vector3(n.x, n.y, n.z);
    const view = world.clone().applyMatrix4(camera.matrixWorldInverse);
    if (view.z >= -camera.near) continue;
    const projected = world.clone().project(camera);
    if (projected.z < -1 || projected.z > 1 || Math.abs(projected.x) > 1.15 || Math.abs(projected.y) > 1.15) continue;
    const sprite = objects.label(id, id === visual.focus.centerId || id === visual.hovered);
    if (!sprite) continue;
    const aspect = sprite.scale.x / Math.max(0.01, sprite.scale.y);
    const pixelHeight = id === visual.focus.centerId ? 48 : 36;
    const worldHeight = 2 * -view.z * Math.tan(camera.getEffectiveFOV() * Math.PI / 360) * pixelHeight / height;
    sprite.scale.set(worldHeight * aspect, worldHeight, 1);
    // Use a billboard offset in camera-up direction, instead of a world-y offset.
    const offset = new Vector3(0, worldHeight * 0.75 + 9, 0).applyQuaternion(camera.quaternion);
    sprite.position.copy(offset);
    const center = world.add(offset).project(camera);
    const x = (center.x + 1) * width / 2;
    const y = (1 - center.y) * height / 2;
    const rect = { left: x - pixelHeight * aspect / 2 - 3, right: x + pixelHeight * aspect / 2 + 3, top: y - pixelHeight / 2 - 3, bottom: y + pixelHeight / 2 + 3 };
    const priority = id === visual.focus.centerId || id === visual.hovered;
    if (!priority && occupied.some(r => rectanglesOverlap(rect, r))) continue;
    sprite.visible = true;
    occupied.push(rect);
  }
  */
}
