# Codeforces Problem Fetcher Design

## Goal

Upgrade `scripts/problem-analysis-tools/fetchers/codeforces.py` so `fetch_problem.py` and URL-mode `new_problem.py` can archive the official English Codeforces statement and write sample input/output files.

The fetcher must support both canonical URL forms:

- `https://codeforces.com/contest/2183/problem/A`;
- `https://codeforces.com/problemset/problem/2183/A`.

It must also continue to support the compact repository problem ID `2183A`.

## Baseline

The current Codeforces fetcher only parses a URL or compact ID and returns skeleton metadata. It does not make a network request or produce `problem.md`, `in*`, or `out*` files.

The official Codeforces API `Problem` object contains contest ID, index, name, type, points, rating, and tags. It does not contain the statement, input/output specifications, samples, or notes. Complete statement archival therefore requires parsing the official problem HTML.

## Data Flow

Use the official Codeforces problem page as the primary source:

1. Split the compact problem ID into numeric `contest_id` and alphanumeric `index`.
2. Request `https://codeforces.com/contest/<contest_id>/problem/<index>` with the existing normal browser user agent.
3. Locate the `.problem-statement` element.
4. Parse its title, time limit, memory limit, main description, input specification, output specification, sample tests, and optional note.
5. Return a fetched `ProblemData` with English statement Markdown and paired `Sample` objects.

If the HTML request or statement parsing fails after the contest and index are known, query the official `problemset.problems` API and locate the matching `contestId` and `index`. Use its `name` only to improve the skeleton title. The API is a fallback rather than a routine first request because it returns the full public problemset and cannot supply statement content.

If both HTML and API fallback fail, preserve the current compact ID title and skeleton behavior. The caller reports the original statement-fetch error and any fallback failure without writing a partial `problem.md`.

Do not fetch or write tags, rating, editorials, submissions, or translations.

## Statement Output

Produce `problem.md` in this form:

````markdown
# 2183A Binary Array Game

- Time limit: 1 second
- Memory limit: 256 megabytes

## 题目描述

<official English statement>

## 输入格式

<official English Input section>

## 输出格式

<official English Output section>

## 输入输出样例 #1

### 输入 #1

```
<sample input>
```

### 输出 #1

```
<sample output>
```

## 说明

<official English Note section>
````

The outer section headings remain Chinese to match existing archived problem statements; all fetched source content remains official English.

The existing fetch pipeline writes every parsed sample to `in1/out1`, `in2/out2`, and so on, and duplicates the first sample as `in`. Existing overwrite flags remain unchanged. `--force-index-meta` updates only `index.md` title and source through the existing pipeline.

## HTML Parser

Use Python's standard-library `HTMLParser` to build a small node tree for the statement subtree. Do not add BeautifulSoup or another dependency.

Convert supported statement content as follows:

- Codeforces `$$$...$$$` delimiters become Markdown/KaTeX `$...$` delimiters.
- Paragraphs and `<br>` preserve paragraph and line boundaries.
- Unordered and ordered lists become Markdown lists, including nested content.
- Teletype spans become inline code where doing so does not corrupt math.
- Links remain links; relative targets become absolute Codeforces URLs.
- Images remain Markdown images; protocol-relative and relative sources become absolute URLs.
- HTML entities are decoded.
- Navigation, tags, forms, scripts, and all content outside `.problem-statement` are ignored.

Codeforces sample `<pre>` elements often contain one `.test-example-line` div per source line rather than raw newline-delimited text. Reconstruct such blocks by joining those divs with newline characters. For older plain `<pre>` markup, preserve raw text and `<br>` line breaks.

Treat sample input and output as a pair. If a sample container lacks either side, add a warning and omit that incomplete pair. A legitimate statement with no sample section remains a successful fetch.

## Validation And Errors

A parsed statement is valid when `.problem-statement` exists and supplies a non-empty title and main description. Input, output, note, time limit, memory limit, and samples are optional because special problem types may omit them.

Detect Cloudflare or other non-problem responses through the missing statement root and raise a targeted `FetchError`. Do not write `problem.md` from arbitrary page text.

Network errors and malformed HTML continue through `fetch_problem.py`'s existing skeleton fallback. Existing user-authored files are never overwritten unless their current force flags explicitly allow it.

## Scope

Modify only:

- `scripts/problem-analysis-tools/fetchers/codeforces.py`;
- a focused Codeforces HTML fixture under `scripts/problem-analysis-tools/tests/fixtures/`;
- Codeforces fetcher tests in `tests/oj-tools.test.js`;
- Codeforces capability notes in `docs/tools/fetch_problem.md`;
- the previously scaffolded `problems/codeforces/2183A/` fetch outputs used for the live verification.

Do not change other fetchers, the general scaffold format, solution code, or analysis article content.

## Verification

1. Parse both supported URL forms into `codeforces/2183A`.
2. Parse the offline fixture without network access.
3. Verify the title excludes the redundant `A.` prefix.
4. Verify time and memory limits are present in `problem.md`.
5. Verify formulas, entities, paragraphs, lists, links, images, input/output, and Note survive Markdown conversion.
6. Verify nested `.test-example-line` elements preserve exact sample line breaks.
7. Verify an HTML statement without samples succeeds with an empty sample list.
8. Verify incomplete sample pairs produce a warning and no partial sample.
9. Verify the fetch pipeline writes `problem.md`, `in1`, `out1`, and `in` from fixture data.
10. Run the live fetch for `https://codeforces.com/contest/2183/problem/A` with statement/sample/index metadata overwrite flags and inspect the generated files.
11. Run the focused OJ tool tests and the repository test suite, reporting unrelated pre-existing failures separately.
