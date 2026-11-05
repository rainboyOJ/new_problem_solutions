import test from 'node:test';
import assert from 'node:assert/strict';
import { existsSync, readFileSync } from 'node:fs';
import { join } from 'node:path';

// The Scriba skill is a doc that must keep matching its own scripts and the
// primitive catalog. Rendering needs a Scriba checkout, so these checks stay
// path-and-text only: they catch a renamed script, a dropped reference, or a
// `\shape{…}{Type}` in the self-test fixture naming a primitive that does not
// exist.

const root = process.cwd();
const skill = join(root, '.agents/skills/oj-scriba-visualizer');

const read = (path) => readFileSync(path, 'utf8');

/** The 21 production primitives, per Scriba docs/spec/primitives.md. */
const PRIMITIVES = new Set([
  'Array', 'Grid', 'DPTable', 'Graph', 'Tree', 'NumberLine', 'Matrix', 'Heatmap',
  'Stack', 'Plane2D', 'MetricPlot', 'CodePanel', 'HashMap', 'LinkedList', 'Queue',
  'Deque', 'VariableWatch', 'Hypercube', 'Forest', 'Bar', 'TraceTable', 'Equation',
]);

test('oj-scriba-visualizer keeps its scripts and references wired', () => {
  const main = join(skill, 'SKILL.md');
  assert.ok(existsSync(main), 'missing oj-scriba-visualizer/SKILL.md');
  const text = read(main);

  for (const ref of ['primitive-cheatsheet.md', 'rbook-integration.md', 'worked-example.md']) {
    assert.ok(existsSync(join(skill, 'references', ref)), `missing reference: ${ref}`);
    assert.match(text, new RegExp(ref.replace('.', '\\.')), `SKILL.md does not route to ${ref}`);
  }

  for (const script of ['svg.py', 'embed.py', 'params.py', 'scriba_root.py', 'selftest.tex']) {
    assert.ok(existsSync(join(skill, 'scripts', script)), `missing script: ${script}`);
    assert.match(text, new RegExp(script.replace('.', '\\.')), `SKILL.md does not mention ${script}`);
  }

  // The skill must state the two hard authoring constraints, not just imply them.
  assert.match(text, /ASCII/);
  assert.match(text, /font-face|字体/);
});

test('the self-test fixture only uses real primitives', () => {
  const fixture = read(join(skill, 'scripts/selftest.tex'));
  const types = [...fixture.matchAll(/\\shape\{[^}]*\}\{(\w+)\}/g)].map((m) => m[1]);
  assert.ok(types.length >= 18, `expected the fixture to cover most primitives, got ${types.length}`);

  for (const type of types) {
    assert.ok(PRIMITIVES.has(type), `selftest.tex declares unknown primitive: ${type}`);
  }
});

test('the Scriba skill is registered where agents look for it', () => {
  const agents = read(join(root, 'AGENTS.md'));
  assert.match(agents, /oj-scriba-visualizer/);

  const readme = read(join(root, 'README.md'));
  assert.match(readme, /\.agents\/skills\/oj-scriba-visualizer\/SKILL\.md/);

  const workflow = read(join(root, '.agents/skills/oj-problem-workflow/SKILL.md'));
  assert.match(workflow, /oj-scriba-visualizer/);

  const visualization = read(join(root, 'docs/problem-visualization.md'));
  assert.match(visualization, /oj-scriba-visualizer/);
});

test('skill frontmatter name matches its directory', () => {
  const text = read(join(skill, 'SKILL.md'));
  const name = text.match(/^---\n[\s\S]*?^name:\s*(\S+)/m);
  assert.ok(name, 'SKILL.md has no name in frontmatter');
  assert.equal(name[1], 'oj-scriba-visualizer');
  assert.match(text, /^description:/m, 'SKILL.md needs a description for skill selection');
});
