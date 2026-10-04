---
oj: "luogu"
problem_id: "P9248"
title: "[集训队互测 2018] 完美的集合"
description: "按最大点权和筛出连通块，用「最浅合法测试点」把存在公共测试点拆成单点计数，DFS 序背包 O(N²M) 求各 A_x，再算 C(A_x,K) mod 5^23（注意 A_x 要精确到 u64、方案数不能取模）。"
difficulty: "省选/NOI-"
date: 2026-10-02 15:07
updated: 2026-10-03 18:30
toc: true
tags: ["树形 DP", "背包", "组合数", "数论", "DFS 序"]
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

给定一棵 $N$ 个点的带权树，点 $i$ 有重量 $w_i$ 与价值 $v_i$（$v_i$ 可为 $0$），边有长度。记点集 $S$ 的重量 $W(S)=\sum_{i\in S} w_i$、价值 $V(S)=\sum_{i\in S} v_i$。

称非空连通点集 $S$ 为**完美的集合**，若它的价值是「重量不超过 $M$ 的连通点集」中最大的，即

$$
V^\*=\max\{V(S): W(S)\le M,\ S\text{ 非空连通}\},\qquad S\in\mathcal P\iff V(S)=V^\* .
$$

对一个点 $x$，称 $x$ **适用于** $S$（是 $S$ 的合法测试点），若

$$
x\in S\quad\text{且}\quad \forall y\in S:\ \operatorname{dist}(x,y)\,v_y\le Max .
$$

求从 $\mathcal P$ 中选出 $K$ 个**互不相同**的集合（无序）的方案数，使得存在一个点 $x$ 同时适用于这 $K$ 个集合，即它们合法测试点集合的交非空。答案对 $11920928955078125=5^{23}$ 取模。

$N\le 60$，$M\le 10^4$，$K\le 10^9$，$Max\le 10^{18}$。

**样例推演。** 样例的完美集合只有 $\{1,2,5\},\{1,4\},\{2,6\}$（价值均为 $3$）。同时适用于前两个的点 $x=1$，适用于第一、三个的点 $x=2$，而第二、三个没有公共测试点，故选 $K=2$ 个的方案数为 $2$。

## 暴力解法

### 思路

$N$ 只有几十，最直接的想法是把所有点集都枚举出来：

1. 枚举所有非空子集（$2^N$ 个），先按重量 $W(S)\le M$ 筛掉一部分，再用一次 BFS/DFS 检查它在树上是否连通；
2. 在所有「连通且重量达标」的集合里求出最大价值 $V^\*$，把价值等于 $V^\*$ 的集合收进 $\mathcal P$；
3. 对每个完美集合 $S$，枚举 $x\in S$ 检查它是否合法（对 $S$ 内每个 $y$ 验证 $\operatorname{dist}(x,y)v_y\le Max$），得到 $S$ 的合法测试点集合；
4. 暴力枚举 $\mathcal P$ 的所有 $K$ 元组合，检查这 $K$ 个集合的合法测试点集合是否有交。

### 代码

@include-code(./brute.cpp, cpp)

### 复杂度

枚举子集 $O(2^N\cdot N^2)$，求合法点 $O(|\mathcal P|\cdot N^2)$，枚举 $K$ 元组合 $O(\binom{|\mathcal P|}{K}\cdot NK)$。对 $N\le 15$、$K\le 4$、$|\mathcal P|$ 较小的数据完全可行，但对 $N=60$、$K=10^9$ 完全不可行——光枚举子集就是 $2^{60}$。

### 瓶颈

瓶颈有两个。第一是「枚举子集求完美集合」本身，第二——也是更要紧的——是**最后一步的组合**。$K$ 可以到 $10^9$，就算 $\mathcal P$ 只有几千个集合，枚举 $K$ 元组合也天文数字。这说明最后的方案数一定可以用**组合数**整体表示，而不需要真的把组合选出来。这是正解的突破口。

## 正解

### 思路

#### 一、把「存在公共测试点」拆成单点计数

记点 $x$ 的**可行域**

$$
B_x=\{y:\operatorname{dist}(x,y)\,v_y\le Max\},
$$

它总含 $x$（$\operatorname{dist}(x,x)=0$）。于是 $x$ 适用于 $S$ 当且仅当 $x\in S\subseteq B_x$。

**关键观察：一个集合的合法测试点全体 $W(S)$ 恒连通。** 若 $x,z\in W(S)$，取 $x$ 到 $z$ 的树上路径上任一点 $u$。树度量满足 $\operatorname{dist}(u,y)\le\max\{\operatorname{dist}(x,y),\operatorname{dist}(z,y)\}$（投影性质），所以

