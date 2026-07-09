#!/usr/bin/env node

import debug from 'debug';
import os from 'os';
import { pathToFileURL } from 'url';

import { buildAccessUrls } from '../lib/access-urls.js';
import {
  buildPreviewApp,
  resolvePreviewProblemOrThrow,
} from '../lib/preview-app.js';

const debugLog = debug('rbook:cli');
export const DEFAULT_PREVIEW_HOST = '0.0.0.0';
export const DEFAULT_PREVIEW_PORT = '3000';

async function main(argv) {
  const [command, ...args] = argv;

  if (!command || command === '--help' || command === '-h') {
    printHelp();
    process.exit(0);
  }

  if (command === 'preview') {
    await previewCommand(args);
    return;
  }

  printHelp();
  process.exit(1);
}

async function previewCommand(args) {
  const { options, positionals } = parsePreviewArgs(args, process.env);
  const [oj, id] = positionals;

  if (!oj || !id || positionals.length > 2) {
    printPreviewHelp();
    process.exit(1);
  }

  let preview;
  try {
    preview = resolvePreviewProblemOrThrow(oj, id);
  } catch (error) {
    if (error.code === 'PREVIEW_PROBLEM_NOT_FOUND') {
      console.error(error.message);
      console.error('Tried:');
      for (const item of error.tried) {
        console.error('- ' + item);
      }
      process.exit(1);
    }
    throw error;
  }

  const app = await buildPreviewApp(preview);

  try {
    await app.listen({ port: options.port, host: options.host });
    onListening(app, preview);
  } catch (error) {
    onListenError(error, options.port);
  }
}

export function parsePreviewArgs(args, env = process.env) {
  const options = {
    host: env.HOST || DEFAULT_PREVIEW_HOST,
    port: normalizePort(env.PORT || DEFAULT_PREVIEW_PORT),
  };
  const positionals = [];

  for (let i = 0; i < args.length; i += 1) {
    const arg = args[i];

    if (arg === '--host') {
      options.host = requireValue(args, i, '--host');
      i += 1;
      continue;
    }

    if (arg === '--port' || arg === '-p') {
      options.port = normalizePort(requireValue(args, i, arg));
      i += 1;
      continue;
    }

    if (arg === '--help' || arg === '-h') {
      printPreviewHelp();
      process.exit(0);
    }

    positionals.push(arg);
  }

  return { options, positionals };
}

function normalizePort(value) {
  const port = parseInt(value, 10);

  if (Number.isNaN(port)) {
    return value;
  }

  if (port >= 0) {
    return port;
  }

  return false;
}

function requireValue(args, index, optionName) {
  const value = args[index + 1];

  if (!value) {
    console.error(`${optionName} requires a value`);
    process.exit(1);
  }

  return value;
}

function onListenError(error, port) {
  if (error.syscall !== 'listen') {
    throw error;
  }

  const bind = typeof port === 'string' ? 'Pipe ' + port : 'Port ' + port;

  if (error.code === 'EACCES') {
    console.error(bind + ' requires elevated privileges');
    process.exit(1);
  }

  if (error.code === 'EADDRINUSE') {
    console.error(bind + ' is already in use');
    process.exit(1);
  }

  throw error;
}

function onListening(app, preview) {
  const addr = app.server.address();
  const bind = typeof addr === 'string' ? 'pipe ' + addr : 'port ' + addr.port;
  debugLog('Listening on ' + bind);

  if (typeof addr === 'string') {
    console.log(`Preview server is running on ${addr}`);
    return;
  }

  const urls = buildAccessUrls(addr.port, os.networkInterfaces());
  const problemPath = `/problems/${preview.problem.oj}/${encodeURIComponent(preview.problem.problem_id)}/`;

  console.log(`Previewing ${preview.problem.oj} ${preview.problem.problem_id}`);
  console.log(`Source: ${preview.problem.md_path}`);
  console.log('Access URLs:');
  for (const url of urls) {
    console.log('- ' + url + problemPath);
  }
}

function printHelp() {
  console.log(`Usage:
  rbook preview <oj> <problem_id> [--port 3000] [--host 0.0.0.0]

Commands:
  preview   Start a fast single-problem preview server`);
}

function printPreviewHelp() {
  console.log(`Usage:
  rbook preview <oj> <problem_id> [--port 3000] [--host 0.0.0.0]

Examples:
  rbook preview luogu 1010
  rbook preview luogu P1010 --port 3100
  rbook preview luogu P1010 --host 127.0.0.1
  npm run preview -- luogu 1010`);
}

if (process.argv[1] && import.meta.url === pathToFileURL(process.argv[1]).href) {
  main(process.argv.slice(2)).catch((error) => {
    console.error(error);
    process.exit(1);
  });
}
