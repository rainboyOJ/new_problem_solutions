import test from 'node:test';
import assert from 'node:assert/strict';
import {
  mkdtempSync,
  mkdirSync,
  renameSync,
  rmSync,
  writeFileSync,
} from 'node:fs';
import { tmpdir } from 'node:os';
import path from 'node:path';
import ProblemManager from '../lib/problem.js';
import ProblemSetManager from '../lib/problem-set.js';
import ContentService, { ContentRenderError } from '../lib/content-service.js';
import LruCache from '../lib/lru-cache.js';
import { buildApp } from '../app.js';

const silentLogger = {
  error() {},
  warn() {},
};

function writeProblem(root, oj, id, extra = '') {
  const directory = path.join(root, oj, id);
  mkdirSync(directory, { recursive: true });
  writeFileSync(path.join(directory, 'index.md'), [
    '---',
    `oj: ${oj}`,
    `problem_id: ${id}`,
    `title: ${id}`,
    extra,
    '---',
    '',
    '# Solution',
  ].filter((line) => line !== '').join('\n'));
}

function createFixture() {
  const root = mkdtempSync(path.join(tmpdir(), 'rbook-content-'));
  const problemsDir = path.join(root, 'problems');
  const problemSetsDir = path.join(root, 'problem-sets');
  mkdirSync(problemsDir);
  mkdirSync(problemSetsDir);
  writeProblem(problemsDir, 'testoj', 'valid');
  writeProblem(problemsDir, 'testoj', 'invalid', 'title: duplicate');
  writeFileSync(path.join(problemSetsDir, 'valid-set.md'), [
    '---',
    'title: Valid Set',
    'order: 1',
    '---',
    '',
    '# Valid Set',
    '',
    '- [ ] [[problem: testoj,valid]]',
  ].join('\n'));
  writeFileSync(path.join(problemSetsDir, 'invalid-set.md'), [
    '---',
    'title: Invalid',
    'title: Duplicate',
    '---',
  ].join('\n'));

  const problemManager = new ProblemManager({ auto_load: false, baseDir: problemsDir });
  const problemSetManager = new ProblemSetManager(problemManager, {
    auto_load: false,
    baseDir: problemSetsDir,
  });
  const contentService = new ContentService({
    problemManager,
    problemSetManager,
    revisionProvider: () => 'revision-1',
    logger: silentLogger,
  });

  return { root, problemsDir, problemSetsDir, problemManager, problemSetManager, contentService };
}

test('LruCache evicts the least recently used entry', () => {
  const cache = new LruCache(2);
  cache.set('a', 1);
  cache.set('b', 2);
  assert.equal(cache.get('a'), 1);
  cache.set('c', 3);
  assert.equal(cache.get('b'), undefined);
  assert.equal(cache.get('a'), 1);
  assert.equal(cache.get('c'), 3);
});

