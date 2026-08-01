import fs from 'fs';
import path from 'path';
import LruCache from './lru-cache.js';

const AVAILABLE_STATES = new Set(['healthy', 'degraded']);
const CONTENT_READY_STATES = new Set(['healthy', 'degraded', 'switching']);

export class ContentRenderError extends Error {
  constructor(type, key, cause) {
    super(`Unable to render ${type}: ${key}`, { cause });
    this.name = 'ContentRenderError';
    this.type = type;
    this.key = key;
  }
}

export default class ContentService {
  constructor(options) {
    this.problemManager = options.problemManager;
    this.problemSetManager = options.problemSetManager;
    this.revisionPath = options.revisionPath
      || process.env.CONTENT_REVISION_PATH
      || path.resolve('.runtime/content-revision.json');
    this.revisionProvider = options.revisionProvider || (() => this.readRevisionHandoff());
    this.snapshotBuilder = options.snapshotBuilder || (() => this.buildSnapshot());
    this.refreshTimeoutMs = options.refreshTimeoutMs ?? 30_000;
    this.drainTimeoutMs = options.drainTimeoutMs ?? 10_000;
    this.logger = options.logger || console;
    this.cache = new LruCache(options.cacheLimit ?? 200);
    this.state = 'initializing';
    this.targetRevision = null;
    this.activeRevision = null;
    this.lastSuccessfulRevision = null;
    this.errors = [];
    this.inFlightRequests = 0;
    this.lastRefreshAt = null;
    this.lastSuccessfulAt = null;
    this.pendingRefresh = null;
    this.refreshPromise = null;
    this.drainWaiters = new Set();
  }

  async initialize() {
    return this.requestRefresh();
  }

  readRevisionHandoff() {
    try {
      const data = JSON.parse(fs.readFileSync(this.revisionPath, 'utf8'));
      return typeof data.targetRevision === 'string' && data.targetRevision
        ? data.targetRevision
        : null;
    } catch (error) {
      if (error.code !== 'ENOENT') {
        this.logger.warn?.(`Unable to read content revision handoff: ${error.message}`);
      }
      return process.env.CONTENT_REVISION || null;
    }
  }

  buildSnapshot() {
    const problems = this.problemManager.buildCatalog();
    const problemSets = this.problemSetManager.buildCatalog();
    return {
      problems,
      problemSets,
      errors: [...problems.errors, ...problemSets.errors],
    };
  }

  requestRefresh(revision = this.revisionProvider()) {
    this.pendingRefresh = { revision };
    if (!this.refreshPromise) {
      this.refreshPromise = this.runRefreshLoop().finally(() => {
        this.refreshPromise = null;
      });
    }
    return this.refreshPromise;
  }

  async runRefreshLoop() {
    let result;
    while (this.pendingRefresh) {
      const request = this.pendingRefresh;
      this.pendingRefresh = null;
      result = await this.performRefresh(request.revision);
    }
    return result;
  }

  async performRefresh(revision) {
    const wasInitializing = this.state === 'initializing';
    this.targetRevision = revision;
    if (!wasInitializing) this.state = 'switching';
    const startedAt = Date.now();
    let timer;

    try {
      const timeout = new Promise((_, reject) => {
        timer = setTimeout(() => reject(new Error('Content refresh timed out')), this.refreshTimeoutMs);
      });
      const snapshot = await Promise.race([
        Promise.resolve().then(() => this.snapshotBuilder()),
        timeout,
      ]);
      if (Date.now() - startedAt > this.refreshTimeoutMs) {
        throw new Error('Content refresh timed out');
      }

      this.problemManager.activateCatalog(snapshot.problems);
      this.problemSetManager.activateCatalog(snapshot.problemSets);
      this.cache.clear();
      this.errors = [...snapshot.errors];
      this.activeRevision = revision;
      this.lastSuccessfulRevision = revision;
      this.state = this.errors.length > 0 ? 'degraded' : 'healthy';
      this.lastRefreshAt = new Date().toISOString();
      this.lastSuccessfulAt = this.lastRefreshAt;

      for (const error of this.errors) {
        this.logger.error?.(`[content:${error.type}] ${error.key}: ${error.message}`);
      }
      return this.publicHealth();
    } catch (error) {
      this.problemManager.clearCatalog();
      this.problemSetManager.clearCatalog();
      this.cache.clear();
      this.errors = [{
        type: 'catalog',
        key: 'content-roots',
        path: null,
        message: error.message,
      }];
      this.activeRevision = null;
      this.state = 'unavailable';
      this.lastRefreshAt = new Date().toISOString();
      this.logger.error?.(`[content:catalog] ${error.stack || error.message}`);
      return this.publicHealth();
    } finally {
      clearTimeout(timer);
    }
  }

  enterSwitching() {
    if (this.state === 'healthy' || this.state === 'degraded' || this.state === 'unavailable') {
      this.state = 'switching';
      return true;
    }
    return this.state === 'switching';
  }

  async waitForDrain(timeoutMs = this.drainTimeoutMs) {
    if (this.inFlightRequests === 0) return true;
    return new Promise((resolve) => {
      const waiter = () => {
        clearTimeout(timer);
        resolve(true);
      };
      const timer = setTimeout(() => {
        this.drainWaiters.delete(waiter);
        resolve(false);
      }, timeoutMs);
      this.drainWaiters.add(waiter);
    });
  }

  acquireRequest() {
    if (!AVAILABLE_STATES.has(this.state)) return null;
    this.inFlightRequests += 1;
    let released = false;
    return () => {
      if (released) return;
      released = true;
      this.inFlightRequests = Math.max(0, this.inFlightRequests - 1);
      if (this.inFlightRequests === 0) {
        for (const waiter of this.drainWaiters) waiter();
        this.drainWaiters.clear();
      }
    };
  }

  render(type, key, factory, variant = 'default') {
    const cacheKey = `${type}:${key}:${variant}`;
    const cached = this.cache.get(cacheKey);
    if (cached !== undefined) return cached;

    try {
      return this.cache.set(cacheKey, factory());
    } catch (error) {
      this.quarantine(type, key, error);
      throw new ContentRenderError(type, key, error);
    }
  }

  quarantine(type, key, error) {
    if (type === 'problem') {
      const separator = key.indexOf('/');
      this.problemManager.remove(key.slice(0, separator), key.slice(separator + 1));
    } else if (type === 'problem-set') {
      this.problemSetManager.remove(key);
    }
    this.cache.clear();
    this.errors.push({
      type,
      key,
      path: null,
      message: error.message,
    });
    if (this.activeRevision !== null) this.state = 'degraded';
    this.logger.error?.(`[content:${type}] lazy render failed for ${key}: ${error.stack || error.message}`);
  }

  publicHealth() {
    return {
      state: this.state,
      ready: CONTENT_READY_STATES.has(this.state),
      targetRevision: this.targetRevision,
      activeRevision: this.activeRevision,
      lastSuccessfulRevision: this.lastSuccessfulRevision,
      problemCount: this.problemManager.getAll().length,
      problemSetCount: this.problemSetManager.list().length,
      errorCount: this.errors.length,
      inFlightRequests: this.inFlightRequests,
      cacheEntries: this.cache.size,
      lastRefreshAt: this.lastRefreshAt,
      lastSuccessfulAt: this.lastSuccessfulAt,
    };
  }

  detailedHealth() {
    return {
      ...this.publicHealth(),
      errors: this.errors.map((error) => ({ ...error })),
    };
  }
}
