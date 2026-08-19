---
name: rbook-markdown
description: >-
  使用本项目 Markdown 时必须触发此 skill：只要用户要创建、修改、审查或解释
  rbook 的 Markdown 语法/写作规范，或提到 admonition/提示框、::: 容器、KaTeX
  公式、Mermaid、Graphviz、代码引用、题目双链、TOC、图片、伪代码、代码 Tab、
  iframe、题解 index.md 格式或 @include-code，就使用本 skill。Use it for any
  Markdown rendered by this rbook project. It identifies the syntax currently
  supported by lib/markdown.js, chooses the right form for the file type, and
  applies the repository's verifiable writing rules instead of guessing from
  generic Markdown or historical plugins.
compatibility: >-
  Requires the repository checkout and its Node.js dependencies when syntax
  behavior must be rendered or verified.
---

# RBook Markdown

Use this skill as the project's Markdown capability and writing guide. It is an
operational guide for an AI agent, not a replacement for the full CommonMark or
Markdown-it documentation.

## Scope and authority

Apply the rules in this order:

1. The current implementation in `lib/markdown.js` and
   `lib/markdown-plugins/` is the behavior authority.
2. Current tests and `docs/` provide tested examples and constraints.
3. `references/syntax-reference.md` and
   `references/writing-conventions.md` explain the behavior for authors.
4. `oj-problem-format-spec` remains the authority for the complete
   `problems/**/index.md` article skeleton and frontmatter.

Treat `old_scripts/rbook/markdown-it/` as historical only. Do not recommend a
plugin or syntax merely because it appears there. If implementation, tests, and
documentation disagree, inspect the implementation and report the discrepancy
instead of silently inventing a rule.

## Choose the document rules

First identify the file being edited:

| File | Apply |
| --- | --- |
| `problems/<oj>/<problem_id>/index.md` | This skill for Markdown plus `oj-problem-format-spec` for article structure and frontmatter. |
| `problems/<oj>/<problem_id>/problem.md` | This skill for rendering only; keep it as the fetched problem-statement archive and do not impose the article template. |
| `problem-sets/*.md` | This skill for rendering, task lists, problem links, and concise list writing. |
| `docs/*.md`, `README.md`, and other rendered Markdown | This skill for rendering and general writing conventions. |

Read the syntax reference for any non-standard construct. Read the writing
conventions when authoring or reviewing prose. For a formal problem solution,
also read the relevant parts of `oj-problem-format-spec/SKILL.md`; do not copy
its complete rules into a new document.

## Three support tiers

Classify a feature before using it:

- **稳定常用**: standard Markdown, code fences, tables, KaTeX, admonitions,
  task lists, problem links, `@include-code`, Mermaid, Graphviz, and ordinary
  relative images. Use these when they fit the teaching goal.
- **专用能力**: fold/class/blackboard/style containers, `@include_md`,
  pseudocode, image sizes, subscript/superscript/mark/insert/delete,
  abbreviations, emoji, and `viz-gallery`. Use them only when the file and
  browser context support the intended presentation.
- **兼容/谨慎**: raw HTML, `/i/` iframe blocks, `.excalidraw.svg` image links,
  inline CSS containers, code-tab annotations (the current final fence renderer
  overrides the tab renderer), external assets, and any syntax whose rendering
  needs a client-side script or external service. Prefer a normal Markdown or
  fenced text fallback when the dependency is optional.

The complete forms, limits, and examples are in
`references/syntax-reference.md`. Do not use a feature just to decorate a
page: explain what a diagram, table, callout, or embedded asset teaches.

## Authoring workflow

1. Identify the Markdown file type and read the applicable rules above.
2. Choose the simplest supported syntax that expresses the content. Prefer
   ordinary Markdown over a custom container when both are equally clear.
3. Keep paths relative to the Markdown file for local code, images, and nested
   Markdown. Use the exact directive spelling and language labels documented in
   the reference.
4. For a non-standard block, copy a minimal example from the reference and
   verify its closing marker, indentation, and surrounding blank lines.
5. For diagrams and tables, write one sentence before the block describing its
   purpose and a short explanation after it describing what the reader should
   notice. Follow the more specific visualization limits in
   `oj-problem-format-spec` and `docs/problem-visualization.md`.
6. When the syntax is uncertain, render a small string with the exported
   `createMarkdownIt()` from `lib/markdown.js`, passing a realistic `env.filePath`
   when relative paths are involved. Do not infer behavior from a browser
   preview alone.
7. Run the narrowest relevant tests, then inspect the rendered HTML for the
   expected element/class and for an unexpanded directive or broken resource.

## Non-negotiable rules

- Do not invent plugin syntax, frontmatter fields, or renderer behavior.
- Do not use `@include-code` for a missing file; fix the path or leave the
  directive visible for the warning fallback.
- Do not put a code block, image, or diagram inside a custom container unless
  its closing marker and indentation have been verified.
- Do not use raw HTML or `style` containers to bypass a readable Markdown
  structure. External iframe URLs must be complete and HTTPS unless the user
  explicitly accepts the security and availability risk.
- Give every image meaningful alt text and use a relative path for repository
  assets. Use an image width/height suffix only when it improves layout.
- Keep Mermaid node IDs ASCII and put Chinese text in labels. Keep Graphviz
  source small enough to inspect in the page; generate a local image for a
  large or static diagram.
- Do not recommend historical footnotes, `kbd`, pangu, or old `viz-gallery`
  variants as current features unless the implementation has been restored and
  verified.
- Never replace the repository's `oj-problem-format-spec` with this skill when
  the task is specifically about a formal problem article skeleton.

## Review checklist

Before handing off a Markdown change, check:

- The file type and applicable skill were identified.
- Every extension is in the current syntax reference and is in the right
  support tier.
- Opening and closing markers match, and nested blocks are not accidentally
  consumed by a parent container.
- Relative code and image paths resolve from the Markdown file's directory.
- Code fences use a useful language label; `mermaid`, `dot`/`graphviz`, and
  `viz-*` fences are intentional.
- A table or visual has a teaching purpose and explanatory prose.
- Headings, TOC usage, frontmatter, and code includes obey the file-specific
  writing conventions.
- No unsupported historical syntax or unexplained raw HTML was introduced.
- A focused render or test was run when a custom extension changed.

## References

- [Syntax reference](references/syntax-reference.md): complete current
  extension inventory, examples, and limits.
- [Writing conventions](references/writing-conventions.md): general Markdown
  prose rules and the boundary with the formal problem-article skill.
- [`oj-problem-format-spec`](../oj-problem-format-spec/SKILL.md): required for
  `problems/**/index.md` article structure.
- [`docs/problem-visualization.md`](../../../docs/problem-visualization.md):
  repository visualization guidance.