test('ContentService activates valid items and isolates invalid frontmatter', async () => {
  const fixture = createFixture();
  try {
    await fixture.contentService.initialize();
    const health = fixture.contentService.detailedHealth();
    assert.equal(health.state, 'degraded');
    assert.equal(health.activeRevision, 'revision-1');
    assert.equal(health.problemCount, 1);
    assert.equal(health.problemSetCount, 1);
    assert.equal(health.errorCount, 2);
    assert.ok(fixture.problemManager.find('testoj', 'valid'));
    assert.equal(fixture.problemManager.find('testoj', 'invalid'), undefined);
    assert.equal(fixture.problemSetManager.find('invalid-set'), null);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('ContentService makes the unified catalog unavailable after a root failure', async () => {
  const fixture = createFixture();
  const hiddenSets = `${fixture.problemSetsDir}.hidden`;
  try {
    await fixture.contentService.initialize();
    renameSync(fixture.problemSetsDir, hiddenSets);
    await fixture.contentService.requestRefresh('revision-2');
    const health = fixture.contentService.publicHealth();
    assert.equal(health.state, 'unavailable');
    assert.equal(health.activeRevision, null);
    assert.equal(health.lastSuccessfulRevision, 'revision-1');
    assert.equal(health.problemCount, 0);
    assert.equal(health.problemSetCount, 0);

    renameSync(hiddenSets, fixture.problemSetsDir);
    await fixture.contentService.requestRefresh('revision-3');
    assert.equal(fixture.contentService.publicHealth().activeRevision, 'revision-3');
  } finally {
    if (!fixture.problemSetManager.baseDir.includes('.hidden')) {
      try { renameSync(hiddenSets, fixture.problemSetsDir); } catch {}
    }
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('ContentService quarantines an item after lazy rendering fails', async () => {
  const fixture = createFixture();
  try {
    await fixture.contentService.initialize();
    assert.throws(
      () => fixture.contentService.render('problem', 'testoj/valid', () => {
        throw new Error('broken include');
      }),
      ContentRenderError,
    );
    assert.equal(fixture.problemManager.find('testoj', 'valid'), undefined);
    assert.equal(fixture.contentService.publicHealth().state, 'degraded');
    assert.equal(fixture.contentService.cache.size, 0);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('ContentService blocks new requests while draining existing leases', async () => {
  const fixture = createFixture();
  try {
    await fixture.contentService.initialize();
    const release = fixture.contentService.acquireRequest();
    assert.equal(typeof release, 'function');
    assert.equal(fixture.contentService.enterSwitching(), true);
    assert.equal(fixture.contentService.acquireRequest(), null);
    const drained = fixture.contentService.waitForDrain(100);
    release();
    assert.equal(await drained, true);
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('ContentService times out refreshes and coalesces pending revisions', async () => {
  const fixture = createFixture();
  try {
    const snapshot = fixture.contentService.buildSnapshot();
    fixture.contentService.refreshTimeoutMs = 20;
    fixture.contentService.snapshotBuilder = () => new Promise(() => {});
    await fixture.contentService.requestRefresh('timed-out');
    assert.equal(fixture.contentService.state, 'unavailable');
    assert.equal(fixture.contentService.activeRevision, null);

    let releaseFirst;
    let builds = 0;
    fixture.contentService.refreshTimeoutMs = 1_000;
    fixture.contentService.snapshotBuilder = async () => {
      builds += 1;
      if (builds === 1) {
        await new Promise((resolve) => { releaseFirst = resolve; });
      }
      return snapshot;
    };

    const first = fixture.contentService.requestRefresh('revision-a');
    await new Promise((resolve) => setImmediate(resolve));
    fixture.contentService.requestRefresh('revision-b');
    fixture.contentService.requestRefresh('revision-c');
    releaseFirst();
    await first;

    assert.equal(builds, 2);
    assert.equal(fixture.contentService.activeRevision, 'revision-c');
    assert.equal(fixture.contentService.state, 'degraded');
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('content routes return centered HTML or structured JSON while switching', async () => {
  const fixture = createFixture();
  try {
    await fixture.contentService.initialize();
    fixture.contentService.enterSwitching();
    const app = await buildApp({
      logger: false,
      problemManager: fixture.problemManager,
      problemSetManager: fixture.problemSetManager,
      contentService: fixture.contentService,
    });
    try {
      const html = await app.inject({ method: 'GET', url: '/' });
      assert.equal(html.statusCode, 503);
      assert.match(html.body, /内容暂时不可用/);
      assert.match(html.body, /content-unavailable__title/);

      const api = await app.inject({ method: 'GET', url: '/api/problems' });
      assert.equal(api.statusCode, 503);
      assert.deepEqual(api.json(), {
        error: 'CONTENT_UNAVAILABLE',
        message: '内容暂时不可用',
        state: 'switching',
        statusCode: 503,
      });

      const live = await app.inject({ method: 'GET', url: '/api/health/live' });
      assert.equal(live.statusCode, 200);
      const content = await app.inject({ method: 'GET', url: '/api/health/content' });
      assert.equal(content.statusCode, 200);
      assert.equal(content.json().state, 'switching');
      const stylesheet = await app.inject({ method: 'GET', url: '/stylesheets/style.css' });
      assert.equal(stylesheet.statusCode, 200);
    } finally {
      await app.close();
    }
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('unavailable content keeps HTTP alive and shows the update failure state', async () => {
  const fixture = createFixture();
  try {
    fixture.problemManager.baseDir = path.join(fixture.root, 'missing-problems');
    await fixture.contentService.initialize();
    const app = await buildApp({
      logger: false,
      problemManager: fixture.problemManager,
      problemSetManager: fixture.problemSetManager,
      contentService: fixture.contentService,
    });
    try {
      const page = await app.inject({ method: 'GET', url: '/' });
      assert.equal(page.statusCode, 503);
      assert.match(page.body, /内容更新失败，请稍后再试/);
      const live = await app.inject({ method: 'GET', url: '/api/health/live' });
      assert.equal(live.statusCode, 200);
      const health = await app.inject({ method: 'GET', url: '/api/health/content' });
      assert.equal(health.statusCode, 503);
      assert.equal(health.json().activeRevision, null);
    } finally {
      await app.close();
    }
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('health detail authentication hides errors from the public endpoint', async () => {
  const fixture = createFixture();
  const originalNodeEnv = process.env.NODE_ENV;
  const originalToken = process.env.CONTENT_HEALTH_TOKEN;
  try {
    await fixture.contentService.initialize();
    process.env.NODE_ENV = 'production';
    delete process.env.CONTENT_HEALTH_TOKEN;
    const app = await buildApp({
      logger: false,
      problemManager: fixture.problemManager,
      problemSetManager: fixture.problemSetManager,
      contentService: fixture.contentService,
    });
    try {
      const publicResponse = await app.inject({ method: 'GET', url: '/api/health/content' });
      assert.equal(publicResponse.statusCode, 200);
      assert.equal(Object.hasOwn(publicResponse.json(), 'errors'), false);

      const disabled = await app.inject({ method: 'GET', url: '/api/health/content/details' });
      assert.equal(disabled.statusCode, 404);

      process.env.CONTENT_HEALTH_TOKEN = 'test-health-token';
      const unauthorized = await app.inject({ method: 'GET', url: '/api/health/content/details' });
      assert.equal(unauthorized.statusCode, 401);
      const detailed = await app.inject({
        method: 'GET',
        url: '/api/health/content/details',
        headers: { authorization: 'Bearer test-health-token' },
      });
      assert.equal(detailed.statusCode, 200);
      assert.ok(detailed.json().errors.length > 0);
      assert.ok(detailed.json().errors[0].path);
    } finally {
      await app.close();
    }
  } finally {
    if (originalNodeEnv === undefined) delete process.env.NODE_ENV;
    else process.env.NODE_ENV = originalNodeEnv;
    if (originalToken === undefined) delete process.env.CONTENT_HEALTH_TOKEN;
    else process.env.CONTENT_HEALTH_TOKEN = originalToken;
    rmSync(fixture.root, { recursive: true, force: true });
  }
});

test('a lazy API render failure removes the active problem and returns 404', async () => {
  const fixture = createFixture();
  try {
    await fixture.contentService.initialize();
    rmSync(path.join(fixture.problemsDir, 'testoj', 'valid', 'index.md'));
    const app = await buildApp({
      logger: false,
      problemManager: fixture.problemManager,
      problemSetManager: fixture.problemSetManager,
      contentService: fixture.contentService,
    });
    try {
      const response = await app.inject({
        method: 'GET',
        url: '/api/problems/testoj/valid',
      });
      assert.equal(response.statusCode, 404);
      assert.equal(fixture.problemManager.find('testoj', 'valid'), undefined);
      assert.equal(fixture.contentService.state, 'degraded');
    } finally {
      await app.close();
    }
  } finally {
    rmSync(fixture.root, { recursive: true, force: true });
  }
});
