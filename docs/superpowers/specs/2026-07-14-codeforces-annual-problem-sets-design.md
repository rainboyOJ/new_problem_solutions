# Codeforces Annual Problem Sets Design

## Goal

Create one chronological Codeforces problem set per year for 2025 and 2026:

- `problem-sets/2025-codeforces.md`;
- `problem-sets/2026-codeforces.md`.

Each set is a complete record of finished, officially rated individual Codeforces contests in that Beijing-calendar year. Contests are ordered from earliest to latest, and every problem from each included contest is listed in its official order.

The 2026 set includes only contests that have finished by the time the generator runs. Later contests are added by rerunning the same generator.

## Scope

Add:

- a reusable Codeforces annual-set generator under `scripts/`;
- an npm script for running the generator;
- generated 2025 and 2026 Markdown problem sets;
- focused automated tests for filtering, ordering, timezone handling, and Markdown rendering.

Do not add local Codeforces solution articles, copy problem statements, display problem tags, fetch Codeforces data at page-request time, or change the existing problem-set page design.

## Data Sources

Use only the official Codeforces API:

- `contest.list?gym=false` for contest IDs, names, phases, types, and start timestamps;
- `contest.ratingChanges?contestId=<id>` to verify that a candidate contest produced Codeforces rating changes;
- `problemset.problems` for problem indexes, English titles, and official ratings.

Use Node.js built-in `fetch`; do not add an HTTP dependency.

## Contest Selection

Convert every contest start timestamp to `Asia/Shanghai` before deriving its displayed date and calendar year.

A contest is included only when all of the following are true:

1. Its Beijing-calendar year is one of the requested years.
2. Its phase is `FINISHED` and its start time is not later than the generator's current time.
3. It is an individual Codeforces contest rather than a Gym contest, mirror, team event, testing event, language-specific event, April Fools contest, or other special unrated event.
4. Its name does not explicitly state that it is unrated.
5. `contest.ratingChanges` returns a non-empty result, confirming that the contest was rated.

Before calling `contest.ratingChanges`, treat a contest as a candidate only when either:

- its API `type` is `CF`; or
- its name starts with `Educational Codeforces Round`; or
- its name starts with `Codeforces Round` and contains `Div. 3` or `Div. 4`.

Reject a candidate before rating verification when its name contains, case-insensitively, `Unrated`, `Mirror`, `Testing Round`, `Kotlin Heroes`, `April Fools`, or `Practice`. This prefilter reduces API calls; the non-empty rating-change result remains the definitive inclusion check.

The included scope covers regular Codeforces Rounds, Div. 1, Div. 2, Div. 3, Div. 4, combined Div. 1 + Div. 2 rounds, Educational Codeforces Rounds, Codeforces Global Rounds, Hello/Good Bye rounds, and sponsored named rounds when they satisfy the rated-contest verification.

Keep every contest ID as an independent contest. In particular, Div. 1 and Div. 2 contests held for the same round at the same time are not merged, even if some problems overlap.

If a finished candidate contest does not yet expose rating changes, omit it from the generated set and report it in the command output. A later run checks it again.

## Problem Selection

Include every problem returned by `problemset.problems` for an included contest ID.

Within a contest, sort by the official problem index in natural ascending order, including compound indexes such as `D1` and `D2`. Preserve separate contest copies of shared Div. 1 and Div. 2 problems because the contest IDs and official indexes differ.

Display the official numeric rating when present. Display `未定级` when Codeforces does not provide a rating. Do not expose official tags because they can reveal the intended solution technique.

A rated contest with no matching problems is a generation error rather than an empty section.

## Generated Markdown

Use these frontmatter values:

```yaml
---
title: "2025 Codeforces 正式比赛题目单"
description: "按北京时间整理的 2025 年 Codeforces 正式 rated 个人赛题目单。"
---
```

Use the matching year in the 2026 file. The introduction states the inclusion rules and generated contest/problem counts.

Order contests by Beijing start time from earliest to latest. Break ties by contest ID so output remains deterministic. Render each contest as:

```markdown
## 2025-01-04｜Hello 2025

[比赛主页](https://codeforces.com/contest/2057)

- [ ] [[problem: codeforces,2057A]] · [A. MEX Table](https://codeforces.com/contest/2057/problem/A) · rating `800`
- [ ] [[problem: codeforces,2057B]] · [B. Gorilla and the Exam](https://codeforces.com/contest/2057/problem/B) · rating `900`
```

The local problem reference supplies the stable `codeforces/<contestId><index>` task key used by the existing progress tracker and links to a local explanation when one exists. The external link always provides direct access to the original Codeforces problem. Missing local explanations continue to use the existing `未收录` state.

All generated source checkboxes start unchecked. Completion state remains browser-local through the existing problem-set progress mechanism and is not rewritten by future generator runs.

## Generator Interface

Add an npm command with positional years:

```bash
npm run generate:codeforces-sets -- 2025 2026
```

The generator must:

1. Validate requested years before making requests.
2. Fetch the contest list and problemset data once per run.
3. Apply the candidate filters before making per-contest rating requests.
4. Retry transient HTTP or Codeforces API failures a bounded number of times.
5. Space `contest.ratingChanges` requests by at least two seconds to respect the Codeforces API limit.
6. Collect, validate, sort, and render all requested output in memory before modifying a destination file.
7. Write each completed file through a temporary file and atomic rename.
8. Print per-year contest/problem totals and list candidate contests skipped because rating changes were unavailable.

Rerunning the generator replaces the requested generated files deterministically. It must not modify other problem sets.

## Error Handling

Abort with a non-zero exit code for invalid arguments, network failures that remain after retries, malformed API responses, duplicate problem keys within a contest, rated contests without problems, or filesystem write failures.

An API-level response specifically stating that rating changes are unavailable is a selection result, not a transport failure: report and skip that candidate. Do not write any year's destination until the shared contest and problem data and all required rating checks for the run have completed.

## Verification

Add fixture-based tests that do not require network access. Cover:

1. UTC timestamps that cross a Beijing date or year boundary.
2. Exclusion of unrated, mirror, Kotlin, Testing, and April Fools contests.
3. Inclusion of verified regular, Educational, Div. 3/4, Global, Hello/Good Bye, and sponsored rated rounds.
4. Separate preservation of same-time Div. 1 and Div. 2 contest IDs.
5. Earliest-to-latest contest ordering and natural problem-index ordering.
6. Numeric ratings and the `未定级` fallback.
7. Deterministic frontmatter, counts, stable task keys, contest links, and direct problem links.

After generating the live files:

1. Audit the reported 2025 and 2026 totals against the selected API data.
2. Confirm no duplicate contest IDs or duplicate problem keys occur within either file.
3. Confirm the latest 2026 entry is finished and no future contest is present.
4. Run the repository test suite.
5. Request `/problem-sets/2025-codeforces` and `/problem-sets/2026-codeforces`; verify status 200, chronological sections, working external links, and progress controls.
