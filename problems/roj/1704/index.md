---
oj: "roj"
problem_id: "1704"
title: "奇特的猫"
description: "每天的字符串集合是前缀封闭的，恰为一棵 Trie 的结点集；编辑距离就是树上距离。三天答案化为子树大小、换根距离和与一次 LCA 配对 DP。"
difficulty: "提高+/省选-"
date: 2026-10-07 17:18
updated: 2026-10-07 17:18
toc: true
favorite: false
favorite_reason: ""
tags:
  - 字符串
  - Trie
  - 树形DP
  - 换根DP
  - python
categories:
  - 字符串
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1704
---

[[TOC]]

## 形式化题目

键盘只有两种操作：敲一个字符（追加到串尾）、按退格（删除串尾一个字符）。三天各给出
一串按键（$ASCII$ 值，退格是 $8$），记第 $d$ 天"屏幕上出现过的所有串（含空串）"为集合
$S_d$，即 $A, B, C$。同一个集合内的距离为编辑距离

$$d(P, Q) = |P| + |Q| - 2 \cdot \mathrm{LCP}(P, Q),$$

其中 $\mathrm{LCP}$ 是最长公共前缀长度。$\mathrm{LCP}$ 的定义本身就说明 $S_d$ 是**前缀封闭**的。

**第 1 天**：求 $A$ 内所有无序对的距离之和 $W(A)$，最小值和最大值相同。

**第 2 天**：选定特殊串 $A_0 \in A$、$B_0 \in B$，规定跨集合的距离为
$d(P, Q) = d(P, A_0) + 1 + d(B_0, Q)$（$P \in A, Q \in B$）。求
$\sum_{P \in A} \sum_{Q \in B} d(P, Q)$ 的最小值与最大值。

**第 3 天**：选定 $A_0 \in A$、$B_0, B_1 \in B$（可相同）、$C_0 \in C$，跨集合距离规定为

$$d(A,B) = d(P,A_0)+1+d(B_0,Q), \quad d(B,C) = d(P,B_1)+1+d(C_0,Q),$$
$$d(A,C) = d(P,A_0)+1+d(B_0,B_1)+1+d(C_0,Q).$$

求 $\sum_{P \in A}\sum_{Q \in B} + \sum_{P \in B}\sum_{Q \in C} + \sum_{P \in A}\sum_{Q \in C}$ 的最小值与最大值。

输出三行，每行两个整数（该天的最小值与最大值）。

以样例 1 为例，三天按键分别是 `97`、`97`、`97 8 97 8`，于是
$A = \{\varepsilon, \texttt{a}\}$、$B = \{\varepsilon, \texttt{a}\}$、
$C = \{\varepsilon, \texttt{a}\}$（第三个串敲 `a`、退格、再敲 `a`，集合没有新增元素）。
第 1 天 $W(A) = d(\varepsilon, \texttt{a}) = 1$；第 2 天取 $A_0 = B_0 = \varepsilon$ 时
$A \times B$ 四对距离之和是 $1 + 1 + 1 + 3 = 6$，但取 $A_0 = B_0 = \texttt{a}$ 时是 $10$——
无论怎么取都是 $10$，故输出 `10 10`。

## 正解

### 思路

**关键观察一：集合就是 Trie 的结点集。** 光标永远在串尾，敲字符 = 从当前结点走一个孩子，
退格 = 回父结点。所以"屏幕出现过的串"就是走出来的所有结点，$S_d$ 恰好是这棵 Trie 的
**结点集合**（含根 = 空串），而

$$d(P, Q) = |P| + |Q| - 2\,\mathrm{LCP}(P,Q) = \mathrm{depth}(P) + \mathrm{depth}(Q) - 2\,\mathrm{depth}(\mathrm{lca}(P,Q))$$

正是树上距离。记 $n_d = |S_d|$，它就是 Trie 的结点数。于是三天的问题全部变成
**树上距离的统计**。

**关键观察二：跨集合的那 $1$ 个单位可以摊到每个串上。** 第 2 天固定 $A_0, B_0$ 后

