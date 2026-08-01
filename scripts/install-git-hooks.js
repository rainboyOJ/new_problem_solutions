#!/usr/bin/env node

import fs from 'node:fs';
import path from 'node:path';
import { spawnSync } from 'node:child_process';
import { pathToFileURL } from 'node:url';

export function installGitHooks(cwd = process.cwd()) {
  const rootResult = spawnSync('git', ['rev-parse', '--show-toplevel'], {
    cwd,
    encoding: 'utf8',
  });

  if (rootResult.error?.code === 'ENOENT' || rootResult.status !== 0) {
    return false;
  }

  const repoRoot = rootResult.stdout.trim();
  const hookPath = path.join(repoRoot, '.githooks', 'pre-push');
  if (!fs.existsSync(hookPath)) {
    throw new Error(`Git hook does not exist: ${hookPath}`);
  }

  const configResult = spawnSync(
    'git',
    ['config', '--local', 'core.hooksPath', '.githooks'],
    { cwd: repoRoot, encoding: 'utf8' },
  );
  if (configResult.status !== 0) {
    throw new Error(configResult.stderr.trim() || 'Unable to configure core.hooksPath');
  }

  console.log('Git hooks configured: core.hooksPath=.githooks');
  return true;
}

function isMainModule() {
  return process.argv[1]
    && pathToFileURL(path.resolve(process.argv[1])).href === import.meta.url;
}

if (isMainModule()) {
  try {
    installGitHooks();
  } catch (error) {
    console.error(`Git hook installation failed: ${error.message}`);
    process.exitCode = 1;
  }
}
