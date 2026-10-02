#!/usr/bin/env node
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { chromium } from '@playwright/test';
import { buildApp } from '../app.js';

// Browser diagnostics use the installed React fiber only to inspect public graph props/ref.
// No test hooks or implementation data are exposed to application users.
function browserGraph() {
  const element = document.querySelector('.relations3-stage');
  const key = Object.keys(element).find(k => k.startsWith('__reactFiber$'));
  const pending = [element[key]];
  const visited = new Set();
  while (pending.length) {
    const fiber = pending.pop();
    if (!fiber || visited.has(fiber)) continue;
    visited.add(fiber);
    if (fiber?.memoizedProps?.graphData && fiber.ref?.current?.camera) return { props: fiber.memoizedProps, graph: fiber.ref.current };
    if (fiber?.child) pending.push(fiber.child);
    if (fiber?.sibling) pending.push(fiber.sibling);
    if (fiber?.alternate) pending.push(fiber.alternate);
  }
  throw new Error('Cannot inspect the mounted graph component');
}

const output = path.resolve(process.env.R3_BROWSER_OUTPUT || '.tmp/relations3-browser');
fs.mkdirSync(output, { recursive: true });
const app = await buildApp({ logger: false });
let browser;
const report = { date: new Date().toISOString(), scenarios: [], metrics: {}, errors: [], output };
try {
  await app.listen({ host: '127.0.0.1', port: 0 });
  const base = `http://127.0.0.1:${app.server.address().port}`;
  const raw = (await app.inject({ url: '/api/relations' })).json();
  report.summary = raw.summary;
  const counts = new Map(raw.nodes.map(n => [n.id, { pre: 0, next: 0, common: 0 }]));
  for (const e of raw.edges) {
    if (e.type === 'pre') { counts.get(e.source).next++; counts.get(e.target).pre++; }
    else { counts.get(e.source).common++; counts.get(e.target).common++; }
  }
  const mixed = raw.nodes.find(n => Object.values(counts.get(n.id)).every(Boolean));
  const alternate = [...counts].sort((a,b) => Object.values(b[1]).reduce((x,y)=>x+y,0)-Object.values(a[1]).reduce((x,y)=>x+y,0))[0][0];
  const isolated = raw.nodes.find(n => n.isolated);
  assert.ok(mixed && isolated, 'Real catalog needs mixed and isolated samples');
  report.samples = { mixed: mixed.id, busiest: alternate, isolated: isolated.id };
  const executablePath = process.env.R3_CHROMIUM || (fs.existsSync('/usr/bin/chromium') ? '/usr/bin/chromium' : undefined);
  browser = await chromium.launch({ executablePath, headless: process.env.R3_HEADFUL !== '1', args: ['--no-sandbox', '--enable-unsafe-swiftshader', ...(process.env.R3_SOFTWARE_GPU === '0' ? [] : ['--use-angle=swiftshader'])] });
  report.browser = browser.version();
  const context = await browser.newContext({ viewport: { width: 1440, height: 1000 }, deviceScaleFactor: 1 });
  await context.addInitScript(`window.__r3LongTasks=[];new PerformanceObserver(list=>window.__r3LongTasks.push(...list.getEntries().map(e=>({start:e.startTime,duration:e.duration})))).observe({type:'longtask',buffered:true});window.__r3BrowserGraph=${browserGraph.toString()}`);
  const page = await context.newPage();
  page.on('pageerror', e => report.errors.push(e.message));
  const scenario = name => { report.scenarios.push(name); console.log(`✓ ${name}`); };
  const waitReady = async p => { await p.waitForSelector('[data-render-ready="true"]', { timeout: 20000 }); await p.waitForSelector('[data-layout-running="false"]', { timeout: 20000 }); await p.waitForTimeout(650); };
  const snapshot = p => p.evaluate(() => {
    const { props, graph } = window.__r3BrowserGraph();
    const camera = graph.camera(); const target = graph.controls().target;
    return {
      positions: Object.fromEntries(props.graphData.nodes.map(n => [n.id, [n.x,n.y,n.z]])),
      view: { position: [camera.position.x,camera.position.y,camera.position.z], target: [target.x,target.y,target.z] },
      visibleNodes: props.graphData.nodes.filter(n => n.__threeObj?.visible).length,
      visibleEdges: props.graphData.links.filter(e => e.__lineObj?.visible).map(e=>e.id),
      labels: [...document.querySelectorAll('[data-label-id]')].map(el => ({ id: el.dataset.labelId, text: el.textContent.replaceAll('\n', '') })),
    };
  });
  const selectViaSearch = async (p, id) => {
    const node = raw.nodes.find(n => n.id === id);
    await p.getByRole('searchbox').fill(`${node.oj} ${node.problem_id}`);
    await p.locator('.relations3-search-results button').filter({hasText:node.label}).first().click();
    await p.getByRole('button', {name:'清除搜索'}).click();
    await p.waitForTimeout(700);
    assert.equal(await p.locator('.relations3-detail-code').innerText(),node.label);
  };
  const verifyGroups = async (p, id, pre=true, common=true) => {
    const expected = {
      predecessors: pre ? raw.edges.filter(e=>e.type==='pre'&&e.target===id).map(e=>e.source) : [],
      successors: pre ? raw.edges.filter(e=>e.type==='pre'&&e.source===id).map(e=>e.target) : [],
      commons: common ? raw.edges.filter(e=>e.type==='common'&&(e.source===id||e.target===id)).map(e=>e.source===id?e.target:e.source) : [],
    };
    for (const [name,ids] of Object.entries(expected)) assert.deepEqual((await p.locator(`[data-relation-group="${name}"] [data-node-id]`).evaluateAll(els=>els.map(e=>e.dataset.nodeId))).sort(),ids.sort());
  };
  const nodePoint = (p,id) => p.evaluate(id => {
    const {props,graph}=window.__r3BrowserGraph();const n=props.graphData.nodes.find(n=>n.id===id);
    const screen=graph.graph2ScreenCoords(n.x,n.y,n.z);const box=document.querySelector('.relations3-stage').getBoundingClientRect();
    return {x:box.x+screen.x,y:box.y+screen.y};
  },id);
  const openCenter = id => `${base}/relations?oj=${encodeURIComponent(id.slice(0,id.indexOf('/')))}&pid=${encodeURIComponent(id.slice(id.indexOf('/')+1))}`;

  const entryStarted=performance.now();
  // Measure graph readiness without waiting for unrelated page/CDN load events.
  await page.goto(`${base}/relations`,{waitUntil:'commit'});
  await page.waitForSelector('[data-render-ready="true"]',{timeout:20000});
  report.metrics.firstCanvasReadyMs=performance.now()-entryStarted;
  await page.waitForSelector('[data-layout-running="false"]',{timeout:20000});
  report.metrics.firstLayoutSettledMs=performance.now()-entryStarted;
  await waitReady(page);
  const defaultState = await snapshot(page);
  assert.ok(defaultState.labels.length > 0, 'Overview must have readable labels');
  assert.ok(defaultState.labels.some(label => label.text.includes(' · ')));
  assert.equal(await page.locator('.relations3-heading').count(), 0);
  assert.equal(await page.locator('.relations3-details-scroll .relations3-stats').count(), 1);
  const detailsBox = await page.locator('.relations3-details').boundingBox();
  const stageBox = await page.locator('.relations3-stage').boundingBox();
  assert.ok(detailsBox.x + detailsBox.width <= stageBox.x + 1, 'Desktop details belong on the left');
  await page.screenshot({path:path.join(output,'desktop-overview.png')});
  assert.equal(defaultState.visibleNodes,raw.summary.relationNodes);
  assert.equal(defaultState.visibleEdges.length,raw.summary.edges);
  assert.equal(await page.locator('.relations3-detail-code').count(),0);
  assert.equal(new URL(page.url()).pathname,'/relations');
  assert.equal(await page.locator('a[href^="/relations2"], a[href^="/relations3?"]').count(),0);
  for(const url of ['/relations2','/relations-graph/assets/index.js','/relations2-graph/assets/index.js']) assert.equal((await app.inject({url})).statusCode,404);
  scenario('普通入口总览与默认孤立筛选');
  const beforeSearch=defaultState.positions;
  await selectViaSearch(page,mixed.id);
  await verifyGroups(page,mixed.id);
  assert.deepEqual((await snapshot(page)).positions,beforeSearch);
  const centerState = await snapshot(page);
  const full=raw.nodes.find(n=>n.id===mixed.id);
  assert.ok(centerState.labels.some(l=>l.id===mixed.id&&l.text.includes(full.title)));
  scenario('搜索选题、一层关系、完整中心标签和位置稳定');
  await page.screenshot({path:path.join(output,'desktop-focus.png')});
  const centerReason=await page.locator('.relations3-reason').count();
  assert.ok(centerReason>0,'Mixed real sample should have readable relation reasons');
  await page.locator('.relations3-reason summary').first().click();
  assert.ok((await page.locator('.relations3-reason[open] p').first().innerText()).length>0);
  const solutionHref=await page.locator('.relations3-relation-entry a').first().getAttribute('href');
  const solution=await context.newPage();const solutionResponse=await solution.goto(`${base}${solutionHref}`);
  assert.equal(solutionResponse.status(),200);await solution.locator('h2.mb-0').waitFor();await solution.close();
  scenario('阅读真实关系说明并打开邻居题解');
  const firstNeighbor=await page.locator('.relations3-relation-entry [data-node-id]').first().getAttribute('data-node-id');
  await page.locator(`.relations3-relation-entry [data-node-id="${firstNeighbor}"]`).first().click();
  await page.waitForTimeout(650); await verifyGroups(page,firstNeighbor);
  await page.getByRole('button',{name:'← 上一题',exact:true}).click();
  await page.waitForTimeout(650); await verifyGroups(page,mixed.id);
  await selectViaSearch(page,firstNeighbor);await selectViaSearch(page,alternate);
  await page.getByRole('button',{name:'← 上一题',exact:true}).click();await page.waitForTimeout(650);
  await verifyGroups(page,firstNeighbor);
  await page.getByRole('button',{name:'← 上一题',exact:true}).click();await page.waitForTimeout(650);
  await verifyGroups(page,mixed.id);
  assert.deepEqual((await snapshot(page)).positions,beforeSearch);
  scenario('侧栏切换中心与探索历史返回');
  await page.getByLabel('前置关系',{exact:true}).uncheck();
  await verifyGroups(page,mixed.id,false,true);
  assert.deepEqual((await snapshot(page)).visibleEdges.sort(),raw.edges.filter(e=>e.type==='common').map(e=>e.id).sort());
  await page.getByLabel('相似关系',{exact:true}).uncheck();
  assert.equal((await snapshot(page)).visibleEdges.length,0);
  await page.getByLabel('前置关系',{exact:true}).check();await page.getByLabel('相似关系',{exact:true}).check();
  await verifyGroups(page,mixed.id);
  assert.deepEqual((await snapshot(page)).positions,beforeSearch);
  scenario('关系筛选与侧栏同步、两类关闭和恢复');

  await page.waitForTimeout(650);
  const point=await nodePoint(page,mixed.id);
  await page.mouse.move(point.x,point.y);await page.mouse.down();await page.mouse.move(point.x+80,point.y+35,{steps:12});await page.mouse.up();await page.waitForTimeout(500);
  const dragged=await snapshot(page);
  assert.notDeepEqual(dragged.positions[mixed.id],beforeSearch[mixed.id],'Node drag must move the node');
  const saved=await page.evaluate(()=>JSON.parse(localStorage.getItem('rbook.relations3.layout.v1.latest')));
  assert.ok(saved.userPinnedIds.includes(mixed.id));
  await page.reload();await waitReady(page);
  assert.deepEqual((await snapshot(page)).positions,dragged.positions);
  scenario('真实鼠标拖拽固定与刷新恢复三维位置');
  await page.getByRole('button',{name:'重置视角',exact:true}).click();await page.waitForTimeout(650);
  assert.deepEqual((await snapshot(page)).positions,dragged.positions);
  await page.getByRole('button',{name:'重新布局',exact:true}).click();await waitReady(page);
  const reLayout=await snapshot(page);assert.notDeepEqual(reLayout.positions[mixed.id],dragged.positions[mixed.id]);
  await page.waitForTimeout(300);
  assert.deepEqual(await page.evaluate(()=>JSON.parse(localStorage.getItem('rbook.relations3.layout.v1.latest')).userPinnedIds),[]);
  scenario('重置视角保留坐标，重新布局清除用户固定');

  await page.locator('label[for="themeDark"]').click();await page.waitForTimeout(250);
  assert.equal(await page.locator('html').getAttribute('data-bs-theme'),'dark');
  assert.deepEqual((await snapshot(page)).positions,reLayout.positions);
  await page.screenshot({path:path.join(output,'desktop-dark.png')});
  await page.locator('label[for="themeLight"]').click();
  scenario('深浅主题切换不重排');
  await page.route('**/api/relations',route=>route.fulfill({status:503,contentType:'application/json',body:'{"error":"test"}'}));
  await page.getByRole('button',{name:'刷新数据',exact:true}).click();
  await page.getByText('关系数据加载失败：HTTP 503').waitFor();
  assert.equal((await snapshot(page)).visibleNodes,raw.summary.relationNodes);
  await page.unroute('**/api/relations');await page.getByRole('button',{name:'重试加载'}).click();
  await page.getByText('关系数据加载失败：HTTP 503').waitFor({state:'hidden'});
  assert.deepEqual((await snapshot(page)).positions,reLayout.positions);
  scenario('刷新失败保留图与重试成功');
  const beforeResize=await snapshot(page);await page.setViewportSize({width:1100,height:800});await page.waitForTimeout(650);
  assert.deepEqual((await snapshot(page)).positions,beforeResize.positions);
  assert.equal(await page.locator('canvas').evaluate(c=>c.clientWidth),Math.round((await page.locator('.relations3-stage').boundingBox()).width));
  await page.setViewportSize({width:1440,height:1000});await page.waitForTimeout(650);
  scenario('窗口缩放更新画布与取景且保持坐标');

  const metrics=async(name,all=false)=>{
    if(all){await page.getByLabel('显示孤立题目',{exact:true}).check();await page.getByRole('button',{name:'返回总览',exact:true}).click();await page.getByRole('button',{name:'适应视图',exact:true}).click();await page.waitForTimeout(650);}
    await page.evaluate(()=>{window.__r3Frames=[];window.__r3Measuring=true;let prev=performance.now();const tick=now=>{window.__r3Frames.push(now-prev);prev=now;if(window.__r3Measuring)requestAnimationFrame(tick);};requestAnimationFrame(tick);});
    const box=await page.locator('.relations3-stage').boundingBox();
    await page.mouse.move(box.x+box.width*.2,box.y+box.height*.3);await page.mouse.down();
    for(let i=0;i<20;i++){await page.mouse.move(box.x+box.width*(.2+i*.015),box.y+box.height*(.3+i*.008));await page.waitForTimeout(60);}
    await page.mouse.up();
    report.metrics[name]=await page.evaluate(()=>{window.__r3Measuring=false;const frames=window.__r3Frames;const duration=frames.reduce((a,b)=>a+b,0);const {graph}=window.__r3BrowserGraph();const gl=graph.renderer().getContext();const ext=gl.getExtension('WEBGL_debug_renderer_info');return {frames:frames.length,durationMs:duration,fps:frames.length/duration*1000,maximumFrameMs:Math.max(...frames),longTasks:window.__r3LongTasks.filter(t=>t.duration>100),renderer:ext?gl.getParameter(ext.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER),gpuMemory:graph.renderer().info.memory};});
  };
  await metrics('defaultNetwork');await metrics('fullCatalog',true);
  assert.equal((await snapshot(page)).visibleNodes,raw.summary.nodes);
  scenario('默认网络与完整目录的真实旋转/帧率测量');
  await page.getByLabel('显示孤立题目',{exact:true}).uncheck();
  await selectViaSearch(page,isolated.id);await verifyGroups(page,isolated.id);
  assert.ok((await snapshot(page)).visibleNodes>raw.summary.relationNodes);
  scenario('搜索选中孤立题目');

  await page.goto(openCenter(mixed.id));await waitReady(page);await verifyGroups(page,mixed.id);
  scenario('URL 直达恢复指定题目');
  await page.evaluate(()=>window.__r3BrowserGraph().graph.renderer().getContext().getExtension('WEBGL_lose_context').loseContext());
  await page.getByRole('heading',{name:'继续通过清单探索'}).waitFor();
  await selectViaSearch(page,alternate);await verifyGroups(page,alternate);
  await page.getByRole('button',{name:'重试 3D 图形'}).click();await waitReady(page);
  scenario('WebGL context lost 后清单探索与真正重建画布');
  const allocations=async()=>page.evaluate(()=>{
    const {graph}=window.__r3BrowserGraph();const geometries=new Set();let nodeObjects=0;
    graph.scene().traverse(object=>{if(object.geometry)geometries.add(object.geometry);if(object.__graphObjType==='node')nodeObjects++;});
    return {...graph.renderer().info.memory,sceneGeometries:geometries.size,nodeObjects,canvases:document.querySelectorAll('.relations3-stage canvas').length};
  });
  // GPU uploads depend on which meshes have entered the camera's frustum.
  // Check actual scene allocations for growth, and keep upload counts as diagnostics.
  await selectViaSearch(page,mixed.id);
  report.metrics.resourcesBefore=await allocations();
  for(let i=0;i<3;i++){
    await selectViaSearch(page,mixed.id);await selectViaSearch(page,alternate);
    await page.goto(`${base}${mixed.url}`);
    await page.locator('h2.mb-0').waitFor();
    await page.locator(`a[href="/relations?oj=${encodeURIComponent(mixed.oj)}&pid=${encodeURIComponent(mixed.problem_id)}"]`).click();
    await waitReady(page);assert.equal(new URL(page.url()).pathname,'/relations');
  }
  report.metrics.resourcesAfter=await allocations();
  assert.equal(report.metrics.resourcesAfter.canvases,1);
  assert.equal(report.metrics.resourcesAfter.sceneGeometries,report.metrics.resourcesBefore.sceneGeometries);
  assert.equal(report.metrics.resourcesAfter.nodeObjects,raw.summary.nodes);
  scenario('题目页进入默认 3D 关系图与反复进出页面无渲染资源增长');

  const mobile=await browser.newContext({viewport:{width:390,height:844},deviceScaleFactor:1,isMobile:true,hasTouch:true});
  await mobile.addInitScript(`window.__r3BrowserGraph=${browserGraph.toString()}`);
  const mp=await mobile.newPage();mp.on('pageerror',e=>report.errors.push(e.message));
  await mp.goto(openCenter(mixed.id));await waitReady(mp);
  const touchPoint=await nodePoint(mp,mixed.id);await mp.touchscreen.tap(touchPoint.x,touchPoint.y);await mp.waitForTimeout(650);
  assert.equal(await mp.locator('.relations3-drawer-toggle').getAttribute('aria-expanded'),'true');
  await verifyGroups(mp,mixed.id);
  assert.ok((await mp.locator('.relations3-stage').boundingBox()).height>80);
  const mobileStage = await mp.locator('.relations3-stage').boundingBox();
  const mobileDetails = await mp.locator('.relations3-details').boundingBox();
  assert.ok(mobileDetails.y >= mobileStage.y + mobileStage.height - 1, 'Mobile drawer stays below the graph');
  await mp.screenshot({path:path.join(output,'mobile-focus.png')});
  const cdp=await mobile.newCDPSession(mp);
  const mb=await mp.locator('.relations3-stage').boundingBox();
  const oldView=(await snapshot(mp)).view;
  const x=mb.x+mb.width*.2,y=mb.y+mb.height*.35;
  await cdp.send('Input.dispatchTouchEvent',{type:'touchStart',touchPoints:[{x,y,id:1}]});
  for(let i=1;i<=6;i++)await cdp.send('Input.dispatchTouchEvent',{type:'touchMove',touchPoints:[{x:x+i*7,y:y+i*3,id:1}]});
  await cdp.send('Input.dispatchTouchEvent',{type:'touchEnd',touchPoints:[]});await mp.waitForTimeout(300);
  assert.notDeepEqual((await snapshot(mp)).view.position,oldView.position);
  const beforePinch=(await snapshot(mp)).view;
  const cx=mb.x+mb.width*.5,cy=mb.y+mb.height*.5;
  await cdp.send('Input.dispatchTouchEvent',{type:'touchStart',touchPoints:[{x:cx-35,y:cy,id:1},{x:cx+35,y:cy,id:2}]});
  for(let i=1;i<=5;i++)await cdp.send('Input.dispatchTouchEvent',{type:'touchMove',touchPoints:[{x:cx-35-i*5,y:cy,id:1},{x:cx+35+i*5,y:cy,id:2}]});
  await cdp.send('Input.dispatchTouchEvent',{type:'touchEnd',touchPoints:[]});await mp.waitForTimeout(300);
  assert.notDeepEqual((await snapshot(mp)).view.position,beforePinch.position);
  scenario('手机触摸点选、抽屉、旋转和双指缩放');
  await mobile.close();

  const stress={nodes:[{id:'test/C',oj:'test',problem_id:'C',title:'高邻居数测试中心'},...Array.from({length:100},(_,i)=>({id:`test/N${i}`,oj:'test',problem_id:`N${i}`,title:`具有较长标题的邻居题目 ${i}`}))],edges:Array.from({length:100},(_,i)=>({id:`stress${i}`,source:'test/C',target:`test/N${i}`,type:i%2?'common':'pre',reason:`关系说明 ${i}`})),tagStats:[]};
  await page.route('**/api/relations',route=>route.fulfill({status:200,contentType:'application/json',body:JSON.stringify(stress)}));
  await page.goto(`${base}/relations?oj=test&pid=C`);await waitReady(page);
  assert.equal(await page.locator('[data-relation-group="successors"] [data-node-id]').count(),50);
  assert.equal(await page.locator('[data-relation-group="commons"] [data-node-id]').count(),50);
  assert.ok((await snapshot(page)).labels.length<101,'Labels should avoid collisions while all neighbors remain in lists');
  await page.screenshot({path:path.join(output,'high-degree.png')});
  await metrics('hundredNeighbors');
  scenario('100 个直接邻居的完整清单与标签避让');
  const stressBefore=await snapshot(page);
  const selectionStarted=performance.now();
  await page.locator('[data-node-id="test/N0"]').first().click();
  await page.locator('.relations3-detail-code').filter({hasText:'test N0'}).waitFor();
  report.metrics.selectionFeedbackMs=performance.now()-selectionStarted;
  await page.getByRole('button',{name:'← 上一题',exact:true}).click();
  await page.locator('[data-node-id="test/N2"]').first().click();
  await page.waitForTimeout(650);
  const rapid=await snapshot(page);
  assert.deepEqual(rapid.positions,stressBefore.positions);
  const target=rapid.positions['test/N2'];
  assert.ok(rapid.view.target.every((n,i)=>Math.abs(n-target[i])<1e-6));
  scenario('动画过程中快速切换中心，最终目标正确且无重排');

  const unavailable=await browser.newContext({viewport:{width:1280,height:800}});
  await unavailable.addInitScript(()=>{const original=HTMLCanvasElement.prototype.getContext;window.__r3DisableWebGL=true;HTMLCanvasElement.prototype.getContext=function(type,...args){if(window.__r3DisableWebGL&&String(type).startsWith('webgl'))return null;return original.call(this,type,...args);};});
  const unavailablePage=await unavailable.newPage();
  await unavailablePage.goto(openCenter(mixed.id));
  await unavailablePage.getByRole('heading',{name:'继续通过清单探索'}).waitFor();
  await verifyGroups(unavailablePage,mixed.id);
  await selectViaSearch(unavailablePage,alternate);await verifyGroups(unavailablePage,alternate);
  await unavailablePage.evaluate(()=>{window.__r3DisableWebGL=false;});
  await unavailablePage.getByRole('button',{name:'重试 3D 图形'}).click();await waitReady(unavailablePage);
  await unavailable.close();
  scenario('首次无法创建 WebGL 时清单可用，恢复能力后重试成功');

  await page.unroute('**/api/relations');
  await page.route('**/api/relations',route=>route.fulfill({status:200,contentType:'application/json',body:JSON.stringify({nodes:[],edges:[]})}));
  await page.getByRole('button',{name:'刷新数据',exact:true}).click();
  await page.getByText('当前目录没有可浏览的有效题目。').waitFor();
  assert.equal(await page.locator('.relations3-detail-code').count(),0);
  await page.getByRole('button',{name:'知道了'}).click();
  assert.equal((await snapshot(page)).visibleNodes,0);
  scenario('刷新删除中心与空目录具有明确反馈');
  assert.deepEqual(report.errors,[]);
  report.result='passed';
} catch(error) {
  report.result='failed';report.failure=error.stack;
  console.error(error);process.exitCode=1;
} finally {
  if(browser)await browser.close();
  await app.close();
  fs.writeFileSync(path.join(output,'report.json'),JSON.stringify(report,null,2)+'\n');
  console.log(`Browser report: ${path.join(output,'report.json')}`);
}
