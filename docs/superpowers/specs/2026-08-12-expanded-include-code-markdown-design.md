# Expanded Include-Code Markdown Design

## Goal

Make problem API `md_content` self-contained by replacing every successfully
resolved `@include-code(...)` directive with the referenced source code in a
standard Markdown fenced code block. The `Md Raw` modal will therefore display
and copy the complete article without making extra requests.

The source `index.md` and included code files remain unchanged on disk.

## Architecture

`MarkdownRenderer` will expand include directives while loading Markdown,
before either `md_content` or `html_content` is exposed. Both API fields will
therefore derive from the same expanded Markdown string:

```text
index.md
  -> expand @include_md recursively
  -> expand @include-code relative to its containing Markdown file
  -> md_content
  -> Markdown-It rendering
  -> html_content
```

The include-code expansion logic will be a focused, testable helper. The
existing Markdown-It include-code plugin remains responsible for unresolved
directives so HTML keeps its current warning behavior.

## Expansion Rules

An include directive has the existing syntax:

```text
@include-code(path, optional-language)
```

- Resolve relative paths against the directory containing the directive.
- Prefer an explicit language argument.
- Otherwise infer the language from the referenced file extension.
- Replace a successful include with a Markdown fenced code block containing the
  source file's exact text.
- Ensure the opening and closing fence are longer than every run of backticks in
  the source, so embedded Markdown fences cannot terminate the generated block.
- Add only the boundary newlines required to form valid Markdown. Do not rewrite
  or trim source content.
- Process `@include-code` directives inside recursively included
  `@include_md(...)` files relative to each included Markdown file.

For missing or unreadable files, preserve the original `@include-code(...)`
line in `md_content`. When that Markdown is rendered, the existing plugin will
continue to emit its escaped warning block in `html_content`.

Malformed lines that do not match the existing directive grammar remain
ordinary Markdown.

## API Behavior

No API route or response schema changes are required. Both production and
single-problem preview APIs continue returning `md_content` and `html_content`.

After this change:

- `md_content` contains expanded fenced source for all successful includes.
- `html_content` renders that same expanded source with escaped HTML and stable
  `language-*` classes.
- `html_content` still contains no server-side Prism `token` spans.
- Failed includes remain visible as directives in `md_content` and warnings in
  `html_content`.

The `Md Raw` controller remains unchanged because it already displays and
copies the API string verbatim.

## Testing

Focused renderer tests will cover:

- explicit language arguments;
- extension-based language inference;
- paths relative to the containing Markdown file;
- includes nested through `@include_md`;
- source containing backtick runs;
- empty files and files with or without terminal newlines;
- missing or unreadable files preserving the original directive;
- expanded `md_content` and client-highlightable `html_content` remaining
  consistent.

Production and preview API tests will assert that `md_content` contains actual
`main.py` or `main.cpp` source and no successful include directive. They will
also retain the existing escaped-source, language-class, and no-server-token
assertions for `html_content`.

Browser acceptance will confirm that `Md Raw` shows expanded code, Prism
highlights its Markdown, and `复制全部` still copies exactly the API
`md_content` value.

## Non-Goals

- Modifying `index.md` or included source files.
- Adding new API fields or client-side file fetching.
- Changing `@include_md` syntax.
- Changing the rendered code-block UI, clipboard feedback, or Prism loading.
