import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import yaml from 'js-yaml';
import * as matter from 'gray-matter';
import { scanAiNotes } from './ai-notes.js';

// ESM 下没有 __dirname，用 import.meta.url 还原出本文件所在目录。
const __dirname = path.dirname(fileURLToPath(import.meta.url));

const __workdir = path.resolve();
const __problemdir = path.join(__workdir, 'problems');
const GRAPH_TAG_COLORS = [
  '#2563eb',
  '#16a34a',
  '#dc2626',
  '#9333ea',
  '#ea580c',
  '#0891b2',
  '#4f46e5',
  '#be123c',
  '#0f766e',
  '#ca8a04',
  '#7c3aed',
  '#475569',
];

// 难度档位以 lib/difficulty.json 为唯一来源：前端排序、视图徽章、Python 校验脚本
// 全部从它读取，避免各写一套导致漂移。顺序即难度序（由易到难）。
const DIFFICULTY_FILE = path.join(__dirname, 'difficulty.json');
const DIFFICULTY_TABLE = JSON.parse(fs.readFileSync(DIFFICULTY_FILE, 'utf8')).values;

// 只有 ranked 的条目构成难度序；「未知」是缺省标记，不参与排序。
export const DIFFICULTY_ORDER = DIFFICULTY_TABLE
  .filter((item) => item.ranked !== false)
  .map((item) => item.value);

// 难度值 → CSS 徽章后缀（对应 public/stylesheets/style.css 里的 .difficulty-*）。
export const DIFFICULTY_SLUG = new Map(
  DIFFICULTY_TABLE.map((item) => [item.value, item.slug]),
);

// 中文档位 → 代表 Codeforces rating（用于跨 OJ 混排；未知档位没有代表值）。
const DIFFICULTY_RATING = new Map(
  DIFFICULTY_TABLE
    .filter((item) => Number.isFinite(item.rating))
    .map((item) => [item.value, item.rating]),
);

// 只有带代表 rating 的档位参与「数字归档上色」，按 rating 升序。
const RATED_TIERS = DIFFICULTY_TABLE
  .filter((item) => item.ranked !== false && Number.isFinite(item.rating))
  .sort((a, b) => a.rating - b.rating);

/**
 * 从 difficulty 取出可比较的 rating 数值。
 * - Codeforces 题写的是官方 rating 数字（字符串形式，如 "1500"），直接返回；
 * - 中文档位查代表 rating 表；
 * - 未知 / 空 / 非法值返回 null（调用方自行决定排最后）。
 */
export function difficultyRating(value) {
  if (value === null || value === undefined) return null;
  const raw = String(value).trim();
  if (raw === '') return null;
  if (DIFFICULTY_RATING.has(raw)) return DIFFICULTY_RATING.get(raw);
  if (/^\d+$/.test(raw)) return Number.parseInt(raw, 10);
  return null;
}

/**
 * 任意难度 → 8 档之一的 slug（数字取「最接近代表 rating」的档位上色）。
 * 未知值（含非数字非法值）统一落到 unknown。
 */
export function difficultySlug(value) {
  if (value === null || value === undefined) return 'unknown';
  const raw = String(value).trim();
  const exact = DIFFICULTY_SLUG.get(raw);
  if (exact) return exact;
  const rating = difficultyRating(raw);
  if (rating === null || RATED_TIERS.length === 0) return 'unknown';
  let best = RATED_TIERS[0];
  let bestDistance = Math.abs(rating - best.rating);
  for (const tier of RATED_TIERS.slice(1)) {
    const distance = Math.abs(rating - tier.rating);
    if (distance < bestDistance) {
      best = tier;
      bestDistance = distance;
    }
  }
  return best.slug;
}

const DIFFICULTY_RANK = new Map(DIFFICULTY_ORDER.map((value, index) => [value, index]));
// DIFFICULTY_RANK 保留给只需要「中文档位名 → 序号」的下游（如关系批量审校）读档序用；
// 跨 OJ 难度排序请用上面的 difficultyRating()，它同时能处理数字 rating。

