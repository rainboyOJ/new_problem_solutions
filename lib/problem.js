import fs from 'fs';
import path from 'path';
import yaml from 'js-yaml';
import * as matter from 'gray-matter';

const __workdir = path.resolve();
const __problemdir = path.join(__workdir, 'problems');
const __problemJsonPath = path.join(__workdir, 'problems.json');

class ProblemManager {
  constructor(opts = { auto_load: true }) {
    this.name = 'problems';
    this.problem_files = [];
    this.problems = [];
    this.config = null;

    if (opts.auto_load) {
      this.init();
      this.load_problems();
    }

    this.config = this.load_config();
  }

  load_config(configPath = 'book.yaml') {
    try {
      const configFile = path.join(__workdir, configPath);
      if (!fs.existsSync(configFile)) {
        return {};
      }

      const content = fs.readFileSync(configFile, 'utf8');
      return yaml.load(content);
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
    } catch (error) {
      console.warn(`加载缓存失败: ${error.message}, 重新扫描`);
      this.init();
      this.save_problems();
    }
  }

  find(oj, problem_id) {
    return this.problems.find(p => p.oj === oj && p.problem_id === problem_id);
  }

  problem_url(oj, id) {
    return `/problems/${oj}/${id}`;
  }

  front_matter(md_path) {
    const raw_md = fs.readFileSync(md_path, 'utf8');
    const prob_front = matter.default(raw_md).data;
    return prob_front;
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
    const walkDir = (dir) => {
      const entries = fs.readdirSync(dir, { withFileTypes: true });
      for (const entry of entries) {
        const fullPath = path.join(dir, entry.name);
        if (entry.isDirectory()) {
          walkDir(fullPath);
        } else if (entry.isFile() && entry.name.endsWith('.md') && !entry.name.startsWith('_')) {
          files.push(path.relative(__problemdir, fullPath));
        }
      }
    };
    walkDir(__problemdir);
    return files;
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
        dateA: prob_front.date ? new Date(prob_front.date).getTime() : 0
      });
    }
  }

  getAll() {
    return this.problems;
  }

  filterByTag(tag) {
    return this.problems.filter(p => p.tags && p.tags.includes(tag));
  }

  filterByOJ(oj) {
    return this.problems.filter(p => p.oj === oj);
  }

  search(keyword) {
    const lowerKeyword = keyword.toLowerCase();
    return this.problems.filter(p => {
      const title = (p.title || '').toLowerCase();
      const problem_id = (p.problem_id || '').toLowerCase();
      return title.includes(lowerKeyword) || problem_id.includes(lowerKeyword);
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
        totalPages
      }
    };
  }

  getAllTags() {
    const tagSet = new Set();
    for (const p of this.problems) {
      if (p.tags) {
        for (const tag of p.tags) {
          tagSet.add(tag);
        }
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