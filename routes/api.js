import MarkdownRenderer from '../lib/markdown.js';
import path from 'path';
import fs from 'fs';
import { contentGuard } from '../lib/content-http.js';

export default async function apiRoutes(app, options) {
  const { problemManager, contentService } = options;
  const guard = contentGuard(contentService, 'json');

  app.get('/health/live', async () => ({ status: 'ok' }));

  app.get('/health/content', async (request, reply) => {
    const health = contentService.publicHealth();
    return reply.code(health.ready ? 200 : 503).send(health);
  });

  app.get('/health/content/details', async (request, reply) => {
    const token = process.env.CONTENT_HEALTH_TOKEN || '';
    if (!token && process.env.NODE_ENV === 'production') {
      return reply.callNotFound();
    }
    if (token && request.headers.authorization !== `Bearer ${token}`) {
      return reply.code(401).send({
        error: 'Unauthorized',
        statusCode: 401,
      });
    }
    return contentService.detailedHealth();
  });

  app.get('/', async (request, reply) => {
    const endpoints = [
      {
        method: 'GET',
        path: '/api/problems',
        desc: '题目列表，支持分页和筛选',
        query: 'page, limit, oj, tag, search, favorite',
        example: '/api/problems?page=1&limit=20&favorite=true',
      },
      {
        method: 'GET',
        path: '/api/problems/:oj/:id',
        desc: '单个题目详情（包含渲染后的 HTML）',
        query: '-',
        example: '/api/problems/poj/3061',
      },
      {
        method: 'GET',
        path: '/api/tags',
        desc: '标签列表',
        query: '-',
        example: '/api/tags',
      },
      {
        method: 'GET',
        path: '/api/relations',
        desc: '题目关系图数据',
        query: '-',
        example: '/api/relations',
      },
      {
        method: 'GET',
        path: '/api/oj',
        desc: 'OJ 平台列表',
        query: '-',
        example: '/api/oj',
      },
    ];

    return reply.view('api.pug', {
      title: 'API 文档',
      endpoints,
      baseUrl: `${request.protocol}://${request.headers.host}`,
    });
  });

  app.get('/problems', { preHandler: guard }, async (request, reply) => {
    const page = parseInt(request.query.page, 10) || 1;
    const limit = parseInt(request.query.limit, 10) || 20;
    const { oj, tag, search, favorite } = request.query;

    let problems = problemManager.getAll();

    if (search) {
      problems = problemManager.search(search);
    }

    if (oj) {
      problems = problems.filter((problem) => problem.oj === oj);
    }

    if (tag) {
      problems = problems.filter((problem) => problem.tags && problem.tags.includes(tag));
    }

    if (favorite === 'true') {
      problems = problems.filter((problem) => problem.favorite === true);
    }

    const offset = (page - 1) * limit;
    const total = problems.length;
    const totalPages = Math.ceil(total / limit);
    const data = problems.slice(offset, offset + limit);

    return reply.send({
      data,
      pagination: {
        total,
        page,
        limit,
        totalPages,
      },
    });
  });

  app.get('/problems/:oj/:id', { preHandler: guard }, async (request, reply) => {
    const { oj, id } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem) {
      return reply.code(404).send({
        error: 'Problem not found',
        oj,
        problem_id: id,
      });
    }

    const mdPath = path.join(problemManager.baseDir, problem.md_path);

    let content;
    try {
      content = contentService.render(
        'problem',
        `${problem.oj}/${problem.problem_id}`,
        () => {
          if (!fs.existsSync(mdPath)) {
            throw new Error(`Problem markdown file not found: ${problem.md_path}`);
          }
          return new MarkdownRenderer(mdPath, problemManager).toJSON();
        },
        'api',
      );
    } catch (error) {
      if (error.name === 'ContentRenderError') {
        return reply.code(404).send({
          error: 'Problem not found',
          oj,
          problem_id: id,
        });
      }
      throw error;
    }

    return reply.send({
      oj: problem.oj,
      problem_id: problem.problem_id,
      title: problem.title,
      description: problem.description || '',
      tags: problem.tags || [],
      favorite: problem.favorite === true,
      favorite_reason: typeof problem.favorite_reason === 'string'
        ? problem.favorite_reason
        : '',
      md_path: problem.md_path,
      url: problem.url,
      relations: problemManager.getRelations(problem),
      html_content: content.html_content,
      md_content: content.md_content,
    });
  });

  app.get('/tags', { preHandler: guard }, async () => problemManager.getAllTags());

  app.get('/relations', { preHandler: guard }, async () => problemManager.getRelationGraph());

  app.get('/oj', { preHandler: guard }, async () => problemManager.getAllOJs());
}
