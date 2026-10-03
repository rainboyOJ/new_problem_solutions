---
oj: "luogu"
problem_id: "P9248"
title: "[集训队互测 2018] 完美的集合"
description: "按最高价值筛出连通块集合，用「最浅合法测试点」分解成树上背包计数，再对答案套 5^23 的幂次型组合数取模。"
difficulty: "省选/NOI-"
date: 2026-10-02 15:07
updated: 2026-10-03 12:16
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P9248
---

[[TOC]]

## 形式化题目

给定一棵 $N$ 个点的带权树，点 $i$ 有重量 $w_i$ 与价值 $v_i$，边有长度。称一个点集 $S$ 是**连通块**，若 $S$ 非空且 $S$ 在树上诱导的子图连通。记
$$W(S)=\sum_{i\in S} w_i,\qquad V(S)=\sum_{i\in S} v_i .$$
令 $V^\*=\max\{V(S):W(S)\leqslant M,\ S \text{ 连通}\}$，把满足 $V(S)=V^\*$ 的连通块 $S$ 称为**完美的集合**；记完美集合的全体为 $\mathcal P$。

对一个完美集合 $S$ 与一个点 $x$，称 $x$ **适用于** $S$，若
$$x\in S\quad\text{且}\quad \forall y\in S:\ \operatorname{dist}(x,y)\cdot v_y\leqslant M\!ax .$$
把满足上式的 $x$ 全体记为 $W(S)$（每个集合的「合法测试点」集合）。

求无序的 $K$ 元组 $\{S_1,\dots,S_K\}\subseteq\mathcal P$（允许相同元素出现，即按可重集合计数）的个数，使得存在一个点 $x$ 同时适用于所有 $S_i$，即 $\bigcap_{i=1}^{K}W(S_i)\neq\varnothing$。答案对 $11920928955078125=5^{23}$ 取模，其中 $K\leqslant 10^9$，故必须支持大 $K$ 的组合数取模。

**样例推演。** 对样例，完美集合只有
$$\{1,2,5\},\quad\{1,4\},\quad\{2,6\},$$
价值均为 $3$。可验证同时适用于前两个集合的点 $x=1$，适用于第一、三个集合的点 $x=2$，而第二、三个集合没有公共合法测试点。因此答案为 $2$。

## 正解

### 思路

**第一步：把「存在公共测试点」改写成对单点的计数。**

对点 $x$ 记可行域
$$B_x=\{y:\operatorname{dist}(x,y)\cdot v_y\leqslant Max\},$$
它总是包含 $x$（$\operatorname{dist}(x,x)=0$）。再记
$$A_x=\#\{S\in\mathcal P:\ x\in S\subseteq B_x\}.$$
即 $A_x$ 是「以 $x$ 为测试点时 $x$ 能负责的完美集合数」。

关键观察是：$W(S)$ 恒**连通**。若 $x,z\in W(S)$，则对 $S$ 中任一点 $y$，$y$ 落在 $x$ 到 $z$ 的树上路径上的点 $u$ 满足 $\operatorname{dist}(u,y)\leqslant\max\{\operatorname{dist}(x,y),\operatorname{dist}(z,y)\}$，故 $u\in W(S)$。于是 $W(S)$ 是 $S$ 的一棵子树，**非空子树有唯一的最靠近根的点**。取原树以 $1$ 为根，令
$$x^\*(S)=\text{「}W(S)\text{ 中最浅的点」}.$$
对每个 $x$ 统计「$x^\*(S)=x$」的 $S$ 个数，再用「$K$ 个集合都含 $x$」减去「$K$ 个集合都含 $x$ 与 $x$ 的父亲」：

$$\boxed{\ \text{answer}=\sum_{x=1}^{N}\left[\binom{A_x}{K}-\binom{A_x\cap A_{\mathrm{fa}(x)}}{K}\right]\ }$$

其中 $A_x\cap A_{\mathrm{fa}(x)}$ 表示同时含 $x$、$\mathrm{fa}(x)$ 且被 $B_x\cap B_{\mathrm{fa}(x)}$ 包住的完美集合数，根的该项取 $0$。等号右侧每一项都是 $K$ 元可重组合，因为「集合可重复选取」。样例中 $A_1=A_2=2$，$A_4=A_5=A_6=1$，$A_3=A_7=0$；各对父子交集分别为 $A_1\cap A_2=1$、$A_1\cap A_4=1$、$A_2\cap A_5=1$、$A_2\cap A_6=0$，求和得 $\binom22-\binom12+\binom22-\binom11+\binom12-\binom11+\binom11-\binom01=1+1+1+1-1=2$。

**第二步：用树上背包求出每个 $A_x$ 与每个父子交集。**

先求 $V^\*$：一次树上背包算出「必选某点并向外扩展」的最大价值（此处对每个点做一次 DFS 序背包，见下）。

