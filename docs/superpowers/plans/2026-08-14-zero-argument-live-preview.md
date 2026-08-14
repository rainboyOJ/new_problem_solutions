# Zero-Argument Live Preview Implementation Plan

**Goal:** Start the single-problem preview without a problem ID, follow the
most recently edited article, and reload every connected browser after a
stable relevant file change.

**Architecture:** `preview-state` owns immutable valid render snapshots and the
active version. `preview-watcher` converts Chokidar events into validated
snapshot replacements. `preview-app` resolves every route against current
state and publishes updates through SSE. A preview-only browser script applies
reload/switch events.

**Tech Stack:** Node.js ESM, Fastify 5, Chokidar 4, Pug, native EventSource,
`node:test`, `node:vm`, Chromium.

---

### Task 1: Specify Selection And Browser Behavior

**Files:**

- Create: `tests/preview-state.test.js`
- Create: `tests/preview-live-reload.test.js`
- Modify: `tests/rbook-cli.test.js`

- [ ] Test newest valid `index.md` selection, deterministic timestamp ties,
  empty repositories, snapshot metadata, and last-valid replacement.
- [ ] Test the browser script's initial state correction, same-page scroll
  save/reload/restore, and cross-problem `location.replace()`.
- [ ] Change CLI tests to zero positionals, retained host/port options, and
  rejected old positionals.
- [ ] Run the focused tests and confirm RED.

### Task 2: Implement Active Snapshots

**Files:**

- Create: `lib/preview-state.js`
- Modify: `lib/preview-app.js`
- Modify: `tests/preview-app.test.js`

- [ ] Move preview descriptor resolution into reusable state helpers while
  retaining existing exports where useful.
- [ ] Build immutable snapshots containing rendered page/API/statement data.
- [ ] Add active state with monotonic versions and subscriptions.
- [ ] Make routes resolve the current snapshot per request; redirect stale
  problem pages to the active canonical URL.
- [ ] Add `Cache-Control: no-store` to all preview responses.

### Task 3: Add SSE And Browser Reloading

**Files:**

- Create: `lib/preview-events.js`
- Create: `public/javascripts/preview-live-reload.js`
- Modify: `lib/preview-app.js`
- Modify: `views/problem.pug`
- Modify: `tests/preview-app.test.js`

- [ ] Publish initial state plus `reload`/`switch` events to all connected SSE
  responses, with heartbeat and cleanup.
- [ ] Load the live-reload client only on preview-rendered problem pages.
- [ ] Preserve document scroll for reloads, replace stale URLs for switches,
  and recover after EventSource reconnection.

### Task 4: Watch Problem Files

**Files:**

- Create: `lib/preview-watcher.js`
- Create: `tests/preview-watcher.test.js`
- Modify: `package.json`
- Modify: `package-lock.json`

- [ ] Add Chokidar as a direct runtime dependency.
- [ ] Coalesce relevant events for 500ms, select the newest valid changed
  `index.md`, rebuild active snapshots, and ignore inactive ordinary files.
- [ ] Preserve the last valid snapshot on invalid/deleted files and log concise
  recovery information.
- [ ] Verify watcher shutdown clears timers and file handles.

### Task 5: Replace The CLI Contract

**Files:**

- Modify: `bin/rbook.js`
- Modify: `tests/rbook-cli.test.js`

- [ ] Remove problem positionals, discover the initial snapshot, and start the
  watcher around the Fastify lifecycle.
- [ ] Retain network options and update startup/switch/refresh output.
- [ ] Close watcher, SSE clients, and Fastify on normal termination or startup
  failure.

### Task 6: Documentation And Verification

**Files:**

- Modify: `README.md`
- Modify: `docs/tools/rbook-preview.md`

- [ ] Document zero-argument selection, automatic switching, refresh scope,
  500ms stability, cache policy, errors, and retained network options.
- [ ] Run focused tests, `npm test`, and `npm run build`.
- [ ] Start `npm run preview` against the real repository and verify with
  Chromium that article, included-code, statement, and asset saves refresh;
  editing another `index.md` switches every connected browser.
- [ ] Commit the implementation without modifying problem content.
