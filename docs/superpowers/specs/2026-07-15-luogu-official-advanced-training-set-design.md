# Luogu Official Advanced Training Set Design

## Goal

Extend the pending Luogu official training-set generator so it maintains both official series with shared code:

- `srqc-jc`: the basic collection already designed and generated;
- `srqc-jj`: the “深入浅出进阶篇” collection requested here.

Create:

`problem-sets/luogu-official-advanced-training.md`

The current advanced source contains 22 official subgroups, 368 problem entries, 357 distinct problem IDs, nine repeated problem IDs, and 11 extra occurrences.

## Collection Configuration

Replace hard-coded basic-collection constants in `scripts/generate-luogu-official-training-set.py` with immutable collection configurations:

| Key | Luogu type | Output | Title | Default order |
| --- | --- | --- | --- | ---: |
| `basic` | `srqc-jc` | `problem-sets/luogu-official-basic-training.md` | 洛谷官方入门与基础算法题单 | 35 |
| `advanced` | `srqc-jj` | `problem-sets/luogu-official-advanced-training.md` | 洛谷官方深入浅出进阶篇题单 | 36 |

The advanced description is:

`按洛谷官方深入浅出进阶篇训练题单整理的完整练习路径。`

Its source is:

`https://www.luogu.com.cn/training/list?type=srqc-jj`

Keep the existing CookieJar client, pagination, official-provider checks, response-shape checks, problem validation, Markdown escaping, repeated-problem statistics, deterministic rendering, existing-order preservation, and atomic per-file writes shared between both configurations.

Do not duplicate the generator into a second script.

## Command Interface

Add the plural npm command:

```bash
npm run generate:luogu-official-sets
```

It generates both configured collections by default. Support selecting one collection:

```bash
npm run generate:luogu-official-sets -- --collection basic
npm run generate:luogu-official-sets -- --collection advanced
```

Reject unknown collection keys before making network requests.

Keep `generate:luogu-official-set` as a compatibility alias for the same default all-collection behavior because the basic generator command was already exposed during the previous task.

When generating all collections, fetch and validate every selected collection before modifying either destination. Then render all outputs in memory and atomically replace each destination. A fetch or validation error in either collection leaves both previous files untouched.

Print one statistics line per generated collection.

## Advanced Markdown

Use this frontmatter on first generation:

```yaml
---
title: "洛谷官方深入浅出进阶篇题单"
description: "按洛谷官方深入浅出进阶篇训练题单整理的完整练习路径。"
order: 36
source: "https://www.luogu.com.cn/training/list?type=srqc-jj"
---
```

Preserve an existing finite numeric order on later runs. Render body statistics, repeated-problem notes, subgroup links, local task references, titles, and official problem links with the same format as the basic set.

Example:

```markdown
## 【算法2-1】前缀和、差分与离散化

[洛谷官方子题单](https://www.luogu.com.cn/training/200) · 18 题

- [ ] [[problem: luogu,P8218]] · [P8218 【深进1.例1】求区间和](https://www.luogu.com.cn/problem/P8218)
```

Preserve all official entries and subgroup order. Do not copy course advertisements or display difficulty, tags, acceptance data, or provider metadata.

The duplicate-key synchronization added for the basic set applies unchanged to the advanced set.

## Scope

Extend the current uncommitted basic-set work only where necessary:

- `scripts/generate-luogu-official-training-set.py`;
- `package.json`;
- `problem-sets/luogu-official-advanced-training.md`;
- generator fixtures and tests;
- problem-set ordering and Fastify page tests.

Do not modify the progress storage shape, duplicate synchronization behavior, other problem sets, solution directories, page layout, or unrelated current Codeforces changes.

## Verification

1. Test `basic`, `advanced`, default-all, and invalid collection selection.
2. Test that each configuration supplies the correct type, source, output path, title, description, and default order.
3. Test that list requests use the selected Luogu type on every page.
4. Test that rendered basic and advanced metadata cannot be mixed.
5. Test that all selected models are fetched and validated before any output write begins.
6. Preserve the existing CookieJar, pagination, malformed-data, duplicate, order, deterministic-rendering, and progress tests.
7. Run the live all-collection command and confirm basic remains `18 / 271 / 262 / 7 / 9`.
8. Confirm advanced produces `22 / 368 / 357 / 9 / 11`.
9. Confirm the advanced Markdown contains 22 subgroup headings and 368 task references, with 357 unique keys.
10. Run the command again and verify both file hashes remain unchanged when the source data is unchanged.
11. Request `/problem-sets`; confirm order 35 then 36 then 40.
12. Request `/problem-sets/luogu-official-advanced-training`; confirm status 200, 368 rendered tasks, official subgroup/problem links, and the progress script.
13. Run focused tests and the repository suite, reporting the known unrelated stale-cache assertion separately if it remains.
