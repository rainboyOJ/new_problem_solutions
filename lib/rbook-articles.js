const DEFAULT_TIMEOUT_MS = 2_000;
const DEFAULT_CACHE_TTL_MS = 60_000;

function withoutTrailingSlash(value) {
  return String(value).replace(/\/+$/, '');
}

function defaultApiBaseUrl() {
  return process.env.RBOOK_API_BASE_URL
    || (process.env.NODE_ENV === 'production' ? 'http://rbook:3000' : 'https://rbook2.roj.ac.cn');
}

function defaultPublicBaseUrl() {
  return process.env.RBOOK_PUBLIC_BASE_URL || 'https://rbook2.roj.ac.cn';
}

function toArticleMap(payload, publicBaseUrl) {
  const articles = new Map();
  if (!payload || !Array.isArray(payload.items)) return articles;

  for (const item of payload.items) {
    if (
      !item
      || typeof item.id !== 'string'
      || typeof item.title !== 'string'
      || typeof item.url !== 'string'
      || !item.url.startsWith('/')
      || item.url.startsWith('//')
    ) continue;

    articles.set(item.id, {
      id: item.id,
      title: item.title,
      url: new URL(item.url, publicBaseUrl).toString(),
    });
  }

  return articles;
}

export class RbookArticleService {
  constructor(options = {}) {
    this.apiBaseUrl = withoutTrailingSlash(options.apiBaseUrl || defaultApiBaseUrl());
    this.publicBaseUrl = withoutTrailingSlash(options.publicBaseUrl || defaultPublicBaseUrl());
    this.timeoutMs = options.timeoutMs ?? DEFAULT_TIMEOUT_MS;
    this.cacheTtlMs = options.cacheTtlMs ?? DEFAULT_CACHE_TTL_MS;
    this.fetchImpl = options.fetchImpl || globalThis.fetch;
    this.logger = options.logger || console;
    this.catalog = null;
    this.catalogFetchedAt = 0;
    this.catalogPromise = null;
  }

  async getArticles(articleIds) {
    const ids = Array.isArray(articleIds)
      ? articleIds.filter((id) => typeof id === 'string' && id.length > 0)
      : [];
    if (ids.length === 0) return [];

    const catalog = await this.getCatalog();
    return ids.flatMap((id) => {
      const article = catalog.get(id);
      if (article) return [article];
      this.logger.warn?.({ articleId: id }, 'RBook article referenced by showAtRbook was not found');
      return [];
    });
  }

  async getCatalog() {
    if (this.catalog && Date.now() - this.catalogFetchedAt < this.cacheTtlMs) return this.catalog;
    if (this.catalogPromise) return this.catalogPromise;

    this.catalogPromise = this.refreshCatalog();
    try {
      return await this.catalogPromise;
    } finally {
      this.catalogPromise = null;
    }
  }

  async refreshCatalog() {
    try {
      const response = await this.fetchImpl(
        `${this.apiBaseUrl}/api/catalog?compact=true&includeHidden=true`,
        { signal: AbortSignal.timeout(this.timeoutMs) },
      );
      if (!response.ok) throw new Error(`RBook catalog request failed with HTTP ${response.status}`);

      const catalog = toArticleMap(await response.json(), this.publicBaseUrl);
      this.catalog = catalog;
      this.catalogFetchedAt = Date.now();
      return catalog;
    } catch (error) {
      if (this.catalog) {
        this.logger.warn?.({ err: error }, 'RBook catalog refresh failed; using the last successful catalog');
        return this.catalog;
      }

      this.logger.warn?.({ err: error }, 'RBook catalog fetch failed; hiding RBook article links');
      return new Map();
    }
  }
}
