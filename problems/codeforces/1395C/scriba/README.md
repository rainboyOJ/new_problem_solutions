# 本题的 Scriba 图源

这里的 `.svg` / `.html` 由 [Scriba](~/__git__/scriba) 的 `\begin{diagram}` 与
`\begin{animation}` 渲染，**不要手改产物** —— 改 `.tex` 后重新生成。
工具与规则见 skill [`oj-scriba-visualizer`](../../../../.agents/skills/oj-scriba-visualizer/SKILL.md)。

| 文件 | 用在 index.md 的位置 | 内容 |
| --- | --- | --- |
| `fig1-prefix-mask.tex` → `.svg` | 「一段已经确定的高位前缀，怎样约束每一行？」之后 | 前缀 `010??` 转成允许位掩码 `01011`，三个候选值的按位子集判定 |
| `fig2-greedy-trace.tex` → `.svg` | 「下面用原题样例展示这个过程。」之后 | 原题样例的逐位干跑表（`TraceTable`） |
| `anim-greedy.tex` → `.html` | 图二说明之后，`<iframe>` 内嵌 | 同一过程的 5 帧动画，带上一帧/下一帧与旁白 |

## 重新生成

```bash
cd .agents/skills/oj-scriba-visualizer/scripts
P=../../../../problems/codeforces/1395C/scriba

# 静态图：烘样式 + 字体 + 底色板，输出可直接 ![]() 引用的独立 SVG
python3 svg.py $P/fig1-prefix-mask.tex  -o $P/fig1-prefix-mask.svg  --compact --scale 1.7
python3 svg.py $P/fig2-greedy-trace.tex -o $P/fig2-greedy-trace.svg --compact --scale 1.7

# 动画：去掉 h1 与主题按钮、压平页边距，供 <iframe> 使用
python3 embed.py $P/anim-greedy.tex -o $P/anim-greedy.html --lang zh-CN
```

脚本默认在 `~/__git__/scriba` 找 Scriba（可用 `SCRIBA_ROOT` 或 `--scriba-root` 覆盖）。

## 本题的取舍

- 单元格与列头保持 ASCII（`k`、`T`、`ok`、`M`、`a2`）。Scriba 的度量表没有中文
  字形，`TraceTable` 的中文列头会溢出格子；中文只写进 `label=`（图注）。
- 图二失败行的 `a6` 列写 `-`（该行无合法候选），不写 `100`——`100` 正是被排除
  的那个候选，写进去会让表格和结论矛盾。
- 静态图烘一块白色底板：Scriba 的图注带白描边，裸透明 SVG 放到深色主题下会变成
  「深字白边」。
- 动画在 prelude 里先放一行空数据，否则第 1 帧的表格是空的、下方一大片留白。
