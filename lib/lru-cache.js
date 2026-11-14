// Budget retained text at two bytes per UTF-16 code unit, plus entry overhead.
// Object payloads in the render cache contain JSON data, not renderer instances.
function estimateBytes(value, key) {
  const text = typeof value === 'string' ? value : JSON.stringify(value) ?? '';
  return 2 * (String(key).length + text.length) + 128;
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
    const bytes = this.maxBytes === Infinity && this.maxEntryBytes === Infinity
      ? 0 : this.sizeOf(value, key);
    if (!Number.isSafeInteger(bytes) || bytes < 0) {
      throw new TypeError('LRU entry size must be a non-negative integer');
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
