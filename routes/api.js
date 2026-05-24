import MarkdownRenderer from '../lib/markdown.js';
import path from 'path';
import fs from 'fs';
import problemManager from '../lib/instance.js';

const problemdir = path.resolve('problems');

export default async function apiRoutes(app) {
  app.get('/', async (request, reply) => {
    const endpoints = [
      {
        method: 'GET',
        path: '/api/problems',
        desc: '题目列表，支持分页和筛选',
        query: 'page, limit, oj, tag, search',
        example: '/api/problems?page=1&limit=20&oj=poj',
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

  app.get('/problems', async (request, reply) => {
    const page = parseInt(request.query.page, 10) || 1;
    const limit = parseInt(request.query.limit, 10) || 20;
    const { oj, tag, search } = request.query;

    let problems = problemManager.getAll();

    if (oj) {
      problems = problemManager.filterByOJ(oj);
    }

    if (tag) {
      problems = problemManager.filterByTag(tag);
    }

    if (search) {
      problems = problemManager.search(search);
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

  app.get('/problems/:oj/:id', async (request, reply) => {
    const { oj, id } = request.params;
    const problem = problemManager.find(oj, id);

    if (!problem) {
      return reply.code(404).send({
        error: 'Problem not found',
        oj,
        problem_id: id,
      });
    }

    const mdPath = path.join(problemdir, problem.md_path);

    if (!fs.existsSync(mdPath)) {
      return reply.code(404).send({
        error: 'Problem markdown file not found',
        md_path: problem.md_path,
      });
    }

    const renderer = new MarkdownRenderer(mdPath, problemManager);
    const content = renderer.toJSON();

    return reply.send({
      oj: problem.oj,
      problem_id: problem.problem_id,
      title: problem.title,
      tags: problem.tags || [],
      md_path: problem.md_path,
      url: problem.url,
      html_content: content.html_content,
      md_content: content.md_content,
    });
  });

  app.get('/tags', async () => problemManager.getAllTags());

  app.get('/oj', async () => problemManager.getAllOJs());
}
