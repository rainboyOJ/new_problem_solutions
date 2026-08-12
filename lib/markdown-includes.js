import fs from 'fs';
import path from 'path';

const INCLUDE_DIRECTIVE_REGEX = /^(?:@include_md\("([^"]+)"\)|@include-code\(([^,)]+)(?:,[ \t]*([^)]+))?[ \t]*\))[ \t]*\r?$/gm;

function resolveIncludePath(currentFilePath, includePath) {
  return path.isAbsolute(includePath)
    ? includePath
    : path.resolve(path.dirname(currentFilePath), includePath);
}

function getCodeFence(source) {
  let longestRun = 0;

  for (const match of source.matchAll(/`+/g)) {
    longestRun = Math.max(longestRun, match[0].length);
  }

  return '`'.repeat(Math.max(3, longestRun + 1));
}

function renderCodeFence(source, language) {
  const fence = getCodeFence(source);
  const boundaryNewline = source.length > 0 && !source.endsWith('\n') ? '\n' : '';
  return `${fence}${language}\n${source}${boundaryNewline}${fence}`;
}

export function expandMarkdownIncludes(content, currentFilePath) {
  return content.replace(
    INCLUDE_DIRECTIVE_REGEX,
    (directive, markdownIncludePath, rawCodePath, explicitLanguage) => {
      if (markdownIncludePath !== undefined) {
        const fullPath = resolveIncludePath(currentFilePath, markdownIncludePath);

        try {
          if (!fs.existsSync(fullPath)) {
            console.warn(`Warning: Included file not found: ${fullPath}`);
            return `<!-- Warning: File not found: ${markdownIncludePath} -->`;
          }

          const includedContent = fs.readFileSync(fullPath, 'utf8');
          return expandMarkdownIncludes(includedContent, fullPath);
        } catch (error) {
          console.error(`Error including file ${markdownIncludePath}:`, error.message);
          return `<!-- Error including file: ${markdownIncludePath} -->`;
        }
      }

      const codePath = rawCodePath.trim();
      const language = (explicitLanguage || path.extname(codePath).slice(1)).trim();
      const fullPath = resolveIncludePath(currentFilePath, codePath);

      try {
        const source = fs.readFileSync(fullPath, 'utf8');
        return renderCodeFence(source, language);
      } catch {
        return directive;
      }
    },
  );
}

export function readMarkdownWithIncludes(markdownPath) {
  const content = fs.readFileSync(markdownPath, 'utf8');
  return expandMarkdownIncludes(content, markdownPath);
}
