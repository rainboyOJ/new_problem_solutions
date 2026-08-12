# Md Raw And Client-Side Code Highlighting Implementation Plan

> **For agentic workers:** Implement each task in order. Keep every commit
> independently testable; do not remove server-side highlighting until the
> client highlighter is active.

**Goal:** Add an `Md Raw` modal backed by the existing problem API and move all
Markdown code syntax highlighting from the server to locally hosted,
client-side Prism.

**Architecture:** Fastify exposes only the installed `prismjs` package at a
dedicated static prefix. Server-rendered Markdown emits escaped code and stable
language metadata, while one idempotent browser highlighter handles initial
and dynamic code. A separate modal controller fetches and caches `md_content`,
then reuses shared highlighting and clipboard APIs.

**Tech Stack:** Node.js ESM, Fastify 5, Pug, Bootstrap 5, Markdown-It, PrismJS,
native Fetch/Clipboard APIs, `node:test`, `node:vm`, Chromium.

---

## File Structure

- Create: `lib/prism-assets.js` (shared Prism static registration)
- Create: `views/includes/prism-client.pug` (ordered client Prism scripts)
- Create: `public/javascripts/code-highlight.js` (initial/dynamic highlighting)
- Create: `public/javascripts/md-raw-modal.js` (Raw modal state machine)
- Create: `tests/code-highlight.test.js` (browser-script unit tests)
- Create: `tests/code-copy.test.js` (shared clipboard unit tests)
- Create: `tests/md-raw-modal.test.js` (Raw controller unit tests)
- Modify: `app.js` (register local Prism assets)
- Modify: `lib/preview-app.js` (register the same assets)
- Modify: `lib/markdown.js` (remove server Prism and normalize languages)
- Modify: `public/javascripts/code-copy.js` (publish shared clipboard API)
- Modify: `public/javascripts/gen-modal.js` (use shared dynamic highlighter)
- Modify: `public/stylesheets/style.css` (Raw dialog and source-action styles)
- Modify: `views/layout.pug` (use local Prism theme)
- Modify: `views/problem.pug` (Prism client, trigger, and Raw dialog)
- Modify: `views/problem-set.pug` (Prism client)
- Modify: `tests/fastify-app.test.js` (asset and article integration)
- Modify: `tests/markdown-problem-link.test.js` (unhighlighted server contract)
- Modify: `tests/preview-app.test.js` (preview contract and Raw UI)

### Task 1: Serve Prism Locally Without Changing Rendering

**Files:**

- Create: `lib/prism-assets.js`
- Modify: `app.js`
- Modify: `lib/preview-app.js`
- Modify: `views/layout.pug`
- Modify: `tests/fastify-app.test.js`
- Modify: `tests/preview-app.test.js`

- [ ] **Step 1: Add failing static-asset assertions**

Extend application and preview tests to request:

```text
/vendor/prism/components/prism-core.min.js
/vendor/prism/components/prism-cpp.min.js
/vendor/prism/plugins/autoloader/prism-autoloader.min.js
/vendor/prism/themes/prism-tomorrow.min.css
```

Assert status `200` and representative content types. Also request a path that
would escape the Prism directory, such as
`/vendor/prism/../../package.json`, and assert it is not served.

Update the article-page assertion to require the local theme URL and reject
the old CDN Prism theme URL.

- [ ] **Step 2: Run focused tests to verify RED**

Run:

```bash
node --test --test-name-pattern='Prism|problem detail page|preview app renders' \
  tests/fastify-app.test.js tests/preview-app.test.js
```

Expected: FAIL because `/vendor/prism/` is not registered and the layout still
uses the CDN theme.

- [ ] **Step 3: Add one shared static registration helper**

Resolve the installed package directory from `import.meta.url`, not
`process.cwd()`. Register it with:

```js
{
  root: prismPackageRoot,
  prefix: '/vendor/prism/',
  decorateReply: false,
}
```

Call the helper after the existing `public/` static registration in both
`buildApp` and `buildPreviewApp`. Do not expose all of `node_modules`.