// rbook 文章引用统一写成 `<site>:<id>`（rbook1 = rbook.roj.ac.cn 的静态书，
// rbook2 = rbook2.roj.ac.cn 的 Node 服务）。裸 id 会在这里直接报错，因为两本书
// 有 4 对同名不同文的 id，靠猜测站点迟早出错。
const RBOOK_REF_PATTERN = /^(rbook1|rbook2):[A-Za-z0-9][A-Za-z0-9._-]*$/;
const RBOOK_LINK_KEYS = new Set(['id', 'url', 'label', 'reason']);

function normalizeRbookRef(value, fieldName) {
  if (typeof value !== 'string' || value.trim() === '') {
    throw new Error(`${fieldName} 的条目必须是非空字符串`);
  }
  const ref = value.trim();
  if (ref.includes('#')) {
    throw new Error(`${fieldName} 的 id 不能带锚点，小节定位只能写在 url 形态里（当前 ${ref}）`);
  }
  if (!RBOOK_REF_PATTERN.test(ref)) {
    throw new Error(`${fieldName} 的 id 必须写成 rbook1:<id> 或 rbook2:<id>（当前 ${ref}）`);
  }
  return ref;
}

export function normalizeShowAtRbook(value) {
  if (value === undefined || value === null) {
    return [];
  }
  if (!Array.isArray(value)) {
    throw new Error('showAtRbook must be an array of strings');
  }

  const result = [];
  const seen = new Set();
  for (const item of value) {
    const ref = normalizeRbookRef(item, 'showAtRbook');
    if (!seen.has(ref)) {
      seen.add(ref);
      result.push(ref);
    }
  }
  return result;
}

/**
 * rbookLinks：本题要先读的 rbook 知识文章。
 *
 * 元素形如 `{ id | url, label?, reason }`：id 与 url 二选一，reason 恒必填；
 * url 形态的 label 也必填（没有目录可以查标题）。同一本 rbook 书里一篇文章
 * 只能出现一次，重复的直接去重。
 */
export function normalizeRbookLinks(value) {
  if (value === undefined || value === null) return [];
  if (!Array.isArray(value)) {
    throw new Error('rbookLinks must be an array of objects');
  }

  const result = [];
  const seen = new Set();
  for (const item of value) {
    if (!item || typeof item !== 'object' || Array.isArray(item)) {
      throw new Error('rbookLinks 的每个条目必须是对象');
    }
    for (const key of Object.keys(item)) {
      if (!RBOOK_LINK_KEYS.has(key)) {
        throw new Error(`rbookLinks 不支持字段 ${key}（只允许 id / url / label / reason）`);
      }
    }

    const reason = typeof item.reason === 'string' ? item.reason.trim() : '';
    if (reason === '') {
      throw new Error('rbookLinks 的每个条目都必须写 reason');
    }

    const hasId = item.id !== undefined && item.id !== null;
    const hasUrl = item.url !== undefined && item.url !== null;
    if (hasId === hasUrl) {
      throw new Error('rbookLinks 的条目必须在 id 与 url 之间二选一');
    }

    if (hasId) {
      if (item.label !== undefined) {
        throw new Error('rbookLinks 用 id 形态时不要写 label，文章标题从 rbook 目录里取');
      }
      const ref = normalizeRbookRef(item.id, 'rbookLinks');
      if (!seen.has(ref)) {
        seen.add(ref);
        result.push({ id: ref, reason });
      }
      continue;
    }

    const url = typeof item.url === 'string' ? item.url.trim() : '';
    if (!/^https?:\/\/[^\s]+$/.test(url)) {
      throw new Error(`rbookLinks 的 url 必须是 http(s) 绝对地址（当前 ${String(item.url)}）`);
    }
    const label = typeof item.label === 'string' ? item.label.trim() : '';
    if (label === '') {
      throw new Error('rbookLinks 用 url 形态时必须写 label');
    }
    const key = `url:${url}`;
    if (!seen.has(key)) {
      seen.add(key);
      result.push({ url, label, reason });
    }
  }

  return result;
}

// 出题时间用 dateA，最后修改时间用 updatedA；老数据没有 updated 时回退到出题时间。
export function problemRecency(problem) {
  return problem?.updatedA || problem?.dateA || 0;
}