$$
\sum_{P \in A}\sum_{Q \in B} d(P,Q)
= \underbrace{\sum_{P \in A}\sum_{Q \in B}\bigl[d(P,A_0) + d(B_0,Q)\bigr]}_{n_B \cdot D_A[A_0] \;+\; n_A \cdot D_B[B_0]} + \; n_A n_B,
$$

其中 $D_S[v] = \sum_{u \in S} d(v, u)$。注意 $A$、$B$ 内部的距离项一次都不出现：
第 2 天只统计 $A \times B$ 之间的对。

同理第 3 天的三项分别是

$$
\underbrace{n_B D_A[A_0] + n_A D_B[B_0] + n_A n_B}_{A \times B},\qquad
\underbrace{n_C D_B[B_1] + n_B D_C[C_0] + n_B n_C}_{B \times C},
$$
$$
\underbrace{n_C D_A[A_0] + n_A D_C[C_0] + n_C \cdot d(B_0,B_1) + 2 n_A n_C}_{A \times C}.
$$

把固定项合起来，第 3 天的总距离为

$$
\mathrm{base} + (n_B+n_C)D_A[A_0] + (n_A+n_B)D_C[C_0] + \underbrace{n_A D_B[B_0] + n_C D_B[B_1] + n_A n_C\, d(B_0,B_1)}_{\text{只有这一项需要 } B_0 \ne B_1},
$$

$$\mathrm{base} = W(A) + W(B) + W(C) + n_A n_B + n_B n_C + 2 n_A n_C .$$

最小值把三个 $D$ 都取到各自的最小值即可，而 $B_0 = B_1$ 时最后一项退化成
$(n_A + n_C)D_B$，正好是 $\min D_B$——所以

$$\text{day3min} = \mathrm{base} + (n_B+n_C)\min D_A + (n_A+n_B)\min D_C + (n_A+n_C)\min D_B .$$

（用一个恒等式可以自检：取 $B_0 = B_1$ 时括号里恰好还原成 $(n_A+n_C)D_B$。）

**关键观察三：三个基础统计量都是一次 DFS。** 设结点数 $n$、子树大小 $\mathrm{sz}$：

- $W = \sum_{v \ne \text{root}} \mathrm{sz}[v]\cdot (n - \mathrm{sz}[v])$——每条边 $(p,v)$ 恰好被
  "一侧在子树内、一侧在子树外"的点对跨过；
- $D[\text{root}] = \sum_v \mathrm{depth}[v]$，换根 $D[v] = D[p] + n - 2\,\mathrm{sz}[v]$
  （从父结点走进子树，子树内 $n$ 个点里有 $\mathrm{sz}[v]$ 个近了 $1$，其余 $n - \mathrm{sz}[v]$ 个远了 $1$）；
- $\min D$、$\max D$ 扫一遍即可。

**最大值里的配对项。** 唯一麻烦的是第 3 天最大值的最后一项

$$\max_{x,y \in B}\Bigl[\, n_A D_B[x] + n_C D_B[y] + L\, d(x,y)\,\Bigr], \qquad L = n_A n_C .$$

代入 $d(x,y) = \mathrm{depth}(x) + \mathrm{depth}(y) - 2\,\mathrm{depth}(\mathrm{lca}(x,y))$，令

$$f[v] = n_A D_B[v] + L\,\mathrm{depth}[v], \qquad g[v] = n_C D_B[v] + L\,\mathrm{depth}[v],$$

就得到 $\max_{x,y}\bigl[f[x] + g[y] - 2L\,\mathrm{depth}(\mathrm{lca}(x,y))\bigr]$。
按 $\mathrm{lca}$ 分类：对每个结点 $v$ 只统计"$\mathrm{lca}$ 恰好是 $v$"的配对，一共三种

1. $x = y = v$：值 $f[v] + g[v]$；
2. 一端是 $v$、另一端在某个孩子子树 $c$ 内：$\max\bigl(f[v] + \mathrm{best1}[c],\ \mathrm{best0}[c] + g[v]\bigr)$，
   其中 $\mathrm{best0}[v] = \max_{u \in \text{subtree}(v)} f[u]$，$\mathrm{best1}$ 同理对 $g$；