$$
\operatorname{dist}(u,y)\,v_y\le \max\{\operatorname{dist}(x,y)v_y,\ \operatorname{dist}(z,y)v_y\}\le Max,
$$

即 $u$ 也合法，且 $u\in S$（$S$ 连通）。故 $W(S)$ 是 $S$ 里的连通块。

把树以 $0$ 为根。一棵连通子树有唯一**最浅点**。对一组选出的 $K$ 个集合 $T$，设

$$
X=\bigcap_{S\in T} W(S)\neq\varnothing,
$$

$X$ 是若干连通子树的交，仍是连通子树，故有唯一最浅点 $x^\*$。按 $x^\*$ 分类计数，每组 $T$ 恰好被统计一次：

$$
\#\{T\}=\sum_{x}\big[\#\{T:\ x\in X\}-\#\{T:\ x\in X,\ \operatorname{fa}(x)\in X\}\big].
$$

记

$$
A_x=\#\{S\in\mathcal P:\ x\in S\subseteq B_x\},\qquad
C_x=\#\{S\in\mathcal P:\ \{x,\operatorname{fa}(x)\}\subseteq S\subseteq B_x\cap B_{\operatorname{fa}(x)}\},
$$

则「$x\in X$」要求 $K$ 个集合都从「以 $x$ 为合法测试点」的 $A_x$ 个里选，方案数 $\binom{A_x}{K}$；「$x$ 与父亲都在 $X$」要求从 $C_x$ 个里选，方案数 $\binom{C_x}{K}$（根没有父亲，该项为 $0$）。于是

$$
\boxed{\ \text{answer}=\sum_{x=1}^{N}\Big[\binom{A_x}{K}-\binom{C_x}{K}\Big]\ }
$$

**注意组合数是不放回的** $\binom{n}{K}$（选出 $K$ 个互不相同的集合）：样例里 $3$ 个完美集合选 $2$ 个、若允许重复会出现更多方案，与样例答案 $2$ 矛盾。当 $A_x<K$ 时 $\binom{A_x}{K}=0$。

**样例验证。** 以 $1$ 为根：$A_1=A_2=2$、$A_4=A_5=A_6=1$、$A_3=A_7=0$；父子交集 $C_2=C_4=C_5=C_6=1$（都是 $\{1,2,5\}$ 那一类），$C_3=C_7=0$，$C_1=0$（根）。代入：

$$
\binom22+\big(\binom22-\binom12\big)+\big(\binom11-\binom11\big)+\big(\binom11-\binom11\big)+\big(\binom11-\binom01\big)=1+1=2.\ \checkmark
$$

#### 二、DFS 序背包求 $A_x$ 与 $C_x$

先求 $V^\*$：对每个点 $r$ 强制选中 $r$，做一次背包取最大价值，$V^\*$ 是对所有 $r$ 取最大。

再对每个 $x$ 求 $A_x$。把树按 DFS 序拍成序列 $p_0,p_1,\dots,p_{N-1}$（以 $x$ 为根），维护 $f_i[\,]$ 表示处理到第 $i$ 个位置的状态，容量记**重量恰好为 $c$**（这是关键，见下）：

- **选** $p_i$：转移到 $i+1$，重量加 $w_{p_i}$，价值加 $v_{p_i}$；
- **不选** $p_i$：它的整棵子树都不能再选（否则与已选部分不连通），直接跳到 $i+\operatorname{size}(p_i)$。

每个状态记录「重量 $\to$（最大价值，达到最大价值的方案数）」。单次 $O(NM)$。

> **容量必须记「恰好为 $c$」而不是「不超过 $c」。** 如果记「不超过 $c$」，两个价值相同、重量不同的集合会在同一个状态上被合并、方案数相加，导致计数错误（本题一个隐蔽的坑）。记「恰好为 $c」则每个集合对应唯一的决策序列，互不干扰。

**方案数不能取模！** 求出的 $A_x$ 是后面组合数 $\binom{A_x}{K}$ 的**精确**输入——它依赖 $A_x$ 的 $5$ 进制展开，而不是 $A_x\bmod 5^{23}$。好在 $N\le 60$ 的树的连通点集个数最多是星形的 $2^{N-1}+N-1=2^{59}+59$，恰好放得下 `unsigned long long`，所以背包里的方案数用 `u64` 精确保存、全程不取模，最后组合时再取模。

