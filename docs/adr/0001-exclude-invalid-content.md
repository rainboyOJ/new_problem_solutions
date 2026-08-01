---
status: accepted
---

# Exclude invalid content independently

Content catalog metadata is parsed independently per problem and problem set. An item with invalid frontmatter is excluded from its catalog and is not rendered; its public URL returns 404, while other valid updates continue to publish. We deliberately do not serve the last known good version because the current repository state is the publication source of truth.

## Consequences

Content errors must be visible through service logs and a protected content health check. One invalid problem or problem set cannot block catalog activation or service startup.

A content revision with isolated frontmatter errors still activates all valid items and remains deployed, but its content health is `degraded` and the GitHub Actions run fails with the invalid-item report. A red workflow therefore signals content quality failure, not necessarily rollback or total unavailability.

Problem bodies, included code, statements, and problem-set bodies are deliberately not validated during catalog activation. They render on first request. A render failure returns 404, atomically removes that item from the active catalog, and changes content health to `degraded`; it cannot retroactively fail a completed deployment workflow.
