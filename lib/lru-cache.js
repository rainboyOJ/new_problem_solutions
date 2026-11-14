// Budget retained text at two bytes per UTF-16 code unit, plus entry overhead.
// Object payloads in the render cache contain JSON data, not renderer instances.
//
// Size is measured by walking the payload instead of JSON.stringify()ing it. The
// render cache stores whole HTML pages, so serialising every value just to weigh
// it costs milliseconds and allocates a temporary string the size of the page —
// the very pressure this cache exists to bound. Walking only reads `.length`.
//
// Depth and cycle guards keep pathological payloads cheap: a metered worst case
// is a constant, and undercounting merely evicts sooner than strictly needed.
const MAX_DEPTH = 4;
const NODE_OVERHEAD = 16;

function estimateBytes(value, key) {
  const seen = new Set();

  function measure(node, depth) {
    if (typeof node === 'string') return 2 * node.length;
    if (node === null || node === undefined) return 0;
    if (typeof node === 'number' || typeof node === 'boolean') return 8;
    if (typeof node !== 'object') return NODE_OVERHEAD;
    if (depth >= MAX_DEPTH || seen.has(node)) return NODE_OVERHEAD;

    seen.add(node);
    let total = NODE_OVERHEAD;
    if (Array.isArray(node)) {
      for (const item of node) total += measure(item, depth + 1);
    } else {
      for (const [property, item] of Object.entries(node)) {
        total += 2 * property.length + measure(item, depth + 1);
      }
    }
    seen.delete(node);
    return total;
  }

  return 2 * String(key).length + 128 + measure(value, 0);
}

export default class LruCache {
  constructor(limit = 200, options = {}) {
    if (!Number.isInteger(limit) || limit < 1) {
      throw new TypeError('LRU cache limit must be a positive integer');
    }
    this.limit = limit;
    this.maxBytes = options.maxBytes ?? Infinity;
    this.maxEntryBytes = options.maxEntryBytes ?? this.maxBytes;
    for (const budget of [this.maxBytes, this.maxEntryBytes]) {
      if (!(budget > 0) || (budget !== Infinity && !Number.isSafeInteger(budget))) {
        throw new TypeError('LRU byte budgets must be positive integers');
      }
    }
    this.sizeOf = options.sizeOf ?? estimateBytes;
    this.totalBytes = 0;
    this.items = new Map();
  }

  get(key) {
    if (!this.items.has(key)) return undefined;
    const entry = this.items.get(key);
    this.items.delete(key);
    this.items.set(key, entry);
    return entry.value;
  }

  set(key, value) {
    // Measuring must never be able to fail a render. A cache that cannot weigh a
    // value simply declines to retain it; throwing here would surface as a
    // rendering error in callers that wrap set() in a try/catch.
    let bytes = 0;
    if (this.maxBytes !== Infinity || this.maxEntryBytes !== Infinity) {
      try {
        bytes = this.sizeOf(value, key);
      } catch {
        bytes = Infinity;
      }
      if (!Number.isSafeInteger(bytes) || bytes < 0) bytes = Infinity;
    }
    this.delete(key);
    // Still return an oversized render to the caller; do not retain it or flush
    // useful small entries to make room for something that can never fit.
    if (bytes > this.maxEntryBytes || bytes > this.maxBytes) return value;
    this.items.set(key, { value, bytes });
    this.totalBytes += bytes;
    while (this.items.size > this.limit || this.totalBytes > this.maxBytes) {
      this.delete(this.items.keys().next().value);
    }
    return value;
  }

  delete(key) {
    const entry = this.items.get(key);
    if (!entry) return false;
    this.totalBytes -= entry.bytes;
    return this.items.delete(key);
  }

  clear() {
    this.items.clear();
    this.totalBytes = 0;
  }

  get bytes() {
    return this.totalBytes;
  }

  get size() {
    return this.items.size;
  }
}
