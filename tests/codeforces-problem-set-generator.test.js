import test from 'node:test';
import assert from 'node:assert/strict';
import {
  beijingDate,
  beijingYear,
  isRatedContestCandidate,
  parseYears,
  renderAnnualProblemSet,
  selectContestCandidates,
} from '../scripts/generate-codeforces-problem-sets.js';

function timestamp(isoDate) {
  return Math.floor(Date.parse(isoDate) / 1000);
}

test('beijingDate derives the date and year in Asia/Shanghai', () => {
  const lateUtc = timestamp('2024-12-31T17:00:00Z');

  assert.equal(beijingDate(lateUtc), '2025-01-01');
  assert.equal(beijingYear(lateUtc), 2025);
});

test('isRatedContestCandidate accepts standard contests and rejects special contests', () => {
  const included = [
    { name: 'Codeforces Round 1000 (Div. 2)', type: 'CF' },
    { name: 'Educational Codeforces Round 180 (Rated for Div. 2)', type: 'ICPC' },
    { name: 'Codeforces Round 1043 (Div. 3)', type: 'ICPC' },
    { name: 'Codeforces Round 1050 (Div. 4)', type: 'ICPC' },
    { name: 'Codeforces Global Round 30 (Div. 1 + Div. 2)', type: 'CF' },
    { name: 'Hello 2025', type: 'CF' },
    { name: 'Pinely Round 5 (Div. 1 + Div. 2)', type: 'CF' },
  ];
  const excluded = [
    { name: 'Codeforces Round 1010 (Div. 2, Unrated)', type: 'CF' },
    { name: 'ICPC Finals (Unrated, Online Mirror)', type: 'ICPC' },
    { name: 'Testing Round 20', type: 'ICPC' },
    { name: 'Kotlin Heroes: Episode 13', type: 'ICPC' },
    { name: 'April Fools Day Contest 2025', type: 'ICPC' },
    { name: 'Kotlin Heroes: Practice 13', type: 'ICPC' },
  ];

  assert.ok(included.every(isRatedContestCandidate));
  assert.ok(excluded.every((contest) => !isRatedContestCandidate(contest)));
});

test('selectContestCandidates filters years and future contests while retaining separate divisions', () => {
  const sameStart = timestamp('2025-03-23T14:35:00Z');
  const contests = [
    { id: 2089, name: 'Codeforces Round 1012 (Div. 1)', type: 'CF', phase: 'FINISHED', startTimeSeconds: sameStart },
    { id: 2090, name: 'Codeforces Round 1012 (Div. 2)', type: 'CF', phase: 'FINISHED', startTimeSeconds: sameStart },
    { id: 2091, name: 'Codeforces Round 1013 (Div. 3)', type: 'ICPC', phase: 'BEFORE', startTimeSeconds: timestamp('2025-03-25T14:35:00Z') },
    { id: 2183, name: 'Hello 2026', type: 'CF', phase: 'FINISHED', startTimeSeconds: timestamp('2026-01-07T14:35:00Z') },
  ];

  const selected = selectContestCandidates(contests, [2025], timestamp('2025-12-31T23:59:59Z'));

  assert.deepEqual(selected.map((contest) => contest.id), [2089, 2090]);
});

test('renderAnnualProblemSet renders deterministic chronological contests and natural problem order', () => {
  const contests = [
    { id: 2002, name: 'Second [Round]', startTimeSeconds: timestamp('2025-01-02T12:00:00Z') },
    { id: 2001, name: 'First Round', startTimeSeconds: timestamp('2025-01-01T12:00:00Z') },
  ];
  const problems = [
    { contestId: 2001, index: 'D2', name: 'Hard Version' },
    { contestId: 2001, index: 'A', name: 'Opening Problem', rating: 800 },
    { contestId: 2001, index: 'D1', name: 'Easy Version', rating: 1700 },
    { contestId: 2002, index: 'A', name: 'A [Bracket] Test', rating: 900 },
  ];

  const markdown = renderAnnualProblemSet(2025, contests, problems);

  assert.match(markdown, /title: "2025 Codeforces 正式比赛题目单"/);
  assert.match(markdown, /共收录 \*\*2\*\* 场比赛、\*\*4\*\* 道题。/);
  assert.ok(markdown.indexOf('First Round') < markdown.indexOf('Second \\[Round\\]'));
  assert.ok(markdown.indexOf('2001A') < markdown.indexOf('2001D1'));
  assert.ok(markdown.indexOf('2001D1') < markdown.indexOf('2001D2'));
  assert.match(markdown, /\[\[problem: codeforces,2001A\]\]/);
  assert.match(markdown, /https:\/\/codeforces\.com\/contest\/2001\/problem\/A/);
  assert.match(markdown, /rating `800`/);
  assert.match(markdown, /rating `未定级`/);
  assert.ok(markdown.includes('A. A \\[Bracket\\] Test'));
  assert.match(markdown, /rating `未定级`\n\n## 2025-01-02/);
});

test('parseYears validates, sorts, and deduplicates positional years', () => {
  assert.deepEqual(parseYears(['2026', '2025', '2026']), [2025, 2026]);
  assert.throws(() => parseYears([]), /At least one year/);
  assert.throws(() => parseYears(['20x5']), /Invalid year/);
});

test('renderAnnualProblemSet rejects rated contests without problems', () => {
  const contests = [
    { id: 2001, name: 'Missing Problems', startTimeSeconds: timestamp('2025-01-01T12:00:00Z') },
  ];

  assert.throws(() => renderAnnualProblemSet(2025, contests, []), /has no problems/);
});