- [ ] **Step 4: Replace the external Prism theme**

Change `views/layout.pug` to load:

```pug
link(href="/vendor/prism/themes/prism-tomorrow.min.css", rel="stylesheet")
```

Do not add browser Prism scripts yet. Server-side highlighting remains active
in this commit.

- [ ] **Step 5: Run focused and complete tests**

Run:

```bash
node --test tests/fastify-app.test.js tests/preview-app.test.js
npm test
```

Expected: PASS.

- [ ] **Step 6: Commit**

```bash
git add lib/prism-assets.js app.js lib/preview-app.js views/layout.pug \
  tests/fastify-app.test.js tests/preview-app.test.js
git commit -m "feat: serve Prism assets locally"
```

### Task 2: Add The Shared Client Highlighter

**Files:**

- Create: `public/javascripts/code-highlight.js`
- Create: `views/includes/prism-client.pug`
- Create: `tests/code-highlight.test.js`
- Modify: `views/problem.pug`
- Modify: `views/problem-set.pug`
- Modify: `public/javascripts/gen-modal.js`
- Modify: `tests/fastify-app.test.js`
- Modify: `tests/preview-app.test.js`

- [ ] **Step 1: Write failing browser-script unit tests**

Use `node:vm` with small document, code-element, and Prism doubles. Cover:

- initial highlighting of each eligible `code[class*="language-"]` element;
- skipping `language-none`;
- skipping server-rendered code that already contains `.token` spans during
  this transitional commit;
- loading two missing languages independently;
- one language load failure not blocking another language;
- idempotent repeated calls, including calls made while a grammar request is
  still in flight;
- a dynamic single-element entry point for generator and Raw content;
- at most one console warning for repeated failures.

The public interface should be:

```js
window.RbookCodeHighlight.highlight(root);
window.RbookCodeHighlight.highlightElement(codeElement);
```

- [ ] **Step 2: Run the unit test to verify RED**

Run:

```bash
node --test tests/code-highlight.test.js
```

Expected: FAIL because the script does not exist.

- [ ] **Step 3: Implement idempotent Prism orchestration**

The script must:

- return without changing code when Prism is unavailable;
- identify the canonical language from the element class;
- skip `none` and already highlighted elements;
- use a loaded grammar immediately;
- otherwise call `Prism.plugins.autoloader.loadLanguages` once per language;
- preserve escaped source text on every error path;
- mark loading, successful, and failed elements so later subtree scans do not
  duplicate requests or highlighting;
- scan the document once at startup.

Load missing languages separately rather than as one batch.

- [ ] **Step 4: Add the ordered Pug include**

Create `views/includes/prism-client.pug` with this order:

```pug
script.
  window.Prism = { manual: true };
script(src="/vendor/prism/components/prism-core.min.js")
script(
  src="/vendor/prism/plugins/autoloader/prism-autoloader.min.js"
  data-autoloader-path="/vendor/prism/components/"
)
script(src="/javascripts/code-highlight.js")
```

Include it in the `block scripts` of `problem.pug` and `problem-set.pug` before
scripts that insert dynamic code. Assert both rendered page types contain the
local script URLs in the correct order.

- [ ] **Step 5: Route generator highlighting through the shared API**

Replace the direct `Prism.highlightElement(codeEl)` call in `gen-modal.js` with
`window.RbookCodeHighlight.highlightElement(codeEl)`. If the shared API is
unavailable, leave fetched source as readable plain text.

- [ ] **Step 6: Run focused and complete tests**

Run:

```bash
node --test tests/code-highlight.test.js tests/fastify-app.test.js \
  tests/preview-app.test.js
npm test
```

Expected: PASS. Existing server-generated token markup is still present and is
skipped safely by the client initializer.

- [ ] **Step 7: Commit**

```bash
git add public/javascripts/code-highlight.js public/javascripts/gen-modal.js \
  views/includes/prism-client.pug views/problem.pug views/problem-set.pug \
  tests/code-highlight.test.js tests/fastify-app.test.js tests/preview-app.test.js
git commit -m "feat: add client-side Prism highlighter"
```

