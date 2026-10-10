---
oj: "roj"
problem_id: "1724"
title: "小K的农场"
description: "把三种记忆化成 x_v≤x_u+w 的差分约束边，加超级源点后用 SPFA 判负环：无负环则输出 Yes，有负环则输出 No。"
difficulty: "普及+/提高-"
date: 2026-10-07 18:46
updated: 2026-10-07 18:46
toc: true
tags:
  - 图论
  - 差分约束
  - 最短路
  - SPFA
  - python
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1724
---

[[TOC]]

## 形式化题目

给定 $n$ 个变量 $x_1,\dots,x_n$ 与 $m$ 条约束，约束有三种形式：

- `1 a b c`：$x_a - x_b \geqslant c$（农场 $a$ 至少比 $b$ 多 $c$）；
- `2 a b c`：$x_a - x_b \leqslant c$（农场 $a$ 至多比 $b$ 多 $c$）；
- `3 a b`：$x_a = x_b$。

判断是否存在一组赋值同时满足全部约束，满足输出 `Yes`，否则输出 `No`。
约束中 $1 \leqslant n, m, a, b, c \leqslant 10000$。

## 正解

### 思路

三类约束都是**变量差值**的限制，这正是**差分约束系统**的标准形状：把每条约束改写成
$x_v \leqslant x_u + w$ 的形式，再在图上连一条 $u \to v$ 权 $w$ 的有向边。逐条化边：

1. $x_a - x_b \geqslant c \iff x_b \leqslant x_a + (-c)$：连边 $a \to b$，权 $-c$；
2. $x_a - x_b \leqslant c \iff x_a \leqslant x_b + c$：连边 $b \to a$，权 $c$；
3. $x_a = x_b$：双向各连一条权 $0$ 的边。

化完之后，"存在一组赋值满足全部约束" $\iff$ 图中**没有负环**。直觉是：若存在负环
$u_1 \to u_2 \to \cdots \to u_k \to u_1$，沿环把所有不等式相加得到 $0 \leqslant (\text{负数})$，
矛盾；反之无负环时，以超级源点为起点跑单源最短路，令 $x_i = \mathrm{dist}(i)$，
每条边的松弛不等式 $\mathrm{dist}(v) \leqslant \mathrm{dist}(u) + w$ 恰好就是原约束，即得到一组可行解。

图可能不连通，因此加**超级源点** $0$，向每个农场连一条权 $0$ 的边，从 $0$ 一次
SPFA 即可判完整张图。判据用 Bellman-Ford 队列法的标准写法：统计每个点的入队次数，
某点入队次数超过点数（含源点，即 $n+1$）即存在负环，输出 `No`；跑完未发现负环输出 `Yes`。

本题只问可行性、不问具体赋值，且所有约束只限制差值（解可整体平移），
所以不需要关心作物数量是否非负——可行性判据与平移无关。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

两份代码是同一算法：先按三种记忆建边，再加超级源点，SPFA 判负环。
C++ 版用静态链式前向星存图，Python 版用邻接表 + `deque`，均为标准库实现。

### 复杂度

- 时间：SPFA 均摊接近 $O(km)$（$k$ 为点松弛轮数），边数 $2m + n \leqslant 3\times 10^4$，
  实测 10 个数据点均为毫秒级；最坏退化情形 $O(nm)$，本题规模下不会触发。
- 空间：$O(n + m)$，两个版本实测峰值内存均在 10 MB 以内。

## 总结

差分约束的套路是固定的：**约束改写成 $x_v \leqslant x_u + w$ → 建边 → 加超级源点 →
SPFA/Bellman-Ford 判负环**。关键在于把"至少多 $c$"翻译成 $-c$ 权的边方向，
以及记住"可行 $\iff$ 无负环"这一判据；只问可行性时无需还原具体赋值。

---

### 数据与验证说明（如实记录）

- 素材源 `std.cpp` 已在真实数据 `data/` 的 10 个点上全部实跑，与 `.out` 完全一致，
  故作为算法参考使用；本题解的两份代码为独立改写，未照抄。
- 样例（1 组）：`main.cpp` 与 `main.py` 实际输出均为 `Yes`，与期望一致。
- 真实数据：`main.cpp` 经 `check_sample.py` 验证 10/10 PASS；`main.py` 用同样
  `.in` 逐点运行并与 `.out` 比对，10/10 一致。
- 本题素材源附带 `data.py` 生成脚本（cyaron 分层造数据），说明 `data/` 为自造测试
  数据；题面与一本通 1724 / 洛谷 P1993 逐字一致，但本仓验证结论仅对随仓数据成立，
  不等同于官方 OJ 的 AC 判定。
