import type { Position3D } from './types';
export const LAYOUT_PREFIX = 'rbook.relations3.layout.v1';
export const LAYOUT_VERSION = 1;
export interface SavedLayout3D {
  version: 1; layoutVersion: number; fingerprint: string; updatedAt: number;
  positions: Record<string, Position3D>; userPinnedIds: string[];
}
export interface StorageLike { getItem(key: string): string | null; setItem(key: string, value: string): void; removeItem(key: string): void }
export function finitePosition(value: unknown): value is Position3D {
  if (!value || typeof value !== 'object') return false;
  const p = value as Position3D;
  return typeof p.x === 'number' && typeof p.y === 'number' && typeof p.z === 'number' && Number.isFinite(p.x) && Number.isFinite(p.y) && Number.isFinite(p.z);
}
export function validateLayout(value: unknown, ids: Set<string>): SavedLayout3D | null {
  if (!value || typeof value !== 'object') return null;
  const input = value as Partial<SavedLayout3D>;
  if (input.version !== 1 || input.layoutVersion !== LAYOUT_VERSION || typeof input.fingerprint !== 'string' || !input.positions || typeof input.positions !== 'object' || !Array.isArray(input.userPinnedIds)) return null;
  const positions = Object.fromEntries(Object.entries(input.positions).filter(([id, p]) => ids.has(id) && finitePosition(p)).map(([id, p]) => [id, { x: p.x, y: p.y, z: p.z }]));
  return { version: 1, layoutVersion: LAYOUT_VERSION, fingerprint: input.fingerprint, updatedAt: Number(input.updatedAt) || 0, positions, userPinnedIds: input.userPinnedIds.filter(id => ids.has(id) && !!positions[id]) };
}
export function loadLayout(storage: StorageLike | undefined, fingerprint: string, ids: Set<string>) {
  for (const key of [`${LAYOUT_PREFIX}.${fingerprint}`, `${LAYOUT_PREFIX}.latest`]) {
    try {
      const result = validateLayout(JSON.parse(storage?.getItem(key) || 'null'), ids);
      if (result) return result;
    } catch { /* Storage is optional, including in private browsing. */ }
  }
  return null;
}
export function saveLayout(storage: StorageLike | undefined, layout: SavedLayout3D): boolean {
  if (!storage) return false;
  try {
    const old = JSON.parse(storage.getItem(`${LAYOUT_PREFIX}.latest`) || 'null') as SavedLayout3D | null;
    if (old?.fingerprint && old.fingerprint !== layout.fingerprint) storage.removeItem(`${LAYOUT_PREFIX}.${old.fingerprint}`);
    const text = JSON.stringify(layout);
    storage.setItem(`${LAYOUT_PREFIX}.${layout.fingerprint}`, text);
    storage.setItem(`${LAYOUT_PREFIX}.latest`, text);
    return true;
  } catch { return false; }
}
export function clearLayout(storage: StorageLike | undefined, fingerprint: string): void {
  try {
    storage?.removeItem(`${LAYOUT_PREFIX}.${fingerprint}`);
    const latest = JSON.parse(storage?.getItem(`${LAYOUT_PREFIX}.latest`) || 'null') as SavedLayout3D | null;
    if (latest?.fingerprint === fingerprint) storage?.removeItem(`${LAYOUT_PREFIX}.latest`);
  } catch { /* Optional storage. */ }
}
export function browserStorage(): StorageLike | undefined {
  try { return window.localStorage; } catch { return undefined; }
}
