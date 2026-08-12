import matter from 'gray-matter';
import MarkdownIt from 'markdown-it';
import Katex from 'katex';
import TexMath from 'markdown-it-texmath';
import anchor from 'markdown-it-anchor';
import tocDoneRight from 'markdown-it-toc-done-right';
import mdItContainer from 'markdown-it-container';
import implicitFigures from 'markdown-it-image-figures';
import imsize from 'markdown-it-imsize';
import insDel from 'markdown-it-ins-del';
import inlineComments from 'markdown-it-inline-comments';
import sup from 'markdown-it-sup';
import sub from 'markdown-it-sub';
import mark from 'markdown-it-mark';
import abbr from 'markdown-it-abbr';
import taskCheckbox from 'markdown-it-task-checkbox';
import iframe from 'markdown-it-iframe';
import codetabs from 'markdown-it-codetabs';
import { full as emoji } from 'markdown-it-emoji';
import twemoji from 'twemoji';
import uslug from 'uslug';
import fs from 'fs';
import path from 'path';
import createProblemLinkPlugin from './markdown-plugins/problemLink.js';
import includeCodePlugin from './markdown-plugins/includeCode.js';
import admonition from './markdown-plugins/rbook/admonition.js';
import mdLink2Url from './markdown-plugins/rbook/mdLink2Url.js';
import tocAnchorExtent from './markdown-plugins/rbook/tocAnchorExtent.js';
import vizGallery from './markdown-plugins/rbook/vizGallery.js';
import defaultContainer from './markdown-plugins/rbook/container/default.js';
import foldContainer from './markdown-plugins/rbook/container/fold.js';
import classContainer from './markdown-plugins/rbook/container/class.js';
import blackboardContainer from './markdown-plugins/rbook/container/blackboard.js';
import styleContainer from './markdown-plugins/rbook/container/style.js';
import imageExtensionPlugin from './markdown-plugins/rbook/markdown-it-excalidraw-svg/index.js';
import pseudocodePlugin from './markdown-plugins/rbook/markdown-it-pseudocodejs/index.js';

const DEFAULT_ADMONITIONS = [
  'note', 'abstract', 'info', 'tip', 'success', 'question',
  'warning', 'failure', 'danger', 'bug', 'example', 'quote'
];

const MATH_ADMONITIONS = [
  'definition', 'theorem', 'corollary', 'lemma',
  'proof', 'exercise', 'problem'
];

function slugifyHeading(title) {
  return uslug(title) || 'section';
}

function mapFenceLanguage(info) {
  const lang = info.trim().toLowerCase();
  if (['text', 'plain', 'none'].includes(lang)) return 'none';
  if (/^(?:input|output)\d*$/.test(lang)) return 'none';
  if (lang === 'js') return 'javascript';
  if (lang === 'vue' || lang === 'html') return 'markup';
  if (lang === 'md') return 'markdown';
  if (lang === 'ts') return 'typescript';
  if (lang === 'py') return 'python';
  if (lang === 'hs') return 'haskell';
  if (lang === 'cs') return 'csharp';
  if (lang === 'c++' || lang === 'cpp') return 'cpp';
  if (lang === 'c') return 'c';
  return lang;
}

function getFenceInfo(rawInfo) {
  const normalized = rawInfo.trim();
  const language = normalized.split(/\s+/, 1)[0] || 'text';

  return {
    rawInfo: normalized,
    label: normalized || 'text',
    language,
    mappedLanguage: mapFenceLanguage(language)
  };
}

function renderLineNumbers(content, md) {
  const lineCount = Math.max(1, content.split('\n').length);
  const lines = Array.from({ length: lineCount }, (_, index) => index + 1).join('\n');

  return `<span class="line-numbers-wrapper" aria-hidden="true">${md.utils.escapeHtml(lines)}</span>`;
}

function renderCodeBlock({ md, rawInfo, language, escapedContent, lineNumbers }) {
  const escapedLanguage = md.utils.escapeHtml(language);
  const escapedLabel = md.utils.escapeHtml(rawInfo);

  return `<div class="language-${escapedLanguage} line-numbers-mode code-block">`
    + '<div class="code-info-header">'
    + `<span class="code-info-label">${escapedLabel}</span>`
    + '<button class="code-copy-button" type="button" data-code-copy aria-label="复制代码">复制</button>'
    + '</div>'
    + '<pre>'
    + lineNumbers
    + `<code class="language-${escapedLanguage}">${escapedContent}</code>`
    + '</pre>'
    + '</div>\n';
}

