import path from 'path';
import MarkdownRenderer from '../lib/markdown.js';
import problemManager from '../lib/instance.js';

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

    const mdPath = path.join(process.cwd(), 'problems', problem.md_path);
    const renderer = new MarkdownRenderer(mdPath, problemManager);
    const htmlContent = renderer.toHTML();

    return reply.view('problem.pug', {
      problem,
      content: htmlContent,
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
