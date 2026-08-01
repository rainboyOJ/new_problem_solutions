export default class LruCache {
  constructor(limit = 200) {
    if (!Number.isInteger(limit) || limit < 1) {
      throw new TypeError('LRU cache limit must be a positive integer');
    }
    this.limit = limit;
    this.items = new Map();
  }

  get(key) {
    if (!this.items.has(key)) return undefined;
    const value = this.items.get(key);
    this.items.delete(key);
    this.items.set(key, value);
    return value;
  }

  set(key, value) {
    this.items.delete(key);
    this.items.set(key, value);
    while (this.items.size > this.limit) {
      this.items.delete(this.items.keys().next().value);
    }
    return value;
  }

  clear() {
    this.items.clear();
  }

  get size() {
    return this.items.size;
  }
}
