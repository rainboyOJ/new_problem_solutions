# Md Raw And Client-Side Code Highlighting Design

## Goal

Add an `Md Raw` action to every problem article. It opens a read-only modal
containing the existing problem API's `md_content`, with Markdown syntax
highlighting, line numbers, and a copy-all command.

As part of this work, move Prism syntax highlighting out of the server-side
Markdown renderer and into the browser for every rendered Markdown surface:

- problem analyses;
- problem statements;
- problem-set articles;
- the `Md Raw` modal;
- dynamically loaded generator source;
- single-problem preview pages.

The server will continue to produce complete, safe, readable code-block HTML.
Client-side highlighting is a progressive visual enhancement.

## Existing Behavior And Contract Change

`MarkdownRenderer` currently imports Prism, loads all supported grammars, and
writes Prism `token` spans into rendered HTML. Its output is consumed by page
views, the problem API, problem-set rendering, and the preview application.

After this change, `MarkdownRenderer` will no longer import or invoke Prism.
It will retain the existing code-block wrapper, language label, normalized
`language-*` class, line-number wrapper, escaped code text, and copy button.
It will not emit `class="token ..."` markup.

This intentionally changes the `/api/problems/:oj/:id` `html_content`
contract: the field remains fully rendered Markdown HTML with complete code
text and language metadata, but syntax coloring must be applied by a client.
The existing `md_content` field and API URL remain unchanged.

## Prism Asset Architecture

The installed `prismjs` dependency is the single source of browser Prism
assets. A shared Fastify registration helper will mount that package directory
read-only at `/vendor/prism/`. Both the production application and the
single-problem preview application will use the helper.

Pages that render Markdown will load, in order:

1. the locally hosted Prism theme;
2. an inline `window.Prism = { manual: true }` assignment;
3. Prism core;
4. Prism's autoloader plugin;
5. the project's client highlighting initializer.

The autoloader's component path will be fixed to
`/vendor/prism/components/`. It will load only grammars required by code blocks
on the current page. No Prism resource will depend on an external CDN, no
third-party source will be copied into `public/`, and no new frontend build
step will be introduced.

Fastify's static-file boundary will limit requests to files inside the
installed Prism package. Other `node_modules` and repository files will not be
exposed. Because each application already registers `@fastify/static` for
`public/`, the Prism registration will use `decorateReply: false` and reuse the
existing `reply.sendFile` decorator without a registration conflict.

## Language Normalization

The server remains responsible for turning fence labels into stable Prism
language names. Existing aliases such as `cpp`, `py`, `md`, and `html` remain
supported, and repository aliases such as `hs` and `cs` will normalize to
`haskell` and `csharp`.

Labels used only to describe data, including `text`, `plain`, `none`,
`inputN`, and `outputN`, will preserve their original visible header label but
use `language-none` for the code element. Prism's autoloader ignores
`language-none`, preventing pointless missing-component requests.

Unknown non-empty language labels may still be passed to the autoloader. If a
matching Prism component does not exist or fails to load, that block remains
readable plain code.

## Client Highlighting

A small project-owned client script will provide one idempotent entry point for
highlighting a document or a newly inserted subtree. It will:

- skip `language-none` blocks;
- avoid reprocessing blocks that have already been highlighted;
- request each missing language separately through Prism autoloader, allowing
  it to resolve that grammar's dependencies;
- support both initial page content and dynamically inserted content;
- log one concise browser-console warning if a grammar or Prism resource fails;
- leave the original escaped code visible on every failure path.

The initial page pass covers problem analyses, problem statements already
present in modal DOM, and problem-set content. The generator modal will call
the same entry point after inserting fetched source. The `Md Raw` controller
will call it after inserting `md_content`.

With JavaScript disabled, all server-rendered code remains visible with its
language header, line numbers, and source text. It only lacks syntax colors and
interactive copying.

## Md Raw Entry Point

The article action row will contain an `Md Raw` button immediately after the
`GitHub` button. It will use the same compact outline treatment and dark-theme
contrast rules as the GitHub source action.

The button will be hidden in server-rendered HTML. The `Md Raw` controller will
reveal it after successful initialization, so a browser without JavaScript
does not show a dead control. The trigger will carry a canonical API URL built
from the problem's OJ and problem ID; it will not derive identity from an
arbitrary location string.

Controller initialization requires Bootstrap Modal, Fetch, and the shared
clipboard helper, but it does not require Prism to succeed. If syntax
highlighting is unavailable, the controller still reveals the button and
provides readable raw text, loading, retry, and copy behavior.