### Task 3: Remove Server-Side Prism Highlighting

**Files:**

- Modify: `lib/markdown.js`
- Modify: `tests/markdown-problem-link.test.js`
- Modify: `tests/fastify-app.test.js`
- Modify: `tests/preview-app.test.js`

- [ ] **Step 1: Change tests to the new server contract**

Update Markdown renderer, preview page, preview API, and production API tests
to assert:

- C++ source appears HTML-escaped, for example `&lt;bits/stdc++.h&gt;`;
- wrapper and code elements retain the normalized `language-cpp` class;
- language label, line-number wrapper, and copy button remain;
- no server response contains `<span class="token` for code blocks;
- `py`, `md`, `html`, `hs`, and `cs` map to Prism's canonical language names;
- `text`, `plain`, `none`, `input1`, and `output2` display their original label
  while code uses `language-none`;
- Mermaid and Graphviz keep their existing special rendering and never become
  Prism code blocks.

- [ ] **Step 2: Run tests to verify RED**

Run:

```bash
node --test tests/markdown-problem-link.test.js tests/fastify-app.test.js \
  tests/preview-app.test.js
```

Expected: FAIL because `MarkdownRenderer` still emits Prism tokens.

- [ ] **Step 3: Simplify the server renderer**

Remove these server-side dependencies from `lib/markdown.js`:

```js
import Prism from 'prismjs';
import loadPrismLanguages from 'prismjs/components/index.js';
loadPrismLanguages();
```

Make the fence renderer always pass `md.utils.escapeHtml(displayContent)` into
the code element. Keep line counting based on the original display content.

Centralize aliases and data-only labels in `mapFenceLanguage`. Return `none`
for plain/data labels while keeping `rawInfo` as the visible header. Do not
change `md_content` construction or include expansion.

- [ ] **Step 4: Run focused and complete tests**

Run:

```bash
node --test tests/markdown-problem-link.test.js tests/fastify-app.test.js \
  tests/preview-app.test.js
npm test
```

Expected: PASS. At this point server responses are unhighlighted, while article
and problem-set pages restore colors in the browser.

- [ ] **Step 5: Commit**

```bash
git add lib/markdown.js tests/markdown-problem-link.test.js \
  tests/fastify-app.test.js tests/preview-app.test.js
git commit -m "refactor: move Markdown code highlighting to client"
```

### Task 4: Publish A Shared Clipboard API

**Files:**

- Create: `tests/code-copy.test.js`
- Modify: `public/javascripts/code-copy.js`

- [ ] **Step 1: Write failing clipboard tests**

Use `node:vm` and DOM doubles to verify:

- secure contexts call `navigator.clipboard.writeText`;
- insecure contexts use the temporary textarea fallback and remove it;
- secure Clipboard success resolves `true`, Clipboard rejection rejects, and
  textarea fallback resolves the boolean returned by `execCommand('copy')`;
- button feedback becomes `已复制` or `复制失败` and resets after 1.5 seconds;
- existing delegated `[data-code-copy]` behavior copies only the code element's
  `textContent`;
- the same helpers are exposed for the Raw controller.

Use this browser interface:

```js
window.RbookClipboard.copyText(text);
window.RbookClipboard.setButtonState(button, text, stateClass);
```

- [ ] **Step 2: Run the test to verify RED**

Run:

```bash
node --test tests/code-copy.test.js
```

Expected: FAIL because the current helpers are private.

- [ ] **Step 3: Refactor without changing existing code-copy behavior**

Publish the two helpers on `window.RbookClipboard`, then make the delegated
listener call that same object. Preserve the current secure-context preference,
textarea fallback, status classes, Chinese messages, and timeout.

- [ ] **Step 4: Run focused and complete tests**

Run:

```bash
node --test tests/code-copy.test.js tests/markdown-problem-link.test.js
npm test
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add public/javascripts/code-copy.js tests/code-copy.test.js
git commit -m "refactor: share browser clipboard helpers"
```

### Task 5: Add The Progressive Md Raw Interface

**Files:**

