# Shumeng OJ Single-Problem Fetcher Design

## Goal

Add single-problem fetching support for Shumeng OJ to the existing
`scripts/problem-analysis-tools/fetch_problem.py` provider architecture.

The fetcher must support both forms:

```bash
fetch_problem shumeng CSP201312A
fetch_problem https://oj.shumeng.tech/p/CSP201312A
```

It creates or completes the standard problem directory at
`problems/shumeng/<problem_id>/`, while preserving the existing non-overwrite
rules for handwritten files and previously fetched artifacts.

Batch fetching from problem-list pages is explicitly outside this change.

## Source Format

Shumeng OJ is powered by Hydro. A public problem page embeds a JSON string in
the JavaScript assignment `window.UiContextNew`. The decoded object contains a
`pdoc` object with the fields needed by this fetcher:

- `pid`: display problem ID, such as `CSP201312A`.
- `title`: problem title.
- `content`: a JSON-encoded language-to-Markdown mapping.

The fetcher will parse this structured data instead of converting the rendered
HTML. This preserves the original Markdown, TeX expressions, fenced blocks,
and section structure.

## Architecture

Add `scripts/problem-analysis-tools/fetchers/shumeng.py` with a
`ShumengFetcher` subclass of `BaseFetcher`.

Register one `ShumengFetcher` instance in
`scripts/problem-analysis-tools/fetchers/__init__.py`, and export the class in
`__all__`. No changes to the generic write path or scaffold implementation are
required.

The provider will use:

- `name = "shumeng"`.
- `site_prefixes` limited to `https://oj.shumeng.tech`.
- Original problem ID casing for both `problem_id` and `problem_dir_id`.
- Canonical source URL `https://oj.shumeng.tech/p/<problem_id>` when invoked by
  OJ name and ID.

## Data Flow

1. Accept `shumeng <problem_id>` or a recognized single-problem URL.
2. Normalize and validate the problem ID.
3. Fetch `https://oj.shumeng.tech/p/<problem_id>` through `BaseFetcher.http_get`.
4. Extract and decode the JSON string assigned to `window.UiContextNew`.
5. Read `pdoc.pid`, `pdoc.title`, and `pdoc.content`.
6. Decode `pdoc.content` and select the Markdown body.
7. Parse paired fenced sample blocks named `inputN` and `outputN`.
8. Return `ProblemData` with title, source, original Markdown, and samples.
9. Let the existing `fetch_problem.py` workflow create the scaffold and write
   `problem.md`, `inN`, `outN`, and `in`.

## Markdown And Samples

The full selected Markdown body becomes `statement_md` without rebuilding its
sections. This retains Shumeng OJ's time limit, memory limit, statement,
constraints, formulas, and embedded sample blocks.

Sample extraction recognizes fenced blocks whose info strings are exactly
`inputN` or `outputN`, where `N` is a positive integer. Input and output blocks
are paired by the same numeric suffix and returned in ascending numeric order.

The contents of sample files preserve internal whitespace and line breaks. The
generic writer continues to normalize repository line endings to LF.

If only one side of a numbered sample exists, it is not emitted as a `Sample`.
The fetch result includes a warning naming the incomplete sample number.

## Language Selection

`pdoc.content` is expected to decode to an object mapping language codes to
Markdown strings. The fetcher selects content in this order:

1. Non-empty `zh` content.
2. The first non-empty string value in the mapping.

If the decoded value is already a non-empty string, it may be accepted as the
Markdown body for compatibility. Missing or empty content is a fetch failure.

## URL And ID Handling

Recognized URLs have the shape:

```text
https://oj.shumeng.tech/p/<problem_id>
```

Query strings and fragments are ignored while parsing the ID. Problem-list,
submission, and other non-problem URLs are rejected. Percent-encoded IDs are
decoded before validation.

The fetcher validates that the final ID is a single safe path component. The
existing scaffold validation remains the final protection before filesystem
writes.

## Error Handling

The provider raises `FetchError` when:

- the network request fails;
- the URL does not identify a single problem;
- `window.UiContextNew` is missing or malformed;
- `pdoc` is missing or not an object;
- the page's problem ID conflicts with the requested ID;
- `pdoc.content` cannot be decoded or contains no usable Markdown.

For a recognizable OJ name and ID or single-problem URL, the existing
`fetch_problem.py` behavior catches `FetchError`, creates only the skeleton,
and reports a warning. This design does not add retries, login state, cookies,
or browser automation.

## Tests

Add a minimal offline fixture at
`scripts/problem-analysis-tools/tests/fixtures/shumeng_csp201312a.html`. It will
contain only the embedded data needed to exercise the parser, including TeX,
two complete sample pairs, and one incomplete pair for warning behavior.

Extend `fetch_problem.py --self-test` to verify:

- OJ name, problem ID, directory ID, title, and canonical source URL;
- preservation of Markdown and TeX text;
- numeric ordering and exact content of complete samples;
- omission and warning for an incomplete sample;
- registration through the shared `FETCHERS` list.

After offline tests pass, manually verify the live page using a temporary
problem root or `--dry-run` so no real problem directory is committed.

## Documentation

Update `docs/tools/fetch_problem.md` to list Shumeng OJ as a fully supported
single-problem source and add both invocation examples. Document that problem
list pages and batch import are not supported by this provider.

## Non-Goals

- Fetching all 130 CSP problems from the category list.
- Downloading hidden judge test data.
- Importing Shumeng tags, difficulty, statistics, or submission records.
- Authenticating a user or submitting solutions.
- Introducing third-party parsing or browser dependencies.
