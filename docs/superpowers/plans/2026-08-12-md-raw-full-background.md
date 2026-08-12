# Md Raw Full-Height Background Implementation Plan

**Goal:** Keep the `Md Raw` line-number and code backgrounds continuous from
the first source line through the last line for long and short Markdown.

**Architecture:** Preserve the existing modal DOM and scrolling owner. Correct
the flex cross-axis sizing in CSS so the two source columns use their natural
content height, while a shared minimum height keeps short content filling the
visible viewer.

**Tech Stack:** CSS, Fastify integration assertions, Chromium DevTools Protocol.

---

### Task 1: Lock The Layout Contract

**Files:**

- Modify: `tests/fastify-app.test.js`

- [ ] Add stylesheet assertions requiring the source viewport to align its
  columns at the start and requiring both the line-number and code columns to
  fill the viewer's minimum height.
- [ ] Run the focused test and confirm it fails against the current
  `align-items: stretch` layout.

### Task 2: Correct The Source Viewer Sizing

**Files:**

- Modify: `public/stylesheets/style.css`

- [ ] Override the Prism theme's `pre[class*=language-]` padding on the `Md Raw`
  viewport so the viewport remains the single scrolling/background boundary.
- [ ] Change cross-axis alignment to `flex-start`, allowing long columns to
  grow to their natural source height.
- [ ] Give the line-number and code columns a shared `min-height: 100%` so
  short documents still fill the visible viewer.
- [ ] Keep the existing sticky gutter, colors, font metrics, responsive rules,
  and horizontal scrolling behavior unchanged.

### Task 3: Verify Long And Short Documents

**Files:**

- Verify: `tests/fastify-app.test.js`
- Verify: `tests/md-raw-modal.test.js`

- [ ] Run focused tests for stylesheet delivery and `Md Raw` behavior.
- [ ] Run the full automated test suite and production build.
- [ ] Open real `luogu/P1001` in Chromium at desktop and mobile viewport
  widths. Confirm both source columns cover all 72 expanded lines and remain
  covered after scrolling beyond line 31.
- [ ] Replace the displayed Markdown with a short fixture in the browser and
  confirm both columns still fill the visible source viewer.
- [ ] Commit the implementation as `fix: extend Md Raw background through source`.