function compareStableProblemKey(a, b) {
  const dateDiff = (b.dateA || 0) - (a.dateA || 0);
  if (dateDiff !== 0) return dateDiff;

  const aKey = `${a.oj || ''}/${a.problem_id || ''}/${a.md_path || ''}`;
  const bKey = `${b.oj || ''}/${b.problem_id || ''}/${b.md_path || ''}`;
  return aKey.localeCompare(bKey);
}

// 默认顺序：最后修改时间降序；平局先比出题时间，再比 oj/题号/路径，保证顺序稳定。
export function compareProblemsByRecency(a, b) {
  const recencyDiff = problemRecency(b) - problemRecency(a);
  if (recencyDiff !== 0) return recencyDiff;

  return compareStableProblemKey(a, b);
}

export function sortProblemsForApi(problems, sort, order = 'asc') {
  if (sort !== 'difficulty') {
    return problems;
  }

  const direction = order === 'desc' ? -1 : 1;
  return [...problems].sort((a, b) => {
    const aRank = difficultyRating(a.difficulty);
    const bRank = difficultyRating(b.difficulty);

    if (aRank !== bRank) {
      if (aRank === null) return 1;
      if (bRank === null) return -1;
      return direction * (aRank - bRank);
    }

    return compareProblemsByRecency(a, b);
  });
}

export function normalizeProblemId(oj, problemId) {
  const value = String(problemId ?? '').trim();
  if (String(oj || '').toLowerCase() !== 'luogu') {
    return value;
  }

  const match = /^p?(\d+)$/i.exec(value);
  return match ? `P${match[1]}` : value;
}

class ProblemManager {
  constructor(opts = { auto_load: true }) {
    this.name = 'problems';
    this.problem_files = [];
    this.problems = [];
    this.problemMap = new Map();
    this.config = null;

    this.baseDir = opts.baseDir || __problemdir;

    if (opts.auto_load) {
      this.init();
    }

    this.config = this.load_config();
  }

  load_config(configPath = 'config.yml') {
    try {
      let configFile = path.join(__workdir, configPath);
      if (!fs.existsSync(configFile) && configPath === 'config.yml') {
        configFile = path.join(__workdir, 'book.yaml');
      }

      if (!fs.existsSync(configFile)) {
        return {};
      }

      const content = fs.readFileSync(configFile, 'utf8');
      return yaml.load(content) || {};
    } catch (error) {
      console.warn(`加载配置文件失败: ${error.message}`);
      return {};
    }
  }

  buildIndex() {
    this.problemMap.clear();
    for (const p of this.problems) {
      this.problemMap.set(this.problemKey(p.oj, p.problem_id), p);
    }
  }

  problemKey(oj, problem_id) {
    return `${String(oj || '')}/${normalizeProblemId(oj, problem_id)}`;
  }

  normalizeProblem(problem) {
    const normalized = {
      ...problem,
      favorite: problem?.favorite === true,
      favorite_reason: typeof problem?.favorite_reason === 'string'
        ? problem.favorite_reason
        : '',
      showAtRbook: normalizeShowAtRbook(problem?.showAtRbook),
      rbookLinks: normalizeRbookLinks(problem?.rbookLinks),
    };
    if (Object.prototype.hasOwnProperty.call(problem || {}, 'problem_id')) {
      normalized.problem_id = normalizeProblemId(problem.oj, problem.problem_id);
    }
    return normalized;
  }

  sortProblems() {
    this.problems.sort(compareProblemsByRecency);
  }

  find(oj, problem_id) {
    return this.problemMap.get(this.problemKey(oj, problem_id));
  }

  normalizeRelationItems(items) {
    if (!Array.isArray(items)) {
      return [];
    }

    return items
      .filter((item) => item && typeof item === 'object' && !Array.isArray(item))
      .map((item) => ({
        oj: item.oj || '',
        problem_id: normalizeProblemId(item.oj, item.problem_id || ''),
        reason: item.reason || '',
      }))
      .filter((item) => item.oj && item.problem_id);
  }

