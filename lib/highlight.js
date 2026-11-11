import { createHighlighterCoreSync } from 'shiki/core';
import { createJavaScriptRegexEngine } from 'shiki/engine/javascript';
import LruCache from './lru-cache.js';

// 双主题输出：浅色写进 style 的 color，深色写进 --shiki-dark 变量，
// 由 CSS 在 [data-bs-theme="dark"] 下切换。服务端不需要知道访客当前主题。
export const SHIKI_THEMES = { light: 'github-light', dark: 'github-dark' };

// 站点内容里实际出现的语言（problems/ 与 problem-sets/ 的 fence 标签统计）。
// 只装这些语法，避免把 Shiki 的全量语言包拖进构建产物。
export const SUPPORTED_LANGUAGES = [
  'bash',
  'c',
  'cpp',
  'csharp',
  'css',
  'go',
  'haskell',
  'html',
  'java',
  'javascript',
  'json',
  'julia',
  'kotlin',
  'lua',
  'markdown',
  'ocaml',
  'pascal',
  'perl',
  'php',
  'python',
  'ruby',
  'rust',
  'scala',
  'typescript',
  'yaml',
];

// fence 标签里的同义写法。Shiki 自己认 js/py/c++ 等别名，这里只补
// Shiki 不认识的写法，以及「只是数据、不该上色」的标签。
const LANGUAGE_ALIASES = {
  'c++': 'cpp',
  cs: 'csharp',
  hs: 'haskell',
  md: 'markdown',
  markup: 'html',
  none: null,
  plain: null,
  plaintext: null,
  sh: 'bash',
  text: null,
};

// input / output / input1 / output2 这类标签只描述数据，统一按纯文本处理。
const DATA_ONLY_LANGUAGE = /^(?:input|output)\d*$/;

export function normalizeLanguage(rawLanguage) {
  const language = String(rawLanguage ?? '').trim().toLowerCase().split(/\s+/, 1)[0];
  if (!language) return null;
  if (DATA_ONLY_LANGUAGE.test(language)) return null;
  if (Object.hasOwn(LANGUAGE_ALIASES, language)) return LANGUAGE_ALIASES[language];
  return language;
}

export function escapeHtml(text) {
  return String(text)
    .replaceAll('&', '&amp;')
    .replaceAll('<', '&lt;')
    .replaceAll('>', '&gt;')
    .replaceAll('"', '&quot;')
    .replaceAll("'", '&#39;');
}

// 语法包在模块加载阶段一次性读完（25 个语言 + 2 个主题，约 0.3s），
// 之后所有渲染路径都是同步的：MarkdownRenderer.toHTML() 不需要变成 async。
let highlighter = null;
try {
  const [themes, langs] = await Promise.all([
    Promise.all([
      import('@shikijs/themes/github-light'),
      import('@shikijs/themes/github-dark'),
    ]),
    Promise.all(SUPPORTED_LANGUAGES.map((name) => import(`@shikijs/langs/${name}`))),
  ]);

  highlighter = createHighlighterCoreSync({
    themes: themes.map((module) => module.default),
    langs: langs.map((module) => module.default),
    // 纯 JS 正则引擎：同步可用，输出与 oniguruma wasm 逐字节一致，
    // 部署时不需要额外搬运 onig.wasm。
    engine: createJavaScriptRegexEngine({ forgiving: true }),
  });
} catch (error) {
  // 语法包加载失败不能让整站起不来：退化成不高亮的纯文本代码块。
  console.warn(`[highlight] Shiki 初始化失败，代码块将不高亮: ${error.message}`);
}

export function isHighlightReady() {
  return highlighter !== null;
}

// 同一份代码会被反复渲染（页面、API、preview、热刷新），缓存到 HTML 这一层。
const htmlCache = new LruCache(4000);

function styleAttribute(style) {
  return Object.entries(style)
    .map(([property, value]) => `${property}:${value}`)
    .join(';');
}

function renderLinesHtml(lines) {
  // 行之间用真实换行，外层 `white-space: pre` 才能让代码与行号列逐行对齐。
  return lines
    .map((line) => line
      .map((token) => (token.htmlStyle
        ? `<span class="shiki-token" style="${token.htmlStyle}">${escapeHtml(token.text)}</span>`
        : escapeHtml(token.text)))
      .join(''))
    .join('\n');
}

/**
 * 把代码高亮成 `<code>` 内部的 HTML。
 * 返回 null 表示这门语言不该上色（纯文本标签、未知语言、语法包缺失），
 * 调用方应回退到转义后的纯文本。
 */
export function renderCodeHtml(code, rawLanguage) {
  if (!highlighter) return null;

  const language = normalizeLanguage(rawLanguage);
  if (!language) return null;
  if (!highlighter.getLoadedLanguages().includes(language)) return null;

  const normalizedCode = String(code ?? '').replace(/\n$/, '');
  const cacheKey = `${language}\u0000${normalizedCode}`;
  const cached = htmlCache.get(cacheKey);
  if (cached !== undefined) return cached;

  let result;
  try {
    result = highlighter.codeToTokens(normalizedCode, { lang: language, themes: SHIKI_THEMES });
  } catch {
    // 语法或输入把 Shiki 弄崩时按纯文本渲染，不要拖垮整篇 Markdown。
    return null;
  }

  const html = renderLinesHtml(result.tokens.map((line) => line.map((token) => ({
    htmlStyle: token.htmlStyle ? styleAttribute(token.htmlStyle) : '',
    text: token.content,
  }))));

  htmlCache.set(cacheKey, html);
  return html;
}
