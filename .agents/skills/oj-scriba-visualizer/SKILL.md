---
name: oj-scriba-visualizer
description: >-
  用 Scriba 给 OJ 题解做配图时必须触发此 skill：只要用户要求“给这道题配张图 / 配个图 /
  画个示意 / 做个动画 / 生成 SVG / 把 DP 表画出来 / 画样例过程 / 题目可视化”，
  或提到 Scriba、`\begin{diagram}`、`\begin{animation}`、Array/Grid/DPTable/Graph/
  Tree/TraceTable/Hypercube/Bar/Equation、standalone SVG、iframe 嵌动画，
  就用这个 skill。它把 Scriba 的声明式 primitive 编译成 rbook 能直接引用的独立
  SVG（或 iframe 动画），而不是手写 SVG 坐标。Use it to author a figure with
  Scriba, render it into `.agents/skills/oj-scriba-visualizer/scripts/`, and wire
  the artifact into `index.md` without shipping Scriba CSS.
compatibility: >-
  Requires a Scriba checkout on this machine (`$SCRIBA_ROOT`, default
  `~/__git__/scriba`) and Python 3.10+. Renders offline; no browser needed to
  produce a figure.
---

# 用 Scriba 给题解配图

Scriba 是一个把 `.tex` 编译成自包含 HTML/SVG 的渲染流水线。它提供了 21 种声明式
**primitive**（数组、DP 表、图、树、矩阵、干跑表、子集格、柱状图、方程……），你写
“有哪些形状、它们处于什么状态”，而不是手写 `<rect x=… y=…>` 坐标。

这个 skill 负责：**选形 → 写 `.tex` → 编译成 rbook 能直接吃的产物 → 接进 `index.md`**。

## 边界：什么时候用本 skill，什么时候不用

| 需求 | 用什么 |
| --- | --- |
| 数组 / DP 表 / 网格 / 矩阵 / 图 / 树 / 栈队列 / 干跑表 / 子集格 / 柱状图 / 方程 | **本 skill**（Scriba primitive） |
| 需要“一步步点开”的过程演示（多帧 + 旁白） | **本 skill** 的 `animation` 通道 |
| 纯样例的 Markdown 表格、ASCII 小图 | `oj-sample-visualizer`（不必引 Scriba） |
| 题目专用解析脚本 `problem-analysis-workspace/viz_render.py` | `oj-sample-visualizer` |
| 二叉树 / 线段树只需一张静态结构图 | 二选一：`tree_draw.py` 更省事；需要着色/悬停语义再用本 skill |
| 图论样例只需 dot 源码入库 | `rbook-markdown` 的 ```` ```dot ```` 代码块 |

**不要两套都上**：同一道题里 Scriba 图和 `viz_render.py` 手绘 SVG 混用会让风格
不一致。要么全程 Scriba，要么全程手写；决定后写进 `02-observation-and-model.md`。

本 skill 不负责：写题解正文（`oj-problem-analysis-writer`）、章节骨架与 frontmatter
（`oj-problem-format-spec`）、Markdown 语法（`rbook-markdown`）、可视化取舍的
教学判断（`oj-problem-analysis-writer/references/visualization.md`）。

## 产物放哪

```text
problems/<oj>/<problem_id>/
  scriba/                       ← 图源与产物同目录，便于重生成
    fig1-xxx.tex                ← 手写源（唯一需要人维护的文件）
    fig1-xxx.svg                ← 产物，index.md 用 ![]() 引用
    anim-xxx.tex
    anim-xxx.html               ← 产物，index.md 用 <iframe> 引用
    README.md                   ← 重生成命令 + 本题的取舍说明
