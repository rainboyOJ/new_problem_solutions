import Fastify from 'fastify';
import fastifyCookie from '@fastify/cookie';
import fastifyFormbody from '@fastify/formbody';
import fastifyStatic from '@fastify/static';
import fastifyView from '@fastify/view';
import fs from 'fs';
import matter from 'gray-matter';
import path from 'path';
import pug from 'pug';
import { fileURLToPath } from 'url';

import MarkdownRenderer from './markdown.js';
import { registerPrismAssets } from './prism-assets.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const projectRoot = path.resolve(__dirname, '..');

function unique(items) {
  return Array.from(new Set(items.filter(Boolean)));
}

function normalizeLuoguId(id) {
  const match = /^P?(\d+)$/i.exec(id);
  if (!match) {
    return [];
  }

  return [match[1], `P${match[1]}`];
}

function getCandidateDirNames(oj, id) {
  if (oj.toLowerCase() === 'luogu') {
    return unique([id, ...normalizeLuoguId(id)]);
  }

  return [id];
}

function readProblemFromIndex(indexPath, problemDir, problemsRoot) {
  const raw = fs.readFileSync(indexPath, 'utf8');
  const frontMatter = matter(raw).data || {};
  const mdPath = path.relative(problemsRoot, indexPath).split(path.sep).join('/');

  return {
    ...frontMatter,
    oj: frontMatter.oj || path.basename(path.dirname(problemDir)),
    problem_id: frontMatter.problem_id || path.basename(problemDir),
    md_path: mdPath,
    url: '',
    dateA: frontMatter.date ? new Date(frontMatter.date).getTime() : 0,
  };
}

export function resolvePreviewProblem(oj, id, opts = {}) {
  const root = path.resolve(opts.projectRoot || projectRoot);
  const problemsRoot = path.join(root, 'problems');
  const tried = [];

  for (const dirName of getCandidateDirNames(oj, id)) {
    const problemDir = path.join(problemsRoot, oj, dirName);
    const indexPath = path.join(problemDir, 'index.md');
    tried.push(path.relative(root, indexPath));

    if (!fs.existsSync(indexPath)) {
      continue;
    }

    const problem = readProblemFromIndex(indexPath, problemDir, problemsRoot);
    const aliases = unique([
      id,
      dirName,
      problem.problem_id,
      ...normalizeLuoguId(id),
      ...normalizeLuoguId(problem.problem_id || ''),
    ]);
    problem.url = `/problems/${problem.oj}/${problem.problem_id}/`;

    return {
      root,
      problemsRoot,
      problemDir,
      indexPath,
      problem,
      aliases,
      tried,
    };
  }

  return null;
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
      return `/problems/${oj}/${this.preview.problem.problem_id}/`;
    }

    return `/problems/${oj}/${id}`;
  }

  github_url() {
    return '';
  }
}

function renderProblem(preview, problemManager) {
  const renderer = new MarkdownRenderer(preview.indexPath, problemManager);
  const htmlContent = renderer.toHTML();
  const statementPath = path.join(preview.problemDir, 'problem.md');
  const hasStatement = fs.existsSync(statementPath);
  const statementHtml = hasStatement
    ? new MarkdownRenderer(statementPath, problemManager).toHTML()
    : '';

  return {
    problem: preview.problem,
    content: htmlContent,
    hasStatement,
    statementHtml,
    relations: problemManager.getRelations(preview.problem),
    recommendations: problemManager.getRecommendations(preview.problem),
    githubUrl: '',
  };
}

export async function buildPreviewApp(preview, opts = {}) {
  const app = Fastify({
    logger: opts.logger ?? true,
  });
  const viewsPath = path.join(projectRoot, 'views');
  const problemManager = new PreviewProblemManager(preview);

  await app.register(fastifyView, {
    engine: { pug },
    root: viewsPath,
    production: process.env.NODE_ENV === 'production',
  });

  await app.register(fastifyCookie);
  await app.register(fastifyFormbody);

  await app.register(fastifyStatic, {
    root: path.join(projectRoot, 'public'),
    prefix: '/',
  });
  await registerPrismAssets(app);

  app.get('/', async (request, reply) => {
    return reply.redirect(`/problems/${preview.problem.oj}/${preview.problem.problem_id}/`);
  });

  app.get('/relations', async (request, reply) => {
    return reply.redirect(`/problems/${preview.problem.oj}/${preview.problem.problem_id}/`);
  });

  app.get('/api/problems/:oj/:id', async (request, reply) => {
    const { oj, id } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem) {
      return reply.code(404).send({
        error: 'Preview problem not found',
        oj,
        problem_id: id,
      });
    }

    const renderer = new MarkdownRenderer(preview.indexPath, problemManager);
    const content = renderer.toJSON();

    return reply.send({
      oj: problem.oj,
      problem_id: problem.problem_id,
      title: problem.title,
      description: problem.description || '',
      tags: problem.tags || [],
      md_path: problem.md_path,
      url: problem.url,
      relations: problemManager.getRelations(problem),
      html_content: content.html_content,
      md_content: content.md_content,
    });
  });

  app.get('/problems/:oj/:id', async (request, reply) => {
    const { oj, id } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem) {
      return reply.callNotFound();
    }

    return reply.redirect(`/problems/${problem.oj}/${problem.problem_id}/`);
  });

  app.get('/problems/:oj/:id/', async (request, reply) => {
    const { oj, id } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem) {
      return reply.callNotFound();
    }

    return reply.view('problem.pug', renderProblem(preview, problemManager));
  });

  app.get('/problems/:oj/:id/*', async (request, reply) => {
    const { oj, id, '*': resourcePath } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem || !resourcePath) {
      return reply.callNotFound();
    }

    return reply.sendFile(resourcePath, preview.problemDir);
  });

  app.setNotFoundHandler(async (request, reply) => {
    if (request.raw.url?.startsWith('/api/')) {
      return reply.code(404).send({
        error: 'Not found in single-problem preview',
        statusCode: 404,
      });
    }

    return reply.code(404).view('error.pug', {
      message: 'Not Found in single-problem preview',
      error: {},
    });
  });

  return app;
}

export function createPreviewNotFoundError(oj, id, tried) {
  const error = new Error(`Problem not found for preview: ${oj} ${id}`);
  error.code = 'PREVIEW_PROBLEM_NOT_FOUND';
  error.tried = tried;
  return error;
}

export function resolvePreviewProblemOrThrow(oj, id, opts = {}) {
  const preview = resolvePreviewProblem(oj, id, opts);

  if (!preview) {
    const root = path.resolve(opts.projectRoot || projectRoot);
    const problemsRoot = path.join(root, 'problems');
    const tried = getCandidateDirNames(oj, id).map((dirName) =>
      path.relative(root, path.join(problemsRoot, oj, dirName, 'index.md'))
    );
    throw createPreviewNotFoundError(oj, id, tried);
  }

  return preview;
}
