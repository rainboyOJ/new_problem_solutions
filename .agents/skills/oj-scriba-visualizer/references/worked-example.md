# 完整实例：Codeforces 1395C 的三张图

题目是「给每行选一个 $a_i \mathbin{\&} b_j$，最小化整体 OR」。题解的推理链是
**前缀 → 允许位掩码 → 逐行按位子集判定 → 按位贪心**。三张图分别承担链条上的
一段，不重复。

产物在 `problems/codeforces/1395C/scriba/`。这是仓库里第一个用 Scriba 的题解，
可以直接当模板抄。

## 图一：把抽象条件画成“允许/禁止的位”

**要解释的事**：读完“前缀 `010??` 等价于一个允许位掩码”之后，读者需要一个具体
的位图去对照。

**选形**：4 个 `Array`（前缀 / 掩码 / 两个合法候选 / 一个非法候选），5 列对齐成
“二进制位”的列，靠颜色而不是文字表达结论。

```latex
\begin{diagram}[id="cf1395c-prefix-mask", label="前缀转成允许位掩码"]
\shape{pre}{Array}{size=5, data=["0","1","0","?","?"], label="已定前缀 010??"}
\shape{msk}{Array}{size=5, data=["0","1","0","1","1"], label="允许位掩码 M"}
\shape{c1}{Array}{size=5, data=["0","1","0","0","1"], label="候选 x1 合法（x1 ⊆ M）"}
\shape{c2}{Array}{size=5, data=["0","0","0","1","0"], label="候选 x2 合法（x2 ⊆ M）"}
\shape{c3}{Array}{size=5, data=["0","1","1","0","0"], label="候选 x3 不合法（禁用位出现 1）"}

\recolor{pre.cell[3]}{state=dim}      % 未定的位淡化
\recolor{pre.cell[4]}{state=dim}
\recolor{msk.cell[0]}{state=error}    % M=0：禁用
\recolor{msk.cell[2]}{state=error}
\recolor{msk.cell[1]}{state=good}     % M=1：允许但不强制
\recolor{msk.cell[3]}{state=good}
\recolor{msk.cell[4]}{state=good}
\recolor{c1.cell[1]}{state=done}
\recolor{c1.cell[4]}{state=done}
\recolor{c2.cell[3]}{state=done}
\recolor{c3.cell[2]}{state=error}     % 越界的那个 1
\end{diagram}
```

**踩过的坑**：一开始加了 `\annotate{msk.cell[2]}{label="M 为 0：必须取 0"}`，胶囊
和上一行的图注撞在一起；标签里的信息本来就在图注和正文里，删掉更干净。
**教训**：能在图注里说清的事，不要塞进胶囊。

## 图二：逐位干跑表

**要解释的事**：贪心的每一轮到底发生了什么——这是全文最需要一个表格的地方。

**选形**：`TraceTable`。它天生就是“变量 × 步骤”向下生长，一行一轮，且跨帧
`viewBox` 稳定。

```latex
\begin{diagram}[id="cf1395c-greedy", label="原题样例的按位贪心干跑"]
\shape{t}{TraceTable}{columns=["k", "T", "a2", "a6", "a4", "a0", "ok", "M"],
  label="样例 a=[2,6,4,0], b=[2,4]：a* 列是该行在 T 下取到的一个合法候选，- 表示无解"}
\apply{t}{row=["-", "111", "010", "010", "000", "000", "-", "111"]}
\apply{t}{row=["2", "011", "010", "010", "000", "000", "yes", "011"]}
\apply{t}{row=["1", "001", "000", "-", "000", "000", "no", "011"]}
\apply{t}{row=["0", "010", "010", "010", "000", "000", "yes", "010"]}
\recolor{t.cell[1][6]}{state=good}    % 成功
\recolor{t.cell[2][3]}{state=error}   % 这一行无解
\recolor{t.cell[2][6]}{state=error}
\recolor{t.cell[2][7]}{state=error}   % 这一位必须保留 1
\recolor{t.cell[3][6]}{state=good}
\recolor{t.cell[3][7]}{state=done}
\end{diagram}
```

**踩过的坑（两个，都是真错）**：

1. 列头一开始写中文 `["试探位", "试探掩码", "第 2 行候选", "判定", "M"]`，被截成
   `试探`／`第 2 行`。Scriba 的中文度量是 1em/字的估算，列宽按估算值算，实际
   字体更宽 → 溢出。改成 `k`/`T`/`ok`/`M` 后正常。
