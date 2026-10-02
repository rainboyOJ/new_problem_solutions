import test from 'node:test';
import assert from 'node:assert/strict';
import { normalizeGraphResponse, buildVisibleGraph, relationFingerprint, matchesQuery } from '../src/graph-data.ts';
import { buildRelationIndex, focusNeighborhood } from '../src/relation-index.ts';
import { explorationReducer, initialExploration } from '../src/exploration.ts';
import { GraphModel, initialPosition } from '../src/graph-model.ts';
import { loadLayout, saveLayout, clearLayout, validateLayout, LAYOUT_PREFIX } from '../src/layout-store.ts';
import { focusCamera, distance } from '../src/camera.ts';
import { readUrlState, writeUrlState } from '../src/url-state.ts';
import { scopedForce } from '../src/layout-policy.ts';
import { forceCollide, forceManyBody } from 'd3-force-3d';
import { PerspectiveCamera } from 'three';
import { projectLabels, labelText, rectanglesOverlap } from '../src/label-manager.ts';

test('overview labels avoid overlap, expand on zoom, and preserve full priority titles', () => {
  const data = fixture();
  const model = new GraphModel(); model.reconcile(data);
  [...model.nodes.values()].forEach((node, i) => Object.assign(node, { x: (i - 2) * 30, y: 0, z: 0 }));
  const visual = { data, visibleNodes: new Set(data.nodes.map(n => n.id)), focus: focusNeighborhood(buildRelationIndex(data), null, new Set()), matched: new Set(), hovered: '', labelMode: 'full' };
  const camera = new PerspectiveCamera(50, 2, 1, 10000);
  camera.position.z = 2500;
  const measure = text => [...text].length * 12;
  const far = projectLabels(model, visual, camera, 800, 400, measure);
  assert.ok(far.length > 0);
  for (let i = 0; i < far.length; i++) for (let j = i + 1; j < far.length; j++) {
    const rect = l => ({ left: l.left, top: l.top, right: l.left + l.width, bottom: l.top + l.height });
    assert.equal(rectanglesOverlap(rect(far[i]), rect(far[j])), false);
  }
  camera.position.z = 180;
  const near = projectLabels(model, visual, camera, 800, 400, measure);
  assert.ok(near.length > far.length);
  data.nodes[2].title = '一个很长的完整题目名称'.repeat(5);
  visual.hovered = data.nodes[2].id;
  const hovered = projectLabels(model, visual, camera, 800, 400, measure).find(l => l.id === visual.hovered);
  assert.ok(hovered.text.replaceAll('\n', '').includes(data.nodes[2].title));
  model.nodes.get(visual.hovered).z = 300;
  assert.ok(!projectLabels(model, visual, camera, 800, 400, measure).some(l => l.id === visual.hovered));
});

test('labelText switches between full, title, pi, and off modes', () => {
  assert.equal(labelText('oj/A', '标题 A', 'full'), 'oj/A · 标题 A');
  assert.equal(labelText('oj/A', '标题 A', 'title'), '标题 A');
  assert.equal(labelText('oj/A', '标题 A', 'pi'), 'oj/A');
  assert.equal(labelText('oj/A', '标题 A', 'off'), '');
  // 标题缺失时回退到题号，避免空白标签
  assert.equal(labelText('oj/A', '', 'title'), 'oj/A');
  assert.equal(labelText('oj/A', '', 'full'), 'oj/A');
});

function fixture() {
  return normalizeGraphResponse({ nodes: ['A','B','C','D','E'].map(id => ({ id: `oj/${id}`, oj: 'oj', problem_id: id, title: `标题 ${id}`, tags: ['搜索'], difficulty: '提高', color: '#123456' })), edges: [
    { id: 'AC', source: 'oj/A', target: 'oj/C', type: 'pre', reason: '先理解 A' },
    { id: 'CB', source: 'oj/C', target: 'oj/B', type: 'pre' },
    { id: 'DC', source: 'oj/D', target: 'oj/C', type: 'common', reason: '同一模型' },
    { id: 'AD', source: 'oj/A', target: 'oj/D', type: 'common' },
    { id: 'CA', source: 'oj/C', target: 'oj/A', type: 'common' },
  ], tagStats: [{ tag: '搜索', count: 5, color: '#123456' }] });
}
const filters = { relationMode: 'both', showIsolated: false };