function rbookFenceRendererPlugin(md) {
  md.renderer.rules.fence = (tokens, idx, options, env, self) => {
    const token = tokens[idx];
    const { rawInfo, label, language, mappedLanguage } = getFenceInfo(token.info);
    const displayContent = token.content.replace(/\n$/, '');

    if (language === 'mermaid') {
      return `<pre class="mermaid">\n${md.utils.escapeHtml(token.content)}</pre>\n`;
    }

    const vizReg = /^viz($|-\w+)/;
    if (language === 'dot' || language === 'graphviz' || vizReg.test(language)) {
      const vizEngine = vizReg.test(language) ? language.slice(4) || 'dot' : 'dot';
      return `<div class="graphviz" data-viz-engine="${md.utils.escapeHtml(vizEngine)}"><pre class="dot">\n${md.utils.escapeHtml(token.content)}</pre></div>\n`;
    }

    return renderCodeBlock({
      md,
      rawInfo: label,
      language: mappedLanguage,
      escapedContent: md.utils.escapeHtml(displayContent),
      lineNumbers: renderLineNumbers(displayContent, md)
    });
  };
}

function createMarkdownIt(problemManager, options = {}) {
  const md = new MarkdownIt({
    html: true,
    linkify: true,
    typographer: true
  });

  md.use(TexMath, {
    engine: Katex,
    delimiters: ['dollars', 'beg_end', 'julia'],
    katexOptions: {
      macros: { '\\R': '\\mathbb{R}' },
      strict: false,
      throwOnError: false
    }
  });

  md.use(createProblemLinkPlugin(problemManager));
  md.use(includeCodePlugin, { baseDir: options.projectRoot });
  md.use(admonition, {
    types: [...DEFAULT_ADMONITIONS, ...MATH_ADMONITIONS]
  });
  md.use(mdLink2Url, {
    baseDir: options.problemsRoot,
    baseUrl: '/problems'
  });

  md.use(taskCheckbox);
  md.use(mdItContainer, ...defaultContainer);
  md.use(mdItContainer, ...foldContainer);
  md.use(mdItContainer, ...classContainer);
  md.use(mdItContainer, ...blackboardContainer);
  md.use(mdItContainer, ...styleContainer);
  md.use(iframe);
  md.use(vizGallery);
  md.use(imsize);
  md.use(insDel);
  md.use(inlineComments);
  md.use(sup);
  md.use(sub);
  md.use(mark);
  md.use(abbr);
  md.use(anchor, {
    level: [2, 3],
    slugify: slugifyHeading,
    permalink: false,
    permalinkBefore: true,
    permalinkSymbol: '§'
  });
  md.use(tocDoneRight, {
    level: 2,
    slugify: slugifyHeading
  });
  md.use(tocAnchorExtent);
  md.use(implicitFigures, { figcaption: true });
  md.use(codetabs);
  md.use(emoji);
  md.use(imageExtensionPlugin, {
    excalidraw_server_addrs: 'https://excalidraw.roj.ac.cn/',
    blog_url: options.blogUrl || '',
    base_path: options.problemsRoot
  });
  md.use(pseudocodePlugin, { lineNumber: true });
  md.use(rbookFenceRendererPlugin);

  md.renderer.rules.emoji = (tokens, idx) => twemoji.parse(tokens[idx].content);

  return md;
}

class MarkdownRenderer {
  constructor(md_path = '', problemManager = null) {
    this.name = 'rbook';
    this.front_matter = {};
    this.md_content = '';
    this.html_content = undefined;
    this.md_path = '';
    this.problemManager = problemManager;
    this.projectRoot = process.cwd();
    this.problemsRoot = path.join(this.projectRoot, 'problems');
    this.md = createMarkdownIt(this.problemManager, {
      projectRoot: this.projectRoot,
      problemsRoot: this.problemsRoot,
      blogUrl: ''
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
      this.html_content = this.md.render(this.md_content, { filePath: this.md_path });
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

export { createMarkdownIt };
export default MarkdownRenderer;
