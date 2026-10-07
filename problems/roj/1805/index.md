---
oj: "roj"
problem_id: "1805"
title: "数数"
description: "把 popcount 按位拆成 floor 差分，用类欧几里得在 O(log) 内求出每位的 1 的个数，全程 __int128 防溢出。"
difficulty: "提高+/省选-"
date: 2026-10-08 04:20
updated: 2026-10-08 04:20
toc: true
tags: ["数学", "类欧几里得", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1805
---

[[TOC]]

## 形式化题目

给出等差数列的末项偏移 $B$、公差 $A$ 与项数 $N$，数列的第 $i$ 项为

$$x_i = B + i \cdot A, \qquad i = 1, 2, \dots, N .$$

记 $\operatorname{popcount}(x)$ 为 $x$ 的二进制表示中 $1$ 的个数，求

$$S = \sum_{i=1}^{N} \operatorname{popcount}(x_i).$$

共有 $T$ 组询问，每组给出 $A, B, N$：

$$1 \leqslant T \leqslant 20, \quad 1 \leqslant A \leqslant 10^4, \quad 1 \leqslant B \leqslant 10^{16}, \quad 1 \leqslant N \leqslant 10^{12}.$$

由范围可知最大项 $B + N \cdot A \leqslant 10^{16} + 10^{12} \times 10^4 = 2 \times 10^{16} < 2^{55}$，
即所有数都落在 $55$ 个二进制位以内。

## 正解

### 思路

**朴素做法。** 逐项求出 $B + i\cdot A$，用二进制计数函数累加。单组 $O(N)$，
而 $N$ 可达 $10^{12}$，限时 $1000$ ms 下最多跑 $10^8$ 量级，必然超时。
瓶颈在于"逐项"——必须改成"按位整体统计"。

**观察一：按位拆分。** 一个数 $x$ 的第 $k$ 位是不是 $1$，取决于
$\lfloor x / 2^k \rfloor$ 的奇偶性。利用向下取整，可以把这一位的取值写成一个精确的差分：

$$\operatorname{bit}_k(x) = \left\lfloor \frac{x}{2^k} \right\rfloor - 2 \left\lfloor \frac{x}{2^{k+1}} \right\rfloor \in \{0, 1\}.$$

对整列求和，位与位之间互不干扰，答案就是各位贡献之和：

$$S_k = \sum_{i=1}^{N} \left\lfloor \frac{B + i\cdot A}{2^k} \right\rfloor, \qquad
S = \sum_{k \geqslant 0} \left( S_k - 2\,S_{k+1} \right).$$

因为最大项小于 $2^{55}$，$k$ 只需枚举到 $2^k > B + N\cdot A$ 为止，至多 $55$ 个非零项。
问题于是化为：**怎样快速求出 $S_k$？**

**观察二：$S_k$ 是类欧几里得能处理的形状。** 把下标平移一下：

$$S_k = \sum_{i=1}^{N} \left\lfloor \frac{A\cdot i + B}{2^k} \right\rfloor
     = \sum_{j=0}^{N-1} \left\lfloor \frac{A\cdot j + (A + B)}{2^k} \right\rfloor
     = f\!\left(A,\; A+B,\; 2^k,\; N-1\right),$$

其中定义通用和式

$$f(a, b, c, n) = \sum_{i=0}^{n} \left\lfloor \frac{a \cdot i + b}{c} \right\rfloor .$$

它的几何意义是直线 $y = \dfrac{a x + b}{c}$ 在 $x \in [0, n]$ 上盖住的整点个数
（含边界，取直线下方/线上的整点）。注意 $S_k$ 中 $a = A$ 固定，只有 $c = 2^k$ 在变，
所以每组数据的 $55$ 次调用共享同一个 $a$。

**观察三：$f$ 的化简与辗转相除同构。** 分两种情况。

*情况 A：$a \geqslant c$ 或 $b \geqslant c$。* 把整除部分直接拆出来：

$$\left\lfloor \frac{a i + b}{c} \right\rfloor
= \left\lfloor \frac{a}{c} \right\rfloor i + \left\lfloor \frac{b}{c} \right\rfloor
+ \left\lfloor \frac{(a \bmod c)\, i + (b \bmod c)}{c} \right\rfloor,$$

对 $i = 0..n$ 求和即得

$$f(a, b, c, n) = \frac{n(n+1)}{2}\left\lfloor \frac{a}{c} \right\rfloor
  + (n+1)\left\lfloor \frac{b}{c} \right\rfloor
  + f(a \bmod c,\; b \bmod c,\; c,\; n).$$

*情况 B：$a < c$ 且 $b < c$。* 此时斜率小于 $1$，改用**转置坐标轴**计数：
把"对每个 $x$ 数 $y$ 的下方整点"换成"对每个 $y$ 数 $x$ 的右侧整点"，用补集相减即可得到

$$f(a, b, c, n) = n \cdot m - f\!\left(c,\; c - b - 1,\; a,\; m - 1\right),
\qquad m = \left\lfloor \frac{a n + b}{c} \right\rfloor .$$

推导要点：$m$ 是最大纵坐标，若 $m = 0$ 则一个整点都没有，直接返回 $0$；
否则在矩形 $[0, n] \times [1, m]$ 中，直线严格上方的整点数可用"总数减下方数"算出，
再换成 $y$ 为自变量、$x$ 为因变量后，系数 $(c, a)$ 互换，其中 $-1$ 来自严格不等号
到非严格不等号的边界调整。这一步把 $c$ 与 $a$ 的角色对调，
下一次递归必然进入情况 A 并对新 $c$ 取模，因此参数按 $c \bmod a$ 的速度衰减，
递归深度为 $O(\log \max(a, c))$——这正是"类欧几里得"的名字来源。

**汇总。** 每组数据枚举 $k = 0, 1, \dots$（$2^k \leqslant B + N\cdot A$），
累加 $f(A, A+B, 2^k, N-1) - 2 f(A, A+B, 2^{k+1}, N-1)$ 即可。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- **时间**：单次 $f$ 的递归深度为 $O(\log \max(a, c)) = O(55)$，
  每组数据枚举至多 $55$ 个二进制位，故单组 $O(55^2)$，即常数级；
  总时间 $O(T \cdot \log^2(\text{值域}))$，实测 20 组顶格数据远低于 1 ms。
- **空间**：递归深度不超过 $55$ 层，$O(\log(\text{值域}))$，可视为 $O(1)$。
- **与 C++ 解法的关系**：`main.cpp` 与 `main.py` 是同一算法。
  两者的唯一差别是整数宽度：$n(n+1)/2$、$a\cdot n + b$、$n \cdot m$ 这些中间量
  会达到 $10^{24}$ 量级，C++ 必须用 `__int128`（`long long` 只有约 $1.8 \times 10^{19}$），
  而 Python 的整数天然任意精度，不需要额外处理，也不需要担心 $1 \ll 31$ 之类的移位溢出。

## 总结

- **"数 $1$ 的个数"总是先想按位拆**：$\operatorname{bit}_k(x) = \lfloor x/2^k \rfloor - 2\lfloor x/2^{k+1} \rfloor$
  把 popcount 变成两个 floor 之和的差，$\sum \lfloor \cdot \rfloor$ 才可能上数据结构或数论算法。
- **$S_k$ 只差一个 $c = 2^k$**：数列是等差数列，$a = A$ 恒定不变，
  这也是可以复用同一套类欧几里得代码的原因。
- **类欧几里得就是"取模 + 坐标轴转置"交替**：斜率大就拆整数部分（取模），
  斜率小于 $1$ 就转置坐标轴（把 $c$ 与 $a$ 互换），两个动作轮流把参数压到对数级。
- **溢出是本题的头号实现坑**：$N \leqslant 10^{12}$、$B \leqslant 10^{16}$ 时，
  $n(n+1)/2$ 级别为 $10^{24}$，C++ 必须 `__int128` 全程参与运算；
  Python 无此问题，但要注意别用 `float`。
- **该素材源自带数据生成脚本（`data.py` / `gen.*`），说明测试数据是自造的**，
  题面也属于网络重建（同名原题见 JZOJ 3492 /【NOIP2013模拟联考12】数数）。
  因此本解以题面给出的范围为唯一依据，验证只保证"样例 + 仓库 data/ 全过"，
  不代表官方数据通过。
