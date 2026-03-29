// Core markdown-it
import MarkdownIt from 'markdown-it';

// Code highlighting and math rendering
import Shiki from 'markdown-it-shiki';
import Katex from 'katex';
import TexMath from 'markdown-it-texmath';

// Image and link enhancements
import implicitFigures from 'markdown-it-image-figures';
import LinkAttributes from 'markdown-it-link-attributes';

// Utility plugins
import highlight from './lib/highlight.js';
import twemoji from 'twemoji';
import mdItContainer from 'markdown-it-container';
import uslug from 'uslug';
import admonition from './lib/markdown-it-admonition.js';
import includeCode from './lib/include-code.js';
import mdLink2Url from './lib/md-link2url.js';

// Content extensions
import lineNumber from './lib/lineNumber.js';
import emoji from 'markdown-it-emoji';
import taskCheckbox from 'markdown-it-task-checkbox';
import defaultContainer from './lib/container/default.js';
import foldContainer from './lib/container/fold.js';
import classContainer from './lib/container/class.js';
import blackboardContainer from './lib/container/blackboard.js';
import iframe from 'markdown-it-iframe';
import vizGallery from './lib/viz-gallery.js';
// ![test](test.jpg =100x) 设置宽度,高度自动适应
// ![test](test.jpg =100x200) 设置宽度和高度
import imsize from 'markdown-it-imsize';
import insDel from 'markdown-it-ins-del';
import inlineComments from 'markdown-it-inline-comments';
import sup from 'markdown-it-sup';
import sub from 'markdown-it-sub';
import mark from 'markdown-it-mark';
import abbr from 'markdown-it-abbr';
import anchor from 'markdown-it-anchor';
import tocDoneRight from 'markdown-it-toc-done-right';
import tocAnchorExtent from './lib/tocAnchorExtent.js';
import codetabs from 'markdown-it-codetabs';

import problemLinkPlugin from './lib/problemLink.js';

import MDItPseudo from './lib/markdown-it-pseudocodejs/index.js';

// .excalidraw.svg
import imageExtensionPlugin from './lib/markdown-it-excalidraw-svg/index.js';

// Node.js modules
import { fileURLToPath } from 'url';
import path, { dirname, resolve } from 'path';

// Path configuration
const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
const project_root = resolve(__dirname, '../../../');
const project_book_root = resolve(__dirname, '../../../book');

// Initialize markdown-it
const md = MarkdownIt({
    html: true,
    linkify: true,
    typographer: true,
});

// Plugin configuration

// Include code plugin
md.use(includeCode, { baseDir: project_root });

// Admonition types configuration
const math_admonition = [
    "definition", "theorem", "corollary", "lemma", 
    "proof", "exercise", "problem"
];

const default_admonition = [
    "note", "abstract", "info", "tip", "success", "question", 
    "warning", "failure", "danger", "bug", "example", "quote"
];

md.use(admonition, {
    types: [...default_admonition, ...math_admonition]
});

// Link processing plugin
md.use(mdLink2Url, {
    baseDir: project_book_root,
    baseUrl: '/'
});

// Math rendering plugin
md.use(TexMath, {
    engine: Katex,
    delimiters: ['dollars', 'beg_end', 'julia'],
    katexOptions: {
        macros: { '\\R': '\\mathbb{R}' },
        strict: function (errorCode, errMsg, token) {
            console.error('--->', errorCode, errMsg);
            console.log(token);
            return errMsg;
        }
    }
});

// Additional plugins
// Note: LinkAttributes plugin is disabled for now
// md.use(LinkAttributes, {
//     matcher: (link) => /^https?:\/\//.test(link),
//     attrs: {
//         target: '_blank',
//         rel: 'noopener',
//     },
// });

// Apply plugins individually

// Line numbers for code blocks
md.use(lineNumber);

// Emoji support with twemoji rendering
md.use(emoji);

// Multi-markdown table support (disabled)
// md.use(require('markdown-it-multimd-table'), {
//     multiline: true,
//     rowspan: false,
//     headerless: true,
// });

// Keyboard key bindings (disabled)
// md.use(require('markdown-it-kbd'));

// Task checkbox support
md.use(taskCheckbox);

// Default container types
md.use(mdItContainer, ...defaultContainer);

// Foldable/collapsible containers
md.use(mdItContainer, ...foldContainer);

// Custom class containers
md.use(mdItContainer, ...classContainer);

// Blackboard style containers
md.use(mdItContainer, ...blackboardContainer);

// iframe embedding support
md.use(iframe);

// Visualization gallery
md.use(vizGallery);

// Bilibili video embedding (disabled)
// md.use(require('./lib/bilibili_frame.js'));

// Custom heading enhancements (disabled)
// md.use(require('./lib/heading.js'));

// Image size specification
md.use(imsize);

// Insert and delete text styling
md.use(insDel);

// Inline comments support
md.use(inlineComments);

// Superscript text
md.use(sup);

// Subscript text
md.use(sub);

// Marked/highlighted text
md.use(mark);

// Problem link support [[problem: ojname,id]]
md.use(problemLinkPlugin);

// Abbreviation support
md.use(abbr);

// Anchor links for headings
md.use(anchor, { 
    level: [2, 3], 
    permalink: false, 
    permalinkBefore: true, 
    permalinkSymbol: '§' 
});

// Table of contents generation
md.use(tocDoneRight, { level: 2 });

// Automatic figure wrapping for images
md.use(implicitFigures, { figcaption: true });

// Extended TOC anchor functionality
md.use(tocAnchorExtent);

// Code tabs support
md.use(codetabs);

// Custom emoji renderer
md.renderer.rules.emoji = function(token, idx) {
    return twemoji.parse(token[idx].content);
};


// .excalidraw.svg
md.use(imageExtensionPlugin, { 
  excalidraw_server_addrs: "https://excalidraw.roj.ac.cn/",
  blog_url : "https://rbook2.roj.ac.cn/" ,
  base_path:  project_book_root
});

// Pseudocode support
md.use(MDItPseudo,{lineNumber:true});

/**
 * Render markdown content
 * @param {string} md_raw - Raw markdown content
 * @param {Object} config - Configuration options
 * @param {Object} config.mdit - markdown-it environment options
 * @param {string} config.filePath - File path for relative link resolution
 * @returns {string} Rendered HTML
 */
function render(md_raw, config = {}) {
    const env = config.mdit || {};
    
    if (config.filePath) {
        env.filePath = config.filePath;
    }
    
    return md.render(md_raw, env);
}

// Exports
export {
    render,   // Render function
    md        // markdown-it instance
};

export default md;