const DEFAULT_TIMEOUT_MS = 2_000;
const DEFAULT_CACHE_TTL_MS = 60_000;

// 两本 rbook 书的站点短名。题解里的 id 一律写成 `<site>:<id>`，因为两本书
// 有 4 对同名不同文的 id（base、mst、minimal-string、other），裸 id 无法区分。
export const RBOOK_SITES = ['rbook1', 'rbook2'];
const RBOOK_SITE_SET = new Set(RBOOK_SITES);

// 文章 id 只允许字母数字开头，后接字母数字、点、下划线、连字符。
// 不允许冒号（会和站点前缀冲突）、斜杠和井号（那是 url 形态的事）。
const ARTICLE_ID_PATTERN = /^[A-Za-z0-9][A-Za-z0-9._-]*$/;

function withoutTrailingSlash(value) {
  return String(value).replace(/\/+$/, '');
}

function defaultRbook2ApiBaseUrl() {
  // In production the app is a native systemd service on the same host as
  // rbook.service, which listens on 127.0.0.1:3000. The old default here was
  // the docker-compose service name "rbook", which no longer resolves.
  return process.env.RBOOK_API_BASE_URL
    || (process.env.NODE_ENV === 'production' ? 'http://127.0.0.1:3000' : 'https://rbook2.roj.ac.cn');
}

function defaultRbook2PublicBaseUrl() {
  return process.env.RBOOK_PUBLIC_BASE_URL || 'https://rbook2.roj.ac.cn';
}

function defaultRbook1PublicBaseUrl() {
  return process.env.RBOOK1_PUBLIC_BASE_URL || 'https://rbook.roj.ac.cn';
}

function defaultRbook1CatalogUrl() {
  return process.env.RBOOK1_CATALOG_URL || `${withoutTrailingSlash(defaultRbook1PublicBaseUrl())}/catalog.json`;
}

/**
 * 把 `rbook2:binary-search` 拆成站点与文章 id。裸 id、未知站点、非法 id 都返回 null。
 */
export function parseRbookRef(value) {
  if (typeof value !== 'string') return null;
  const separator = value.indexOf(':');
  if (separator <= 0) return null;

  const site = value.slice(0, separator);
  const id = value.slice(separator + 1);
  if (!RBOOK_SITE_SET.has(site) || !ARTICLE_ID_PATTERN.test(id)) return null;

  return { site, id };
}

function toArticleMap(payload, publicBaseUrl, site) {
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
      site,
      id: item.id,
      title: item.title,
      url: new URL(item.url, publicBaseUrl).toString(),
    });
  }

  return articles;
}

/**
 * 单本 rbook 书的目录缓存。
 *
 * rbook2（rbook_nunjucks）是 Node 服务，有 `/api/catalog`；rbook1（newRbook_ejs）
 * 是纯静态站，目录来自构建期生成的 `/catalog.json`。两者条目形状一致，
 * 所以只有取数地址不同。
 */
class SiteCatalog {
  constructor(options) {
    this.site = options.site;
    this.catalogUrl = options.catalogUrl;
    this.publicBaseUrl = withoutTrailingSlash(options.publicBaseUrl);
    this.timeoutMs = options.timeoutMs;
    this.cacheTtlMs = options.cacheTtlMs;
    this.fetchImpl = options.fetchImpl;
    this.logger = options.logger;
    this.catalog = null;
    this.fetchedAt = 0;
    this.pending = null;
  }

  async load({ strict = false } = {}) {
    if (this.catalog && Date.now() - this.fetchedAt < this.cacheTtlMs) return this.catalog;
    if (this.pending) return this.pending;

    this.pending = this.refresh({ strict });
    try {
      return await this.pending;
    } finally {
      this.pending = null;
    }
  }

  async refresh({ strict }) {
    try {
      const response = await this.fetchImpl(this.catalogUrl, {
        signal: AbortSignal.timeout(this.timeoutMs),
      });
      if (!response.ok) {
        throw new Error(`catalog request failed with HTTP ${response.status}`);
      }

      const catalog = toArticleMap(await response.json(), this.publicBaseUrl, this.site);
      this.catalog = catalog;
      this.fetchedAt = Date.now();
      return catalog;
    } catch (error) {
      if (strict) {
        const failure = new Error(`RBook 站点 ${this.site} 不可用：${error.message}（${this.catalogUrl}）`);
        failure.cause = error;
        failure.site = this.site;
        throw failure;
      }

      if (this.catalog) {
        this.logger.warn?.({ err: error, site: this.site }, 'RBook catalog refresh failed; using the last successful catalog');
        return this.catalog;
      }

      this.logger.warn?.({ err: error, site: this.site }, 'RBook catalog fetch failed; hiding RBook article links');
      return new Map();
    }
  }
}

