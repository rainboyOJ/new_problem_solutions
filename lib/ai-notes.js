import fs from 'node:fs';
import path from 'node:path';
import matter from 'gray-matter';
import { createMarkdownIt } from './markdown.js';

export const AI_NOTES_DIRECTORY = 'talking_with_ai';
const SLUG_PATTERN = /^[a-z0-9]+(?:-[a-z0-9]+)*$/;
const ASSET_EXTENSIONS = new Set(['.avif', '.gif', '.jpeg', '.jpg', '.png', '.webp']);

function isInside(parent, candidate) {
  const relative = path.relative(parent, candidate);
  return relative !== ''
    && !relative.startsWith(`..${path.sep}`)
    && relative !== '..'
    && !path.isAbsolute(relative);
}

function normalizeDate(value, rawFrontmatter) {
  if (!(typeof value === 'string' || value instanceof Date)) return null;
  const match = rawFrontmatter.match(/^\s*date:\s*["']?(\d{4}-\d{2}-\d{2})["']?\s*(?:#.*)?$/m);
  if (!match) return null;
  const date = match[1];
  const parsed = new Date(`${date}T00:00:00.000Z`);
  return Number.isNaN(parsed.getTime()) || parsed.toISOString().slice(0, 10) !== date ? null : date;
}

function requiredText(data, key, errors, filePath) {
  if (typeof data[key] !== 'string' || data[key].trim() === '') {
    errors.push({
      type: 'ai-note',
      path: filePath,
      message: `frontmatter.${key} 必须是非空字符串`,
    });
    return '';
  }
  return data[key].trim();
}

function validateAiNote(filePath, fileName) {
  const errors = [];
  let parsed;
  let raw;
  try {
    raw = fs.readFileSync(filePath, 'utf8');
    parsed = matter(raw);
  } catch (error) {
    return {
      note: null,
      errors: [{ type: 'ai-note', path: filePath, message: `无法解析 Markdown: ${error.message}` }],
    };
  }

  const data = parsed.data || {};
  const title = requiredText(data, 'title', errors, filePath);
  const description = requiredText(data, 'description', errors, filePath);
  const rawFrontmatter = raw.match(/^---\r?\n([\s\S]*?)\r?\n---(?:\r?\n|$)/)?.[1] || '';
  const date = normalizeDate(data.date, rawFrontmatter);
  if (!date) {
    errors.push({
      type: 'ai-note',
      path: filePath,
      message: 'frontmatter.date 必须是 YYYY-MM-DD',
    });
  }
  const slug = requiredText(data, 'slug', errors, filePath);
  if (slug && !SLUG_PATTERN.test(slug)) {
    errors.push({
      type: 'ai-note',
      path: filePath,
      message: 'frontmatter.slug 只能使用小写字母、数字和连字符',
    });
  }
  if (data.draft !== undefined && typeof data.draft !== 'boolean') {
    errors.push({
      type: 'ai-note',
      path: filePath,
      message: 'frontmatter.draft 必须是布尔值',
    });
  }
  if (errors.length > 0) return { note: null, errors };

  return {
    note: {
      title,
      description,
      date,
      slug,
      draft: data.draft === true,
      fileName,
    },
    errors,
  };
}

export function scanAiNotes(problemDir) {
  const directory = path.join(problemDir, AI_NOTES_DIRECTORY);
  if (!fs.existsSync(directory)) return { notes: [], errors: [] };

  const errors = [];
  let stats;
  try {
    stats = fs.lstatSync(directory);
  } catch (error) {
    return { notes: [], errors: [{ type: 'ai-note', path: directory, message: error.message }] };
  }
  if (!stats.isDirectory() || stats.isSymbolicLink()) {
    return {
      notes: [],
      errors: [{ type: 'ai-note', path: directory, message: 'talking_with_ai 必须是普通目录，不能是符号链接' }],
    };
  }

  const notes = [];
  const slugs = new Map();
  for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
    if (entry.name.startsWith('.') || path.extname(entry.name).toLowerCase() !== '.md') continue;
    const filePath = path.join(directory, entry.name);
    if (!entry.isFile() || entry.isSymbolicLink()) {
      errors.push({ type: 'ai-note', path: filePath, message: '对话文档必须是普通 Markdown 文件，不能是符号链接' });
      continue;
    }
    const result = validateAiNote(filePath, entry.name);
    errors.push(...result.errors);
    if (!result.note) continue;
    if (slugs.has(result.note.slug)) {
      errors.push({
        type: 'ai-note',
        path: filePath,
        message: `slug 与 ${slugs.get(result.note.slug)} 重复: ${result.note.slug}`,
      });
      continue;
    }
    slugs.set(result.note.slug, entry.name);
    if (!result.note.draft) notes.push(result.note);
  }

  notes.sort((left, right) => right.date.localeCompare(left.date) || left.slug.localeCompare(right.slug));
  return { notes, errors };
}

export function findAiNote(notes, slug) {
  return Array.isArray(notes) ? notes.find((note) => note.slug === slug) || null : null;
}

export function resolveAiNotePath(problemDir, note) {
  const directory = path.join(problemDir, AI_NOTES_DIRECTORY);
  const candidate = path.resolve(directory, note.fileName);
  if (!isInside(directory, candidate) || path.extname(candidate).toLowerCase() !== '.md') {
    throw new Error('Invalid AI note path');
  }
  const stats = fs.lstatSync(candidate);
  if (!stats.isFile() || stats.isSymbolicLink()) throw new Error('AI note is not a regular file');
  return candidate;
}

export function resolveAiNoteAssetPath(problemDir, resourcePath) {
  const directory = path.join(problemDir, AI_NOTES_DIRECTORY, 'assets');
  const normalized = String(resourcePath || '').replace(/\\/g, '/');
  if (!normalized || normalized.startsWith('/') || normalized.split('/').some((part) => !part || part === '.' || part === '..')) {
    return null;
  }
  const candidate = path.resolve(directory, normalized);
  if (!isInside(directory, candidate) || !ASSET_EXTENSIONS.has(path.extname(candidate).toLowerCase())) return null;
  try {
    const stats = fs.lstatSync(candidate);
    return stats.isFile() && !stats.isSymbolicLink() ? candidate : null;
  } catch {
    return null;
  }
}

function stripLeadingTitle(content, title) {
  const match = content.match(/^\s*#\s+(.+?)\s*(?:\r?\n|$)/);
  return match && match[1].trim() === title ? content.slice(match[0].length) : content;
}

export function readAiNoteMarkdown(problemDir, note) {
  const filePath = resolveAiNotePath(problemDir, note);
  const raw = fs.readFileSync(filePath, 'utf8');
  return stripLeadingTitle(matter(raw).content, note.title);
}

export function readAiNoteRawContent(problemDir, note) {
  return matter(fs.readFileSync(resolveAiNotePath(problemDir, note), 'utf8')).content;
}

export function renderAiNoteMarkdown(problemDir, note, problemManager, assetBaseUrl) {
  const markdown = readAiNoteMarkdown(problemDir, note);
  const renderer = createMarkdownIt(problemManager, {
    profile: 'ai-note',
    assetBaseUrl,
  });
  return renderer.render(markdown, { filePath: resolveAiNotePath(problemDir, note) });
}