再求 $A_x$。对固定 $x$，只允许使用 $B_x$ 中的点，求「含 $x$、总重量 $\leqslant M$、总价值恰为 $V^\*$」的连通块个数。直接做树上背包是 $O(N M^2)$，无法接受；改用 **DFS 序背包**：把树按 DFS 序拍成序列，$f_i[\ ]$ 表示处理到第 $i$ 个位置。位置 $i$ 对应点 $p_i$：

- **选** $p_i$（仅当它已与已选部分连通、且 $p_i\in B_x$）：转移到 $i+1$，重量加上 $w_{p_i}$，价值加上 $v_{p_i}$；
- **不选** $p_i$：$p_i$ 的整棵子树都不能再选（否则不连通），直接跳到 $i+\mathrm{size}(p_i)$。

对每个 $i$ 维护「重量 $\to$ (最大价值, 该最大价值的方案数)」的数组，容量截断到 $M$。这样单次复杂度 $O(NM)$，状态数 $NM$ 且转移 $O(1)$。

计数细节：$B_x$ 之外的点的子树全部强制跳过；强制 $x$ 被选（从 $x$ 所在位置先「必选」一次）。答案规模不超过 $2^{59}+59$（星形树、$w\equiv1$ 时连通块最多），恰好放得下 `unsigned long long`，所以模 $5^{23}$ 之前用 64 位整数无损保存，最后再做一次取模。

对父子交集，把「必选的点集」改成 $\{x,\mathrm{fa}(x)\}$、可行域改成 $B_x\cap B_{\mathrm{fa}(x)}$，同一套 DFS 序背包即可（沿路径强制选中，其余点仍按子树跳步）。总复杂度仍是 $O(N)$ 次 $O(NM)$ 背包。

**第三步：$\binom{n}{K}\bmod 5^{23}$。**

$n$ 可达 $2^{59}$，$K\leqslant10^9$，模数是素数幂 $5^{23}$。常规扩展 Lucas（预处理长度 $5^{23}$ 的阶乘前缀积）不可能，需要 **Granville 的素数幂 Lucas 定理**：把 $n,k,n-k$ 展开成 $5$ 进制数字 $n_j,k_j,r_j$，令进位 $e_j$ 满足
$$k_j+r_j+e_j=n_j+p\,e_{j+1},\qquad e_0=0,$$
则
$$v_5\binom nk=\sum_{j\geqslant0}e_{j+1},$$
并且当 $v_5\binom nk<23$ 时
$$\binom nk \equiv 5^{\,v_5\binom nk}\cdot(-1)^{\sum_{j\geqslant23\ \text{之后的有效进位}}}\cdot\prod_{j\geqslant0}\frac{n_j!}{k_j!\,r_j!}\pmod{5^{23}} .$$
本题 $K\leqslant10^9$ 至多 $13$ 位 $5$ 进制，$n<5^{27}$，故只需枚举前 $27$ 位数字，逐位算小阶乘并处理进位符号即可，复杂度 $O(\log_5 n)$。

**取模不是素数。** 且 $K$ 可以大于 $n$（此时 $\binom nK=0$），以及 $v_5\binom nK\geqslant23$ 时答案也是 $0$，都要显式判断。由于 $K$ 相同，$\sum_x$ 的每一项都用同一个 $K$ 做一次上述计算，共 $O(N\log_5 n)$ 次。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 树形预处理（距离、DFS 序、子树大小）：$O(N^2)$。
- 每次 DFS 序背包：$O(NM)$；共需 $1$ 次求 $V^\*$、$N$ 次求 $A_x$、$N-1$ 次求父子交集，即 $O(N)$ 次背包，总计 $O(N^2M)=60^2\times10^4\approx3.6\times10^7$。
- 组合数：每组 $O(\log_5 n)$，共 $O(N\log_5 n)$。
- 空间：背包一维长度 $M+1$，加树结构，$O(NM)$ 量级以内。

## 总结

整道题由三层拼成：**几何/树结构层**把「存在公共测试点」这一全局条件，经由「合法测试点集合恒是子树」这一观察，分解为对每个点 $x$ 的「最浅测试点恰为 $x$」计数，于是答案化成父子差分的组合数求和；**背包层**用 DFS 序跳步把「含指定点的连通块」计数从 $O(NM^2)$ 降到 $O(NM)$，并把 $A_x$ 的数值在 64 位内无损算出；**数论层**用 Granville 定理处理 $K$ 很大而模数为 $5^{23}$ 的组合数。

三个难点彼此独立，任何一个环节写错都会在样例之后的测试点上暴露。特别要注意：`答案计数是 K 元可重组合（集合可重复选）`、`v_5(C(n,K)) >= 23 或 K > n 时组合数为 0`、以及 `A_x 必须满足 S 含 x 且 S ⊆ B_x` 这三个边界。
