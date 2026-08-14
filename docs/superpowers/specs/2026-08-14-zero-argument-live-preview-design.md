# Zero-Argument Live Preview Design

## Goal

Make `npm run preview` a zero-problem-argument workflow. It initially previews
the most recently modified valid article, then watches only that problem.
Navigating to another problem page switches the one active watch directory and
synchronizes every connected browser.

## Command Contract

The supported commands are:

```bash
npm run preview
npm run preview -- --port 3100
npm run preview -- --host 127.0.0.1
```

`rbook preview` supports the same options. The old `<oj> <problem_id>`
positionals are removed and rejected with the new usage text. `HOST`, `PORT`,
`--host`, and `--port/-p` remain supported. The server does not open a browser.

## Initial Selection

At startup, scan `problems/**/index.md` and select the valid article with the
newest modification time. Equal times use normalized path order as a stable
tie-breaker. Exit with a clear error if no valid article exists.

The initial article is rendered into an immutable snapshot containing problem
metadata, expanded Markdown, HTML, statement content, generator metadata, and
the preview path aliases required by the routes.

## Active Preview State

A mutable `ActivePreview` owner holds exactly one valid snapshot and a
monotonic version. Fastify routes consult this owner per request rather than
closing over one startup problem.

- `/` redirects to the active problem URL.
- The active canonical URL and its aliases serve the snapshot.
- A valid problem page URL activates that problem and replaces the snapshot.
- The API serves the same snapshot as the HTML page.
- Problem-local assets are served only from the active problem directory.

All preview responses use `Cache-Control: no-store`, including pages, JSON,
problem-local files, and shared static assets. Production behavior is
unchanged.

## File Watching

Use Chokidar as a direct runtime dependency and watch only the active problem
directory. Events use a 500ms stability window and are coalesced before
processing. When page navigation activates another problem, close the old
watcher and create one for the new directory.

Any file event inside the active problem directory refreshes that problem.
Inactive directories are outside the watcher entirely and cannot trigger a
refresh or switch.

Article, included-code, statement, and asset changes rebuild a complete snapshot.
Static asset changes can retain the snapshot and only increment its version.
An invalid, incomplete, deleted, or unreadable article never replaces the
active snapshot. The terminal reports the path and concise error; a later valid
save recovers automatically.

## Browser Protocol

Preview pages load a preview-only client script that connects to
`/__preview/events` with `EventSource`.

The server sends the active canonical URL and version when a client connects,
then broadcasts:

- `reload` when the active problem changes;
- `switch` when another problem becomes active.

All open browsers receive the events. EventSource reconnects automatically;
the initial state message corrects a stale client that missed a switch.

For `reload`, the client stores the document scroll coordinates in
`sessionStorage`, reloads the entire page, then restores those coordinates.
For `switch`, it calls `location.replace()` and starts at the top. Modals close
on every reload and are not restored.

## Lifecycle And Logging

Startup output names the selected problem, source path, watch behavior, and
local/LAN access URLs. Refreshes, switches, and rejected snapshots log their
reason and source path.

On shutdown, close the watcher, SSE connections, and Fastify cleanly. Startup
failures must not leave a watcher or bound port behind.

## Testing

Automated coverage includes:

- newest valid article selection and deterministic ties;
- no-article and invalid-article errors;
- snapshot replacement and last-valid fallback;
- current-directory refresh, cross-problem switch, and irrelevant-event ignore;
- page navigation aliases, invalid navigation fallback, and global activation;
- 500ms event coalescing;
- SSE initial state, reload, switch, multiple clients, and reconnection state;
- browser scroll restore and `location.replace()` behavior;
- stale URL redirects and `no-store` headers;
- zero-positionals CLI parsing, retained network options, and rejected old
  positionals;
- updated help and documentation.

Final acceptance uses real problem files and connected browsers to verify
article, included code, statement, and asset changes.

## Non-Goals

- Hot-reloading application source, templates, or CSS changes.
- Partially replacing page DOM.
- Restoring modal state.
- Serving the complete problem catalog in preview mode.
- Automatically opening a browser.
