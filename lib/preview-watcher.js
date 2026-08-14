import chokidar from 'chokidar';
import fs from 'fs';
import path from 'path';

import {
  createPreviewSnapshot,
  resolvePreviewProblemFromIndex,
} from './preview-state.js';

const FILE_EVENTS = new Set(['add', 'change', 'unlink']);

function normalizedRelativePath(root, filePath) {
  return path.relative(root, filePath).split(path.sep).join('/');
}

function isInside(parent, filePath) {
  const relative = path.relative(parent, filePath);
  return relative === '' || (!relative.startsWith(`..${path.sep}`) && relative !== '..' && !path.isAbsolute(relative));
}

function isProblemIndex(problemsRoot, filePath) {
  const parts = path.relative(problemsRoot, filePath).split(path.sep);
  return parts.length === 3 && parts[2] === 'index.md';
}

function candidateOrder(root, a, b) {
  if (a.mtimeMs !== b.mtimeMs) return b.mtimeMs - a.mtimeMs;
  const aPath = normalizedRelativePath(root, a.path);
  const bPath = normalizedRelativePath(root, b.path);
  if (aPath < bPath) return -1;
  if (aPath > bPath) return 1;
  return 0;
}

function loggerFor(value) {
  if (value === false) return { info() {}, error() {} };
  if (value) {
    return {
      info: value.info?.bind(value) || value.log?.bind(value) || (() => {}),
      error: value.error?.bind(value) || value.warn?.bind(value) || (() => {}),
    };
  }
  return { info: console.log, error: console.error };
}

function conciseError(error) {
  return String(error?.message || error).split('\n')[0];
}

export class PreviewWatcher {
  #active;
  #closed = false;
  #logger;
  #pending = new Map();
  #processing = Promise.resolve();
  #stabilityMs;
  #timer = null;
  #watcher;

  constructor(active, opts = {}) {
    this.#active = active;
    this.#logger = loggerFor(opts.logger);
    this.#stabilityMs = opts.stabilityMs ?? 500;
    this.root = path.resolve(opts.projectRoot || active.snapshot.preview.root);
    this.problemsRoot = path.join(this.root, 'problems');

    const watchFactory = opts.watchFactory || ((watchPath, watchOptions) =>
      chokidar.watch(watchPath, watchOptions));
    this.#watcher = watchFactory(this.problemsRoot, {
      ignoreInitial: true,
      persistent: true,
    });
    this.#watcher.on('all', (event, filePath) => this.#onEvent(event, filePath));
    this.#watcher.on('error', (error) => {
      this.#logger.error(`[preview] Watch error: ${conciseError(error)}`);
    });
  }

  #onEvent(event, filePath) {
    if (this.#closed || !FILE_EVENTS.has(event)) return;
    const absolutePath = path.resolve(filePath);
    const snapshot = this.#active.snapshot;
    const relevant = isProblemIndex(this.problemsRoot, absolutePath)
      || isInside(snapshot.preview.problemDir, absolutePath);
    if (!relevant) return;

    this.#pending.set(absolutePath, event);
    if (this.#timer) clearTimeout(this.#timer);
    this.#timer = setTimeout(() => void this.flush(), this.#stabilityMs);
  }

  async flush() {
    if (this.#timer) clearTimeout(this.#timer);
    this.#timer = null;
    if (this.#pending.size === 0) return this.#processing;

    const batch = Array.from(this.#pending, ([filePath, event]) => ({ filePath, event }));
    this.#pending.clear();
    this.#processing = this.#processing
      .then(() => this.#process(batch))
      .catch((error) => {
        this.#logger.error(`[preview] Refresh failed: ${conciseError(error)}`);
      });
    return this.#processing;
  }

  async #process(batch) {
    const indexEvents = batch.filter(({ filePath }) =>
      isProblemIndex(this.problemsRoot, filePath));
    const candidates = [];

    for (const item of indexEvents) {
      try {
        candidates.push({
          ...item,
          path: item.filePath,
          mtimeMs: fs.statSync(item.filePath).mtimeMs,
        });
      } catch (error) {
        this.#reportRejected(item.filePath, error);
      }
    }
    candidates.sort((a, b) => candidateOrder(this.root, a, b));

    for (const candidate of candidates) {
      try {
        const preview = resolvePreviewProblemFromIndex(candidate.path, {
          projectRoot: this.root,
        });
        const update = this.#active.commit(createPreviewSnapshot(preview), {
          path: candidate.path,
          reason: candidate.event,
        });
        this.#reportUpdate(update, candidate.path);
        return;
      } catch (error) {
        this.#reportRejected(candidate.path, error);
      }
    }

    const current = this.#active.snapshot;
    const activeChange = batch.find(({ filePath }) =>
      path.basename(filePath) !== 'index.md'
      && isInside(current.preview.problemDir, filePath));
    if (!activeChange) return;

    try {
      const preview = resolvePreviewProblemFromIndex(current.preview.indexPath, {
        projectRoot: this.root,
      });
      const update = this.#active.commit(createPreviewSnapshot(preview), {
        path: activeChange.filePath,
        reason: activeChange.event,
      });
      this.#reportUpdate(update, activeChange.filePath);
    } catch (error) {
      this.#reportRejected(activeChange.filePath, error);
    }
  }

  #reportUpdate(update, filePath) {
    const action = update.type === 'switch' ? 'Switched' : 'Reloaded';
    this.#logger.info(
      `[preview] ${action} ${update.url} (${normalizedRelativePath(this.root, filePath)})`,
    );
  }

  #reportRejected(filePath, error) {
    this.#logger.error(
      `[preview] Kept last valid page; ${normalizedRelativePath(this.root, filePath)}: ${conciseError(error)}`,
    );
  }

  async close() {
    if (this.#closed) return;
    this.#closed = true;
    if (this.#timer) clearTimeout(this.#timer);
    this.#timer = null;
    this.#pending.clear();
    await this.#processing;
    await this.#watcher.close();
  }
}

export function createPreviewWatcher(active, opts = {}) {
  return new PreviewWatcher(active, opts);
}
