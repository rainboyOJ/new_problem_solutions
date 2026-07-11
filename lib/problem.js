import fs from 'fs';
import path from 'path';
import yaml from 'js-yaml';
import * as matter from 'gray-matter';

const __workdir = path.resolve();
const __problemdir = path.join(__workdir, 'problems');
const __problemJsonPath = path.join(__workdir, 'problems.json');
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

class ProblemManager {
  constructor(opts = { auto_load: true }) {
    this.name = 'problems';
    this.problem_files = [];
    this.problems = [];
    this.problemMap = new Map();
    this.config = null;

    if (opts.auto_load) {
      this.load_problems();
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

  save_problems() {
    fs.writeFileSync(__problemJsonPath, JSON.stringify(this.problems, null, 2));
  }

  load_problems() {
    if (!fs.existsSync(__problemJsonPath)) {
      this.init();
      this.save_problems();
      return;
    }

    try {
      this.problems = JSON.parse(fs.readFileSync(__problemJsonPath, 'utf8'));
      if (!Array.isArray(this.problems) || this.isProblemCacheStale()) {
        this.init();
        this.save_problems();
        return;
      }
      this.sortProblems();
      this.buildIndex();
    } catch (error) {
      console.warn(`加载缓存失败: ${error.message}, 重新扫描`);
      this.init();
      this.save_problems();
    }
  }

  buildIndex() {
    this.problemMap.clear();
    for (const p of this.problems) {
      this.problemMap.set(this.problemKey(p.oj, p.problem_id), p);
    }
  }

  problemKey(oj, problem_id) {
    return `${String(oj || '')}/${String(problem_id || '')}`;
  }

  sortProblems() {
    this.problems.sort((a, b) => {
      const dateDiff = (b.dateA || 0) - (a.dateA || 0);
      if (dateDiff !== 0) {
        return dateDiff;
      }

      const aKey = `${a.oj || ''}/${a.problem_id || ''}/${a.md_path || ''}`;
      const bKey = `${b.oj || ''}/${b.problem_id || ''}/${b.md_path || ''}`;
      return aKey.localeCompare(bKey);
    });
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
        problem_id: item.problem_id || '',
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
        problem_id: item.problem_id || '',
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
    return `/problems/${oj}/${id}`;
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

    const walkDir = (dir) => {
      let entries;
      try {
        entries = fs.readdirSync(dir, { withFileTypes: true });
      } catch (error) {
        if (error.code === 'ENOENT') {
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
          files.push(path.relative(__problemdir, fullPath));
        }
      }
    };

    walkDir(__problemdir);
    return files;
  }

  isProblemCacheStale() {
    if (!fs.existsSync(__problemJsonPath)) {
      return true;
    }

    const files = this.scanProblems();
    const cachedPaths = new Set(this.problems.map((problem) => problem?.md_path).filter(Boolean));

    if (cachedPaths.size !== files.length) {
      return true;
    }

    for (const file of files) {
      if (!cachedPaths.has(file)) {
        return true;
      }
    }

    const cacheMtime = fs.statSync(__problemJsonPath).mtimeMs;
    for (const file of files) {
      const mdPath = path.join(__problemdir, file);
      if (fs.statSync(mdPath).mtimeMs > cacheMtime + 1) {
        return true;
      }
    }

    return false;
  }

  init() {
    const files = this.scanProblems();
    this.problem_files = files;
    this.problems = [];

    for (const md of files) {
      const md_path = path.join(__problemdir, md);
      const prob_front = this.front_matter(md_path);

      if (!prob_front) {
        console.log(`md_path: ${md_path} front_matter is empty`);
        continue;
      }

      if (!prob_front.oj || !prob_front.problem_id) {
        console.log(`md_path: ${md_path} front_matter.oj or front_matter.problem_id is empty`);
        continue;
      }

      this.problems.push({
        ...prob_front,
        md_path: md,
        url: this.problem_url(prob_front.oj, prob_front.problem_id),
        dateA: prob_front.date ? new Date(prob_front.date).getTime() : 0,
      });
    }

    this.sortProblems();
    this.buildIndex();
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
      return title.includes(lowerKeyword)
        || problem_id.includes(lowerKeyword)
        || description.includes(lowerKeyword);
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
