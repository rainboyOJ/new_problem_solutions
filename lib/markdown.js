import matter from 'gray-matter';
import MarkdownIt from 'markdown-it';
import Katex from 'katex';
import TexMath from 'markdown-it-texmath';
import anchor from 'markdown-it-anchor';
import tocDoneRight from 'markdown-it-toc-done-right';
import fs from 'fs';
import path from 'path';
import createProblemLinkPlugin from './markdown-plugins/problemLink.js';

function tocWrapperPlugin(md) {
  const title = `<div class="toc-title">
        <h3>目录</h3>
</div>
<div class="toc-content">`;

  md.renderer.rules.toc_open = () => `<div class="toc-body">${title}`;
  md.renderer.rules.toc_close = () => '</div></div>';
}

class MarkdownRenderer {
  constructor(md_path = '', problemManager = null) {
    this.name = 'rbook';
    this.front_matter = {};
    this.md_content = '';
    this.html_content = undefined;
    this.md_path = '';
    this.problemManager = problemManager;

    this.md = new MarkdownIt({
      html: true,
      linkify: true,
      typographer: true
    });

    this.md.use(TexMath, {
      engine: Katex,
      delimiters: ['dollars', 'beg_end', 'julia'],
      katexOptions: {
        macros: { '\\R': '\\mathbb{R}' },
        strict: false,
        throwOnError: false
      }
    });

    this.md.use(createProblemLinkPlugin(this.problemManager));
    this.md.use(anchor, {
      level: [2, 3],
      permalink: false,
      permalinkBefore: true,
      permalinkSymbol: '§'
    });
    this.md.use(tocDoneRight, { level: 2 });
    this.md.use(tocWrapperPlugin);

    if (md_path && md_path.length > 0) {
      this.load(md_path);
    }
  }

  load(md_path) {
    this.md_path = md_path;
    const raw_md = this.readfile(md_path);
    const result = matter(raw_md);
    this.front_matter = result.data;
    this.md_content = result.content;
  }

  readfile(md_path) {
    let raw_md = fs.readFileSync(md_path, 'utf8');
    raw_md = this.processIncludeMd(raw_md, md_path);
    return raw_md;
  }

  processIncludeMd(content, currentFilePath) {
    const includeRegex = /^@include_md\("([^"]+)"\)\s*$/gm;
    const currentDir = path.dirname(currentFilePath);

    return content.replace(includeRegex, (match, includePath) => {
      const fullPath = path.resolve(currentDir, includePath);

      try {
        if (!fs.existsSync(fullPath)) {
          console.warn(`Warning: Included file not found: ${fullPath}`);
          return `<!-- Warning: File not found: ${includePath} -->`;
        }

        const includedContent = fs.readFileSync(fullPath, 'utf8');
        return this.processIncludeMd(includedContent, fullPath);
      } catch (error) {
        console.error(`Error including file ${includePath}:`, error.message);
        return `<!-- Error including file: ${includePath} -->`;
      }
    });
  }

  toHTML() {
    if (this.html_content === undefined) {
      this.html_content = this.md.render(this.md_content);
    }
    return this.html_content;
  }

  toJSON() {
    if (this.html_content === undefined) {
      this.html_content = this.toHTML();
    }
    return {
      front_matter: this.front_matter,
      md_content: this.md_content,
      html_content: this.html_content
    };
  }
}

export default MarkdownRenderer;
