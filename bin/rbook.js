#!/usr/bin/env node

import debug from 'debug';
import os from 'os';
import { pathToFileURL } from 'url';

import { buildAccessUrls } from '../lib/access-urls.js';
import { buildPreviewApp } from '../lib/preview-app.js';
import { ActivePreview, findLatestPreviewSnapshot } from '../lib/preview-state.js';
import { createPreviewWatcher } from '../lib/preview-watcher.js';

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
  let options;
  try {
    ({ options } = parsePreviewArgs(args, process.env));
  } catch (error) {
    if (error.code !== 'PREVIEW_POSITIONALS_UNSUPPORTED') throw error;
    console.error(error.message);
    printPreviewHelp();
    process.exitCode = 1;
    return;
  }

  let snapshot;
  try {
    snapshot = findLatestPreviewSnapshot();
  } catch (error) {
    if (error.code === 'PREVIEW_NO_VALID_PROBLEM') {
      console.error(error.message);
      for (const item of error.errors || []) {
        console.error(`- ${item.path}: ${String(item.error?.message || item.error).split('\n')[0]}`);
      }
      process.exitCode = 1;
      return;
    }
    throw error;
  }

  const active = new ActivePreview(snapshot);
  const app = await buildPreviewApp(active);

  try {
    await app.listen({ port: options.port, host: options.host });
  } catch (error) {
    await app.close();
    if (onListenError(error, options.port)) {
      process.exitCode = 1;
      return;
    }
    throw error;
  }

  let watcher;
  try {
    watcher = createPreviewWatcher(active);
  } catch (error) {
    await app.close();
    throw error;
  }

  onListening(app, active.snapshot);
  installShutdownHandlers(app, watcher);
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

  if (positionals.length > 0) {
    const error = new Error('rbook preview no longer accepts problem arguments');
    error.code = 'PREVIEW_POSITIONALS_UNSUPPORTED';
    throw error;
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
    return false;
  }

  const bind = typeof port === 'string' ? 'Pipe ' + port : 'Port ' + port;

  if (error.code === 'EACCES') {
    console.error(bind + ' requires elevated privileges');
    return true;
  }

  if (error.code === 'EADDRINUSE') {
    console.error(bind + ' is already in use');
    return true;
  }

  return false;
}

function onListening(app, snapshot) {
  const addr = app.server.address();
  const bind = typeof addr === 'string' ? 'pipe ' + addr : 'port ' + addr.port;
  debugLog('Listening on ' + bind);

  if (typeof addr === 'string') {
    console.log(`Preview server is running on ${addr}`);
    return;
  }

  const urls = buildAccessUrls(addr.port, os.networkInterfaces());

  console.log(`Previewing ${snapshot.problem.oj} ${snapshot.problem.problem_id}`);
  console.log(`Source: ${snapshot.problem.md_path}`);
  console.log('Watching all problem index files and the active problem directory (500ms stability).');
  console.log('Access URLs:');
  for (const url of urls) {
    console.log('- ' + url + snapshot.canonicalUrl);
  }
}

function installShutdownHandlers(app, watcher) {
  let closing = false;

  const shutdown = async () => {
    if (closing) return;
    closing = true;
    process.removeListener('SIGINT', shutdown);
    process.removeListener('SIGTERM', shutdown);

    const results = await Promise.allSettled([watcher.close(), app.close()]);
    for (const result of results) {
      if (result.status !== 'rejected') continue;
      console.error(result.reason);
      process.exitCode = 1;
    }
  };

  process.once('SIGINT', shutdown);
  process.once('SIGTERM', shutdown);
}

function printHelp() {
  console.log(`Usage:
  rbook preview [--port 3000] [--host 0.0.0.0]

Commands:
  preview   Follow the most recently edited problem article`);
}

function printPreviewHelp() {
  console.log(`Usage:
  rbook preview [--port 3000] [--host 0.0.0.0]

Examples:
  rbook preview
  rbook preview --port 3100
  rbook preview --host 127.0.0.1
  npm run preview`);
}

if (process.argv[1] && import.meta.url === pathToFileURL(process.argv[1]).href) {
  main(process.argv.slice(2)).catch((error) => {
    console.error(error);
    process.exit(1);
  });
}
