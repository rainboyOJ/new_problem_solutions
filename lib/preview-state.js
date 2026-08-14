import fs from 'fs';
import { globSync } from 'glob';
import matter from 'gray-matter';
import path from 'path';
import { fileURLToPath } from 'url';

import MarkdownRenderer from './markdown.js';

const moduleRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');

function unique(items) {
  return Array.from(new Set(items.filter(Boolean)));
}

function normalizeLuoguId(id) {
  const match = /^P?(\d+)$/i.exec(id);
  return match ? [match[1], `P${match[1]}`] : [];
}

function candidateDirNames(oj, id) {
  return oj.toLowerCase() === 'luogu'
    ? unique([id, ...normalizeLuoguId(id)])
    : [id];
}

function normalizedRelativePath(root, filePath) {
  return path.relative(root, filePath).split(path.sep).join('/');
}

function readProblem(indexPath, problemDir, problemsRoot) {
  const raw = fs.readFileSync(indexPath, 'utf8');
  const frontMatter = matter(raw).data || {};

  if (typeof frontMatter.title !== 'string' || frontMatter.title.trim() === '') {
    const error = new Error(`Preview article requires a non-empty title: ${indexPath}`);
    error.code = 'PREVIEW_INVALID_FRONTMATTER';
    throw error;
  }

  return {
    ...frontMatter,
    oj: frontMatter.oj || path.basename(path.dirname(problemDir)),
    problem_id: frontMatter.problem_id || path.basename(problemDir),
    md_path: normalizedRelativePath(problemsRoot, indexPath),
    url: '',
    dateA: frontMatter.date ? new Date(frontMatter.date).getTime() : 0,
  };
}

export function resolvePreviewProblemFromIndex(indexPath, opts = {}) {
  const root = path.resolve(opts.projectRoot || moduleRoot);
  const problemsRoot = path.join(root, 'problems');
  const absoluteIndexPath = path.resolve(indexPath);
  const problemDir = path.dirname(absoluteIndexPath);
  const relativeParts = path.relative(problemsRoot, absoluteIndexPath).split(path.sep);

  if (relativeParts.length !== 3 || relativeParts[2] !== 'index.md') {
    const error = new Error(`Preview article is outside problems/<oj>/<id>: ${absoluteIndexPath}`);
    error.code = 'PREVIEW_INVALID_ARTICLE_PATH';
    throw error;
  }

  const dirOj = relativeParts[0];
  const dirId = relativeParts[1];
  const problem = readProblem(absoluteIndexPath, problemDir, problemsRoot);
  const aliases = unique([
    dirId,
    problem.problem_id,
    ...normalizeLuoguId(dirId),
    ...normalizeLuoguId(problem.problem_id || ''),
  ]);
  problem.url = `/problems/${problem.oj}/${problem.problem_id}/`;

  return {
    root,
    problemsRoot,
    problemDir,
    indexPath: absoluteIndexPath,
    problem,
    aliases,
    dirOj,
    dirId,
  };
}

export function resolvePreviewProblem(oj, id, opts = {}) {
  const root = path.resolve(opts.projectRoot || moduleRoot);
  const problemsRoot = path.join(root, 'problems');

  for (const dirName of candidateDirNames(oj, id)) {
    const indexPath = path.join(problemsRoot, oj, dirName, 'index.md');
    if (!fs.existsSync(indexPath)) continue;

    const preview = resolvePreviewProblemFromIndex(indexPath, { projectRoot: root });
    preview.aliases = unique([
      id,
      ...preview.aliases,
      ...normalizeLuoguId(id),
    ]);
    return preview;
  }

  return null;
}

export function createPreviewNotFoundError(oj, id, tried) {
  const error = new Error(`Problem not found for preview: ${oj} ${id}`);
  error.code = 'PREVIEW_PROBLEM_NOT_FOUND';
  error.tried = tried;
  return error;
}

export function resolvePreviewProblemOrThrow(oj, id, opts = {}) {
  const preview = resolvePreviewProblem(oj, id, opts);
  if (preview) return preview;

  const root = path.resolve(opts.projectRoot || moduleRoot);
  const problemsRoot = path.join(root, 'problems');
  const tried = candidateDirNames(oj, id).map((dirName) =>
    normalizedRelativePath(root, path.join(problemsRoot, oj, dirName, 'index.md'))
  );
  throw createPreviewNotFoundError(oj, id, tried);
}

