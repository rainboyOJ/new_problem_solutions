import Fastify from 'fastify';
import fastifyCookie from '@fastify/cookie';
import fastifyFormbody from '@fastify/formbody';
import fastifyStatic from '@fastify/static';
import fastifyView from '@fastify/view';
import path from 'path';
import pug from 'pug';
import { fileURLToPath } from 'url';

import { PreviewEventBroker } from './preview-events.js';
import { registerPrismAssets } from './prism-assets.js';
import {
  ActivePreview,
  createPreviewSnapshot,
  createPreviewNotFoundError,
  resolvePreviewProblem,
  resolvePreviewProblemOrThrow,
} from './preview-state.js';

export {
  createPreviewNotFoundError,
  resolvePreviewProblem,
  resolvePreviewProblemOrThrow,
};

const projectRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');

function toActivePreview(preview) {
  if (preview instanceof ActivePreview) return preview;
  return new ActivePreview(createPreviewSnapshot(preview));
}

function pageLocals(snapshot) {
  return {
    problem: snapshot.problem,
    content: snapshot.htmlContent,
    hasStatement: snapshot.hasStatement,
    statementHtml: snapshot.statementHtml,
    relations: snapshot.relations,
    recommendations: snapshot.recommendations,
    githubUrl: snapshot.githubUrl,
    hasGenFile: snapshot.hasGenFile,
    genFileName: snapshot.genFileName,
    previewLiveReload: true,
  };
}

function isCurrentProblem(snapshot, oj, id) {
  return Boolean(snapshot.problemManager.find(oj, id));
}

function activateRequestedProblem(active, oj, id, request) {
  const current = active.snapshot;
  if (isCurrentProblem(current, oj, id)) return current;

  try {
    const preview = resolvePreviewProblem(oj, id, {
      projectRoot: current.preview.root,
    });
    if (!preview) return null;

    const snapshot = createPreviewSnapshot(preview);
    active.commit(snapshot, {
      path: request.raw.url,
      reason: 'navigation',
    });
    return snapshot;
  } catch (error) {
    request.log.warn({ err: error, oj, problemId: id }, 'Preview navigation rejected');
    return null;
  }
}

export async function buildPreviewApp(preview, opts = {}) {
  const active = toActivePreview(preview);
  const events = new PreviewEventBroker(active, opts.events);
  const app = Fastify({ logger: opts.logger ?? true });
  const viewsPath = path.join(projectRoot, 'views');

  app.addHook('onSend', async (request, reply, payload) => {
    reply.header('Cache-Control', 'no-store');
    return payload;
  });

  app.addHook('onClose', async () => events.close());

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

  app.get('/__preview/events', async (request, reply) => {
    reply.hijack();
    reply.raw.writeHead(200, {
      'Cache-Control': 'no-store',
      'Content-Type': 'text/event-stream; charset=utf-8',
      Connection: 'keep-alive',
    });
    events.connect(reply.raw, request.raw);
  });

  app.get('/', async (request, reply) => reply.redirect(active.snapshot.canonicalUrl));
  app.get('/relations', async (request, reply) => reply.redirect(active.snapshot.canonicalUrl));

  app.get('/api/problems/:oj/:id', async (request, reply) => {
    const { oj, id } = request.params;
    const snapshot = active.snapshot;
    const problem = snapshot.problemManager.find(oj, id);

    if (!problem) {
      return reply.code(404).send({
        error: 'Preview problem not found',
        oj,
        problem_id: id,
      });
    }

    return reply.send({
      oj: problem.oj,
      problem_id: problem.problem_id,
      title: problem.title,
      description: problem.description || '',
      tags: problem.tags || [],
      md_path: problem.md_path,
      url: problem.url,
      relations: snapshot.relations,
      html_content: snapshot.htmlContent,
      md_content: snapshot.mdContent,
    });
  });

  app.get('/problems/:oj/:id', async (request, reply) => {
    const { oj, id } = request.params;
    const snapshot = activateRequestedProblem(active, oj, id, request);
    if (!snapshot) return reply.callNotFound();
    return reply.redirect(snapshot.canonicalUrl);
  });

  app.get('/problems/:oj/:id/', async (request, reply) => {
    const { oj, id } = request.params;
    const snapshot = activateRequestedProblem(active, oj, id, request);
    if (!snapshot) return reply.callNotFound();

    return reply.view('problem.pug', pageLocals(snapshot));
  });

  app.get('/problems/:oj/:id/index.html', async (request, reply) => {
    const { oj, id } = request.params;
    const snapshot = activateRequestedProblem(active, oj, id, request);
    if (!snapshot) return reply.callNotFound();
    return reply.redirect(snapshot.canonicalUrl);
  });

  app.get('/problems/:oj/:id/*', async (request, reply) => {
    const { oj, id, '*': resourcePath } = request.params;
    const snapshot = active.snapshot;

    if (!resourcePath || !isCurrentProblem(snapshot, oj, id)) {
      return reply.callNotFound();
    }

    return reply.sendFile(resourcePath, snapshot.preview.problemDir);
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
