import matter from 'gray-matter';
import MarkdownIt from 'markdown-it';
import fs from 'fs';
import path from 'path';

class MarkdownRenderer {
  constructor(md_path = '') {
    this.name = 'rbook';
    this.front_matter = {};
    this.md_content = '';
    this.html_content = undefined;
    this.md_path = '';

    this.md = new MarkdownIt({
      html: true,
      linkify: true,
      typographer: true
    });

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