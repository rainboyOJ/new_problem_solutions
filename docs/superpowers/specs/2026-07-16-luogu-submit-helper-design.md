# Luogu Submit Helper Design

## Goal

Turn `scripts/problem-analysis-tools/submit_helper.py` into a keyboard-driven helper for manually submitting a Luogu problem set. It must resolve repository problem paths correctly, prefer `main.py`, skip problems already accepted by the configured Luogu user, and show enough local context to move backward and forward safely.

The helper copies code and opens a browser page. It does not submit code, read browser login cookies, or bypass Luogu verification.

## Command Line

The existing invocation remains valid:

```bash
python3 scripts/problem-analysis-tools/submit_helper.py <problem-set.md> --skip-done
```

New options:

- `--user USERNAME`: Luogu username used for public accepted-problem lookup; defaults to `Rainboy`.
- `--wait-min MINUTES`: lower bound of the random Enter delay; defaults to `1`.
- `--wait-max MINUTES`: upper bound of the random Enter delay; defaults to `5`.

Wait values accept non-negative decimals. The command rejects a negative value or a minimum greater than the maximum.

## Problem Loading

The helper parses problem references in Markdown order and keeps their original metadata. It only adds Luogu problems whose solution file exists. Luogu IDs use the repository convention:

- `B2002` maps to `problems/luogu/b2002`.
- `P1068` and `1068` map to `problems/luogu/1068`.

Within a problem directory, `main.py` has first priority, followed by the existing fallback languages.

When `--skip-done` is present, the helper resolves the username through Luogu's public user search endpoint, then reads the user's public practice page once and extracts all accepted problem IDs. It skips the union of those IDs and Markdown entries marked `[x]`. The accepted set remains fixed for the process so list positions do not change during navigation.

If public accepted-problem lookup fails or returns an invalid response, `--skip-done` stops with a clear error. It must not silently continue with an empty accepted set.

## Terminal Interaction

The terminal enters a single-key mode and renders a five-item window centered on the current problem when possible:

```text
  [18/173] P5703
  [19/173] P5704
> [20/173] B2002  problems/luogu/b2002/main.py
  [21/173] P5705
  [22/173] P5706

o open  n next now  Enter timed next  p previous  q quit
```

The denominator is the fixed number of navigable problems after filtering. At list boundaries, the window shifts while showing up to five entries. Selecting a problem copies its source code to the clipboard.

Key behavior:

- `o` opens `https://www.luogu.com.cn/problem/<REAL_ID>#submit` with Python's browser launcher.
- `n` immediately selects the next problem.
- `Enter` chooses a random duration in the configured inclusive range, shows an in-place `MM:SS` countdown, then selects the next problem.
- `p` immediately selects the previous problem.
- `q` exits.
- Unknown keys do nothing and redraw the prompt.

During a countdown, `Ctrl+C` cancels the countdown and stays on the current problem. A later `Ctrl+C` at the normal prompt exits cleanly. At the last problem, next commands keep the selection at the end and report that there is no next problem.

## Network Handling

The public Luogu lookup uses a normal HTTP session so the CDN session cookie returned during redirects is retained. It uses timeouts, bounded redirects, and a descriptive user agent. No Chromium profile or authenticated cookie is accessed.

The user search result must match the requested username case-insensitively. The practice-page parser accepts either a direct JSON response or the `lentille-context` JSON embedded in HTML, and validates that the accepted-problem collection is present.

## Verification

Focused tests cover:

- Markdown checkbox parsing and Luogu ID normalization.
- `B2002`, `P1068`, and numeric directory resolution with `main.py` priority.
- Public user-search and practice-page parsing using local fixtures, without live-network dependence.
- Accepted-problem filtering and stable progress indices.
- Five-item window behavior at the start, middle, and end.
- Wait-range validation and deterministic countdown selection through injected randomness.
- Browser URLs ending in `#submit`.
- Keyboard navigation, including immediate `n`, timed Enter, `p`, and clean cancellation.

A final smoke test runs the helper against the official Luogu basic training list with short wait parameters and a mocked browser launcher.
