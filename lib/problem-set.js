import fs from 'fs';
import path from 'path';
import matter from 'gray-matter';
import cheerio from 'cheerio';
import MarkdownRenderer from './markdown.js';

const __workdir = path.resolve();
const __problemSetDir = path.join(__workdir, 'problem-sets');

function slugFromFilename(filename) {
  return filename.replace(/\.md$/i, '');
}

function titleFromSlug(slug) {
  return slug
    .split(/[-_]+/)
    .filter(Boolean)
    .map((part) => part.charAt(0).toUpperCase() + part.slice(1))
    .join(' ');
}

export function compareProblemSets(left, right) {
  const leftHasOrder = Number.isFinite(left.order);
  const rightHasOrder = Number.isFinite(right.order);

  if (leftHasOrder && rightHasOrder && left.order !== right.order) {
    return left.order - right.order;
  }
  if (leftHasOrder !== rightHasOrder) {
    return leftHasOrder ? -1 : 1;
  }
  return left.slug.localeCompare(right.slug);
}

export function parseProblemReference(raw) {
  if (!raw) return null;

  const text = String(raw).trim();
  let match = text.match(/^\[\[\s*problem\s*:\s*([A-Za-z0-9_]+)\s*,\s*([A-Za-z0-9_-]+)\s*\]\]$/i);
  if (match) {
    return { oj: match[1], problem_id: match[2] };
  }

  match = text.match(/^\[\[\s*([A-Za-z0-9_]+)\s*\/\s*([A-Za-z0-9_-]+)\s*\]\]$/);
  if (match) {
    return { oj: match[1], problem_id: match[2] };
  }

  return null;
}

function normalizeTaskNoteHtml(html) {
  let result = String(html || '').trim();
  let previous = '';
  while (result && result !== previous) {
    previous = result;
    result = result.replace(/^<br\s*\/?>/i, '').trim();
  }
  return result;
}

function trailingLabelNoteHtml($, $label) {
  if (!$label.length) return '';

  const $link = $label.find('a.problem-link').first();
  if (!$link.length) return '';

  const labelHtml = $label.html() || '';
  const linkHtml = $.html($link);
  const linkIndex = labelHtml.indexOf(linkHtml);
  if (linkIndex === -1) return '';

  return normalizeTaskNoteHtml(labelHtml.slice(linkIndex + linkHtml.length));
}

function transformProblemTasks(html, problemManager) {
  const $ = cheerio.load(html);

  $('li.task-list-item').each((_, element) => {
    const $li = $(element);
    const href = $li.find('a.problem-link').attr('href') || '';
    const hrefMatch = href.match(/^\/problems\/([^/]+)\/([^/]+)$/);
    if (!hrefMatch) return;

    const ref = { oj: decodeURIComponent(hrefMatch[1]), problem_id: decodeURIComponent(hrefMatch[2]) };
    const key = `${ref.oj}/${ref.problem_id}`;
    const checked = $li.find('input[type="checkbox"]').is(':checked');
    const problem = problemManager.find(ref.oj, ref.problem_id);
    const title = problem?.title || '';
    const exists = Boolean(problem);
    const fallbackUrl = !exists && ref.oj.toLowerCase() === 'luogu'
      ? `https://www.luogu.com.cn/problem/${encodeURIComponent(ref.problem_id)}`
      : '';
    const noteHtml = [
      trailingLabelNoteHtml($, $li.find('label').first()),
      $li.children('ul, ol').toArray().map((node) => $.html(node)).join(''),
    ].filter(Boolean).join('\n');

    const linkHtml = exists
      ? `<a class="problem-set-task-link" href="${problem.url}">${ref.oj} ${ref.problem_id}${title ? ` ${title}` : ''}</a>`
      : fallbackUrl
        ? `<a class="problem-set-task-link" href="${fallbackUrl}">${ref.oj} ${ref.problem_id}</a>`
      : `<span class="problem-set-task-link is-disabled">${ref.oj} ${ref.problem_id}</span>`;
    const badgeHtml = exists
      ? '<span class="problem-set-task-badge is-available">题解</span>'
      : fallbackUrl
        ? '<span class="problem-set-task-badge is-external">洛谷原题</span>'
      : '<span class="problem-set-task-badge is-missing">未收录</span>';

    $li
      .attr('class', `problem-set-task ${exists ? 'is-available' : 'is-missing'}${checked ? ' is-completed' : ''}`)
      .attr('data-problem-task', '')
      .attr('data-problem-key', key)
      .attr('data-problem-exists', exists ? '1' : '0')
      .html([
        '<div class="problem-set-task-row">',
        '<label class="problem-set-task-check">',
        `<input type="checkbox" data-problem-toggle ${checked ? 'checked' : ''}>`,
        '<span aria-hidden="true"></span>',
        '</label>',
        '<div class="problem-set-task-main">',
        linkHtml,
        badgeHtml,
        '</div>',
        '</div>',
        noteHtml.trim() ? `<div class="problem-set-task-notes">${noteHtml}</div>` : '',
      ].join(''));
    $li.parent('ul').addClass('problem-set-task-list').removeClass('task-list');
  });

  $('input[type="checkbox"][disabled]').removeAttr('disabled');

  return $('body').html() || $.root().html() || html;
}

export class ProblemSetManager {
  constructor(problemManager) {
    this.problemManager = problemManager;
    this.baseDir = __problemSetDir;
  }

  list() {
    if (!fs.existsSync(this.baseDir)) {
      return [];
    }

    return fs.readdirSync(this.baseDir, { withFileTypes: true })
      .filter((entry) => entry.isFile() && entry.name.endsWith('.md'))
      .map((entry) => {
        const slug = slugFromFilename(entry.name);
        const fullPath = path.join(this.baseDir, entry.name);
        const raw = fs.readFileSync(fullPath, 'utf8');
        const parsed = matter(raw);
        const firstHeading = parsed.content.match(/^#\s+(.+)$/m);

        return {
          slug,
          title: parsed.data.title || (firstHeading ? firstHeading[1].trim() : titleFromSlug(slug)),
          description: parsed.data.description || '',
          order: Number.isFinite(parsed.data.order) ? parsed.data.order : null,
          path: fullPath,
          updatedAt: fs.statSync(fullPath).mtimeMs,
        };
      })
      .sort(compareProblemSets);
  }

  find(slug) {
    const safeSlug = String(slug || '').trim();
    if (!safeSlug || safeSlug.includes('/') || safeSlug.includes('\\')) {
      return null;
    }

    const mdPath = path.join(this.baseDir, `${safeSlug}.md`);
    if (!fs.existsSync(mdPath)) {
      return null;
    }

    const renderer = new MarkdownRenderer(mdPath, this.problemManager);
    const content = transformProblemTasks(renderer.toHTML(), this.problemManager);
    const frontmatter = renderer.front_matter || {};
    const firstHeading = renderer.md_content.match(/^#\s+(.+)$/m);

    return {
      slug: safeSlug,
      title: frontmatter.title || (firstHeading ? firstHeading[1].trim() : titleFromSlug(safeSlug)),
      description: frontmatter.description || '',
      content,
      mdPath,
    };
  }
}

export default ProblemSetManager;
