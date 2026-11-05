# 把 Scriba 产物接进 rbook

Scriba 的输出不是“另存为 SVG”就能用的。它假设自己跑在自己的页面里：样式在外部
CSS、字体在 `@font-face`、主题由 `data-theme` 决定、SVG 由父容器给宽。这个仓库
没有那套环境，所以中间必须有一层烘焙。本文记录**每个处理为什么必要**，出问题时
按症状查。

## 1. 为什么不能直接引用 Scriba 的 SVG

| Scriba 的假设 | rbook 的现实 | 症状 |
| --- | --- | --- |
| 外部 `scriba-scene-primitives.css` 提供状态色 | 没有这张表 | 所有格子一片灰 |
| `@font-face "Scriba Sans"` 由页面提供 | 读者机器上不存在 | 列宽按度量表算好，实际字体更宽 → 文字溢出格子 |
| `data-theme` + `prefers-color-scheme` 决定明暗 | 读者的系统偏好未知 | 深色系统下浅色图被刷成暗字暗底 |
| 页面是白底，图注描白边 | 深色页面 | 深字 + 白描边，糊成一团 |
| 父容器给宽度，SVG 只有 `viewBox` | `<img>` 需要内禀尺寸 | 退回 300×150 |

`scripts/svg.py` 逐条对上表处理：

1. `--compact`：按 SVG 里**实际出现**的 class 名与 `data-primitive` 裁剪样式表
   （197 条规则 → 十几条）。裁之前先删注释，因为 Scriba 的注释里写着
   `svg { --scriba-diagram-font-scale: 1.3; }` 这种带花括号的示例，会骗过任何
   正则分块。
2. 内联 `inline_text_font_css()`（Inter 子集，约 36 KB base64）。**必须**：不嵌
   字体的话，Scriba 用度量表算出来的列宽与浏览器实际排版不一致。
3. 用括号配对（不是正则）解析样式表，整块丢掉
   `[data-theme="dark"]` 与 `@media (prefers-color-scheme: dark)`。后者尤其要删：
   `:root:not([data-theme="light"])` 在裸 SVG 里会命中，把浅色图刷暗。
4. 把 `viewBox` 的宽高发布成 `width`/`height`（乘 `--scale`），并补一块
   `--plate-color` 底板。
5. `:root` → `svg`：裸 SVG 没有 `<html>`，自定义属性要挂在根元素上。

体积参考：单图 70--76 KB，其中 36 KB 是字体、约 26 KB 是裁剪后的样式、正文
5--6 KB。**不要**为了瘦身去掉字体——换来的就是溢出。

## 2. 为什么中文只能进 `label`

Scriba 的 `_text_metrics` 只有 Inter 子集的精确 advance 表；CJK **刻意不在**
启发式表里，按 1em/字估算。它自己的注释说这个估算“从不裁切”，但那只对
`\annotate` 的胶囊标签成立；`TraceTable` / `Grid` 的列宽是另一个算法，中文列头
实测会溢出格子（`第 2 行候选` 被截成 `第 2 行`）。

结论：**格子内容与列头写 ASCII**（`k`、`T`、`ok`、`M`、`a2`），中文写 `label=`
或正文。这个约束不损失教学效果，因为图注本来就要承担“这列是什么”的解释。

## 3. 尺寸与 `--scale`

SVG 的 `viewBox` 由内容算出（5 列数组约 332×409），直接按 1:1 显示在 900px 正文
栏里会显得字号偏小。`--scale` 只改 `width`/`height`，`viewBox` 不变，所以放大后
依旧矢量清晰、字号接近正文。

| 图宽（列数） | 建议 `--scale` |
| --- | --- |
| 5 列数组（332px） | `1.7` → 564px |
| 8 列干跑表（518px） | `1.7` → 880px |
| 单图/树（≤300px） | `1.8--2.0` |

正文栏宽约 940px，留出边距后 880px 是安全上限。超过就降低 `--scale`，不要靠
CSS 压缩——压缩会把字号压到看不清。

