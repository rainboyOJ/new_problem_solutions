# Expanded Include-Code Markdown Implementation Plan

> **For agentic workers:** Execute the tasks in order. Use focused tests to
> establish each behavior before changing the implementation.

**Goal:** Return self-contained problem `md_content` by expanding every
resolvable `@include-code(...)` directive into a fenced Markdown code block,
including directives inside recursively included Markdown files.

**Architecture:** A filesystem-focused include expander will traverse
`@include_md` and `@include-code` together while retaining the path of the
Markdown file that owns each directive. `MarkdownRenderer` will parse
frontmatter from the expanded string, expose its body as `md_content`, and
render the same body as `html_content`. The existing Markdown-It include-code
plugin remains as the fallback that turns unresolved directives into HTML
warnings.

**Tech Stack:** Node.js ESM, synchronous `fs`, `path`, Gray Matter,
Markdown-It, `node:test`, Fastify injection tests.

---

## File Structure

- Create: `lib/markdown-includes.js` (recursive Markdown/code expansion)
- Create: `tests/markdown-includes.test.js` (focused filesystem behavior)
- Modify: `lib/markdown.js` (use the shared expansion result)
- Modify: `tests/markdown-problem-link.test.js` (renderer/API field contract)
- Modify: `tests/preview-app.test.js` (preview API contract)
- Modify: `tests/fastify-app.test.js` (production API contract)

### Task 1: Specify Include Expansion At The Filesystem Boundary

**Files:**

- Create: `tests/markdown-includes.test.js`

- [ ] **Step 1: Add failing tests for language and path resolution**

Create temporary Markdown trees and assert that:

- an explicit language is preferred over the file extension;
- a missing language is inferred from the extension;
- relative code paths use the directory of their containing Markdown file;
- code directives nested through `@include_md` use the nested file's
  directory, including deeper recursive includes.

- [ ] **Step 2: Add failing tests for lossless fenced output**

Cover source files that are empty, omit their terminal newline, include one or
more terminal newlines, and contain embedded runs of backticks. Assert the
source bytes appear unchanged between the required fence-boundary newlines and
the generated fence is longer than every source backtick run.

- [ ] **Step 3: Add failing tests for fallback behavior**

Assert a missing or unreadable code file preserves the complete original
directive. Retain the existing `@include_md` missing-file behavior. Malformed
directives remain ordinary Markdown.

- [ ] **Step 4: Run the focused test to verify RED**

Run:

```bash
node --test tests/markdown-includes.test.js
```

Expected: FAIL because the focused expander does not exist.

### Task 2: Implement The Recursive Expander

**Files:**

- Create: `lib/markdown-includes.js`
- Modify: `lib/markdown.js`

- [ ] **Step 1: Implement directive parsing and fence selection**

Match the existing line-oriented grammars. For a successful code include,
resolve the path, read it verbatim, select `max(3, longestBacktickRun + 1)`
backticks, and emit a valid fenced code block. Trim only directive arguments;
never trim or normalize source content.

- [ ] **Step 2: Traverse both include types with file context**

Process each Markdown file while its absolute path is known. Recursing into an
`@include_md` target must change the context before processing its nested
directives. Preserve unresolved code directives for the existing renderer
fallback.

- [ ] **Step 3: Integrate once in `MarkdownRenderer.readfile()`**

Replace `processIncludeMd()` with the shared expander. Keep frontmatter parsing,
`toHTML()`, and the public JSON shape unchanged so both production and preview
routes inherit identical behavior.

- [ ] **Step 4: Run focused tests to verify GREEN**

Run:

```bash
node --test tests/markdown-includes.test.js tests/markdown-problem-link.test.js
```

Expected: PASS.

### Task 3: Lock The Production And Preview API Contract

**Files:**

- Modify: `tests/markdown-problem-link.test.js`
- Modify: `tests/preview-app.test.js`
- Modify: `tests/fastify-app.test.js`

- [ ] **Step 1: Assert renderer field consistency**

For a real problem with an include, assert `md_content` contains the fenced
source and no resolved directive. Assert `html_content` contains the escaped
same source, the canonical `language-*` class, and no server-side Prism token
spans. For a failed include, assert the directive remains in Markdown and the
existing warning appears in HTML.

- [ ] **Step 2: Update preview and production API assertions**

The preview fixture must return its `main.cpp` text inside a `cpp` fence and
must not return the include directive. The production detail API must likewise
return expanded source. Retain all existing client-highlighting assertions.

- [ ] **Step 3: Run focused and complete verification**

Run:

```bash
node --test tests/markdown-includes.test.js \
  tests/markdown-problem-link.test.js tests/preview-app.test.js \
  tests/fastify-app.test.js
npm test
npm run build
```

Expected: PASS.

- [ ] **Step 4: Browser acceptance**

Restart the preview server and open a problem containing
`@include-code(./main.py, python)` or its C++ equivalent. Confirm `Md Raw`
shows a fenced source block, Prism highlights the Markdown view, and
`复制全部` matches the API `md_content` exactly.

- [ ] **Step 5: Commit**

```bash
git add lib/markdown-includes.js lib/markdown.js \
  tests/markdown-includes.test.js tests/markdown-problem-link.test.js \
  tests/preview-app.test.js tests/fastify-app.test.js
git commit -m "feat: expand included code in raw Markdown"
```
