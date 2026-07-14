# Luogu to USACO Analysis Index Pages Design

## Goal

Make all 90 Luogu counterparts in `problem-sets/2026-cspj-summer-first-prize.md` first-class local problem entries without duplicating the completed USACO analysis articles.

The problem set should use each Luogu problem as its primary task and retain a direct local link to the corresponding USACO analysis.

## Baseline

The repository already contains:

- 87 lightweight Luogu index pages created by commit `344bbb3a`;
- 3 full Luogu analyses for `P9974`, `P5832`, and `P9975`;
- 90 verified USACO-to-Luogu mappings in `docs/superpowers/specs/2026-07-14-usaco-luogu-links-design.md`.

The 87 lightweight pages currently resolve correctly, but their missing `title` metadata produces blank HTML page titles. The problem set still uses USACO as the primary task and an external Luogu link as supplementary text.

## Scope

Modify only:

- `problem-sets/2026-cspj-summer-first-prize.md`;
- the 87 lightweight Luogu index pages from commit `344bbb3a`;
- the existing full Luogu analyses for `P9974`, `P5832`, and `P9975`.

Do not copy USACO article bodies or code files, modify the 90 USACO analyses, add application-level redirect behavior, or change problem rendering code.

## Problem Set Format

Replace each USACO-primary task line and external Luogu link with a local Luogu-primary task and local USACO analysis link:

```markdown
- [x] [[problem: luogu,P12022]]（USACO 解析：[[problem: usaco,1515]]）
  训练点：简单枚举，规则映射，稳定处理输入输出。
```

Preserve all 90 completion states, section assignments, ordering, and training notes. Use the existing verified mapping without substitutions.

## Lightweight Luogu Index Pages

Keep the 87 pages as index pages rather than independent solution articles. Each page must contain complete display metadata:

- `oj`: `luogu`;
- `problem_id`: the mapped Luogu ID;
- `title`: the exact Luogu title;
- `description`: inherit the corresponding USACO analysis description;
- `difficulty`: inherit the corresponding USACO analysis difficulty;
- `date`: inherit the corresponding USACO analysis date so the alias does not appear as a newly written independent solution;
- `toc`: `true`;
- `tags`: inherit the corresponding USACO tags and add `usaco` if absent;
- `categories`, `pre`, `common`, and `recommend`: empty arrays;
- `source`: the canonical Luogu URL formed as `https://www.luogu.com.cn/problem/` followed by the exact Luogu problem ID.

The body contains only the table of contents and a same-problem explanation:

```markdown
[[TOC]]

### 同题说明

洛谷 P12022 与 USACO 1515 是同一道题，完整题目解析请见：

- [[problem: usaco,1515]]
```

Do not create `main.cpp`, `brute.cpp`, duplicated statement text, or duplicated analysis text in these directories. The USACO page remains the canonical analysis source.

## Existing Full Luogu Analyses

Preserve the full content and code references in `P9974`, `P5832`, and `P9975`. Add a short `### 同题版本` section immediately after `[[TOC]]`:

```markdown
### 同题版本

本题对应的 USACO 版本及解析：

- [[problem: usaco,1347]]
```

The example above is for `P9974`; use the mapped USACO ID for the other two pages.

Use these pairs:

- `P9974` -> USACO `1347`;
- `P5832` -> USACO `964`;
- `P9975` -> USACO `1348`.

Do not replace these three complete articles with lightweight pages.

## Verification

1. Confirm the USACO training section has exactly 90 primary Luogu task references and 90 supplementary USACO analysis references.
2. Confirm all 90 pairs match the verified mapping and no external Luogu links remain in that section.
3. Confirm 87 lightweight pages contain non-empty required metadata and the correct USACO analysis link.
4. Confirm the three full Luogu articles retain their previous content and include the correct USACO link.
5. Request representative T1, T2, T3, and T4 Luogu pages and confirm status 200, non-empty HTML titles, and working USACO links.
6. Request the problem-set page and confirm all primary Luogu tasks are available without `Missing problem` warnings.
7. Run the repository problem-set and Markdown problem-link tests.
