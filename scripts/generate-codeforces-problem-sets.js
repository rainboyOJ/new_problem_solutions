import fs from 'node:fs/promises';
import path from 'node:path';
import { pathToFileURL } from 'node:url';
import matter from 'gray-matter';

const API_BASE = 'https://codeforces.com/api';
const REQUEST_INTERVAL_MS = 2100;
const MAX_ATTEMPTS = 3;
const problemIndexCollator = new Intl.Collator('en', { numeric: true, sensitivity: 'base' });
const beijingDateFormatter = new Intl.DateTimeFormat('en-CA', {
  timeZone: 'Asia/Shanghai',
  year: 'numeric',
  month: '2-digit',
  day: '2-digit',
});

function sleep(milliseconds) {
  return new Promise((resolve) => setTimeout(resolve, milliseconds));
}

function markdownText(value) {
  return String(value).replace(/([\\`*_[\]<>#])/g, '\\$1');
}

export function beijingDate(timestampSeconds) {
  const parts = beijingDateFormatter.formatToParts(new Date(timestampSeconds * 1000));
  const values = Object.fromEntries(parts.map((part) => [part.type, part.value]));
  return `${values.year}-${values.month}-${values.day}`;
}

export function beijingYear(timestampSeconds) {
  return Number(beijingDate(timestampSeconds).slice(0, 4));
}

export function isRatedContestCandidate(contest) {
  const name = String(contest?.name || '');
  if (/unrated|mirror|testing round|kotlin heroes|april fools|practice/i.test(name)) {
    return false;
  }

  return contest?.type === 'CF'
    || /^Educational Codeforces Round/i.test(name)
    || (/^Codeforces Round/i.test(name) && /Div\.\s*[34]/i.test(name));
}

export function selectContestCandidates(contests, years, nowSeconds) {
  const requestedYears = new Set(years);

  return contests
    .filter((contest) => contest?.phase === 'FINISHED')
    .filter((contest) => Number.isFinite(contest?.startTimeSeconds))
    .filter((contest) => contest.startTimeSeconds <= nowSeconds)
    .filter((contest) => requestedYears.has(beijingYear(contest.startTimeSeconds)))
    .filter(isRatedContestCandidate)
    .sort((left, right) => left.startTimeSeconds - right.startTimeSeconds || left.id - right.id);
}

function sortedContestProblems(contestId, problems) {
  const contestProblems = problems
    .filter((problem) => problem?.contestId === contestId)
    .sort((left, right) => problemIndexCollator.compare(String(left.index), String(right.index)));

  if (contestProblems.length === 0) {
    throw new Error(`Rated contest ${contestId} has no problems.`);
  }

  const keys = new Set();
  for (const problem of contestProblems) {
    if (!problem.index || !problem.name) {
      throw new Error(`Contest ${contestId} contains malformed problem data.`);
    }
    const key = `${contestId}${problem.index}`;
    if (keys.has(key)) {
      throw new Error(`Contest ${contestId} contains duplicate problem key ${key}.`);
    }
    keys.add(key);
  }

  return contestProblems;
}

function renderProblem(problem) {
  const problemId = `${problem.contestId}${problem.index}`;
  const url = `https://codeforces.com/contest/${problem.contestId}/problem/${encodeURIComponent(problem.index)}`;
  const rating = Number.isFinite(problem.rating) ? `\`${problem.rating}\`` : '`未定级`';
  const label = `${markdownText(problem.index)}. ${markdownText(problem.name)}`;

  return `- [ ] [[problem: codeforces,${problemId}]] · [${label}](${url}) · rating ${rating}`;
}

export function renderAnnualProblemSet(year, contests, problems, options = {}) {
  const selectedContests = contests
    .filter((contest) => beijingYear(contest.startTimeSeconds) === year)
    .sort((left, right) => left.startTimeSeconds - right.startTimeSeconds || left.id - right.id);

  const sections = [];
  let problemCount = 0;

  for (const contest of selectedContests) {
    const contestProblems = sortedContestProblems(contest.id, problems);
    problemCount += contestProblems.length;
    sections.push([
      `## ${beijingDate(contest.startTimeSeconds)}｜${markdownText(contest.name)}`,
      '',
      `[比赛主页](https://codeforces.com/contest/${contest.id})`,
      '',
      ...contestProblems.map(renderProblem),
    ].join('\n'));
  }

  const title = `${year} Codeforces 正式比赛题目单`;
  const lines = [
    '---',
    `title: "${title}"`,
    `description: "按北京时间整理的 ${year} 年 Codeforces 正式 rated 个人赛题目单。"`,
  ];

  if (Number.isFinite(options.order)) {
    lines.push(`order: ${options.order}`);
  }
  lines.push(
    '---',
    '',
    `# ${title}`,
    '',
    '本题单按北京时间从早到晚整理 Codeforces 已结束的正式 rated 个人赛。每场比赛保留全部题目和官方题号，不展示算法标签。',
    '',
    `共收录 **${selectedContests.length}** 场比赛、**${problemCount}** 道题。`,
  );

  if (sections.length > 0) {
    lines.push('', sections.join('\n\n'));
  }

  return `${lines.join('\n')}\n`;
}

export function existingProblemSetOrder(markdown) {
  const order = matter(String(markdown || '')).data.order;
  return Number.isFinite(order) ? order : null;
}

export function parseYears(args) {
  if (args.length === 0) {
    throw new Error('At least one year is required.');
  }

  const years = args.map((value) => {
    if (!/^\d{4}$/.test(value)) {
      throw new Error(`Invalid year: ${value}`);
    }
    const year = Number(value);
    if (year < 2010 || year > 9999) {
      throw new Error(`Invalid year: ${value}`);
    }
    return year;
  });

  return [...new Set(years)].sort((left, right) => left - right);
}

async function fetchApi(method, params = {}, options = {}) {
  const url = new URL(`${API_BASE}/${method}`);
  for (const [key, value] of Object.entries(params)) {
    url.searchParams.set(key, value);
  }

  let lastError;
  for (let attempt = 1; attempt <= MAX_ATTEMPTS; attempt += 1) {
    try {
      const response = await fetch(url, { signal: AbortSignal.timeout(30000) });
      if (!response.ok) {
        throw new Error(`HTTP ${response.status}`);
      }

      const payload = await response.json();
      if (payload.status === 'OK') {
        return payload.result;
      }

      if (options.allowUnavailableRating && /rating changes are unavailable/i.test(payload.comment || '')) {
        return null;
      }
      throw new Error(payload.comment || `Codeforces API returned ${payload.status || 'an invalid status'}`);
    } catch (error) {
      lastError = error;
      if (attempt < MAX_ATTEMPTS) {
        await sleep(500 * (2 ** (attempt - 1)));
      }
    }
  }

  throw new Error(`Codeforces API ${method} failed after ${MAX_ATTEMPTS} attempts: ${lastError.message}`);
}

async function verifyRatedContests(candidates) {
  const rated = [];
  const skipped = [];

  for (let index = 0; index < candidates.length; index += 1) {
    const contest = candidates[index];
    if (index > 0) {
      await sleep(REQUEST_INTERVAL_MS);
    }
    process.stdout.write(`\rChecking rated contests: ${index + 1}/${candidates.length}`);
    const changes = await fetchApi('contest.ratingChanges', { contestId: contest.id }, {
      allowUnavailableRating: true,
    });
    if (Array.isArray(changes) && changes.length > 0) {
      rated.push(contest);
    } else {
      skipped.push(contest);
    }
  }

  if (candidates.length > 0) {
    process.stdout.write('\n');
  }
  return { rated, skipped };
}

async function atomicWrite(destination, content) {
  const temporary = `${destination}.tmp-${process.pid}`;
  try {
    await fs.writeFile(temporary, content, 'utf8');
    await fs.rename(temporary, destination);
  } catch (error) {
    await fs.rm(temporary, { force: true });
    throw error;
  }
}

async function readExistingOrder(destination) {
  try {
    return existingProblemSetOrder(await fs.readFile(destination, 'utf8'));
  } catch (error) {
    if (error.code === 'ENOENT') {
      return null;
    }
    throw error;
  }
}

function printHelp() {
  console.log(`Usage: npm run generate:codeforces-sets -- <year> [year...]

Generate chronological annual Codeforces problem sets from the official API.

Example:
  npm run generate:codeforces-sets -- 2025 2026
`);
}

export async function main(args = process.argv.slice(2)) {
  if (args.includes('-h') || args.includes('--help')) {
    printHelp();
    return;
  }

  const years = parseYears(args);
  const nowSeconds = Math.floor(Date.now() / 1000);
  const [contests, problemset] = await Promise.all([
    fetchApi('contest.list', { gym: 'false' }),
    fetchApi('problemset.problems'),
  ]);

  if (!Array.isArray(contests) || !Array.isArray(problemset?.problems)) {
    throw new Error('Codeforces API returned malformed contest or problemset data.');
  }

  const candidates = selectContestCandidates(contests, years, nowSeconds);
  const { rated, skipped } = await verifyRatedContests(candidates);
  const outputs = await Promise.all(years.map(async (year) => {
    const yearContests = rated.filter((contest) => beijingYear(contest.startTimeSeconds) === year);
    const destination = path.resolve('problem-sets', `${year}-codeforces.md`);
    const order = await readExistingOrder(destination);
    const content = renderAnnualProblemSet(year, yearContests, problemset.problems, { order });
    const problemCount = yearContests.reduce(
      (count, contest) => count + problemset.problems.filter((problem) => problem.contestId === contest.id).length,
      0,
    );
    return {
      year,
      content,
      contestCount: yearContests.length,
      problemCount,
      destination,
    };
  }));

  for (const output of outputs) {
    await atomicWrite(output.destination, output.content);
    console.log(`Generated ${path.relative(process.cwd(), output.destination)}: ${output.contestCount} contests, ${output.problemCount} problems.`);
  }

  if (skipped.length > 0) {
    console.log('Skipped candidates without rating changes:');
    for (const contest of skipped) {
      console.log(`- ${contest.id} ${contest.name}`);
    }
  }
}

const entryUrl = process.argv[1] ? pathToFileURL(path.resolve(process.argv[1])).href : '';
if (entryUrl === import.meta.url) {
  main().catch((error) => {
    console.error(error.message);
    process.exitCode = 1;
  });
}
