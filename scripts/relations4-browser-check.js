#!/usr/bin/env node
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { chromium } from '@playwright/test';
import { buildApp } from '../app.js';

// Inspect the mounted canvas ref for diagnostics, as the 3D browser check does.
// The application does not expose a test-only global or download endpoint.
function browserGraph() {
  const canvas = document.querySelector('.r4-overview canvas');
  const key = Object.keys(canvas).find(key => key.startsWith('__reactFiber$'));
  for (let fiber = canvas[key]; fiber; fiber = fiber.return) {
    for (let hook = fiber.memoizedState; hook && typeof hook === 'object'; hook = hook.next) {
      const value = hook.memoizedState?.current;
      if (value?.canvas === canvas && value.camera && value.positions) return value;
    }
  }
  throw new Error('Mounted canvas graph not found');
}
const output = path.resolve(process.env.R4_BROWSER_OUTPUT || '.tmp/relations4-browser');
fs.mkdirSync(output, { recursive: true });
const report = { date: new Date().toISOString(), scenarios: [], metrics: {}, errors: [] };
const app = await buildApp({ logger: false });
let browser;
try {
  await app.listen({ host: '127.0.0.1', port: 0 });
  const base = `http://127.0.0.1:${app.server.address().port}`;
  const raw = (await app.inject({ url: '/api/relations' })).json();
  report.summary = raw.summary;
  const counts = new Map(raw.nodes.map(n => [n.id, { before: [], after: [], similar: [] }]));
  for (const e of raw.edges) {
    if (e.type === 'pre') { counts.get(e.target).before.push(e.source); counts.get(e.source).after.push(e.target); }
    else { counts.get(e.source).similar.push(e.target); if (e.source !== e.target) counts.get(e.target).similar.push(e.source); }
  }
  const mixed = raw.nodes.find(n => Object.values(counts.get(n.id)).every(a => a.length));
  const isolated = raw.nodes.find(n => n.isolated);
  assert.ok(mixed && isolated, 'Real catalog must contain mixed and isolated samples');
  report.samples = { mixed: mixed.id, isolated: isolated.id };
  const executablePath = process.env.R4_CHROMIUM || ['/Applications/Google Chrome.app/Contents/MacOS/Google Chrome', '/usr/bin/chromium'].find(fs.existsSync);
  browser = await chromium.launch({ executablePath, headless: process.env.R4_HEADFUL !== '1', args: ['--no-sandbox'] });
  report.browser = browser.version();
  const context = await browser.newContext({ viewport: { width: 1440, height: 1000 }, deviceScaleFactor: 1 });
  await context.addInitScript(`window.__r4Graph=${browserGraph.toString()};window.__r4LongTasks=[];new PerformanceObserver(list=>window.__r4LongTasks.push(...list.getEntries().map(e=>e.duration))).observe({type:'longtask',buffered:true});`);
  const page = await context.newPage();
  page.on('pageerror', error => report.errors.push(error.message));
  const scenario = name => { report.scenarios.push(name); console.log(`✓ ${name}`); };
  const ready = async p => { await p.waitForSelector('.r4-overview[data-layout-running="false"]'); await p.waitForSelector('canvas[data-render-ready="true"]'); };
  const snap = p => p.evaluate(() => {
    const g = window.__r4Graph();
    return { camera: { ...g.camera }, positions: structuredClone(g.positions), focus: g.canvas.dataset.focusId, highlighted: +g.canvas.dataset.highlightedEdges, labels: g.labels.map(l => ({ ...l })) };
  });
  const searchSelect = async (p, node) => {
    if (await p.locator('.r4-drawer-toggle').isVisible() && !(await p.locator('.r4-details.is-open').count())) await p.locator('.r4-drawer-toggle').click();
    await p.getByRole('searchbox').fill(`${node.oj} ${node.problem_id}`);
    await p.locator('.r4-search-results button[data-node-id]').filter({ hasText: node.label }).first().click();
    await p.locator('.r4-detail-code').filter({ hasText: node.label }).waitFor({ state: 'attached' });
  };
  const verifyGroups = async (p, id) => {
    for (const [key, ids] of Object.entries(counts.get(id))) {
      const actual = await p.locator(`[data-relation-group="${key}"] [data-node-id]`).evaluateAll(els => els.map(el => el.dataset.nodeId));
      assert.deepEqual(actual.sort(), [...ids].sort(), key);
    }
  };
  const start = performance.now();
  await page.goto(`${base}/relations4`, { waitUntil: 'commit' }); await ready(page);
  report.metrics.initialLayoutMs = performance.now() - start;
  const initial = await snap(page);
  assert.equal(initial.focus, ''); assert.ok(initial.labels.length > 0);
  assert.equal(await page.locator('.r4-stats strong').innerText(), String(raw.summary.relationNodes));
  const detailsBox = await page.locator('.r4-details').boundingBox(), stageBox = await page.locator('.r4-stage').boundingBox();
  assert.ok(detailsBox.x + detailsBox.width <= stageBox.x + 1);
  await page.screenshot({ path: path.join(output, 'overview.png'), fullPage: true });
  scenario('真实全网、默认隐藏孤立题、桌面左侧详情与渐进标签');

  await searchSelect(page, mixed); await verifyGroups(page, mixed.id);
  await page.waitForTimeout(80);
  const selected = await snap(page);
  const degree = Object.values(counts.get(mixed.id)).reduce((sum, ids) => sum + ids.length, 0);
  assert.equal(selected.highlighted, degree);
  const candidate = await page.evaluate(() => {
    const g = window.__r4Graph(), box = g.canvas.getBoundingClientRect();
    const neighbors = new Set((g.scene.index.get(g.scene.selected) || []).flatMap(e => [e.source, e.target]));
    const points = [...g.scene.visible].map(id => ({ id, ...g.project(g.positions[id]) }));
    const hit = points.find(p => !neighbors.has(p.id) && g.scene.index.get(p.id)?.length && p.x > 30 && p.x < g.width - 60 && p.y > 110 && p.y < g.height - 60 && points.every(q => q.id === p.id || Math.hypot(q.x - p.x, q.y - p.y) > 22));
    if (!hit) return null;
    return { id: hit.id, x: hit.x + box.x, y: hit.y + box.y, degree: g.scene.index.get(hit.id).length };
  });
  assert.ok(candidate, 'Need a visible non-neighbor to verify unrestricted hover');
  await page.mouse.move(candidate.x, candidate.y);
  await page.waitForFunction(id => document.querySelector('canvas').dataset.focusId === id, candidate.id);
  let hovered = await snap(page);
  assert.equal(hovered.highlighted, candidate.degree); assert.deepEqual(hovered.positions, selected.positions); assert.deepEqual(hovered.camera, selected.camera);
  report.metrics.hoverFrameMs = await page.locator('.r4-overview canvas').getAttribute('data-hover-frame-ms');
  assert.ok(+report.metrics.hoverFrameMs < 120, 'Hover must render promptly');
  await page.screenshot({ path: path.join(output, 'hover.png'), fullPage: true });
  await page.mouse.move(20, 20); await page.waitForFunction(id => document.querySelector('canvas').dataset.focusId === id, mixed.id);
  assert.equal((await snap(page)).highlighted, degree);
  scenario('已锁定时悬停任意节点下一帧点亮一跳，离开恢复，无布局或视角变化');
  await page.mouse.click(candidate.x, candidate.y);
  await page.locator('.r4-detail-code').filter({ hasText: raw.nodes.find(n => n.id === candidate.id).label }).waitFor();
  assert.deepEqual((await snap(page)).camera, selected.camera);
  await page.getByRole('button', { name: '← 上一题', exact: true }).click(); await verifyGroups(page, mixed.id);
  scenario('点击锁定保持视角，上一题恢复中心与完整关系清单');

  // Drag a real node, then ensure its settled position survives a fresh mount.
  await page.mouse.move(candidate.x, candidate.y);
  await page.mouse.down(); await page.mouse.move(candidate.x + 32, candidate.y + 22, { steps: 5 }); await page.mouse.up();
  const dragged = await snap(page);
  assert.ok(Math.abs(dragged.positions[candidate.id].x - selected.positions[candidate.id].x - 32 / selected.camera.k) < 1e-6);
  assert.ok(Math.abs(dragged.positions[candidate.id].y - selected.positions[candidate.id].y - 22 / selected.camera.k) < 1e-6);
  assert.deepEqual(dragged.camera, selected.camera);
  // Return to the settled coordinates used by the mode-switch assertions.
  await page.mouse.move(candidate.x + 32, candidate.y + 22); await page.mouse.down();
  await page.mouse.move(candidate.x, candidate.y, { steps: 5 }); await page.mouse.up(); await page.mouse.move(20, 20);
  const restoredDrag = await snap(page);
  for (const axis of ['x', 'y']) assert.ok(Math.abs(restoredDrag.positions[candidate.id][axis] - selected.positions[candidate.id][axis]) < 1e-6);
  scenario('节点拖动只改变该节点，拖动结束保持稳定');

  await page.getByRole('button', { name: '分层', exact: false }).click();
  for (const key of ['before', 'after', 'similar']) assert.equal(await page.locator(`[data-layer="${key}"] [data-node-id]`).count(), counts.get(mixed.id)[key].length);
  await page.waitForFunction(count => document.querySelectorAll('[data-relation-edge]').length === count, degree);
  assert.equal(await page.locator('.r4-edge-similar[marker-end]').count(), 0);
  await page.screenshot({ path: path.join(output, 'layers.png'), fullPage: true });
  const layerCenter = page.locator('[data-layer="current"] [data-node-id]');
  await layerCenter.hover();
  await page.getByRole('button', { name: '全景', exact: false }).click();
  assert.deepEqual((await snap(page)).camera, selected.camera);
  assert.deepEqual((await snap(page)).positions, restoredDrag.positions);
  scenario('分层三列与独立相似题、真实方向连线、切回全景保留视角与节点位置');

  await page.getByRole('combobox', { name: '关系类型' }).selectOption('common');
  await page.waitForFunction(count => +document.querySelector('canvas').dataset.highlightedEdges === count, counts.get(mixed.id).similar.length);
  assert.equal(await page.locator('[data-relation-group="before"] [data-node-id]').count(), 0);
  await page.getByRole('combobox', { name: '关系类型' }).selectOption('both');
  await searchSelect(page, isolated); await verifyGroups(page, isolated.id);
  assert.ok(await page.locator('.r4-detail-heading').innerText().then(text => text.includes('尚未维护')));
  await page.getByRole('button', { name: '分层', exact: false }).click();
  assert.equal(await page.locator('[data-layer="current"] [data-node-id]').count(), 1);
  await page.getByRole('button', { name: '全景', exact: false }).click();
  scenario('关系类型筛选与全目录孤立题搜索、分层可访问');

  await searchSelect(page, mixed);
  await page.mouse.move(20, 20);
  const beforeReload = await snap(page);
  await page.reload({ waitUntil: 'commit' }); await ready(page);
  const afterReload = await snap(page);
  assert.deepEqual(afterReload.camera, beforeReload.camera); assert.deepEqual(afterReload.positions, beforeReload.positions);
  await verifyGroups(page, mixed.id);
  await page.evaluate(() => { document.documentElement.dataset.bsTheme = 'dark'; });
  await page.waitForTimeout(80);
  await page.screenshot({ path: path.join(output, 'dark.png'), fullPage: true });
  scenario('URL 选题与缓存视角刷新恢复、深色主题');

  const mobile = await browser.newContext({ viewport: { width: 390, height: 844 }, isMobile: true, hasTouch: true, deviceScaleFactor: 1 });
  await mobile.addInitScript(`window.__r4Graph=${browserGraph.toString()}`);
  const mp = await mobile.newPage(); mp.on('pageerror', e => report.errors.push(e.message));
  await mp.goto(`${base}/relations4`, { waitUntil: 'commit' }); await ready(mp);
  await searchSelect(mp, mixed);
  assert.equal(await mp.locator('.r4-details.is-open').count(), 0);
  await mp.locator('.r4-drawer-toggle').click(); await verifyGroups(mp, mixed.id);
  await mp.locator('.r4-drawer-toggle').click();
  await mp.getByRole('button', { name: '分层', exact: false }).click();
  await mp.screenshot({ path: path.join(output, 'mobile-layers.png'), fullPage: true });
  assert.ok(await mp.evaluate(() => document.documentElement.scrollWidth <= window.innerWidth + 1));
  await mp.getByRole('button', { name: '全景', exact: false }).click();
  await mp.screenshot({ path: path.join(output, 'mobile.png'), fullPage: true });
  await mobile.close();
  scenario('手机底部详情抽屉、搜索定位、分层横向浏览且页面无横向溢出');

  // A failed refresh must preserve the last good catalog and selection.
  await page.route('**/api/relations', route => route.fulfill({ status: 503, contentType: 'application/json', body: '{}' }));
  await page.getByRole('button', { name: '刷新关系数据' }).click();
  await page.getByRole('alert').waitFor(); await verifyGroups(page, mixed.id);
  assert.equal(await page.locator('.r4-detail-code').innerText(), mixed.label);
  await page.unroute('**/api/relations');
  await page.getByRole('button', { name: '重试', exact: true }).click(); await ready(page);
  await page.getByRole('alert').waitFor({ state: 'detached' });
  scenario('刷新失败保留数据，重试恢复');

  const fixtureNodes = Array.from({ length: 101 }, (_, i) => ({ id: `test/N${i}`, oj: 'test', problem_id: `N${i}`, label: `test N${i}`, title: `关系验证题 ${i}`, tags: ['验证'], color: '#278a7a' }));
  const fixture = { nodes: fixtureNodes, edges: fixtureNodes.slice(1).map((n, i) => ({ id: `edge-${i}`, source: i < 30 ? n.id : 'test/N0', target: i < 30 ? 'test/N0' : n.id, type: i < 60 ? 'pre' : 'common', reason: `关系原因 ${i}` })) };
  await page.route('**/api/relations', route => route.fulfill({ status: 200, contentType: 'application/json', body: JSON.stringify(fixture) }));
  await page.goto(`${base}/relations4?oj=test&pid=N0&view=layers`, { waitUntil: 'commit' });
  await page.locator('.r4-detail-code').filter({ hasText: 'test N0' }).waitFor();
  for (const [key, count] of [['before', 30], ['after', 30], ['similar', 40]]) {
    assert.equal(await page.locator(`[data-layer="${key}"] [data-node-id]`).count(), count);
    assert.equal(await page.locator(`[data-relation-group="${key}"] [data-node-id]`).count(), count);
  }
  const list = page.locator('[data-layer="before"] .r4-layer-list');
  await list.evaluate(el => { el.scrollTop = 300; });
  const scrollBefore = await list.evaluate(el => el.scrollTop);
  await page.getByRole('button', { name: '全景', exact: false }).click(); await ready(page);
  const dense = await snap(page);
  for (let i = 0; i < dense.labels.length; i++) for (let j = i + 1; j < dense.labels.length; j++) {
    const a = dense.labels[i], b = dense.labels[j];
    assert.ok(!(a.x < b.x + b.width && a.x + a.width > b.x && a.y < b.y + b.height && a.y + a.height > b.y), 'Canvas labels must not overlap');
  }
  await page.getByRole('button', { name: '分层', exact: false }).click();
  assert.equal(await list.evaluate(el => el.scrollTop), scrollBefore);
  await page.screenshot({ path: path.join(output, 'dense-layers.png'), fullPage: true });
  scenario('100 个邻居不截断清单、标签避让、分层滚动位置切换后恢复');

  const noStorage = await browser.newContext({ viewport: { width: 1100, height: 850 } });
  await noStorage.addInitScript(() => { Object.defineProperty(window, 'localStorage', { get() { throw new DOMException('Storage disabled', 'SecurityError'); } }); });
  const np = await noStorage.newPage(); np.on('pageerror', e => report.errors.push(e.message));
  await np.goto(`${base}/relations4?oj=${mixed.oj}&pid=${mixed.problem_id}`, { waitUntil: 'commit' }); await ready(np);
  await verifyGroups(np, mixed.id); await noStorage.close();
  scenario('浏览器禁用本地存储时仍可布局、选题和查看关系');
  report.metrics.longTasksMs = await page.evaluate(() => window.__r4LongTasks);
  assert.deepEqual(report.errors, []);
  report.result = 'passed';
} catch (error) {
  report.result = 'failed'; report.failure = error.stack; console.error(error); process.exitCode = 1;
} finally {
  if (browser) await browser.close();
  await app.close();
  fs.writeFileSync(path.join(output, 'report.json'), JSON.stringify(report, null, 2) + '\n');
  console.log(`Browser report: ${path.join(output, 'report.json')}`);
}
