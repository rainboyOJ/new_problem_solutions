import MarkdownRenderer from '../lib/markdown.js';
import path from 'path';
import fs from 'fs';
import { contentGuard } from '../lib/content-http.js';
import { sortProblemsForApi } from '../lib/problem.js';
import { findAiNote, readAiNoteRawContent } from '../lib/ai-notes.js';
import { renderCodeHtml } from '../lib/highlight.js';

export default async function apiRoutes(app, options) {
  const { problemManager, contentService, rbookArticleService } = options;
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
        query: 'page, limit, oj, tag, showAtRbook, search, favorite, sort, order',
        example: '/api/problems?showAtRbook=rbook2%3Abit&sort=difficulty&order=asc',
      },
      {
        method: 'GET',
        path: '/api/problems/:oj/:id',
        desc: '单个题目详情（包含渲染后的 HTML、showAtRbook 原始引用与解析后的 rbook_links）',
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
      {
        method: 'POST',
        path: '/api/highlight',
        desc: '把一段代码高亮成 HTML（Md Raw 弹窗等运行时内容用）',
        query: '-',
        example: '/api/highlight',
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
    const { oj, tag, showAtRbook, search, favorite, sort, order } = request.query;

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

    if (showAtRbook) {
      problems = problems.filter((problem) => (
        Array.isArray(problem.showAtRbook) && problem.showAtRbook.includes(showAtRbook)
      ));
    }

    if (favorite === 'true') {
      problems = problems.filter((problem) => problem.favorite === true);
    }

    problems = sortProblemsForApi(problems, sort, order);

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

    const rbookLinks = rbookArticleService
      ? await rbookArticleService.getRbookLinks(problem.rbookLinks)
      : [];

    return reply.send({
      oj: problem.oj,
      problem_id: problem.problem_id,
      title: problem.title,
      description: problem.description || '',
      tags: problem.tags || [],
      showAtRbook: problem.showAtRbook || [],
      rbook_links: rbookLinks,
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

  app.get('/problems/:oj/:id/ai-notes/:slug/raw', { preHandler: guard }, async (request, reply) => {
    const { oj, id, slug } = request.params;
    const problem = problemManager.find(oj, id);
    const note = findAiNote(problem?.aiNotes, slug);
    if (!problem || !note) {
      return reply.code(404).send({ error: 'AI note not found', statusCode: 404 });
    }

    const problemDir = path.dirname(path.join(problemManager.baseDir, problem.md_path));
    try {
      return reply.send({
        title: note.title,
        md_content: readAiNoteRawContent(problemDir, note),
      });
    } catch {
      return reply.code(404).send({ error: 'AI note not found', statusCode: 404 });
    }
  });

  app.get('/problems/:oj/:id/statement/raw', { preHandler: guard }, async (request, reply) => {
    const { oj, id } = request.params;
    const problem = problemManager.find(oj, id);
    if (!problem) {
      return reply.code(404).send({ error: 'Problem not found', statusCode: 404 });
    }

    const problemDir = path.dirname(path.join(problemManager.baseDir, problem.md_path));
    const statementPath = path.join(problemDir, 'problem.md');
    let mdContent;
    try {
      mdContent = fs.readFileSync(statementPath, 'utf8');
    } catch {
      return reply.code(404).send({ error: 'Statement not found', statusCode: 404 });
    }

    return reply.send({
      oj: problem.oj,
      problem_id: problem.problem_id,
      md_content: mdContent,
    });
  });

  app.get('/tags', { preHandler: guard }, async () => problemManager.getAllTags());

  // 运行时才出现的代码（Md Raw 原文、随机数据生成器）走这里拿高亮结果，
  // 浏览器端不需要打包整套语法包。
  app.post('/highlight', async (request, reply) => {
    const { code, language } = request.body || {};
    if (typeof code !== 'string' || typeof language !== 'string') {
      return reply.code(400).send({ error: 'code and language are required', statusCode: 400 });
    }
    if (code.length > 400_000) {
      return reply.code(413).send({ error: 'code is too long', statusCode: 413 });
    }

    // html 为 null 表示这门语言不上色，前端保留纯文本即可。
    return reply.send({ html: renderCodeHtml(code, language) });
  });

  app.get('/relations', { preHandler: guard }, async () => problemManager.getRelationGraph());

  app.get('/oj', { preHandler: guard }, async () => problemManager.getAllOJs());
}