2. 最初把失败行的 `a6` 列填成 `100`，并称之为“最小合法候选”。但 `100` 恰恰是
   **不合法**的那个候选——表格说了和结论相反的话。改成 `-` 并标红，图注同步改成
   “…取到的一个合法候选，`-` 表示无解”。

**教训**：图里的每个数字都要对着程序输出复核；图错了比没图更糟。

## 动画：同一过程的步进版

**要解释的事**：把“试探 → 判定 → 接受/放弃”的节奏显式化，读者能自己按。

```latex
\begin{animation}[id="cf1395c-bit-greedy", label="CF1395C：从高位到低位试探清零"]
\shape{M}{Array}{size=3, data=["1","1","1"], labels="2..0", label="允许位掩码 $M$"}
\shape{t}{TraceTable}{columns=["k", "T", "ok", "M"], label="原题样例的干跑"}
\apply{t}{row=["-", "111", "-", "111"]}    % prelude 里放首行，第 1 帧才不空

\step
\narrate{初始 $M=(111)_2$：不禁止任何位，判定必然成功。}

\step
\apply{M.cell[2]}{value="0"}
\recolor{M.cell[2]}{state=current}
\apply{t}{row=["2", "011", "yes", "011"]}
\recolor{t.cell[1][2]}{state=good}
\narrate{试探清第 2 位，$T=(011)_2$：四行都各有一个候选值不含位 2，判定成功，接受 $M=(011)_2$。}
% …失败的一轮、成功的最后一轮同理…
\end{animation}
```

**要点**：

- `\apply{t}{row=[…]}` 在 prelude 里先放一行，否则第 1 帧的表格是空的、下方一大片白。
- 第一帧的表格行会被自动标成 `current`（蓝底），这是 `TraceTable` 的语义，不用管。
- `M.cell[i]{value="0"}` 改的是**字符**，所以能画出“这一位被清成 0”的中间态；
  失败的那一轮改成 `"1"` 并给 `error`，成功定稿给 `done`。
- 旁白里可以写 `$M=(111)_2$`，KaTeX 会渲染。

## 编译命令

```bash
cd .agents/skills/oj-scriba-visualizer/scripts
P=../../../../problems/codeforces/1395C/scriba

python3 svg.py $P/fig1-prefix-mask.tex  -o $P/fig1-prefix-mask.svg  --compact --scale 1.7
python3 svg.py $P/fig2-greedy-trace.tex -o $P/fig2-greedy-trace.svg --compact --scale 1.7
python3 embed.py $P/anim-greedy.tex -o $P/anim-greedy.html --lang zh-CN
```

产物：两张 SVG 各约 73 KB / 75 KB，动画 HTML 600 KB。

## index.md 里的接入

```markdown
![图一：前缀 010?? 转成允许位掩码 01011，候选值只能在掩码为一的位置出现一](./scriba/fig1-prefix-mask.svg)

图中 $M$ 为 $0$ 的两列是所有候选值都不能越过的限制；……

![图二：原题样例的逐位干跑表，四列分别给出各行在试探掩码 T 下取到的一个合法候选值](./scriba/fig2-greedy-trace.svg)

表里每一行是一轮试探：`k` 是被试探清零的位，……

<div class="scriba-embed">
<iframe src="./scriba/anim-greedy.html" title="CF1395C 从高位到低位试探清零的动画" loading="lazy" style="width:100%;height:480px;border:1px solid #dfe3e6;border-radius:6px;background:#fff"></iframe>
</div>
```

每条图前后都必须有解释句：图前说“展示什么”，图后 1--3 句说“该看什么”。
动画单独占一段，先说“按下一帧会发生什么”，读者才知道该点。

## 这道题的整体分工

| 图 | 承担 | 不承担 |
| --- | --- | --- |
| 图一 | 前缀 ⇄ 掩码的**语义** | 不涉及样例数值 |
| 图二 | 一个样例的**完整判定过程** | 不重复讲语义 |
| 动画 | 过程的**节奏**，可自定步 | 不含新信息 |

三张不重复，是因为各自的“读者卡点”不同：先不懂语义，再不懂过程，最后想自己
走一遍。**如果只有 1 张图的预算，留图二。**
