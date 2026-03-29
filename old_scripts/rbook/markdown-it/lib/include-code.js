import fs from 'fs';
import path from 'path';

/**
 * A markdown-it plugin to include code from files.
 *  options {
 *    baseDir: string, // base directory for the files to be included
 * }
 * Syntax: @include-code(path/to/file.ext, language)
 */
function includeCodePlugin(md,options = {}) {

  function includeCodeRule(state, startLine, endLine, silent) {
    const pos = state.bMarks[startLine] + state.tShift[startLine];
    const max = state.eMarks[startLine];

    // Check for the include syntax: @include-code(...)
    const match = state.src.slice(pos, max).match(/^@include-code\(([^,)]+)(?:,\s*([^)]+))?\s*\)/);

    if (!match) {
      return false;
    }

    // `silent` is true when the parser is just checking if the rule can be applied.
    // We should not perform any actions but just report success.
    if (silent) {
      return true;
    }

    const [fullMatch, rawFilePath, lang] = match;
    const filePath = rawFilePath.trim();
    let language = (lang || '').trim();
    
    // If no language is specified, use the file extension as default language
    if (!language) {
      const ext = path.extname(filePath).toLowerCase();
      language = ext.substring(1); // Remove the dot from extension
    }
    let absolutePath;
    if( filePath.startsWith('/') ) {
      absolutePath = path.join(options.baseDir, filePath);
    }
    else {
      // Resolve the absolute path of the file to be included.
      // It's relative to the markdown file being processed.
      let currentDir = path.dirname(state.env.filePath || '.');
      absolutePath = path.resolve(currentDir, filePath);
    }

    let content;
    try {
      content = fs.readFileSync(absolutePath, 'utf8');
    } catch (e) {
      // If the file is not found, render an error message in the output.
      const errorToken = new state.Token('html_block', '', 0);
      errorToken.content = `<div style="color: red; border: 1px solid red; padding: 10px;">[include-code] Error: Failed to read file <code>${filePath}</code>.<br>${e.message}</div>`;
      state.tokens.push(errorToken);
      state.line = startLine + 1;
      return true;
    }

    // Create a 'fence' token to be rendered as a code block.
    // This reuses markdown-it's existing code block rendering.
    const token = new state.Token('fence', 'code', 0);
    token.info = language; // The language for syntax highlighting
    token.content = content.endsWith('\n') ? content : content + '\n';
    token.markup = '```'; // The fence character
    token.map = [startLine, startLine + 1];

    state.tokens.push(token);

    // Advance the parser to the next line.
    state.line = startLine + 1;

    return true;
  }

  // Register the rule. It should be checked before the default 'fence' rule.
  md.block.ruler.before('fence', 'include_code', includeCodeRule);
}

// module.exports = includeCodePlugin;
export default includeCodePlugin;
