# Stable Problem Set Order Design

## Goal

Keep the flat `/problem-sets` list in a stable, explicitly managed order. Editing a problem-set Markdown file must not move its card to a different position.

## Baseline

`ProblemSetManager.list()` currently reads each Markdown file's filesystem modification time and sorts by `updatedAt` descending. This causes any content update, including an automated Codeforces set regeneration, to move that set to the top of the page.

The page currently contains 12 problem sets. Preserve their current visible order when introducing explicit ordering.

## Frontmatter

Add a numeric `order` field to every existing `problem-sets/*.md` file:

| Order | Slug |
| ---: | --- |
| 10 | `2026-codeforces` |
| 20 | `2025-codeforces` |
| 30 | `2026-cspj-summer-first-prize` |
| 40 | `cps-j-math` |
| 50 | `greedy-basic` |
| 60 | `haskell-practice` |
| 70 | `2026-summer-practice` |
| 80 | `csp-j-past` |
| 90 | `csp-s-past` |
| 100 | `csp-j-400` |
| 110 | `csp-s-400` |
| 120 | `graph-basic` |

Use increments of 10 so future sets can be inserted without renumbering the whole list.

## Sorting Rules

`ProblemSetManager.list()` continues to expose `updatedAt`, but it no longer uses that value for ordering.

For each problem set:

1. Treat a finite numeric frontmatter `order` as an explicit order.
2. Sort explicit orders numerically in ascending order.
3. Break equal-order ties by slug in ascending lexical order.
4. Place missing, non-numeric, or non-finite orders after every explicitly ordered set.
5. Sort all unordered sets by slug so their fallback order is deterministic.

Do not reject or hide an unordered set. This keeps newly added files visible even when the maintainer has not assigned an order yet.

## Generated Codeforces Sets

`problem-sets/2025-codeforces.md` and `problem-sets/2026-codeforces.md` are generated files. The Codeforces annual-set generator must read each destination file's existing frontmatter before rendering and preserve its finite numeric `order` value.

The Markdown renderer accepts an optional order value and emits `order: <number>` in frontmatter when present. A destination file that does not exist, or that has no valid order, remains unordered and therefore appears at the end of the list until a maintainer assigns one.

Do not hard-code year-to-order mappings in the generator. Preserving destination metadata allows later annual sets and manual reordering without generator changes.

## Scope

Modify only:

- `lib/problem-set.js`;
- the frontmatter of existing files under `problem-sets/`;
- `scripts/generate-codeforces-problem-sets.js`;
- focused tests for list ordering and generator frontmatter output.

Do not change the `/problem-sets` layout, card styles, routes, progress storage, Markdown task syntax, or problem-set content below frontmatter.

## Verification

1. Test that explicit numeric orders sort ascending regardless of `updatedAt`.
2. Test deterministic slug ordering for equal, missing, and invalid orders.
3. Test that explicit sets precede unordered sets.
4. Test that Codeforces Markdown rendering includes a supplied order.
5. Test or inspect the generated-file metadata preservation path.
6. Request `/problem-sets` and confirm all 12 cards appear in the specified order.
7. Change or simulate a file modification time and confirm the visible order is unchanged.
8. Run the repository tests and report any pre-existing unrelated failure separately.

