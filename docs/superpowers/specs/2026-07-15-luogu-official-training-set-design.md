# Luogu Official Training Problem Set Design

## Goal

Create one repository problem set that mirrors the Luogu official `srqc-jc` training collection at:

`https://www.luogu.com.cn/training/list?type=srqc-jc`

The generated set preserves every official subgroup, subgroup order, and problem order in a single flat problem-set card. The current source contains 18 subgroups, 271 problem entries, and 262 distinct problem IDs.

## Output

Generate:

`problem-sets/luogu-official-basic-training.md`

Use this frontmatter on first generation:

```yaml
---
title: "洛谷官方入门与基础算法题单"
description: "按洛谷官方入门与基础算法训练题单整理的完整练习路径。"
order: 35
source: "https://www.luogu.com.cn/training/list?type=srqc-jc"
---
```

This places the card after `2026-cspj-summer-first-prize` and before `cps-j-math` without renumbering existing sets. On later runs, preserve a finite numeric `order` already present in the destination file; otherwise use the default value 35.

## Data Source

Add:

`scripts/generate-luogu-official-training-set.py`

The script requests Luogu's official content-only structured responses rather than scraping visible page text:

- `/training/list?type=srqc-jc&_contentOnly=1` for subgroup metadata;
- `/training/<id>?_contentOnly=1` for subgroup descriptions and ordered problems.

Send `x-lentille-request: content-only` and a normal browser user agent. Reuse one `urllib` opener with `HTTPCookieProcessor(CookieJar())` for all requests so Luogu's initial self-redirect can set its short-lived cookie and the following request can succeed.

Use bounded retries for transient network or HTTP failures. Require a successful JSON status and the expected `training.list` or `training.show` response shape.

## Data Validation

Preserve the subgroup order returned by the list response. For each subgroup:

1. Require a numeric, unique training ID.
2. Require a non-empty subgroup name.
3. Require the provider to be the official Luogu account.
4. Require `problems` to be an array.
5. Require every problem to have a valid Luogu PID and non-empty name.
6. Require the declared `problemCount` to equal the number of returned problems.
7. Reject duplicate problem IDs within one subgroup.

Allow the number of subgroups and problems to change when Luogu updates the collection. Do not hard-code 18, 271, or 262 as acceptance conditions; report those current values after the initial live generation.

Build and validate the entire model before modifying the destination. Write through a temporary file and atomic rename. Any request, JSON, or validation failure exits non-zero and leaves the previous generated file intact.

## Markdown Format

Start the body with the title, official source link, current subgroup count, problem-entry count, and distinct-problem count. State that repeated problems are intentionally retained because they appear in multiple official learning stages.

Render each subgroup as:

```markdown
## 【入门1】顺序结构

[洛谷官方子题单](https://www.luogu.com.cn/training/100) · 15 题

- [ ] [[problem: luogu,B2002]] · [B2002 Hello,World!](https://www.luogu.com.cn/problem/B2002)
- [ ] [[problem: luogu,B2025]] · [B2025 输出字符菱形](https://www.luogu.com.cn/problem/B2025)
```

The local problem reference supplies the stable progress key and a local explanation link when present. The external link always provides direct access to the official Luogu problem.

Escape Markdown punctuation in subgroup names and problem titles. Do not copy subgroup course advertisements or long descriptions. Do not display difficulty, tags, acceptance data, or provider metadata. All generated source checkboxes start unchecked.

## Repeated Problems

Retain all official entries, including the current seven repeated problem IDs and nine extra occurrences. A repeated problem uses the same `luogu/<pid>` progress key in every subgroup.

Update `public/javascripts/problem-set-progress.js` so changing one task applies the new checked state to every task on the page with the same key before saving and recounting. The counter remains entry-based: completing a problem shown in three official subgroups marks all three entries complete and increases the completed count by three.

The existing localStorage data shape and import/export behavior do not change.

## Generator Interface

Add an npm script:

```bash
npm run generate:luogu-official-set
```

The generator takes no required arguments because it owns one official collection and one destination. It prints subgroup, entry, distinct-problem, and repeated-problem totals after a successful write.

Do not run the generator as part of `npm start` or the normal build. Generation remains an explicit maintenance action so application startup does not depend on Luogu availability.

## Scope

Modify only:

- `scripts/generate-luogu-official-training-set.py`;
- `package.json`;
- `problem-sets/luogu-official-basic-training.md`;
- `public/javascripts/problem-set-progress.js`;
- focused generator and browser-progress tests;
- concise tool documentation if needed for the maintenance command.

Do not create local solution directories, fetch problem statements, modify other problem sets, alter the problem-set page layout, or change progress import/export storage formats.

## Verification

1. Test list and detail response parsing with offline fixtures containing multiple subgroups and a repeated problem.
2. Test internal count validation, invalid PIDs, duplicate subgroup IDs, duplicate IDs within one subgroup, and malformed JSON failures.
3. Test CookieJar handling with a local HTTP server that requires a redirect-set cookie before returning JSON.
4. Test deterministic Markdown frontmatter, subgroup ordering, problem ordering, escaped titles, totals, local task keys, and official links.
5. Test preservation of an existing finite `order` and fallback to 35 for a new file.
6. Test that changing one duplicate task updates every same-key checkbox and the entry-based count.
7. Run the live generator and confirm the current source produces 18 subgroups, 271 entries, 262 distinct problems, seven repeated IDs, and nine extra occurrences.
8. Confirm all 18 headings and 271 task references appear in the generated Markdown.
9. Confirm the generated problem IDs match the live structured responses exactly and no subgroup order differs.
10. Request `/problem-sets`; confirm the new card appears between orders 30 and 40.
11. Request `/problem-sets/luogu-official-basic-training`; confirm status 200, 271 rendered tasks, official links, and duplicate progress synchronization.
12. Run the focused tests and the repository suite, reporting pre-existing unrelated failures separately.