  normalizeRecommendItems(items) {
    if (!Array.isArray(items)) {
      return [];
    }

    return items
      .filter((item) => item && typeof item === 'object' && !Array.isArray(item))
      .map((item) => ({
        oj: item.oj || '',
        problem_id: normalizeProblemId(item.oj, item.problem_id || ''),
        title: item.title || '',
        url: item.url || '',
        reason: item.reason || '',
        relation: item.relation || '',
      }))
      .filter((item) => item.oj && item.problem_id);
  }

  resolveRelationItem(item) {
    const problem = this.find(item.oj, item.problem_id);

    if (problem) {
      return {
        oj: problem.oj,
        problem_id: problem.problem_id,
        title: problem.title || '',
        url: problem.url,
        reason: item.reason || '',
        missing: false,
      };
    }

    return {
      oj: item.oj,
      problem_id: item.problem_id,
      title: '',
      url: this.problem_url(item.oj, item.problem_id),
      reason: item.reason || '',
      missing: true,
    };
  }

  sameProblem(a, b) {
    return a?.oj === b?.oj && a?.problem_id === b?.problem_id;
  }

  relationKey(problem) {
    return `${problem.oj}/${problem.problem_id}`;
  }

  addResolvedRelation(list, seen, item) {
    const key = this.relationKey(item);
    if (seen.has(key)) {
      return;
    }
    seen.add(key);
    list.push(item);
  }

  getRelations(problem) {
    const predecessors = [];
    const successors = [];
    const common = [];
    const predecessorSeen = new Set();
    const successorSeen = new Set();
    const commonSeen = new Set();

    for (const item of this.normalizeRelationItems(problem?.pre)) {
      this.addResolvedRelation(predecessors, predecessorSeen, this.resolveRelationItem(item));
    }

    for (const item of this.normalizeRelationItems(problem?.common)) {
      this.addResolvedRelation(common, commonSeen, this.resolveRelationItem(item));
    }

    for (const candidate of this.problems) {
      if (this.sameProblem(candidate, problem)) {
        continue;
      }

      for (const item of this.normalizeRelationItems(candidate.pre)) {
        if (this.sameProblem(item, problem)) {
          this.addResolvedRelation(successors, successorSeen, {
            oj: candidate.oj,
            problem_id: candidate.problem_id,
            title: candidate.title || '',
            url: candidate.url,
            reason: item.reason || '',
            missing: false,
          });
        }
      }

      for (const item of this.normalizeRelationItems(candidate.common)) {
        if (this.sameProblem(item, problem)) {
          this.addResolvedRelation(common, commonSeen, {
            oj: candidate.oj,
            problem_id: candidate.problem_id,
            title: candidate.title || '',
            url: candidate.url,
            reason: item.reason || '',
            missing: false,
          });
        }
      }
    }

    return {
      predecessors,
      successors,
      common,
      hasAny: predecessors.length > 0 || successors.length > 0 || common.length > 0,
    };
  }

  getRecommendations(problem) {
    return this.normalizeRecommendItems(problem?.recommend);
  }

