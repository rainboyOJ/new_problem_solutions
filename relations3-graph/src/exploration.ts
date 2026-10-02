import type { CameraView } from './types';
export interface HistoryEntry { id: string | null; camera?: CameraView }
export interface Exploration { entries: HistoryEntry[]; cursor: number; revision: number }
export type ExploreAction = { type: 'select'; id: string | null; camera?: CameraView } | { type: 'back'; camera?: CameraView } | { type: 'reconcile'; validIds: Set<string> } | { type: 'url'; id: string | null };
export function initialExploration(id: string | null): Exploration { return { entries: [{ id }], cursor: 0, revision: 0 }; }
export function explorationReducer(state: Exploration, action: ExploreAction): Exploration {
  if (action.type === 'url') return { ...initialExploration(action.id), revision: state.revision + 1 };
  if (action.type === 'reconcile') {
    const current = state.entries[state.cursor].id;
    const kept = state.entries.slice(0, state.cursor + 1).filter(e => !e.id || action.validIds.has(e.id));
    const removed = !!current && !action.validIds.has(current);
    if (removed) kept.push({ id: null });
    if (!removed && kept.length === state.cursor + 1) return state;
    return { entries: kept.length ? kept : [{ id: null }], cursor: Math.max(0, kept.length - 1), revision: state.revision + (removed ? 1 : 0) };
  }
  const entries = state.entries.map((e, i) => i === state.cursor ? { ...e, camera: action.camera } : e);
  if (action.type === 'back') return state.cursor > 0 ? { entries, cursor: state.cursor - 1, revision: state.revision + 1 } : state;
  if (entries[state.cursor].id === action.id) return { ...state, revision: state.revision + 1 };
  return { entries: [...entries.slice(0, state.cursor + 1), { id: action.id }], cursor: state.cursor + 1, revision: state.revision + 1 };
}
