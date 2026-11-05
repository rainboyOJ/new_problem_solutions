#!/usr/bin/env node
/**
 * 列出 newRbook_ejs（rbook1，https://rbook.roj.ac.cn）对外发布的文章。
 *
 * rbook1 是纯静态站，没有 REST API，只能读本地源码。判定规则：
 *   收录范围 = book/catalog.yaml 的叶子条目（实测与 dist/*.html 逐项对齐）
 *   id       = 文章目录 config.{json,jsonc,yaml,yml} 的 id；缺省时按路径推导
 *   url      = 目录型文章 /<dir>/（nginx 返回 200，不带尾斜杠会 301）；
 *              文件型叶子 /<path>.html
 *
 * config.json 里有注释和尾逗号（JSONC），JSON.parse 会直接失败，这里用容错解析。
 *
 * 用法（在 rbook_new_problem_solutions 根目录跑，或用绝对路径）：
 *   node .agents/skills/rbook-idea-linker/scripts/list-rbook1-articles.mjs
 *   node ... --grep 倍增 二分
 *   node ... --verify binary_jump,presum
 *   node ... --json
 *   node ... --book /path/to/newRbook_ejs/book
 *   node ... --manifest            # 改读 dist/catalog.json（构建产物，可能过期）
 */

import fs from 'node:fs'
import os from 'node:os'
import path from 'node:path'
import { createRequire } from 'node:module'

const CONFIG_NAMES = ['config.json', 'config.jsonc', 'config.yaml', 'config.yml']
const SITE_ORIGIN = 'https://rbook.roj.ac.cn'

function defaultBookDir() {
  const env = (process.env.RBOOK1_CODE_PATH || '').trim()
  const candidates = []
  if (env) candidates.push(path.resolve(env), path.resolve(env, 'book'))
  candidates.push(path.resolve(os.homedir(), 'mycode/newRbook_ejs/book'))
  for (const c of candidates) {
    if (fs.existsSync(path.join(c, 'catalog.yaml'))) return c
  }
  return null
}

/** 剥掉 // 与块注释和尾逗号，字符串内容不动。 */
function stripJsonc(text) {
  let out = ''
  let inString = false
  let quote = ''
  for (let i = 0; i < text.length; i++) {
    const ch = text[i]
    const next = text[i + 1]
    if (inString) {
      out += ch
      if (ch === '\\') {
        out += text[i + 1] ?? ''
        i++
      } else if (ch === quote) {
        inString = false
      }
      continue
    }
    if (ch === '"' || ch === "'") {
      inString = true
      quote = ch
      out += ch
      continue
    }
    if (ch === '/' && next === '/') {
      while (i < text.length && text[i] !== '\n') i++
      out += '\n'
      continue
    }
    if (ch === '/' && next === '*') {
      i += 2
      while (i < text.length && !(text[i] === '*' && text[i + 1] === '/')) i++
      i++
      continue
    }
    out += ch
  }
  return out.replace(/,(\s*[}\]])/g, '$1')
}

function loadJsYaml(bookDir) {
  const roots = [bookDir, path.resolve(bookDir, '..'), process.cwd()]
  for (const root of roots) {
    try {
      return createRequire(path.join(root, 'noop.js'))('js-yaml')
    } catch {
      // 换下一个候选根目录
    }
  }
  throw new Error('找不到 js-yaml：请在 newRbook_ejs 仓库或其上层目录运行，或用 --book 指向该书')
}

function loadConfig(dir, yaml) {
  for (const name of CONFIG_NAMES) {
    const file = path.join(dir, name)
    if (!fs.existsSync(file)) continue
    const raw = fs.readFileSync(file, 'utf8')
    if (name.endsWith('.yaml') || name.endsWith('.yml')) {
      const data = yaml.load(raw)
      return data && typeof data === 'object' ? data : {}
    }
    try {
      const data = JSON.parse(stripJsonc(raw))
      return data && typeof data === 'object' ? data : {}
    } catch (err) {
      return { __error: `${name}: ${err.message}` }
    }
  }
  return null
}