class PreviewProblemManager {
  constructor(preview) {
    this.preview = preview;
    this.problems = [preview.problem];
    this.problemMap = new Map();

    for (const alias of preview.aliases) {
      this.problemMap.set(`${preview.problem.oj}/${alias}`, preview.problem);
    }
  }

  find(oj, problemId) {
    return this.problemMap.get(`${oj}/${problemId}`);
  }

  getRelations() {
    return {
      predecessors: [],
      successors: [],
      common: [],
      hasAny: false,
    };
  }

  getRecommendations(problem) {
    return Array.isArray(problem?.recommend) ? problem.recommend : [];
  }

  problem_url(oj, id) {
    if (oj === this.preview.problem.oj && this.preview.aliases.includes(id)) {
      return this.preview.problem.url;
    }
    return `/problems/${oj}/${id}`;
  }

  github_url() {
    return '';
  }
}

function findGenerator(problemDir) {
  for (const fileName of ['gen.py', 'gen.cpp']) {
    if (fs.existsSync(path.join(problemDir, fileName))) return fileName;
  }
  return null;
}

export function createPreviewSnapshot(preview) {
  const problemManager = new PreviewProblemManager(preview);
  const renderer = new MarkdownRenderer(preview.indexPath, problemManager);
  const content = renderer.toJSON();
  const statementPath = path.join(preview.problemDir, 'problem.md');
  const hasStatement = fs.existsSync(statementPath);
  const statementHtml = hasStatement
    ? new MarkdownRenderer(statementPath, problemManager).toHTML()
    : '';
  const genFileName = findGenerator(preview.problemDir);

  return Object.freeze({
    preview,
    problem: preview.problem,
    problemManager,
    canonicalUrl: preview.problem.url,
    mdContent: content.md_content,
    htmlContent: content.html_content,
    hasStatement,
    statementHtml,
    relations: problemManager.getRelations(preview.problem),
    recommendations: problemManager.getRecommendations(preview.problem),
    githubUrl: '',
    hasGenFile: Boolean(genFileName),
    genFileName,
  });
}

function compareCandidates(a, b) {
  if (a.mtimeMs !== b.mtimeMs) return b.mtimeMs - a.mtimeMs;
  if (a.relativePath < b.relativePath) return -1;
  if (a.relativePath > b.relativePath) return 1;
  return 0;
}

export function findLatestPreviewSnapshot(opts = {}) {
  const root = path.resolve(opts.projectRoot || moduleRoot);
  const problemsRoot = path.join(root, 'problems');
  const indexPaths = globSync('*/*/index.md', {
    cwd: problemsRoot,
    absolute: true,
    nodir: true,
  });
  const candidates = [];
  const errors = [];

  for (const indexPath of indexPaths) {
    const relativePath = normalizedRelativePath(root, indexPath);
    try {
      candidates.push({
        indexPath,
        relativePath,
        mtimeMs: fs.statSync(indexPath).mtimeMs,
      });
    } catch (error) {
      errors.push({ path: relativePath, error });
    }
  }
  candidates.sort(compareCandidates);

  for (const candidate of candidates) {
    try {
      const preview = resolvePreviewProblemFromIndex(candidate.indexPath, { projectRoot: root });
      return createPreviewSnapshot(preview);
    } catch (error) {
      errors.push({ path: candidate.relativePath, error });
    }
  }

  const error = new Error(`No valid problem article found under ${problemsRoot}`);
  error.code = 'PREVIEW_NO_VALID_PROBLEM';
  error.errors = errors;
  throw error;
}

export class ActivePreview {
  #listeners = new Set();
  #snapshot;

  constructor(snapshot) {
    this.#snapshot = snapshot;
    this.version = 1;
  }

  get snapshot() {
    return this.#snapshot;
  }

  subscribe(listener) {
    this.#listeners.add(listener);
    return () => this.#listeners.delete(listener);
  }

  commit(snapshot, metadata = {}) {
    const type = snapshot.canonicalUrl === this.#snapshot.canonicalUrl
      ? 'reload'
      : 'switch';
    this.#snapshot = snapshot;
    this.version += 1;
    const update = Object.freeze({
      type,
      version: this.version,
      url: snapshot.canonicalUrl,
      path: metadata.path || snapshot.preview.indexPath,
      reason: metadata.reason || 'change',
    });

    for (const listener of this.#listeners) listener(update);
    return update;
  }

  getClientState() {
    return {
      type: 'state',
      version: this.version,
      url: this.#snapshot.canonicalUrl,
    };
  }
}
