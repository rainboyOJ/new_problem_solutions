#!/usr/bin/env node

import fs from 'node:fs';
import net from 'node:net';
import os from 'node:os';
import path from 'node:path';
import { spawn } from 'node:child_process';
import { once } from 'node:events';
import { pathToFileURL } from 'node:url';

const DEFAULT_TIMEOUT_MS = 60_000;

export function validateLiveHealth(response) {
  if (response.status !== 200 || response.body?.status !== 'ok') {
    throw new Error(`存活检查失败: HTTP ${response.status} ${JSON.stringify(response.body)}`);
  }
}

export function validateContentHealth(response) {
  const health = response.body;
  if (
    response.status !== 200
    || health?.state !== 'healthy'
    || health?.ready !== true
    || health?.errorCount !== 0
  ) {
    throw new Error(`内容健康检查失败: HTTP ${response.status} ${JSON.stringify(health)}`);
  }
  return health;
}

async function reservePort() {
  const server = net.createServer();
  server.unref();
  await new Promise((resolve, reject) => {
    server.once('error', reject);
    server.listen(0, '127.0.0.1', resolve);
  });
  const address = server.address();
  const port = address.port;
  await new Promise((resolve, reject) => server.close((error) => {
    if (error) reject(error);
    else resolve();
  }));
  return port;
}

async function fetchJson(url) {
  const response = await fetch(url, { signal: AbortSignal.timeout(2_000) });
  const text = await response.text();
  let body;
  try {
    body = JSON.parse(text);
  } catch {
    body = text;
  }
  return { status: response.status, body };
}

function delay(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

async function stopChild(child) {
  if (!child.pid) return;
  if (child.exitCode !== null || child.signalCode !== null) return;
  child.kill('SIGTERM');
  const exited = await Promise.race([
    once(child, 'exit').then(() => true),
    delay(3_000).then(() => false),
  ]);
  if (!exited && child.exitCode === null) {
    child.kill('SIGKILL');
    await once(child, 'exit');
  }
}

export async function runSmokeTest(options = {}) {
  const cwd = options.cwd || process.cwd();
  const timeoutMs = options.timeoutMs || DEFAULT_TIMEOUT_MS;
  const port = options.port || await reservePort();
  const runtimeDir = fs.mkdtempSync(path.join(os.tmpdir(), 'rbook-smoke-'));
  const revisionPath = path.join(runtimeDir, 'content-revision.json');
  const child = spawn(process.execPath, ['./bin/www'], {
    cwd,
    env: {
      ...process.env,
      NODE_ENV: 'production',
      HOST: '127.0.0.1',
      PORT: String(port),
      CONTENT_REVISION: 'pre-push-verification',
      CONTENT_REVISION_PATH: revisionPath,
    },
    stdio: ['ignore', 'pipe', 'pipe'],
  });
  let logs = '';
  let spawnError = null;
  child.stdout.on('data', (chunk) => { logs += chunk.toString(); });
  child.stderr.on('data', (chunk) => { logs += chunk.toString(); });
  child.on('error', (error) => {
    spawnError = error;
    logs += `${error.stack || error.message}\n`;
  });

  try {
    const deadline = Date.now() + timeoutMs;
    let lastError = null;
    while (Date.now() < deadline) {
      if (spawnError) throw spawnError;
      if (child.exitCode !== null || child.signalCode !== null) {
        throw new Error(`服务在健康检查前退出，退出码: ${child.exitCode}`);
      }

      try {
        const baseUrl = `http://127.0.0.1:${port}`;
        const live = await fetchJson(`${baseUrl}/api/health/live`);
        validateLiveHealth(live);
        const content = await fetchJson(`${baseUrl}/api/health/content`);
        const health = validateContentHealth(content);
        return { port, health, logs };
      } catch (error) {
        lastError = error;
        if (error.message.startsWith('内容健康检查失败:')) throw error;
        await delay(200);
      }
    }

    throw new Error(`服务在 ${timeoutMs}ms 内未就绪: ${lastError?.message || '无响应'}`);
  } catch (error) {
    error.serviceLogs = logs;
    throw error;
  } finally {
    await stopChild(child);
    fs.rmSync(runtimeDir, { recursive: true, force: true });
  }
}

function isMainModule() {
  return process.argv[1]
    && pathToFileURL(path.resolve(process.argv[1])).href === import.meta.url;
}

if (isMainModule()) {
  try {
    const result = await runSmokeTest({
      timeoutMs: Number(process.env.VERIFY_SMOKE_TIMEOUT_MS) || DEFAULT_TIMEOUT_MS,
    });
    console.log(
      `真实服务健康: ${result.health.problemCount} 道题目, ${result.health.problemSetCount} 个题目单`,
    );
  } catch (error) {
    console.error(error.message);
    if (error.serviceLogs?.trim()) {
      console.error('\n--- 服务日志 ---');
      console.error(error.serviceLogs.trimEnd());
      console.error('--- 服务日志结束 ---');
    }
    process.exitCode = 1;
  }
}
