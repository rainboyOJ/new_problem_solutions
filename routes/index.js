import path from 'path';
import fs from 'fs';
import MarkdownRenderer from '../lib/markdown.js';
import problemManager from '../lib/instance.js';
import ProblemSetManager from '../lib/problem-set.js';

const problemSetManager = new ProblemSetManager(problemManager);

export default async function indexRoutes(app) {
  app.get('/', async (request, reply) => {
    const { q, oj, tag, page, favorite } = request.query;
    const currentFavorite = favorite === 'true';

    let problems = problemManager.getAll();

    if (q) {
      problems = problemManager.search(q);
    }

    if (oj) {
      problems = problems.filter((p) => p.oj === oj);
    }

    if (currentFavorite) {
      problems = problems.filter((p) => p.favorite === true);
    }

    const tagScopeTotal = problems.length;
    const tagOptions = buildTagOptions(problems);

    if (tag) {
      problems = problems.filter((p) => p.tags && p.tags.includes(tag));
    }

    const currentPage = parseInt(page, 10) || 1;
    const { data, pagination } = paginate(problems, currentPage, 60);

    const ojs = problemManager.getAllOJs();

    return reply.view('index.pug', {
      problems: data,
      pagination,
      tagOptions,
      tagScopeTotal,
      ojs,
      query: q || '',
      currentOJ: oj || '',
      currentTag: tag || '',
      currentFavorite,
      pageUrl: (targetPage) =>
        buildPageUrl({
          page: targetPage,
          query: q,
          oj,
          tag,
          favorite: currentFavorite,
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

function buildPageUrl({ page, query, oj, tag, favorite }) {
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
  if (favorite) {
    params.set('favorite', 'true');
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

export function buildTagOptions(problems) {
  const counts = new Map();

  for (const problem of problems) {
    const tags = new Set(Array.isArray(problem.tags) ? problem.tags : []);
    for (const tag of tags) {
      counts.set(tag, (counts.get(tag) || 0) + 1);
    }
  }

  return [...counts.entries()]
    .map(([name, count]) => ({ name, count }))
    .sort((left, right) => right.count - left.count
      || left.name.localeCompare(right.name, 'zh-CN'));
}

function paginate(problems, page, limit) {
  const total = problems.length;
  const totalPages = Math.ceil(total / limit);
  const safePage = totalPages === 0
    ? 1
    : Math.min(Math.max(page, 1), totalPages);
  const safeOffset = (safePage - 1) * limit;
  const data = problems.slice(safeOffset, safeOffset + limit);

  return {
    data,
    pagination: {
      total,
      page: safePage,
      limit,
      totalPages,
      startItem: total === 0 ? 0 : safeOffset + 1,
      endItem: Math.min(safeOffset + limit, total),
      items: buildPaginationItems(safePage, totalPages),
    },
  };
}

function buildPaginationItems(page, totalPages) {
  if (totalPages <= 7) {
    return Array.from({ length: totalPages }, (_, index) => index + 1);
  }

  const visiblePages = new Set([1, totalPages]);
  for (let offset = -2; offset <= 2; offset += 1) {
    const candidate = page + offset;
    if (candidate > 0 && candidate <= totalPages) {
      visiblePages.add(candidate);
    }
  }

  const pages = [...visiblePages].sort((left, right) => left - right);
  const items = [];
  let previous = null;

  for (const value of pages) {
    if (previous !== null && value - previous > 1) {
      items.push('ellipsis');
    }
    items.push(value);
    previous = value;
  }

  return items;
}