## 4. 动画用 iframe 的代价与理由

`render.py` 的产出是完整页面：600 KB 上下，其中约 470 KB 是内联的 KaTeX CSS +
字体（旁白里有 `$…$` 就必须带）。不能内联进 `index.md`——那会把每篇文章的
HTML 都撑大、且 KaTeX 样式会污染整页。

所以用 `<iframe>` 隔离，`loading="lazy"` 保证不点不加载。`embed.py` 另外做三件事：

- 删 `<h1>`（标题会和正文图注重复）与主题切换按钮（读者点不到也管不了）。
- 压平 `scriba-standalone.css` 的 `body { max-width:720px; margin:2rem auto }`，
  否则控件挤在 iframe 左侧一窄条。
- `--lang zh-CN` 修 `<html lang>`，影响朗读与断行。

高度按内容定：先渲一次，看**最后一帧**的上一帧/下一帧胶囊和旁白是否完整可见。
5 帧的数组 + 4 行表约 480px。

## 5. 验证方式（不用浏览器 MCP）

仓库禁止 Playwright / 浏览器 MCP（`AGENTS.md`）。静态验收用命令行：

```bash
# 合法 XML + 内禀尺寸
python3 -c "import xml.dom.minidom,sys;d=xml.dom.minidom.parse(sys.argv[1]);\
print(d.documentElement.getAttribute('width'),d.documentElement.getAttribute('height'))" fig.svg

# 真实浏览器渲染（headless，仅截图）
chromium --headless --disable-gpu --no-sandbox --hide-scrollbars \
  --window-size=1100,600 --screenshot=/tmp/fig.png "file://$PWD/fig.svg"

# 页面里能加载、深色主题下也能读
PORT=3120 node ./bin/www &
chromium --headless ... --screenshot=/tmp/page.png "http://127.0.0.1:3120/problems/<oj>/<id>/"
```

`rsvg-convert` 也能出图，但它不支持 CSS4 的 `:where()`，格子会画成黑块——**不要**
用它判断颜色是否正确，只用它判断几何是否合理。颜色一律用 Chromium 截图核对。

## 6. 与 rbook 渲染管线的接触点

- `index.md` 的 Markdown 允许裸 HTML（`lib/markdown.js` 里 `html: true`），
  所以 `<iframe …>` 能原样通过，不需要 `/i/` 前缀插件（那个只接受 URL）。
- 题目目录下的任意文件都由 `routes/index.js` 的
  `GET /problems/:oj/:id/*` 静态吐出，所以 `./scriba/fig1.svg` 的相对路径可用，
  且 MIME 正确（`image/svg+xml`、`text/html`）。
- 本地 SVG 用标准图片语法：`![说明](./scriba/fig1-xxx.svg)`。
- `npm run check:content` 只校验 frontmatter 与索引，不校验图片；所以图有没有
  渲染对，**只能靠截图**。

## 7. 症状 → 原因

| 症状 | 原因 | 处理 |
| --- | --- | --- |
| 格子全灰 | 没烘样式 | 用 `scripts/svg.py`，别手抄 `render.py` 的 `<svg>` |
| 文字溢出格子 / 列头被截 | 烘样式了但没嵌字体，或格子里放了中文 | 别用 `--no-plate` 之外的方式剥样式；把中文挪进 `label` |
| 深色页面上图变暗、看不清 | 暗色分支没删干净 | 确认 `grep -c data-theme fig.svg` 为 0 |
| 图注是深字白边 | 没铺底板 | 默认就有；检查是否加了 `--no-plate` |
| 图很小 / 300×150 | 没有 `width`/`height` | 用 `scripts/svg.py`（会从 `viewBox` 生成） |
| iframe 里内容挤在左边 | 没压平 720px 版心 | 用 `scripts/embed.py` |
| iframe 底部文字被切 | 高度不够 | 实测最后一帧再定高度 |
| 图里数字和程序输出不一致 | 手写表格时算错/写错 | 对着 `main.cpp` 输出逐格复核 |