/**
 * 题解页与 API 共用的 rbook 文章解析器。
 *
 * `showAtRbook` 与 `rbookLinks` 的元素都已经是 `<site>:<id>` 形式（由
 * lib/problem.js 的归一化保证），这里只负责查目录、拼绝对 URL。
 * 目录按站点分别缓存 60 秒，单站故障时退回上一次成功的快照；从没成功过就
 * 返回空表，页面少一块而不是整页 500。
 */
export class RbookArticleService {
  constructor(options = {}) {
    this.logger = options.logger || console;

    const shared = {
      timeoutMs: options.timeoutMs ?? DEFAULT_TIMEOUT_MS,
      cacheTtlMs: options.cacheTtlMs ?? DEFAULT_CACHE_TTL_MS,
      fetchImpl: options.fetchImpl || globalThis.fetch,
      logger: this.logger,
    };

    this.sites = new Map([
      ['rbook1', new SiteCatalog({
        site: 'rbook1',
        catalogUrl: options.rbook1CatalogUrl || defaultRbook1CatalogUrl(),
        publicBaseUrl: options.rbook1PublicBaseUrl || defaultRbook1PublicBaseUrl(),
        ...shared,
      })],
      ['rbook2', new SiteCatalog({
        site: 'rbook2',
        catalogUrl: `${withoutTrailingSlash(options.apiBaseUrl || defaultRbook2ApiBaseUrl())}/api/catalog?compact=true&includeHidden=true`,
        publicBaseUrl: options.publicBaseUrl || defaultRbook2PublicBaseUrl(),
        ...shared,
      })],
    ]);
  }

  /** 把一组 `<site>:<id>` 解析成文章；查不到的不出现在结果里。 */
  async resolveRefs(refs) {
    const parsed = [];
    for (const ref of Array.isArray(refs) ? refs : []) {
      const item = parseRbookRef(ref);
      if (!item) {
        this.logger.warn?.({ ref }, 'RBook reference is not a valid <site>:<id> pair');
        continue;
      }
      if (!parsed.some((seen) => seen.ref === ref)) parsed.push({ ref, ...item });
    }

    const bySite = new Map();
    for (const item of parsed) {
      if (!bySite.has(item.site)) bySite.set(item.site, []);
      bySite.get(item.site).push(item);
    }

    const resolved = new Map();
    for (const [site, items] of bySite) {
      const catalog = await this.sites.get(site).load();
      for (const item of items) {
        const article = catalog.get(item.id);
        if (article) resolved.set(item.ref, article);
      }
    }

    return resolved;
  }

  /** showAtRbook 用：按录入顺序返回已解析的文章，重复项只出现一次，查不到的跳过。 */
  async getArticles(refs) {
    const list = Array.isArray(refs) ? refs : [];
    const unique = [...new Set(list)];
    const resolved = await this.resolveRefs(unique);
    const articles = [];
    for (const ref of unique) {
      const article = resolved.get(ref);
      if (article) {
        articles.push(article);
        continue;
      }
      if (parseRbookRef(ref)) {
        this.logger.warn?.({ ref }, 'RBook article referenced by showAtRbook was not found');
      }
    }
    return articles;
  }

  /**
   * rbookLinks 用：id 形态查目录，url 形态直接用 label 当标题。
   * 结果保持 frontmatter 里的数组顺序，`reason` 原样带出给页面展示。
   */
  async getRbookLinks(links) {
    const list = Array.isArray(links)
      ? links.filter((link) => link && typeof link === 'object')
      : [];

    const resolved = await this.resolveRefs(
      list.filter((link) => typeof link.id === 'string').map((link) => link.id),
    );

    const result = [];
    for (const link of list) {
      if (typeof link.id === 'string') {
        const article = resolved.get(link.id);
        if (!article) {
          this.logger.warn?.({ ref: link.id }, 'RBook article referenced by rbookLinks was not found');
          continue;
        }
        result.push({ ...article, reason: link.reason || '' });
        continue;
      }

      if (typeof link.url === 'string' && link.url !== '') {
        result.push({
          site: null,
          id: null,
          title: link.label || link.url,
          url: link.url,
          reason: link.reason || '',
        });
      }
    }

    return result;
  }

  /**
   * 校验用：严格要求这些站点的目录可用，拿不到就抛错（供 verify:push 使用）。
   * `sites` 只应包含仓库里真正被引用到的站点。
   */
  async assertSitesAvailable(sites) {
    const wanted = [...new Set(sites)].filter((site) => RBOOK_SITE_SET.has(site));
    for (const site of wanted) {
      await this.sites.get(site).load({ strict: true });
    }
    return wanted;
  }
}