- Modify: `views/problem.pug`
- Modify: `public/stylesheets/style.css`
- Modify: `tests/fastify-app.test.js`
- Modify: `tests/preview-app.test.js`

- [ ] **Step 1: Add failing page-structure tests**

For production and preview article pages, assert:

- a hidden `Md Raw` button appears immediately after the GitHub action when
  GitHub exists, or at the start of the source-action group in preview;
- the button contains a canonical, percent-encoded
  `/api/problems/:oj/:id` URL in a data attribute;
- the modal has `modal-xl`, `modal-dialog-scrollable`, and
  `modal-fullscreen-sm-down`;
- the header contains `Markdown Raw`, `复制全部`, and an accessible close icon;
- copy starts disabled;
- body hooks exist for status, retry, line numbers, and
  `code.language-markdown`;
- retry starts hidden;
- the raw content is not embedded in the article HTML.

- [ ] **Step 2: Run focused tests to verify RED**

Run:

```bash
node --test --test-name-pattern='problem detail page|preview app renders' \
  tests/fastify-app.test.js tests/preview-app.test.js
```

Expected: FAIL because the trigger and modal do not exist.

- [ ] **Step 3: Add semantic Pug markup**

Build the API URL from `problem.oj` and `problem.problem_id` with component
encoding. Use stable `data-md-raw-*` hooks rather than styling IDs. Assign
`hidden` to the trigger and retry button in server HTML.

Render line numbers in an `aria-hidden="true"` sibling of the code element.
Give the loading/error status an appropriate live region. Do not use unescaped
HTML for API content.

- [ ] **Step 4: Add focused responsive styles**

Add styles for:

- a shared `.problem-source-link` dark-theme button treatment used by GitHub
  and `Md Raw`;
- a stable Raw code viewport with separate line-number and code columns;
- `white-space: pre`, horizontal scrolling, and no wrapping;
- readable light/dark colors and visible focus states;
- a compact mobile header whose title and controls do not overlap.

Keep the modal as a top-level dialog; do not nest decorative cards in it.

- [ ] **Step 5: Run focused and complete tests**

Run:

```bash
node --test tests/fastify-app.test.js tests/preview-app.test.js
npm test
```

Expected: PASS. The trigger remains hidden because its controller is added in
the next task.

- [ ] **Step 6: Commit**

```bash
git add views/problem.pug public/stylesheets/style.css \
  tests/fastify-app.test.js tests/preview-app.test.js
git commit -m "feat: add Md Raw modal interface"
```

### Task 6: Implement Raw Loading, Retry, Cache, Highlight, And Copy

**Files:**

- Create: `public/javascripts/md-raw-modal.js`
- Create: `tests/md-raw-modal.test.js`
- Modify: `views/problem.pug`
- Modify: `tests/fastify-app.test.js`
- Modify: `tests/preview-app.test.js`

- [ ] **Step 1: Write failing controller tests**

Run the browser script through `node:vm` with explicit doubles for Bootstrap,
Fetch, clipboard, highlighter, and the required DOM nodes. Cover:

- controller initialization reveals the trigger;
- clicking opens the modal immediately and enters loading state;
- loading disables copy;
- a successful JSON response inserts `md_content` via `textContent`;
- line count is correct for empty, one-line, and trailing-newline content;
- successful content invokes `RbookCodeHighlight.highlightElement`;
- copy uses the cached API string rather than DOM text;
- a second open reuses the successful in-memory result without another fetch;
- HTTP error, invalid JSON, and missing/non-string `md_content` show the same
  error state and reveal retry;
- failures are not cached and retry issues a new request;
- Prism absence/failure still leaves Raw readable and copyable;
- copy success/failure delegates feedback to `RbookClipboard`;
- close focus behavior remains Bootstrap-managed.

- [ ] **Step 2: Run the controller test to verify RED**

Run:

```bash
node --test tests/md-raw-modal.test.js
```

Expected: FAIL because the controller does not exist.

- [ ] **Step 3: Implement a small explicit state machine**