Production and single-problem preview pages will render the same trigger and
use their existing `/api/problems/:oj/:id` implementations.

## Raw Modal

Clicking `Md Raw` opens a Bootstrap modal immediately. It uses `modal-xl` on
desktop and `modal-fullscreen-sm-down` on narrow screens. The dialog body is
vertically scrollable, while the raw content also supports horizontal
scrolling and does not wrap long lines.

The modal header contains:

- the title `Markdown Raw`;
- a `复制全部` button;
- the standard close icon.

These header controls remain visible while the body scrolls. Bootstrap restores
focus to the `Md Raw` trigger when the modal closes.

The content is a selectable, read-only `pre > code.language-markdown` surface.
Line numbers are rendered in a separate `aria-hidden` layer and are never part
of copied content. The API string is assigned through `textContent` before
Prism runs; raw Markdown is never interpreted as HTML.

## Loading State And Cache

The first open starts a request to the trigger's existing problem API URL. The
modal has the following states:

- **Loading:** show `加载中...`; disable `复制全部`.
- **Ready:** show highlighted Markdown and enable copying.
- **Error:** show a clear error and a `重试` command; do not show partial data.

HTTP errors, invalid JSON, and a missing or non-string `md_content` all enter
the same error state. A failed request is not cached. Retrying starts a new
request.

The first successful `md_content` result is cached in memory for the lifetime
of the page. Closing and reopening the modal reuses it immediately. Reloading
the page naturally obtains the latest content revision.

## Clipboard Behavior

The current clipboard implementation will be refactored into a small shared
browser namespace while preserving delegated code-block copying. Both normal
code blocks and `Md Raw` will use the same operation:

1. prefer `navigator.clipboard.writeText` in a secure context;
2. fall back to a temporary read-only textarea and `execCommand('copy')`;
3. report success as `已复制` for 1.5 seconds;
4. report failure as `复制失败` while leaving the content selectable for manual
   copying.

`Md Raw` copies the cached API string directly, never DOM text, so line numbers
and Prism markup cannot contaminate the clipboard.

## Accessibility And Responsive Behavior

The modal will have a labelled title, standard Bootstrap focus containment,
keyboard-operable copy, retry, and close controls, and an announced loading or
error status. Copy is disabled until valid content exists. The close icon has
an accessible name.

Raw code preserves whitespace and source line structure. It scrolls instead of
wrapping. The full-screen mobile dialog maximizes the usable width and keeps
header actions reachable. Light and dark themes must retain sufficient text,
border, focus, and button contrast.

## Error Handling

Prism failures are non-blocking visual failures. They produce at most one
console warning and leave complete plain code in place. One failed language
component must not prevent other languages from highlighting.

Raw API and clipboard failures are user-visible because they block requested
actions. Raw loading never injects error response bodies as Markdown and never
retains a failed response in the page cache.

## Testing

Server-side Markdown tests will verify that fenced and included code:

- preserves escaped source text;
- retains language classes, labels, line numbers, and copy controls;
- does not contain server-generated Prism `token` spans;
- maps aliases and data-only labels correctly.

Application and routing tests will verify that:

- problem and problem-set pages load local Prism and the initializer;
- Prism core, autoloader, themes, and representative language components are
  served from `/vendor/prism/`;
- paths outside the Prism package cannot be read through that prefix;
- article pages contain the hidden `Md Raw` trigger, modal, canonical API URL,
  loading/error/ready hooks, and copy/retry controls;
- the production API continues to return `md_content` and unhighlighted
  `html_content`;
- preview pages expose the same UI and return usable `md_content`.

Client-script tests will cover language normalization and ignored labels,
idempotent initial and dynamic highlighting, failure isolation, Raw API
success and error states, retry, page-lifetime caching, and clipboard feedback.
The repository's complete test suite must remain green.

Browser acceptance will cover desktop and mobile layouts in light and dark
themes. It will exercise initial article code, the statement modal, a
problem-set page, generator source, Raw loading, Markdown highlighting, line
numbers, horizontal scrolling, copying, failure/retry, and lack of overlap.
With JavaScript disabled, browser acceptance will confirm that normal code is
complete and readable and that `Md Raw` is hidden.

## Non-Goals

- Editing or saving Markdown from the modal.
- Adding a new raw-file endpoint or changing `md_content` semantics.
- Including YAML frontmatter in `Md Raw`.
- Downloading Markdown from the modal.
- Server-side syntax highlighting as a fallback.
- Introducing Vite or another build pipeline for the main server-rendered UI.