```

`.tex` 必须提交（可复现），`.svg` / `.html` 也必须提交（网站要能直接吐出来）。
`scriba/` 目录名固定，方便以后批量重生成。

## 工作流程

1. **读题**：`index.md`、`problem.md`、样例输入输出、`main.cpp`、已有
   `problem-analysis-workspace/*.md`。确认这张图要解释哪一步推理。
2. **选形**（见下节表格）。先问“读者卡在哪”，再问“哪个 primitive 能表达它”。
3. **写 `.tex`**：一次只做一张图；配 `label=`（会变成图注，可写中文）。
4. **编译**（两条通道，见下节）。
5. **静态验收**：`rsvg-convert` 或 headless Chromium 截图，检查是否有文字溢出、
   状态色是否如预期。**不要**用浏览器 MCP 工具（仓库禁令），只用命令行截图。
6. **接进 `index.md`**：图前一句说明“展示什么”，图后 1--3 句说明“该看什么”。
7. **写 `scriba/README.md`**：重生成命令 + 本题踩到的取舍。

## 选形表

| 要解释的东西 | Primitive | 关键参数 |
| --- | --- | --- |
| 一维数组、序列、位串 | `Array` | `size`、`data`、`labels="0..4"` |
| 二维网格、棋盘、矩阵 | `Grid` / `Matrix` | `rows`、`cols`、`data=[[…]]` |
| DP 表、转移箭头 | `DPTable` | `n`/`rows`+`cols`，`arrows` |
| 图的样例、DAG、分层 | `Graph` | `nodes`、`edges`、`directed`、`layout="stable"\|"hierarchical"` |
| 树、递归结构、线段树 | `Tree` | `root`、`nodes`、`edges` |
| **逐步干跑（变量 × 步骤）** | `TraceTable` | `columns=[…]`，`\apply{t}{row=[…]}` 追加一行 |
| 子集 / 位掩码格 | `Hypercube` | `bits`，`L.subset[十进制下标]` |
| 高度=数值（直方图、柱） | `Bar` | `data`、`show_values` |
| 单调栈/滑动窗口 | `Stack` / `Queue` / `Deque` | `capacity`、`push_*`/`pop_*` |
| DSU 合并 | `Forest` | `\apply{f}{union={a=3,b=5}}` |
| 哈希桶、链表 | `HashMap` / `LinkedList` | 同名参数 |
| 变量监视、距离数组 | `VariableWatch` | `\apply{vars.var[name]}{value=…}` |
| 代码行高亮 | `CodePanel` | `code=[…]`，**行号 1-based** |
| 递推展开、主定理 | `Equation` | `tex=` 或 `lines=[…]`，`\term{id}{…}` |
| 坐标平面、几何 | `Plane2D` | `points`、`segments`、`circles` |
| 数轴、区间 | `NumberLine` | `lo`、`hi`、`ticks` |
| 折线/累积曲线 | `MetricPlot` | `data` |

完整参数、选择器和错误码见
[`references/primitive-cheatsheet.md`](references/primitive-cheatsheet.md)。

## 两条产出通道

### A. 静态图 → 独立 SVG（最常用）

```bash
cd .agents/skills/oj-scriba-visualizer/scripts
python3 svg.py ../../../../problems/<oj>/<id>/scriba/fig1-xxx.tex \
  -o ../../../../problems/<oj>/<id>/scriba/fig1-xxx.svg \
  --compact --scale 1.7
```

`svg.py` 做四件 `render.py` 不做的事，缺一不可：

1. **烘样式**：Scriba 的 SVG 靠 `scriba-state-*` 类上色，宿主页面没有那张 CSS 就是
   一片灰。它把用到的规则内联进 `<style>`（`--compact` 按实际类名裁剪）。
2. **烘字体**：Scriba 用自带 Inter 子集度量文本；不把 `@font-face` 一起塞进去，
   浏览器换字体后列宽就对不上，文字溢出格子。
3. **只留浅色主题**：删掉 `[data-theme="dark"]` 与
   `@media (prefers-color-scheme: dark)` 分支，否则读者系统是深色时，浅色图会被
   刷成暗字暗底。
4. **给内禀尺寸 + 白底板**：`<img src="*.svg">` 没有 `width`/`height` 会退回
   300×150；不铺底板则图注的白描边在深色页面上变成“深字白边”。

`--scale` 只放大 `width`/`height`（`viewBox` 不变），所以在正文栏里字号接近正文
且依然清晰。5 列左右用 `1.7`，宽的 8 列表用 `1.4--1.6`。

### B. 交互动画 → iframe HTML

```bash
python3 embed.py ../../../../problems/<oj>/<id>/scriba/anim-xxx.tex \
  -o ../../../../problems/<oj>/<id>/scriba/anim-xxx.html --lang zh-CN
```

`embed.py` 在 `render.py` 的产出去掉 `<h1>`（重复图注）和主题切换按钮，把 720px
文档版心压平，让控件在 iframe 里居中。

`index.md` 里用：

```html
<div class="scriba-embed">
<iframe src="./scriba/anim-xxx.html" title="…" loading="lazy" style="width:100%;height:480px;border:1px solid #dfe3e6;border-radius:6px;background:#fff"></iframe>
</div>
```

动画 600 KB 左右（内联 KaTeX CSS + 字体），所以必须 iframe 隔离，不会拖慢正文。
高度按内容实测：先渲一次，看最后一帧的控件和旁白是否被切掉。

## 硬规则

- **单元格和列头只用 ASCII**。Scriba 的文字度量没有中文字形（按 1em/字估算），
  `TraceTable`/`Grid` 的中文列头会溢出格子。中文写进 `label=`（图注）和正文。
- **状态色表达结论**：`error` 红框＝违规/失败，`good` 绿框＝命中/成功，`done`
  绿＝已完成，`dim` 灰＝不再相关。不要靠文字“不合法”而不用颜色。
- **`label=` 要能独立读懂**。它是图注，读者会连同图前那句话一起读。
- **一张图一个结论**。普通题解 1--2 张图，难题最多 3 张。
- **`.tex` 与 `.svg` 一起提交**，并写 `scriba/README.md` 记录重生成命令。
- **不要手改产物**：改 `.tex` 重跑；手改 SVG 会在下次重生成时丢失。
- **图片用相对路径**：`![说明](./scriba/fig1-xxx.svg)`。

## 验收清单

```bash
# 1. 产物是合法 XML / 尺寸正确
python3 -c "import xml.dom.minidom,sys; d=xml.dom.minidom.parse(sys.argv[1]); \
print(d.documentElement.getAttribute('width'), d.documentElement.getAttribute('height'))" \
  problems/<oj>/<id>/scriba/fig1-xxx.svg

# 2. 静态截图看真实渲染（不用浏览器 MCP）
chromium --headless --disable-gpu --no-sandbox --hide-scrollbars \
  --window-size=1100,600 --screenshot=/tmp/fig.png \
  "file://$PWD/problems/<oj>/<id>/scriba/fig1-xxx.svg"

# 3. 页面里真的能加载 + 深色主题下不糊
```

在交付前把截图看一遍：文字有没有溢出格子、有没有空白列、图注有没有被切。
图里有判定结果时，**逐个数字对着程序输出复核**——图错了比没图更糟。

## 参考

- [`references/primitive-cheatsheet.md`](references/primitive-cheatsheet.md) —
  Scriba 语法速查：环境、21 个 primitive 的关键参数、状态、命令、选择器、踩坑。
- [`references/rbook-integration.md`](references/rbook-integration.md) — 烘焙/体积/
  深浅色/CJK/iframe 的具体原因与数字，出问题时先看这里。
- [`references/worked-example.md`](references/worked-example.md) — Codeforces 1395C
  的完整实例：三份 `.tex`、编译命令、图注文字、踩到的坑。
- Scriba 上游文档：`~/__git__/scriba/docs/SCRIBA-TEX-REFERENCE.md`（全量语法）、
  `docs/tutorial/getting-started.md`（入门）、`examples/primitives/*.tex`（可跑样例）。
