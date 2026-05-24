import fs from 'fs';
import path from 'path';

export default function includeCodePlugin(md) {
  function includeCodeRule(state, startLine, endLine, silent) {
    const pos = state.bMarks[startLine] + state.tShift[startLine];
    const max = state.eMarks[startLine];
    const line = state.src.slice(pos, max);
    const match = line.match(/^@include-code\(([^,)]+)(?:,\s*([^)]+))?\s*\)$/);

    if (!match) {
      return false;
    }

    if (silent) {
      return true;
    }

    const rawFilePath = match[1].trim();
    const language = (match[2] || path.extname(rawFilePath).slice(1)).trim();
    const currentDir = path.dirname(state.env.filePath || '.');
    const fullPath = path.isAbsolute(rawFilePath)
      ? rawFilePath
      : path.resolve(currentDir, rawFilePath);

    try {
      const token = new state.Token('fence', 'code', 0);
      token.info = language;
      token.content = fs.readFileSync(fullPath, 'utf8').replace(/\n?$/, '\n');
      token.markup = '```';
      token.map = [startLine, startLine + 1];
      state.tokens.push(token);
    } catch (error) {
      const token = new state.Token('html_block', '', 0);
      token.content = `<div class="alert alert-warning">include-code failed: ${md.utils.escapeHtml(rawFilePath)}</div>\n`;
      state.tokens.push(token);
    }

    state.line = startLine + 1;
    return true;
  }

  md.block.ruler.before('fence', 'include_code', includeCodeRule);
}