function flattenLeaves(entries, parentPath, out) {
  for (const entry of entries || []) {
    if (!entry || typeof entry !== 'object') continue
    const fullPath = parentPath
      ? path.join(parentPath, entry.path ?? '')
      : entry.path ?? ''
    if (Array.isArray(entry.children) && entry.children.length > 0) {
      flattenLeaves(entry.children, fullPath, out)
    } else {
      out.push({ path: fullPath, catalogTitle: entry.title ?? '' })
    }
  }
  return out
}

/** 与 src/publishing/content/metadata-normalizer.ts 的 idFromPath 保持一致。 */
function idFromPath(sourcePath) {
  const parts = sourcePath.replace(/\.md$/i, '').split(/[\\/]/).filter(Boolean)
  const base = parts[parts.length - 1] || 'untitled'
  if (base === 'index' && parts.length >= 2) return parts[parts.length - 2]
  return base
}

/** 站内地址：index.md 用 /dir/（200），其他 md 用 /path.html。 */
function publishUrl(bookRelMd) {
  const posix = bookRelMd.split(path.sep).join('/')
  const noExt = posix.replace(/\.md$/i, '')
  return noExt.endsWith('/index') ? `/${noExt.slice(0, -'index'.length)}` : `/${noExt}.html`
}

function collect(bookDir, yaml) {
  const catalogFile = path.join(bookDir, 'catalog.yaml')
  const catalog = yaml.load(fs.readFileSync(catalogFile, 'utf8'))
  if (!Array.isArray(catalog)) throw new Error('catalog.yaml 顶层必须是数组')

  const articles = []
  for (const leaf of flattenLeaves(catalog, '', [])) {
    const rel = leaf.path.replace(/\/+$/, '')
    const abs = path.join(bookDir, rel)
    if (!fs.existsSync(abs)) {
      articles.push({ id: null, title: leaf.catalogTitle, rel, url: null, error: 'catalog 条目指向的源不存在' })
      continue
    }
    const isDir = fs.statSync(abs).isDirectory()
    const dir = isDir ? abs : path.dirname(abs)
    const config = loadConfig(dir, yaml)
    const file = config && typeof config.file === 'string' && config.file ? config.file : 'index.md'
    const mdPath = isDir ? path.join(abs, file) : abs
    const mdRel = path.relative(bookDir, mdPath)
    const md = fs.existsSync(mdPath) ? fs.readFileSync(mdPath, 'utf8') : ''
    const statusMatch = /^status:\s*(\S+)/m.exec(md)
    articles.push({
      id: (config && typeof config.id === 'string' && config.id.trim()) || idFromPath(mdPath),
      title: (config && typeof config.title === 'string' && config.title.trim()) || leaf.catalogTitle || '',
      rel: mdRel.split(path.sep).join('/'),
      url: publishUrl(mdRel),
      status: statusMatch ? statusMatch[1] : '',
      hasConfig: Boolean(config),
      error: config && config.__error ? config.__error : undefined,
    })
  }
  articles.sort((a, b) => String(a.id).localeCompare(String(b.id)))
  return articles
}

/** dist/catalog.json 是构建期清单，id 与 url 由构建保证可点，但可能落后于源码。 */
function loadManifest(bookDir) {
  const file = path.join(path.resolve(bookDir, '..'), 'dist', 'catalog.json')
  if (!fs.existsSync(file)) return null
  try {
    const data = JSON.parse(fs.readFileSync(file, 'utf8'))
    if (!Array.isArray(data.items)) return null
    return data.items
      .map((item) => ({
        id: String(item.id || ''),
        title: String(item.title || ''),
        rel: '',
        url: String(item.url || ''),
        status: '',
        hasConfig: true,
      }))
      .sort((a, b) => a.id.localeCompare(b.id))
  } catch {
    return null
  }
}

