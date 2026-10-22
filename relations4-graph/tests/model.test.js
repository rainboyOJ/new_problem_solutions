import test from 'node:test';
import assert from 'node:assert/strict';
import { normalizeGraphResponse, buildRelationIndex, focusNeighborhood, buildVisibleGraph, layerGroups, edgeRole, effectiveFocus, readState, writeState } from '../src/model.ts';
import { createLayout, validPositions } from '../src/layout.ts';

const fixture = () => normalizeGraphResponse({
  nodes: ['A', 'B', 'C', 'D', 'alone'].map(id => ({ id: `test/${id}`, oj: 'test', problem_id: id })),
  edges: [
    { id: 'AB', source: 'test/A', target: 'test/B', type: 'pre' },
    { id: 'BA', source: 'test/B', target: 'test/A', type: 'pre' },
    { id: 'BC', source: 'test/B', target: 'test/C', type: 'pre' },
    { id: 'BD', source: 'test/B', target: 'test/D', type: 'common', reason: '相同模型' },
    { id: 'AC', source: 'test/A', target: 'test/C', type: 'common' },
  ],
});
test('focus includes incident edges only, preserving prerequisite direction and cycles', () => {
  const data = fixture(), index = buildRelationIndex(data), visible = buildVisibleGraph(data, { relationMode: 'both', showIsolated: false }, null, new Set());
  const focus = focusNeighborhood(index, 'test/B', visible.edgeIds);
  assert.deepEqual([...focus.edgeIds], ['AB', 'BA', 'BC', 'BD']);
  assert.deepEqual(layerGroups(focus).map(g => g.entries.map(e => e.nodeId)), [['test/A'], ['test/B'], ['test/A', 'test/C']]);
  assert.deepEqual(focus.commons.map(e => e.nodeId), ['test/D']);
  assert.equal(edgeRole(data.edges[0], 'test/B'), 'before');
  assert.equal(edgeRole(data.edges[1], 'test/B'), 'after');
  assert.equal(edgeRole(data.edges[3], 'test/B'), 'similar');
  assert.equal(edgeRole(data.edges[4], 'test/B'), null);
});
test('hover anywhere overrides a locked selection and leaving restores it', () => {
  assert.equal(effectiveFocus('test/D', 'test/B'), 'test/D');
  assert.equal(effectiveFocus('', 'test/B'), 'test/B');
  assert.equal(effectiveFocus('', null), '');
});
test('search and selected isolated nodes remain discoverable without removing the network', () => {
  const data = fixture(), filters = { relationMode: 'both', showIsolated: false };
  const normal = buildVisibleGraph(data, filters, null, new Set());
  const searched = buildVisibleGraph(data, filters, null, new Set(['test/alone']));
  assert.equal(normal.nodeIds.size, 4);
  assert.equal(searched.nodeIds.size, 5);
  assert.deepEqual(searched.edgeIds, normal.edgeIds);
  const common = buildVisibleGraph(data, { ...filters, relationMode: 'common' }, 'test/alone', new Set());
  assert.ok(common.nodeIds.has('test/alone'));
  assert.deepEqual([...common.edgeIds], ['BD', 'AC']);
});
test('mode and existing deep-link semantics round trip, including encoded problem ids', () => {
  const state = { selectedId: 'HDU/A/B & 中文', relationMode: 'common', showIsolated: true, view: 'layers' };
  const url = writeState(new URL('https://example.test/relations4?unrelated=keep'), state);
  assert.deepEqual(readState(url), state);
  assert.equal(url.searchParams.get('unrelated'), 'keep');
  const fallback = readState(new URL('https://example.test/relations4?view=unknown&edges=none'));
  assert.equal(fallback.view, 'overview'); assert.equal(fallback.relationMode, 'both');
});
test('layout handles cycles and isolated nodes deterministically with finite distinct positions', () => {
  const data = fixture(), input = { nodes: data.nodes, edges: data.edges };
  const a = createLayout(input), b = createLayout(input);
  assert.deepEqual(a, b); assert.ok(validPositions(a, data.nodes));
  assert.equal(new Set(Object.values(a).map(p => `${p.x},${p.y}`)).size, data.nodes.length);
  assert.equal(typeof data.edges[0].source, 'string', 'force simulation must not mutate shared graph edges');
  assert.equal(validPositions({ ...a, 'test/B': { x: Infinity, y: 0 } }, data.nodes), false);
  assert.deepEqual(createLayout({ nodes: [], edges: [] }), {});
});
