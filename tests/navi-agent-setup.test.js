import test from 'node:test';
import assert from 'node:assert/strict';
import {
  chmodSync,
  mkdirSync,
  mkdtempSync,
  readFileSync,
  rmSync,
  writeFileSync,
} from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { spawnSync } from 'node:child_process';

const repoRoot = path.resolve();
const setupScript = path.join(repoRoot, 'scripts', 'navi', 'rpi-agent-setup.sh');

function writeJson(file, value) {
  writeFileSync(file, `${JSON.stringify(value, null, 2)}\n`);
}

/** 造一个临时仓库：脚本、仓库级 agent 配置、全局配置，以及一个只用来通过 `command -v pi` 的桩。 */
function createFixture({ sync = true } = {}) {
  const root = mkdtempSync(path.join(os.tmpdir(), 'rbook-rpi-setup-'));
  const home = path.join(root, 'home');
  const bin = path.join(root, 'bin');
  const navi = path.join(root, 'repo', 'scripts', 'navi');
  const agentDir = path.join(root, 'repo', '.pi', 'agent');

  mkdirSync(path.join(home, '.pi', 'agent'), { recursive: true });
  mkdirSync(bin, { recursive: true });
  mkdirSync(navi, { recursive: true });
  mkdirSync(agentDir, { recursive: true });

  writeFileSync(path.join(navi, 'rpi-agent-setup.sh'), readFileSync(setupScript, 'utf8'));
  const piStub = path.join(bin, 'pi');
  writeFileSync(piStub, '#!/bin/sh\nexit 0\n');
  chmodSync(piStub, 0o755);

  writeJson(path.join(home, '.pi', 'agent', 'settings.json'), {
    packages: [
      'git:github.com/luw2007/pi-grill',
      'npm:pi-subagents',
      'git:https://github.com/hasit/pi-community-themes',
      'npm:pi-web-access',
    ],
    defaultModel: 'global-model',
    theme: 'light',
  });

  writeJson(path.join(agentDir, 'settings.json'), {
    sessionDir: '~/.pi/agent/sessions',
    prompts: ['../../scripts/navi/rbook-pi-prompt'],
    packages: [
      'git:github.com/luw2007/pi-grill',
      'npm:pi-web-access',
    ],
    packagesExclude: ['pi-subagents', 'pi-community-themes'],
    defaultProvider: 'zzzxin',
  });

  const args = sync ? ['--sync'] : [];
  const result = spawnSync('bash', [path.join('scripts', 'navi', 'rpi-agent-setup.sh'), ...args], {
    cwd: path.join(root, 'repo'),
    encoding: 'utf8',
    env: { ...process.env, HOME: home, PATH: `${bin}:${process.env.PATH}` },
  });

  const settings = JSON.parse(readFileSync(path.join(agentDir, 'settings.json'), 'utf8'));
  return { root, result, settings, agentDir };
}

test('rpi-agent-setup --sync keeps packages excluded by the repository', () => {
  const fixture = createFixture();
  try {
    assert.equal(fixture.result.status, 0, fixture.result.stderr);
    assert.match(fixture.result.stdout, /packagesExclude 排除：pi-subagents, pi-community-themes/);

    // npm 包按包名排除，git 包按仓库名排除；未列出的包照常同步。
    assert.deepEqual(fixture.settings.packages, [
      'git:github.com/luw2007/pi-grill',
      'npm:pi-web-access',
    ]);
    // 排除清单本身留在仓库配置里，不会被同步覆盖掉。
    assert.deepEqual(fixture.settings.packagesExclude, ['pi-subagents', 'pi-community-themes']);
    // 环境级键正常同步，仓库自己的键保留。
    assert.equal(fixture.settings.defaultModel, 'global-model');
    assert.equal(fixture.settings.theme, 'light');
    assert.equal(fixture.settings.sessionDir, '~/.pi/agent/sessions');
    assert.equal(fixture.settings.defaultProvider, 'zzzxin');
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('rpi-agent-setup without --sync leaves packages untouched', () => {
  const fixture = createFixture({ sync: false });
  try {
    assert.equal(fixture.result.status, 0, fixture.result.stderr);
    assert.deepEqual(fixture.settings.packages, [
      'git:github.com/luw2007/pi-grill',
      'npm:pi-web-access',
    ]);
    assert.equal(fixture.settings.theme, undefined);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('this repository excludes pi-subagents but keeps the rest of the global list', () => {
  const settings = JSON.parse(
    readFileSync(path.join(repoRoot, '.pi', 'agent', 'settings.json'), 'utf8'),
  );
  const sources = settings.packages.map((entry) => (
    typeof entry === 'string' ? entry : entry.source
  ));

  assert.ok(!sources.includes('npm:pi-subagents'));
  assert.deepEqual(settings.packagesExclude, ['pi-subagents']);
  assert.ok(sources.includes('npm:pi-web-access'));
  assert.ok(sources.includes('npm:pi-tool-display'));
});