  getRelationGraph() {
    const nodes = [];
    const edges = [];
    const incidentKeys = new Set();
    const edgeKeys = new Set();
    const tagCounts = new Map();
    const tagColors = new Map();

    const keyOf = (item) => `${item.oj}/${item.problem_id}`;
    const ensureTagColor = (tag) => {
      if (!tagColors.has(tag)) {
        tagColors.set(tag, GRAPH_TAG_COLORS[tagColors.size % GRAPH_TAG_COLORS.length]);
      }
      return tagColors.get(tag);
    };

    for (const problem of this.problems) {
      const tags = Array.isArray(problem.tags) ? problem.tags.filter(Boolean) : [];
      const primaryTag = tags[0] || '';

      for (const tag of tags) {
        tagCounts.set(tag, (tagCounts.get(tag) || 0) + 1);
        ensureTagColor(tag);
      }

      nodes.push({
        id: keyOf(problem),
        oj: problem.oj,
        problem_id: problem.problem_id,
        label: `${problem.oj} ${problem.problem_id}`,
        title: problem.title || '',
        tags,
        primaryTag,
        difficulty: problem.difficulty || '未知',
        color: primaryTag ? ensureTagColor(primaryTag) : '#94a3b8',
        url: problem.url,
        isolated: true,
      });
    }

    const addEdge = ({ id, source, target, type, directed, reason }) => {
      if (edgeKeys.has(id)) {
        return;
      }

      edgeKeys.add(id);
      edges.push({
        id,
        source,
        target,
        type,
        directed,
        reason: reason || '',
      });
      incidentKeys.add(source);
      incidentKeys.add(target);
    };

    for (const problem of this.problems) {
      const target = keyOf(problem);

      for (const item of this.normalizeRelationItems(problem.pre)) {
        const source = keyOf(item);
        addEdge({
          id: `pre:${source}->${target}`,
          source,
          target,
          type: 'pre',
          directed: true,
          reason: item.reason,
        });
      }

      for (const item of this.normalizeRelationItems(problem.common)) {
        const first = target < keyOf(item) ? target : keyOf(item);
        const second = target < keyOf(item) ? keyOf(item) : target;
        addEdge({
          id: `common:${first}--${second}`,
          source: first,
          target: second,
          type: 'common',
          directed: false,
          reason: item.reason,
        });
      }
    }

    for (const node of nodes) {
      node.isolated = !incidentKeys.has(node.id);
    }

    const tagStats = Array.from(tagCounts.entries())
      .map(([tag, count]) => ({
        tag,
        count,
        color: ensureTagColor(tag),
      }))
      .sort((a, b) => b.count - a.count || a.tag.localeCompare(b.tag));

    return {
      nodes,
      edges,
      tagStats,
      summary: {
        nodes: nodes.length,
        edges: edges.length,
        relationNodes: nodes.filter((node) => !node.isolated).length,
        isolatedNodes: nodes.filter((node) => node.isolated).length,
        preEdges: edges.filter((edge) => edge.type === 'pre').length,
        commonEdges: edges.filter((edge) => edge.type === 'common').length,
      },
    };
  }

  problem_url(oj, id) {
    return `/problems/${oj}/${normalizeProblemId(oj, id)}`;
  }

  github_url(mdPath) {
    const repository = this.config?.github_repository || this.config?.github?.repository;
    if (!repository || !mdPath) {
      return '';
    }

    const branch = this.config?.github_branch || this.config?.github?.branch || 'main';
    const normalizedRepo = repository.replace(/\/+$/, '');
    const normalizedPath = path.posix
      .normalize(`problems/${mdPath}`)
      .split('/')
      .map((segment) => encodeURIComponent(segment))
      .join('/');

    return `${normalizedRepo}/blob/${encodeURIComponent(branch)}/${normalizedPath}`;
  }

  front_matter(md_path) {
    const raw_md = fs.readFileSync(md_path, 'utf8');
    return matter.default(raw_md).data;
  }

  md_path_to_url(md_path) {
    if (!md_path || md_path.length === 0) {
      throw new Error('md_path is empty');
    }

    const prob_front = this.front_matter(md_path);
    if (!prob_front.oj || !prob_front.problem_id) {
      throw new Error(`md_path: ${md_path} front_matter.oj or front_matter.problem_id is empty`);
    }

    return this.problem_url(prob_front.oj, prob_front.problem_id);
  }

  scanProblems() {
    const files = [];
    const ignoredDirs = new Set(['problem-analysis-workspace', 'duipai-failed']);

    const walkDir = (dir, isRoot = false) => {
      let entries;
      try {
        entries = fs.readdirSync(dir, { withFileTypes: true });
      } catch (error) {
        if (error.code === 'ENOENT' && !isRoot) {
          return;
        }
        throw error;
      }
      for (const entry of entries) {
        const fullPath = path.join(dir, entry.name);
        if (entry.isDirectory()) {
          if (ignoredDirs.has(entry.name) || entry.name.startsWith('__tmp')) {
            continue;
          }
          walkDir(fullPath);
        } else if (entry.isFile() && entry.name === 'index.md') {
          files.push(path.relative(this.baseDir, fullPath));
        }
      }
    };

    if (!fs.existsSync(this.baseDir)) {
      throw new Error(`Problem content root does not exist: ${this.baseDir}`);
    }

    walkDir(this.baseDir, true);
    return files;
  }

