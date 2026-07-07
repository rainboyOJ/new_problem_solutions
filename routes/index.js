import path from 'path';
import fs from 'fs';
import MarkdownRenderer from '../lib/markdown.js';
import problemManager from '../lib/instance.js';
import ProblemSetManager from '../lib/problem-set.js';

const problemSetManager = new ProblemSetManager(problemManager);

export default async function indexRoutes(app) {
  app.get('/', async (request, reply) => {
    const { q, oj, tag, page } = request.query;

    let problems = problemManager.getAll();

    if (q) {
      problems = problemManager.search(q);
    }

    if (oj) {
      problems = problems.filter((p) => p.oj === oj);
    }

    if (tag) {
      problems = problems.filter((p) => p.tags && p.tags.includes(tag));
    }

    const currentPage = parseInt(page, 10) || 1;
    const { data, pagination } = paginate(problems, currentPage, 20);

    const tags = problemManager.getAllTags();
    const ojs = problemManager.getAllOJs();

    return reply.view('index.pug', {
      problems: data,
      pagination,
      tags,
      ojs,
      query: q || '',
      currentOJ: oj || '',
      currentTag: tag || '',
      pageUrl: (targetPage) =>
        buildPageUrl({
          page: targetPage,
          query: q,
          oj,
          tag,
        }),
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

    const mdPath = path.join(process.cwd(), 'problems', problem.md_path);
    const renderer = new MarkdownRenderer(mdPath, problemManager);
    const htmlContent = renderer.toHTML();
    const problemDir = path.dirname(mdPath);
    const statementPath = path.join(problemDir, 'problem.md');
    const hasStatement = fs.existsSync(statementPath);
    const genFileName = findGenFileName(problemDir);
    const statementHtml = hasStatement
      ? new MarkdownRenderer(statementPath, problemManager).toHTML()
      : '';

    return reply.view('problem.pug', {
      problem,
      content: htmlContent,
      hasStatement,
      statementHtml,
      hasGenFile: genFileName !== null,
      genFileName,
      relations: problemManager.getRelations(problem),
      recommendations: problemManager.getRecommendations(problem),
      githubUrl: problemManager.github_url(problem.md_path),
    });
  });

  app.get('/problems/:oj/:id/*', async (request, reply) => {
    const { oj, id, '*': resourcePath } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem || !resourcePath) {
      return reply.callNotFound();
    }

    const mdPath = path.join(process.cwd(), 'problems', problem.md_path);
    const problemDir = path.dirname(mdPath);

    return reply.sendFile(resourcePath, problemDir);
  });

  app.get('/relations', async (request, reply) => {
    return reply.view('relations.pug', {
      title: '题目关系图',
    });
  });

  app.get('/problem-sets', async (request, reply) => {
    return reply.view('problem-sets-index.pug', {
      title: '题目单',
      sets: problemSetManager.list(),
    });
  });

  app.get('/problem-sets/:slug', async (request, reply) => {
    const problemSet = problemSetManager.find(request.params.slug);
    if (!problemSet) {
      return reply.callNotFound();
    }

    return reply.view('problem-set.pug', {
      title: problemSet.title,
      problemSet,
    });
  });
}

function buildPageUrl({ page, query, oj, tag }) {
  const params = new URLSearchParams();
  params.set('page', String(page));

  if (query) {
    params.set('q', query);
  }
  if (oj) {
    params.set('oj', oj);
  }
  if (tag) {
    params.set('tag', tag);
  }

  return `?${params.toString()}`;
}

export function findGenFileName(problemDir) {
  if (fs.existsSync(path.join(problemDir, 'gen.py'))) {
    return 'gen.py';
  }
  if (fs.existsSync(path.join(problemDir, 'gen.cpp'))) {
    return 'gen.cpp';
  }
  return null;
}

function paginate(problems, page, limit) {
  const offset = (page - 1) * limit;
  const total = problems.length;
  const totalPages = Math.ceil(total / limit);
  const data = problems.slice(offset, offset + limit);

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
