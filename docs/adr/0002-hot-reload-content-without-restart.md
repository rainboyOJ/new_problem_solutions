---
status: accepted
---

# Hot reload content without restarting the service

Application changes continue to build a Docker image and restart the service. Content-only changes skip the image build: the VPS updates its Git worktree and sends `SIGHUP` to the running Node process, which builds one in-memory content snapshot containing both the problem and problem-set catalogs and atomically activates them together. Problem bodies remain request-rendered, and `problems.json` is no longer a required generated deployment artifact.

`problems.json` and its generation path are removed completely from runtime, startup, deployment, and `ProblemManager`. The repository content is the only publication source; a future export use case must introduce a separately named export command rather than revive a runtime cache file.

## Consequences

The content directories remain read-only bind mounts. The running process must survive catalog refresh failures, isolate invalid entries, and expose refresh health without requiring a container restart.

At cold start, the service builds the initial in-memory catalog before serving normal content. Invalid individual items are excluded. If a content root is missing or unreadable, the HTTP service still starts in the content-unavailable state: application and health endpoints remain available, while content HTML and APIs return the established 503 responses until a later `SIGHUP` succeeds.

Before the VPS modifies content files, it puts content routes into a switching state. Those routes return `503 Retry-After` while the Git worktree and catalog snapshot change; health and static asset routes remain available. The service leaves switching state only after the new catalog snapshot is atomically active, preventing requests from combining metadata and bodies from different commits.

Entering switching state blocks new content requests and starts draining requests already rendering content. The deploy waits up to 10 seconds for the in-flight content count to reach zero before changing the worktree. Drain timeout cancels the update before Git mutation, rebuilds the current snapshot to leave switching state, and fails the workflow.

A catalog-wide refresh failure does not roll the Git worktree back and does not reactivate old content. Content routes remain unavailable with HTTP `503`; HTML responses render a prominent centered “内容暂时不可用” state without internal details, and APIs return structured error JSON. This state lasts until a later content revision activates successfully, while the application process, static assets, and health endpoints stay available for diagnosis.

The VPS atomically writes the target Git commit and update time to an untracked `content-revision.json` handoff file, mounted read-only into the container. It does not pass changed paths or request body validation. After `SIGHUP`, the service reports that commit as `activeRevision` only after frontmatter catalog activation succeeds. GitHub Actions waits for the expected revision through content health instead of treating signal delivery as deployment completion; the container does not receive the host repository’s `.git` directory.

Catalog refresh has a 30-second deadline. Timeout moves content from switching to unavailable and fails the workflow without rollback. Concurrent refresh requests are serialized and coalesced: a refresh already in progress finishes or times out, then the service processes only the newest pending revision.

Problem and problem-set bodies are not precompiled as a corpus. They are rendered on demand and share a revision-scoped LRU cache of at most 200 content pages; activating a content revision clears the cache. This bounds memory while avoiding repeated Markdown, math, and syntax-highlighting work for frequently read content.

Content health has a public summary and a protected detail endpoint. The detail endpoint requires `Authorization: Bearer` with `CONTENT_HEALTH_TOKEN`; a missing production token disables that endpoint with 404, and an invalid token returns 401. Secrets and detailed file errors never appear in the public summary, revision handoff, repository, or logs that echo configuration.

Application liveness is separate from content health. `/api/health/live` returns 200 whenever Node can respond and is the only Docker healthcheck target. Public `/api/health/content` returns 200 for healthy, degraded, or switching and 503 for initializing or unavailable. GitHub Actions, not Docker, evaluates content revision and quality, so content failure cannot cause a container restart loop.

Content health uses exactly five states: `initializing` while the first snapshot is built; `healthy` for an active snapshot without known invalid items; `degraded` for an active snapshot with isolated items; `switching` while requests drain, Git changes, or a snapshot builds; and `unavailable` after catalog-wide failure or timeout. Normal content routes are available only in `healthy` and `degraded`.

Health reports `targetRevision`, `activeRevision`, and `lastSuccessfulRevision`. `activeRevision` identifies content actually served, is retained during switching, becomes the target only after successful activation, and is cleared in initializing or unavailable states. `lastSuccessfulRevision` is diagnostic history only and never implies that stale content remains available.
