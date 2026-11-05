# 本题的 Scriba 图源

这里的 `.svg` / `.html` 由 [Scriba](~/__git__/scriba) 的 `\begin{diagram}` 与
`\begin{animation}` 渲染，**不要手改产物** —— 改 `.tex` 后重新生成。

| 文件 | 用在 index.md 的位置 | 内容 |
| --- | --- | --- |
| `fig1-prefix-mask.tex` → `.svg` | 「一段已经确定的高位前缀，怎样约束每一行？」之后 | 前缀 `010??` 转成允许位掩码 `01011`，三个候选值的按位子集判定 |
| `fig2-greedy-trace.tex` → `.svg` | 「下面用原题样例展示这个过程。」之后 | 原题样例的逐位干跑表（`TraceTable`） |
| `anim-greedy.tex` → `.html` | 图二说明之后，`<iframe>` 内嵌 | 同一过程的 5 帧动画，带上一帧/下一帧与旁白 |

## 重新生成

```bash
cd ~/__git__/scriba
P=~/mycode/rbook_new_problem_solutions/problems/codeforces/1395C/scriba

# 静态图：烘样式 + 字体 + 底色板，输出可直接 ![]() 引用的独立 SVG
python3 tools/scriba_svg.py $P/fig1-prefix-mask.tex  -o $P/fig1-prefix-mask.svg  --compact --scale 1.7
python3 tools/scriba_svg.py $P/fig2-greedy-trace.tex -o $P/fig2-greedy-trace.svg --compact --scale 1.7

# 动画：去掉 h1 与主题按钮、压平页边距，供 <iframe> 使用
SCRIBA_ALLOW_ANY_OUTPUT=1 python3 tools/scriba_embed.py $P/anim-greedy.tex -o $P/anim-greedy.html --lang zh-CN
```

`tools/scriba_svg.py` 与 `tools/scriba_embed.py` 是本仓库为 rbook 写的两个桥接脚本
（不属于 Scriba 上游）。前者把 `scriba-state-*` 类样式、Inter 子集字体、light
主题和一块不透明底色板烘进 SVG 内部，产物不依赖站点任何 CSS；`--scale` 只放大
`width`/`height`（`viewBox` 不变），所以正文栏里字号接近正文且依然清晰。后者在
`render.py` 的产出上删掉标题和主题切换按钮，让控件在 iframe 里居中铺满。

## 已知限制

- Scriba 用自带 Inter 子集度量文字，**没有中文字形**（按 1em/字估算）。`TraceTable`
  的中文列头会溢出格子，所以单元格与列头保持 ASCII，中文只写进 `label`（图注）。
- 图注后面 Scriba 会画一圈白描边，默认假设浅色页面；纯透明 SVG 放到深色主题下
  会变成「深字白边」。所以静态图默认烘一块白色底板（`--no-plate` 可关）。
- 动画产物约 600 KB（内联 KaTeX CSS + 字体），因此用 iframe 隔离；静态图约 73 KB。
- Scriba 的 `TraceTable` 按最大行数为整表预留高度（跨帧 `viewBox` 稳定，R-32），
  所以第 1 帧下方会留白，属设计取舍，不是布局错误。