/** 本地目录与 dist 清单对不上时给一句提示，不阻断。 */
function compareManifest(bookDir, fromCatalog) {
  const manifest = loadManifest(bookDir)
  if (!manifest) return ''
  const a = new Set(fromCatalog.map((x) => x.id).filter(Boolean))
  const b = new Set(manifest.map((x) => x.id).filter(Boolean))
  const onlyCatalog = [...a].filter((x) => !b.has(x))
  const onlyManifest = [...b].filter((x) => !a.has(x))
  if (onlyCatalog.length === 0 && onlyManifest.length === 0) return ''
  return `! dist/catalog.json 与 catalog.yaml 不一致：仅源码有 ${onlyCatalog.length} 篇，仅清单有 ${onlyManifest.length} 篇（dist 可能过期，结论以 catalog.yaml 为准）`
}

function main() {
  const args = process.argv.slice(2)
  const flag = (name) => {
    const i = args.indexOf(name)
    return i >= 0 ? args[i + 1] ?? '' : ''
  }
  const has = (name) => args.includes(name)

  const bookDir = path.resolve(flag('--book') || defaultBookDir() || '')
  if (!bookDir || !fs.existsSync(path.join(bookDir, 'catalog.yaml'))) {
    console.error('未找到 book/catalog.yaml。用 --book 指定，或设置 RBOOK1_CODE_PATH。')
    process.exit(2)
  }

  const fromCatalog = collect(bookDir, loadJsYaml(bookDir))
  const all = has('--manifest') ? loadManifest(bookDir) : fromCatalog
  if (!all) {
    console.error('未找到 dist/catalog.json：先生成构建产物，或去掉 --manifest 改用 catalog.yaml。')
    process.exit(2)
  }
  const known = new Set(all.map((a) => a.id).filter(Boolean))

  const verify = flag('--verify')
  if (verify) {
    const wanted = verify.split(',').map((s) => s.trim()).filter(Boolean)
    const bad = wanted.filter((w) => !known.has(w))
    for (const id of wanted) console.log(`${known.has(id) ? 'OK   ' : 'FAIL '} ${id}`)
    console.log(`\n${wanted.length - bad.length}/${wanted.length} 个 id 可用`)
    if (bad.length) console.log('不可用（不在 catalog.yaml 叶子、拼错，或该文未发布）:', bad.join(', '))
    process.exit(bad.length ? 1 : 0)
  }

  let rows = all
  const grep = args.indexOf('--grep')
  if (grep >= 0) {
    const keywords = args.slice(grep + 1).filter((a) => !a.startsWith('--')).map((k) => k.toLowerCase())
    rows = rows.filter((a) =>
      keywords.some(
        (k) =>
          String(a.id).toLowerCase().includes(k)
          || String(a.title).toLowerCase().includes(k)
          || a.rel.toLowerCase().includes(k),
      ),
    )
  }

  if (has('--json')) {
    console.log(JSON.stringify(rows, null, 2))
    return
  }

  console.log(`book 目录: ${bookDir}`)
  console.log(`对外文章: ${all.length} 篇（${has('--manifest') ? 'dist/catalog.json' : 'catalog.yaml 叶子'}）`)
  if (!has('--manifest')) {
    const drift = compareManifest(bookDir, fromCatalog)
    if (drift) console.log(drift)
  }
  console.log('')
  for (const a of rows) {
    const status = a.status ? `  [status: ${a.status}]` : ''
    console.log(`${String(a.id).padEnd(46)} | ${a.title}${status}`)
    console.log(`${' '.repeat(46)}   ${a.url ? SITE_ORIGIN + a.url : '(无地址)'}`)
    if (a.error) console.log(`${' '.repeat(46)}   ! ${a.error}`)
  }
  if (grep >= 0) console.log(`\n命中 ${rows.length} / ${all.length}`)
}

main()
