import chokidar from 'chokidar';
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
  return relative === '' || (
    !relative.startsWith(`..${path.sep}`)
    && relative !== '..'
    && !path.isAbsolute(relative)
  );
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
  #closingWatchers = new Set();
  #logger;
  #pending = new Map();
  #processing = Promise.resolve();
  #stabilityMs;
  #timer = null;
  #unsubscribe;
  #watcher = null;
  #watchFactory;
  #watchedDirectory = null;

  constructor(active, opts = {}) {
    this.#active = active;
    this.#logger = loggerFor(opts.logger);
    this.#stabilityMs = opts.stabilityMs ?? 500;
    this.root = path.resolve(opts.projectRoot || active.snapshot.preview.root);
    this.#watchFactory = opts.watchFactory || ((watchPath, watchOptions) =>
      chokidar.watch(watchPath, watchOptions));

    this.#replaceWatcher(active.snapshot.preview.problemDir);
    this.#unsubscribe = active.subscribe((update) => {
      if (update.type !== 'switch') return;
      try {
        this.#replaceWatcher(this.#active.snapshot.preview.problemDir, update);
      } catch (error) {
        this.#logger.error(`[preview] Cannot switch watcher: ${conciseError(error)}`);
      }
    });
  }

  get watchedDirectory() {
    return this.#watchedDirectory;
  }

  #replaceWatcher(problemDir, update = null) {
    const nextDirectory = path.resolve(problemDir);
    if (this.#closed || nextDirectory === this.#watchedDirectory) return;

    const nextWatcher = this.#watchFactory(nextDirectory, {
      ignoreInitial: true,
      persistent: true,
    });
    const previousWatcher = this.#watcher;

    this.#clearPending();
    this.#watcher = nextWatcher;
    this.#watchedDirectory = nextDirectory;
    nextWatcher.on('all', (event, filePath) => {
      this.#onEvent(nextWatcher, nextDirectory, event, filePath);
    });
    nextWatcher.on('error', (error) => {
      if (nextWatcher !== this.#watcher) return;
      this.#logger.error(`[preview] Watch error: ${conciseError(error)}`);
    });

    if (previousWatcher) this.#retireWatcher(previousWatcher);

    if (update) {
      this.#logger.info(
        `[preview] Activated ${update.url} from ${update.path}; watching ${normalizedRelativePath(this.root, nextDirectory)}`,
      );
    }
  }

  #retireWatcher(watcher) {
    const closing = Promise.resolve()
      .then(() => watcher.close())
      .catch((error) => {
        this.#logger.error(`[preview] Cannot close old watcher: ${conciseError(error)}`);
      })
      .finally(() => this.#closingWatchers.delete(closing));
    this.#closingWatchers.add(closing);
  }

  #onEvent(source, watchedDirectory, event, filePath) {
    if (
      this.#closed
      || source !== this.#watcher
      || watchedDirectory !== this.#watchedDirectory
      || !FILE_EVENTS.has(event)
    ) return;

    const absolutePath = path.resolve(filePath);
    if (!isInside(watchedDirectory, absolutePath)) return;

    this.#pending.set(absolutePath, event);
    if (this.#timer) clearTimeout(this.#timer);
    this.#timer = setTimeout(() => void this.flush(), this.#stabilityMs);
  }

  #clearPending() {
    if (this.#timer) clearTimeout(this.#timer);
    this.#timer = null;
    this.#pending.clear();
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
    const current = this.#active.snapshot;
    const activeChange = batch.find(({ filePath }) =>
      isInside(current.preview.problemDir, filePath));
    if (!activeChange) return;

    try {
      const preview = resolvePreviewProblemFromIndex(current.preview.indexPath, {
        projectRoot: this.root,
      });
      const update = this.#active.commit(createPreviewSnapshot(preview), {
        path: activeChange.filePath,
        reason: activeChange.event,
      });
      this.#logger.info(
        `[preview] Reloaded ${update.url} (${normalizedRelativePath(this.root, activeChange.filePath)})`,
      );
    } catch (error) {
      this.#logger.error(
        `[preview] Kept last valid page; ${normalizedRelativePath(this.root, activeChange.filePath)}: ${conciseError(error)}`,
      );
    }
  }

  async close() {
    if (this.#closed) return;
    this.#closed = true;
    this.#unsubscribe?.();
    this.#unsubscribe = null;
    this.#clearPending();
    await this.#processing;

    if (this.#watcher) this.#retireWatcher(this.#watcher);
    this.#watcher = null;
    this.#watchedDirectory = null;
    await Promise.all(this.#closingWatchers);
  }
}

export function createPreviewWatcher(active, opts = {}) {
  return new PreviewWatcher(active, opts);
}
