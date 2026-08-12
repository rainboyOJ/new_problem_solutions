# Md Raw Full-Height Background Design

## Goal

Ensure the `Md Raw` source viewer keeps its dark code and line-number
backgrounds from the first Markdown line through the final line. The behavior
must remain correct for both long scrollable documents and short documents on
desktop and mobile viewports.

## Root Cause

The source viewport is a horizontal flex container with `align-items: stretch`.
For long Markdown such as `luogu/P1001`, the line-number and code elements are
stretched to the visible viewport height while their `white-space: pre` text
overflows far below those boxes. The text remains scrollable, but the child
background boxes end near line 31 instead of extending through all 72 expanded
lines.

The Markdown response, generated line numbers, and Prism token markup are
complete. This is a layout issue only.

## Design

Change the `Md Raw` viewport's cross-axis alignment so the line-number and code
columns use their natural content height rather than being constrained to the
visible flex height. Give both columns a shared minimum height that fills the
viewer when the Markdown is shorter than the viewport.

The result has two required states:

- Long Markdown: each column grows with all source lines, and its background
  continues through the last scrollable line.
- Short Markdown: each column still fills the visible source area instead of
  leaving an unstyled strip below its content.

No DOM structure, API data, Prism orchestration, line-number generation, theme
palette, or modal controls will change.

## Responsive Behavior

The same layout rule applies at desktop and mobile widths. Existing mobile
font size, padding, horizontal scrolling, sticky line-number gutter, and
44-pixel header controls remain unchanged.

The code column may continue to be wider than the viewport for long source
lines. Horizontal and vertical scrolling remain owned by the existing
`.md-raw-code-viewport` element.

## Testing

Add a focused CSS contract assertion for the corrected alignment and shared
minimum-height behavior.

Browser acceptance will load the real `luogu/P1001` Markdown, open `Md Raw`,
and verify at desktop and mobile viewport widths that:

- all expanded Markdown lines and line numbers remain present;
- the line-number and code boxes extend to the bottom of their scrollable
  content;
- their backgrounds remain active after scrolling beyond line 31;
- short Markdown still fills the visible viewer height;
- Prism highlighting and horizontal/vertical scrolling still work.

## Non-Goals

- Changing Markdown content or include expansion.
- Changing `Md Raw` colors or visual hierarchy.
- Changing the modal size, controls, clipboard behavior, or API contract.
- Fixing unrelated preview-only GitHub button behavior.
