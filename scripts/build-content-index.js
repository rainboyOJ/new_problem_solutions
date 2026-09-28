#!/usr/bin/env node

import fs from 'node:fs';
import path from 'node:path';
import ContentService from '../lib/content-service.js';
import ProblemManager from '../lib/problem.js';
import ProblemSetManager from '../lib/problem-set.js';

function die(message) {
  console.error(`[content-index] ${message}`);
  process.exit(1);
}

const args = process.argv.slice(2);
const values = new Map();
for (let index = 0; index < args.length; index += 2) {
  const name = args[index];
  const value = args[index + 1];
  if (!name?.startsWith('--') || value === undefined) die(`invalid argument: ${name || ''}`);
  values.set(name, value);
}

const root = path.resolve(values.get('--root') || '.');
const output = values.get('--output');
const contentSha = values.get('--content-sha');
if (!output) die('--output is required');
if (!/^[0-9a-f]{40}$/.test(contentSha || '')) die('--content-sha must be a full Git SHA');

const problemManager = new ProblemManager({
  auto_load: false,
  baseDir: path.join(root, 'problems'),
});
const problemSetManager = new ProblemSetManager(problemManager, {
  auto_load: false,
  baseDir: path.join(root, 'problem-sets'),
});
const contentService = new ContentService({
  problemManager,
  problemSetManager,
  revisionProvider: () => contentSha,
});

try {
  const index = contentService.createIndex(contentSha);
  fs.writeFileSync(output, `${JSON.stringify(index)}\n`);
  console.log(
    `[content-index] ${index.problems.problems.length} problems, `
      + `${index.problemSets.problemSets.length} problem sets, schema v${index.schemaVersion}`,
  );
} catch (error) {
  die(error.stack || error.message);
}