3. 两端分别在两个**不同**的孩子子树里：边合并边记"已合并子树的最值"
   （$\mathrm{other0} + \mathrm{best1}[c]$ 与 $\mathrm{other1} + \mathrm{best0}[c]$），
   这样天然保证两端来自不同子树，$\mathrm{lca}$ 正好是 $v$。

三种情况都算完再减去 $2L\,\mathrm{depth}[v]$，对所有 $v$ 取 $\max$ 即可。

**实现上的两个简化。** 一是建 Trie 时**按创建顺序给结点编号**，父结点的编号一定小于子结点，
于是"按编号倒序扫一遍"就是子树大小的拓扑序，"正序扫一遍"就是换根 DP 的拓扑序，
连显式 DFS 都不用写。二是孩子查找：把 $(u, c)$ 编码成 $u \cdot 256 + c$ 后塞进一张
开放寻址的哈希表，这样是 $O(1)$ 而不是遍历孩子链表——退化成菊花形的 Trie 也不会变慢。

**关于数据。** 本题素材目录里带 `data.py`（生成器），说明 `data/` 是自造的，
题面也是网络重建版本，出题意图与官方原题可能存在偏差。第 10 个点是 $|S| = 10^6$ 的
**单条链**（生成器注释写的是"最坏结构"），此时 Trie 深度达到 $10^6$，答案里出现
$1.67 \times 10^{17}$ 量级的数——必须全程 `long long`。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- **时间**：每个按键摊到 $O(1)$，一天的处理是 $O(\text{按键数} + n_d)$。
  生成器给的最坏点是三天的 $|S|$ 都是 $10^6$，按键数各为 $2(|S|-1)$，总操作量约
  $6 \times 10^6$，实测 C++ 在限时 1000 ms 内轻松通过。第 3 天的配对 DP 只对 $B$ 做一次，
  $O(n_B)$。
- **空间**：单天 Trie 的结点数上界 $10^6 + 1$，结点用 struct 数组存，配
  $2^{22}$ 的开放寻址哈希表（装载因子 $\le 1/4$），再加两个 `long long` 的 DP 数组，
  峰值约 80 MB，限时内存 256 MB。
- **与 C++ 解法的关系**：`main.py` 用同一套公式和同一套 Trie，只是把"孩子哈希表"
  换成 Python 的 `dict`（键同样是 `u * 256 + c`），把换根 DP 与配对 DP 写成倒序扫编号的
  `for` 循环。Python 侧的主要风险是 $|S| = 10^6$ 那一点会 TLE / MLE（`dict` 与三个
  长度为 $10^6$ 的 list 开销都在数百 MB 量级），算法本身与 C++ 同阶。

## 总结

- **把操作序列翻译成树**：光标在串尾 + 退格回退，等价于在 Trie 上走一条路径，
  "出现过的所有串"就是访问过的结点集合。这一步之后，字符串的编辑距离问题
  就完全变成了树上距离问题。
- **前缀封闭是关键结构**：$S$ 是 Trie 的结点集而非任意字符串集合，
  所以 $|S|$ 可以直接当结点数用，子树大小也有明确含义。
- **跨集合的那 $1$ 个单位可摊分**：$d(P,Q) = d(P,A_0) + 1 + d(B_0,Q)$ 拆开后，
  只有三个"距离和" $D_S[\cdot]$ 参与优化，其余都是与选择无关的固定项，
  于是最小/最大只需在 $\min D$ / $\max D$ 上取值。
- **$B_0 \ne B_1$ 才带来真正的难度**：最大值里出现 $d(B_0,B_1)$，
  用 $\mathrm{lca}$ 拆项后变成"在每个结点上合并两棵不同子树的最值"，
  这是典型的树形 DP 合并套路。
- **编号即拓扑序**：按创建顺序给 Trie 结点编号，父结点编号恒小于子结点，
  于是子树大小与换根 DP 都退化成一次数组扫描，省掉显式 DFS 和递归栈。