test('one-hop focus distinguishes direction, multiple roles, and edges between neighbors', () => {
  const data = fixture();
  const visible = buildVisibleGraph(data, filters, 'oj/C', new Set());
  const f = focusNeighborhood(buildRelationIndex(data), 'oj/C', visible.edgeIds);
  assert.deepEqual(f.predecessors.map(e=>e.nodeId), ['oj/A']);
  assert.deepEqual(f.successors.map(e=>e.nodeId), ['oj/B']);
  assert.deepEqual(f.commons.map(e=>e.nodeId), ['oj/D','oj/A']);
  assert.equal(f.predecessors[0].reason, '先理解 A');
  assert.deepEqual([...f.nodeIds].sort(), ['oj/A','oj/B','oj/C','oj/D']);
  assert.equal(f.edgeIds.has('AD'), false);
});
test('filters, selected isolates, matches and empty edge choices agree', () => {
  const data=fixture();
  let visible=buildVisibleGraph(data,{...filters,relationMode:'common'},'oj/C',new Set(['oj/E']));
  assert.ok(visible.nodeIds.has('oj/E'));
  const f=focusNeighborhood(buildRelationIndex(data),'oj/C',visible.edgeIds);
  assert.equal(f.predecessors.length+f.successors.length,0);
  assert.equal(f.commons.length,2);
  visible=buildVisibleGraph(data,{...filters,relationMode:'pre'},'oj/E',new Set());
  assert.ok(visible.edges.every(e=>e.type==='pre'));
  assert.equal(data.nodes.find(n=>n.id==='oj/E').isolated,true);
});
test('normalization rejects invalid/duplicate records and recomputes isolated counts',()=>{
  const base=fixture();
  const data=normalizeGraphResponse({...base,nodes:[...base.nodes,base.nodes[0],{id:'bad'}],edges:[...base.edges,base.edges[0],{id:'bad',source:'oj/E',target:'missing',type:'pre'},{id:'unknown',source:'oj/E',target:'oj/C',type:'other'}]});
  assert.equal(data.nodes.length,5);
  assert.equal(data.edges.length,5);
  assert.equal(data.discarded,5);
  assert.equal(data.summary.isolatedNodes,1);
  assert.equal(data.tagStats[0].color,data.nodes[0].color);
  assert.ok(matchesQuery(data.nodes[0],'提高'));
  assert.ok(matchesQuery(data.nodes[0],'OJ'));
});
test('fingerprint is order-independent and metadata-independent but includes relation types',()=>{
  const a=fixture();
  const b={...a,nodes:[...a.nodes].reverse().map(n=>({...n,title:'新标题'})),edges:[...a.edges].reverse().map(e=>({...e,reason:'新说明'}))};
  assert.equal(relationFingerprint(a),relationFingerprint(b));
  assert.notEqual(relationFingerprint(a),relationFingerprint({...a,edges:a.edges.map((e,i)=>i?e:{...e,type:'common'})}));
});
test('engine mutations cannot affect business endpoints and objects survive metadata updates',()=>{
  const a=fixture(); const model=new GraphModel(); model.reconcile(a);
  const n=model.nodes.get('oj/C'); const link=model.links.get('AC');
  link.source=model.nodes.get(link.sourceId);link.target=n;
  n.x=999;model.freeze();
  const original=relationFingerprint(a);
  const graph=model.graphData;
  model.reconcile({...a,nodes:a.nodes.map(n=>({...n,title:'改标题'}))});
  assert.equal(model.nodes.get('oj/C'),n);
  assert.equal(model.graphData,graph);
  assert.equal(n.x,999);
  assert.equal(a.edges[0].source,'oj/A');
  assert.equal(relationFingerprint(a),original);
  assert.doesNotThrow(()=>JSON.stringify(model.snapshot()));
});
test('catalog additions preserve coordinates and user pins; deleting nodes cleans pins',()=>{
  const a=fixture();const m=new GraphModel();m.reconcile(a);m.pin('oj/C');
  const n=m.nodes.get('oj/C');const p={x:n.x,y:n.y,z:n.z};
  const next=normalizeGraphResponse({...a,nodes:[...a.nodes,{id:'oj/F',oj:'oj',problem_id:'F'}]});
  m.reconcile(next);assert.deepEqual({x:n.x,y:n.y,z:n.z},p);assert.ok(m.pinned.has('oj/C'));
  m.reconcile(normalizeGraphResponse({...next,nodes:next.nodes.filter(n=>n.id!=='oj/C')}));
  assert.equal(m.pinned.has('oj/C'),false);
});
test('three-dimensional seeds are deterministic, finite, and not flattened',()=>{
  assert.deepEqual(initialPosition('oj/A',false),initialPosition('oj/A',false));
  assert.notEqual(initialPosition('oj/A',false).z,0);
  assert.notDeepEqual(initialPosition('oj/A',false,2),initialPosition('oj/A',false,3));
  const p=initialPosition('oj/E',true);assert.ok(Math.hypot(p.x,p.y,p.z)>=1300);
});
test('temporary freezing does not become user pinning and release respects real pins',()=>{
  const m=new GraphModel();m.reconcile(fixture());m.pin('oj/A');m.release(new Set(['oj/A','oj/C']));
  assert.equal(m.nodes.get('oj/C').fx,undefined);assert.notEqual(m.nodes.get('oj/A').fx,undefined);
  m.freeze();assert.deepEqual(m.snapshot().userPinnedIds,['oj/A']);
});
test('scoped 3D forces exclude hidden nodes without renumbering them',()=>{
  const nodes=[{id:'hidden',index:0,x:10000,y:10000,z:10000,vx:0,vy:0,vz:0},{id:'a',index:1,x:0,y:0,z:0,vx:0,vy:0,vz:0},{id:'b',index:2,x:1,y:1,z:1,vx:0,vy:0,vz:0}];
  for(const native of [forceCollide(14).iterations(2),forceManyBody().strength(-30)]){
    const force=scopedForce(native,new Set(['a','b']));force.initialize(nodes,()=>0.6,3);force(.5);
    assert.equal(nodes[0].vx,0);assert.equal(nodes[1].index,1);
    assert.ok(Number.isFinite(nodes[1].vx)&&Number.isFinite(nodes[2].vz));
  }
});
test('exploration avoids duplicates, branches after back, and skips deleted history nodes',()=>{
  let s=initialExploration(null);
  for(const id of ['oj/A','oj/B','oj/C'])s=explorationReducer(s,{type:'select',id});
  s=explorationReducer(s,{type:'select',id:'oj/C'});assert.equal(s.entries.length,4);
  s=explorationReducer(s,{type:'back'});assert.equal(s.entries[s.cursor].id,'oj/B');
  s=explorationReducer(s,{type:'select',id:'oj/D'});assert.deepEqual(s.entries.map(e=>e.id),[null,'oj/A','oj/B','oj/D']);
  s=explorationReducer(s,{type:'reconcile',validIds:new Set(['oj/A','oj/D'])});
  s=explorationReducer(s,{type:'back'});assert.equal(s.entries[s.cursor].id,'oj/A');
});
test('deleted center returns to overview and history can restore camera checkpoints',()=>{
  const view={position:{x:1,y:2,z:3},target:{x:0,y:0,z:0}};
  let s=initialExploration('oj/A');s=explorationReducer(s,{type:'select',id:'oj/B',camera:view});
  s=explorationReducer(s,{type:'back'});assert.deepEqual(s.entries[s.cursor].camera,view);
  s=explorationReducer(s,{type:'reconcile',validIds:new Set(['oj/B'])});assert.equal(s.entries[s.cursor].id,null);
});
test('refresh of a valid catalog preserves selection and camera revision',()=>{
  let s=initialExploration('oj/A');
  s=explorationReducer(s,{type:'select',id:'oj/B'});
  assert.equal(explorationReducer(s,{type:'reconcile',validIds:new Set(['oj/A','oj/B'])}),s);
  const pruned=explorationReducer(s,{type:'reconcile',validIds:new Set(['oj/B'])});
  assert.equal(pruned.entries[pruned.cursor].id,'oj/B');
  assert.equal(pruned.revision,s.revision);
});
test('camera fits origin, zero direction, long spans and portrait viewport with finite results',()=>{
  const center={x:0,y:0,z:0};const current={position:center,target:center};const points=[center,{x:1000,y:0,z:0},{x:-800,y:200,z:100}];
  for(const aspect of [16/9,1,9/16,0,NaN]){
    const view=focusCamera(center,points,current,aspect);
    assert.ok(Object.values(view.position).every(Number.isFinite));
    const half=Math.min(25*Math.PI/180,Math.atan(Math.tan(25*Math.PI/180)*(aspect>0&&Number.isFinite(aspect)?aspect:1)));
    assert.ok(distance(view.position,center)*Math.sin(half)>=1010);
    assert.deepEqual(view.target,center);
  }
  assert.ok(distance(focusCamera(center,[],current,1).position,center)>50);
});
test('camera maintains current viewing direction when selecting distant centers',()=>{
  const current={position:{x:100,y:20,z:50},target:{x:0,y:0,z:0}};
  const center={x:1000,y:0,z:-300};const v=focusCamera(center,[center],current,1);
  const a=v.position.x-center.x,b=v.position.z-center.z;assert.ok(Math.abs(a/b-2)<1e-8);
});
function storage(){const m=new Map();return {getItem:k=>m.get(k)||null,setItem:(k,v)=>m.set(k,v),removeItem:k=>m.delete(k)};}
test('cache validates numbers, deletes stale IDs, migrates additions, and bounds snapshots',()=>{
  const s=storage();const m=new GraphModel();m.reconcile(fixture());m.pin('oj/A');let saved=m.snapshot();
  assert.ok(saveLayout(s,saved));
  const ids=new Set(['oj/A','oj/F']);const loaded=loadLayout(s,'new-fingerprint',ids);
  assert.deepEqual(Object.keys(loaded.positions),['oj/A']);assert.deepEqual(loaded.userPinnedIds,['oj/A']);
  saved={...saved,fingerprint:'new'};saveLayout(s,saved);assert.equal(s.getItem(`${LAYOUT_PREFIX}.${m.fingerprint}`),null);
  clearLayout(s,'new');assert.equal(loadLayout(s,'new',ids),null);
  assert.equal(validateLayout({...saved,version:2},ids),null);
  assert.deepEqual(validateLayout({...saved,positions:{'oj/A':{x:Infinity,y:0,z:0}}},ids).positions,{});
});
test('broken JSON and unavailable/throwing storage never prevent graph use',()=>{
  const s=storage();s.setItem(`${LAYOUT_PREFIX}.bad`,'{');assert.equal(loadLayout(s,'bad',new Set()),null);
  const throwing={getItem(){throw Error('blocked');},setItem(){throw Error('quota');},removeItem(){throw Error('blocked');}};
  assert.equal(loadLayout(throwing,'any',new Set()),null);
  assert.equal(saveLayout(throwing,new GraphModel().snapshot()),false);
  assert.doesNotThrow(()=>clearLayout(throwing,'any'));
});
test('URL encodes special problem IDs and handles strict three-way relation modes',()=>{
  const url=new URL('http://localhost/relations?extra=keep');
  assert.deepEqual(readUrlState(url),{selectedId:null,...filters});
  const state={selectedId:'oj/A/B & 中文',relationMode:'pre',showIsolated:true};
  const next=writeUrlState(url,state);assert.equal(next.searchParams.get('extra'),'keep');assert.equal(next.searchParams.get('edges'),'pre');
  assert.deepEqual(readUrlState(next),state);
  // 旧值 none / 非法值一律回退 both
  assert.equal(readUrlState(new URL('http://localhost/relations?edges=none')).relationMode,'both');
  assert.equal(readUrlState(new URL('http://localhost/relations?edges=junk')).relationMode,'both');
  assert.equal(readUrlState(new URL('http://localhost/relations?edges=common')).relationMode,'common');
  assert.equal(readUrlState(new URL('http://localhost/relations?edges=pre,common')).relationMode,'both');
  assert.equal(writeUrlState(next,{...state,selectedId:null}).searchParams.has('pid'),false);
});
