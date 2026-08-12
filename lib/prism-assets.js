import fastifyStatic from '@fastify/static';
import { createRequire } from 'node:module';
import path from 'node:path';

const require = createRequire(import.meta.url);
const prismPackageRoot = path.dirname(require.resolve('prismjs/package.json'));

export async function registerPrismAssets(app) {
  await app.register(fastifyStatic, {
    root: prismPackageRoot,
    prefix: '/vendor/prism/',
    decorateReply: false,
  });
}
