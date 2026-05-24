import Fastify from 'fastify';
import fastifyCookie from '@fastify/cookie';
import fastifyFormbody from '@fastify/formbody';
import fastifyStatic from '@fastify/static';
import fastifyView from '@fastify/view';
import path from 'path';
import { fileURLToPath } from 'url';
import pug from 'pug';

import indexRoutes from './routes/index.js';
import apiRoutes from './routes/api.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

export async function buildApp(options = {}) {
  const app = Fastify({
    logger: options.logger ?? true,
  });

  const viewsPath = path.join(__dirname, 'views');

  await app.register(fastifyView, {
    engine: { pug },
    root: viewsPath,
    production: process.env.NODE_ENV === 'production',
  });

  await app.register(fastifyCookie);
  await app.register(fastifyFormbody);

  await app.register(fastifyStatic, {
    root: path.join(__dirname, 'public'),
    prefix: '/',
  });

  await app.register(indexRoutes);
  await app.register(apiRoutes, { prefix: '/api' });

  app.setNotFoundHandler(async (request, reply) => {
    if (request.raw.url?.startsWith('/api/')) {
      return reply.code(404).send({
        error: 'Not found',
        statusCode: 404,
      });
    }

    return reply.code(404).view('error.pug', {
      message: 'Not Found',
      error: {},
    });
  });

  app.setErrorHandler(async (error, request, reply) => {
    request.log.error(error);

    const statusCode = error.statusCode || error.status || 500;
    if (request.raw.url?.startsWith('/api/')) {
      return reply.code(statusCode).send({
        error: error.message,
        statusCode,
      });
    }

    return reply.code(statusCode).view('error.pug', {
      message: error.message,
      error: process.env.NODE_ENV === 'development' ? error : {},
    });
  });

  return app;
}

const app = await buildApp();

export default app;