  buildCatalog() {
    const files = this.scanProblems();
    const problems = [];
    const errors = [];
    const keys = new Set();

    for (const md of files) {
      const mdPath = path.join(this.baseDir, md);
      try {
        const frontmatter = this.front_matter(mdPath);
        if (!frontmatter?.oj || !frontmatter?.problem_id) {
          throw new Error('frontmatter.oj and frontmatter.problem_id are required');
        }

        const key = this.problemKey(frontmatter.oj, frontmatter.problem_id);
        if (keys.has(key)) {
          throw new Error(`duplicate problem key: ${key}`);
        }
        keys.add(key);

        const aiNotes = scanAiNotes(path.dirname(mdPath));
        errors.push(...aiNotes.errors);
        problems.push(this.normalizeProblem({
          ...frontmatter,
          md_path: md,
          url: this.problem_url(frontmatter.oj, frontmatter.problem_id),
          dateA: frontmatter.date ? new Date(frontmatter.date).getTime() : 0,
          updatedA: frontmatter.updated ? new Date(frontmatter.updated).getTime() : 0,
          aiNotes: aiNotes.notes,
        }));
      } catch (error) {
        errors.push({
          type: 'problem',
          key: md,
          path: mdPath,
          message: error.message,
        });
      }
    }

    problems.sort(compareProblemsByRecency);

    return { files, problems, errors };
  }

  activateCatalog(catalog) {
    this.problem_files = [...catalog.files];
    this.problems = [...catalog.problems];
    this.buildIndex();
  }

  clearCatalog() {
    this.problem_files = [];
    this.problems = [];
    this.buildIndex();
  }

  remove(oj, problemId) {
    const key = this.problemKey(oj, problemId);
    const problem = this.problemMap.get(key);
    if (!problem) return false;
    this.problems = this.problems.filter((candidate) => candidate !== problem);
    this.problemMap.delete(key);
    return true;
  }

  init() {
    const catalog = this.buildCatalog();
    this.activateCatalog(catalog);
    for (const error of catalog.errors) {
      console.warn(`忽略无效题目 ${error.key}: ${error.message}`);
    }
    return catalog;
  }

  getAll() {
    return this.problems;
  }

  filterByTag(tag) {
    return this.problems.filter((p) => p.tags && p.tags.includes(tag));
  }

  filterByOJ(oj) {
    return this.problems.filter((p) => p.oj === oj);
  }

  search(keyword) {
    const lowerKeyword = keyword.toLowerCase();
    return this.problems.filter((p) => {
      const title = (p.title || '').toLowerCase();
      const problem_id = (p.problem_id || '').toLowerCase();
      const description = (p.description || '').toLowerCase();
      const favoriteReason = String(p.favorite_reason || '').toLowerCase();
      const tags = Array.isArray(p.tags) ? p.tags.join(' ').toLowerCase() : '';
      return title.includes(lowerKeyword)
        || problem_id.includes(lowerKeyword)
        || description.includes(lowerKeyword)
        || favoriteReason.includes(lowerKeyword)
        || tags.includes(lowerKeyword);
    });
  }

  paginate(page = 1, limit = 20) {
    const offset = (page - 1) * limit;
    const total = this.problems.length;
    const totalPages = Math.ceil(total / limit);
    const data = this.problems.slice(offset, offset + limit);

    return {
      data,
      pagination: {
        total,
        page,
        limit,
        totalPages,
      },
    };
  }

  getAllTags() {
    const tagSet = new Set();
    for (const p of this.problems) {
      if (!p.tags) {
        continue;
      }
      for (const tag of p.tags) {
        tagSet.add(tag);
      }
    }
    return Array.from(tagSet).sort();
  }

  getAllOJs() {
    const ojSet = new Set();
    for (const p of this.problems) {
      if (p.oj) {
        ojSet.add(p.oj);
      }
    }
    return Array.from(ojSet).sort();
  }
}

export default ProblemManager;