Keep one page-local `cachedMarkdown` value and one optional in-flight request.
Implement named transitions for `loading`, `ready`, and `error`. Each transition
must set status visibility, retry visibility, code visibility, and copy disabled
state together so stale UI cannot leak between attempts.

On ready:

1. set `code.textContent = markdown`;
2. calculate a separate line-number string, with one number per
   `markdown.split('\n')` entry so a terminal newline retains its final blank
   source line;
3. reveal content and enable copy;
4. call the shared highlighter if available.

Do not inject response error bodies. Do not cache failed or malformed data.

- [ ] **Step 4: Load the controller after its dependencies**

Add `/javascripts/md-raw-modal.js` to `problem.pug` after Bootstrap (from the
layout), `code-copy.js` (from the layout), and the Prism client include. Extend
route tests to assert the script is present.

- [ ] **Step 5: Run focused and complete tests**

Run:

```bash
node --test tests/md-raw-modal.test.js tests/code-copy.test.js \
  tests/code-highlight.test.js tests/fastify-app.test.js tests/preview-app.test.js
npm test
```

Expected: PASS.

- [ ] **Step 6: Commit**

```bash
git add public/javascripts/md-raw-modal.js views/problem.pug \
  tests/md-raw-modal.test.js tests/fastify-app.test.js tests/preview-app.test.js
git commit -m "feat: load and copy raw problem Markdown"
```

### Task 7: Runtime And Browser Acceptance

**Files:** No expected source changes. If acceptance exposes a defect, add a
failing automated test before fixing it and commit that fix separately.

- [ ] **Step 1: Run repository verification**

Run:

```bash
git diff --check
npm test
npm run build
```

Expected: all commands pass.

- [ ] **Step 2: Start an isolated local server**

Run on an unused port:

```bash
PORT=3018 HOST=127.0.0.1 npm start
```

Keep the process running through all acceptance checks.

- [ ] **Step 3: Verify assets and API with HTTP requests**

Confirm `200` responses for Prism core, autoloader, Markdown, C++, and Python
components. Request one representative problem API and confirm:

- `md_content` is a non-empty string;
- `html_content` contains escaped source and `language-*` classes;
- `html_content` contains no `<span class="token`.

- [ ] **Step 4: Verify initial client highlighting with Chromium**

Use installed Chromium with a virtual-time budget:

```bash
chromium --headless --no-sandbox --disable-gpu --virtual-time-budget=5000 \
  --dump-dom http://127.0.0.1:3018/problems/luogu/P1001/
```

Confirm the post-JavaScript DOM contains Prism token spans. Repeat for a
problem-set detail page and a problem statement modal page.

- [ ] **Step 5: Exercise the complete interaction in a browser**

Start the installed `chromedriver` on a temporary local port and use its W3C
WebDriver HTTP API to drive the installed Chromium; do not add an npm browser
dependency. Check at desktop and mobile widths in both light and dark themes:

- `Md Raw` becomes visible without shifting or overlapping the action row;
- the modal opens immediately and loads API Markdown;
- desktop uses a wide dialog and mobile uses full screen;
- long lines scroll horizontally and do not wrap;
- line numbers align and are not selected as copied content;
- Markdown is syntax highlighted;
- copy-all produces exactly the API `md_content` and shows feedback;
- close returns focus to the trigger;
- reopen uses the cache without a second network request;
- forced API failure shows retry, and retry succeeds after restoration;
- problem analysis, statement, problem-set, and generator code all highlight;
- no controls or text overlap.

Capture desktop and mobile screenshots through WebDriver for visual comparison.
Use browser script execution to compare clipboard input with API `md_content`
when the headless environment does not expose the system clipboard directly.

- [ ] **Step 6: Verify progressive enhancement**

Disable JavaScript and reload representative problem and problem-set pages.
Confirm server-rendered code is complete, escaped, line-numbered, and readable;
confirm `Md Raw` remains hidden.

- [ ] **Step 7: Stop the server and inspect the final state**

Stop the exact server process started in Step 2. Then run:

```bash
git status --short
git log --oneline -7
```

Expected: only intentional implementation commits exist and the worktree is
clean.
