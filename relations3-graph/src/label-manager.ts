import { PerspectiveCamera, Vector3 } from 'three';
import type { GraphModel } from './graph-model';
import type { VisualState } from './graph-objects';
import type { GraphLabel } from './GraphLabelOverlay';
import type { LabelMode } from './types';

// labelMode 决定标签文本：full=题号·标题，title=仅标题，pi=仅题号，off=空（不渲染）
export function labelText(label: string, title: string, mode: LabelMode): string {
  if (mode === 'off') return '';
  if (mode === 'title') return title || label;
  if (mode === 'pi') return label;
  return title ? `${label} · ${title}` : label;
}

interface Rect { left: number; top: number; right: number; bottom: number }
export interface LabelCandidate { id: string; label: string; title: string; priority: number; full: boolean }
export interface LabelAnchor extends LabelCandidate { x: number; y: number; behind?: boolean }
export interface LabelMeasurement { width: number; height: number }
export function selectLabelCandidates(items: LabelCandidate[], budget: number): LabelCandidate[] {
  return [...items].sort((a, b) => a.priority - b.priority || a.id.localeCompare(b.id)).slice(0, Math.max(0, budget));
}
export function rectanglesOverlap(a: Rect, b: Rect): boolean {
  return a.left < b.right && a.right > b.left && a.top < b.bottom && a.bottom > b.top;
}
export function placeLabels(anchors: LabelAnchor[], measurements: Record<string, LabelMeasurement>, reserved: Rect[] = [], viewport?: { width: number; height: number }): Record<string, { left: number; top: number }> {
  const placed: Record<string, { left: number; top: number }> = {};
  const occupied = [...reserved];
  for (const a of anchors) {
    if (a.behind) continue;
    const m = measurements[a.id] || { width: 80, height: 24 };
    const options = [[a.x - m.width / 2, a.y - m.height - 10], [a.x - m.width / 2, a.y + 10], [a.x + 10, a.y - m.height / 2], [a.x - m.width - 10, a.y - m.height / 2]];
    if (viewport) for (const point of options) {
      point[0] = Math.max(4, Math.min(point[0], viewport.width - m.width - 4));
      point[1] = Math.max(4, Math.min(point[1], viewport.height - m.height - 4));
    }
    const hit = options.find(([left, top]) => !occupied.some(o => rectanglesOverlap({ left: left - 3, top: top - 3, right: left + m.width + 3, bottom: top + m.height + 3 }, o)));
    if (!hit && a.priority > 1) continue;
    const [left, top] = hit || options[0];
    placed[a.id] = { left, top }; occupied.push({ left, top, right: left + m.width, bottom: top + m.height });
  }
  return placed;
}

// Zoom separates projected anchors, making room for additional labels.
export function projectLabels(model: GraphModel, visual: VisualState, camera: PerspectiveCamera, width: number, height: number, measure: (text: string) => number): GraphLabel[] {
  if (!width || !height || visual.labelMode === 'off') return [];
  camera.updateMatrixWorld();
  const anchors: (LabelAnchor & { depth: number })[] = [];
  const measurements: Record<string, LabelMeasurement> = {};
  const texts = new Map<string, string>();
  const metadata = new Map(visual.data.nodes.map(node => [node.id, node]));
  for (const id of visual.visibleNodes) {
    const node = model.nodes.get(id);
    const info = metadata.get(id);
    if (!node || !info) continue;
    const world = new Vector3(node.x, node.y, node.z);
    const view = world.clone().applyMatrix4(camera.matrixWorldInverse);
    const point = world.project(camera);
    if (view.z >= -camera.near || point.z < -1 || point.z > 1 || Math.abs(point.x) > 1 || Math.abs(point.y) > 1) continue;
    const priority = id === visual.focus.centerId ? 0 : id === visual.hovered ? 1 : visual.matched.has(id) ? 2 : visual.focus.nodeIds.has(id) ? 3 : 4;
    const full = priority <= 1;
    const maxWidth = Math.max(40, Math.min(full ? 300 : 190, width - 20) - 12);
    const text = labelText(info.label, info.title, visual.labelMode);
    const lines: string[] = [''];
    for (const char of text) {
      const last = lines.length - 1;
      if (measure(lines[last] + char + (full ? '' : '…')) > maxWidth) {
        if (!full) { lines[last] += '…'; break; }
        lines.push(char);
      } else lines[last] += char;
    }
    texts.set(id, lines.join('\n'));
    measurements[id] = { width: Math.ceil(Math.max(...lines.map(measure))) + 12, height: lines.length * 16 + 6 };
    anchors.push({ id, label: info.label, title: info.title, priority, full, x: (point.x + 1) * width / 2, y: (1 - point.y) * height / 2, depth: -view.z });
  }
  anchors.sort((a, b) => a.priority - b.priority || a.depth - b.depth || a.id.localeCompare(b.id));
  const positions = placeLabels(anchors, measurements, [], { width, height });
  return anchors.filter(a => positions[a.id]).map(a => ({ id: a.id, text: texts.get(a.id)!, priority: a.priority, ...positions[a.id], ...measurements[a.id] }));
}