求 $C_x$：把强制集合改成 $\{x,\operatorname{fa}(x)\}$、可行域改成 $B_x\cap B_{\operatorname{fa}(x)}$。为了让两个强制点落在 DFS 序的前缀上，把 $\operatorname{fa}(x)$ 安排成 $x$ 的第一个孩子（在 $x$ 为根的树里，父亲恰是它的一个孩子），同一套背包即可。总复杂度 $O(N)$ 次 $O(NM)$，即 $O(N^2M)=60^2\times10^4\approx3.6\times10^7$。

#### 三、组合数 $\binom{n}{K}\bmod 5^{23}$

$n$ 可达 $2^{59}$、$K\le 10^9$，模数是素数幂 $5^{23}$。扩展 Lucas 需要预处理长度 $5^{23}$ 的阶乘，不可能；用 **Granville 素数幂组合数**的变形：

把 $n!$ 里所有因子 $5$ 剥出来，记

$$
U(m)=\prod_{i=1}^{m}\big(i\text{ 去掉所有因子 }5\text{ 后的部分}\big)\pmod{5^{23}},\qquad
v_5(m!)=\sum_{j\ge1}\Big\lfloor\frac{m}{5^j}\Big\rfloor,
$$

则

$$
\binom{n}{K}=5^{\,v_5(n!)-v_5(K!)-v_5((n-K)!)}\cdot U(n)\cdot U(K)^{-1}\cdot U(n-K)^{-1}\pmod{5^{23}},
$$

指数 $\ge 23$ 时答案为 $0$。$U(m)$ 与 $5$ 互素故可逆。

$U(m)$ 有递归 $U(m)=U(\lfloor m/5\rfloor)\cdot G(m)$，其中

$$
G(m)=\prod_{\substack{i\le m\\ 5\nmid i}} i
=\Big[\prod_{r=1}^{4}\prod_{j<\lfloor m/5\rfloor}(5j+r)\Big]\cdot\prod_{r=1}^{m\bmod 5}\big(5\lfloor m/5\rfloor+r\big).
$$

而 $\prod_{j<t}(5j+r)$ 展开成以 $5$ 为变量的幂级数，系数是初等对称多项式 $e_k(0,1,\dots,t-1)$，它正是第一类 Stirling 数 $\bigl|{t\atop t-k}\bigr|$；这是关于 $t$ 的 $2k$ 次多项式，用牛顿级数 $\sum_i c_{k,i}\binom{t}{i}$ 求值（$c_{k,i}$ 是整数差分系数），其中 $\binom{t}{i}$（$i\le 46$）把阶乘里的因子 $5$ 剥掉再求逆元即可。单层 $O(\log_5 n)$，预处理 $O(46^2)$，单次求组合数 $O(\log_5 n\cdot 23\cdot 46)$。

**取模不是素数**，所以 $U(m)$ 里不能直接对普通阶乘求逆；上面全程只对「剥掉 $5$ 因子后的部分」求逆，规避了这个问题。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 树形预处理（最短路、DFS 序）：$O(N^3)$ 或 $O(N(N+E)\log N)$。
- 背包：$V^\*$、$N$ 个 $A_x$、$N-1$ 个 $C_x$，共 $O(N)$ 次 $O(NM)$，总 $O(N^2M)\approx3.6\times10^7$。
- 组合数：$O(N\log_5 n)$，可忽略。
- 空间：背包两维 $O(NM)$，最短路 $O(N^2)$，均在限制内。

## 总结

这道题由三层拼成，任何一层写错都会在样例之后暴露：

- **树结构层**：合法测试点集合 $W(S)$ 恒连通（树度量的投影性质），于是「存在公共测试点」可以按交集中**最浅的那个点**分解，答案化成 $\sum_x[\binom{A_x}{K}-\binom{C_x}{K}]$。
- **背包层**：DFS 序跳步把「含指定点的连通块」计数做到 $O(NM)$。两个要害：容量记**重量恰好为 $c$**（否则同价值不同重量的集合被合并漏解）；方案数**不取模、用 `u64` 精确保存**（因为组合数依赖 $A_x$ 的精确值，而连通块个数最多 $2^{59}+59$ 恰好放得下）。
- **数论层**：$\binom{n}{K}\bmod 5^{23}$ 用剥因子 $5$ 的 $U(m)$ 函数，只对 $5$-free 部分求逆，规避了模数不是素数、又无法预处理 $5^{23}$ 阶乘的困难。
- **边界**：组合数是不放回的（选出 $K$ 个互不相同集合）；$K>A_x$ 或 $K>|\mathcal P|$ 时对应项为 $0$；$v_5\binom{n}{K}\ge 23$ 时组合数为 $0$。
