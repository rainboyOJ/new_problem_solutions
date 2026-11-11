---
oj: "codeforces"
problem_id: "1288C"
title: "Two Arrays"
description: "三维动态规划 + 二维前缀和加速 + 单调性端点解耦 + 序列翻转拼接组合数"
difficulty: "1600"
date: 2026-11-11 15:06
updated: 2026-11-11 15:35
toc: true
tags: ["动态规划", "组合数学", "前缀和", "数学"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: ["rbook1:combinatorics", "rbook1:presum", "rbook1:mind_theory"]
rbookLinks:
  - id: "rbook1:combinatorics"
    reason: "运用隔板法与可重组合数模型，将序列翻转拼接后的非降约束转化为组合数直接求解"
  - id: "rbook1:presum"
    reason: "在动态规划实现中，利用二维与一维前缀和将区域累加转移优化至常数复杂度"
  - id: "rbook1:mind_theory"
    reason: "掌握状态解耦与对称翻转思维，将两组关联的约束转化为单调序列的整体拼接"
pre: []
common: []
recommend: []
source: https://vjudge.net/problem/CodeForces-1288C#author=translator:1281311:zh
---

[[TOC]]

## 形式化题目

给定正整数 $n$ 与 $m$。求满足下列全部约束的整数序列对 $(a, b)$ 的数量，结果对 $10^9 + 7$ 取模：

- **长度约束**：两个序列长度均为 $m$，即 $|a| = |b| = m$；
- **值域约束**：对于所有 $1 \leqslant k \leqslant m$，均有 $1 \leqslant a_k, b_k \leqslant n$；
- **逐点偏序约束**：对于所有 $1 \leqslant k \leqslant m$，均有 $a_k \leqslant b_k$；
- **单调性约束**：
  - 序列 $a$ 满足非降性：$a_1 \leqslant a_2 \leqslant \dots \leqslant a_m$；
  - 序列 $b$ 满足非增性：$b_1 \geqslant b_2 \geqslant \dots \geqslant b_m$。

---

## 解法总览

本题呈现出从“直觉状态设计”到“代数前缀和加速”，再到“单调性结构解耦”，直至“全局几何拼接组合数”的经典思维跃迁过程。以下展示四种各具教学价值的独立解法，正式主解采用最简且最优的解法四（组合数闭式解，见 `main.cpp` 与 `main.py`）。

| 解法 | 核心观察 | 复杂度 | 适用场景 | 对应代码 |
| --- | --- | --- | --- | --- |
| 解法一：三维动态规划 | 记录双序列末尾位置，按步暴力转移 | $O(m \cdot n^4)$ | 暴力模拟、小数据对拍验证 | `brute.cpp` |
| 解法二：二维前缀和加速 | 转移区域为二维网格矩形，前缀和 $O(1)$ 转移 | $O(m \cdot n^2)$ | 基础 DP 优化教学、网格区间求和模板 | `main2.cpp` |
| 解法三：单调性解耦 DP | 中间偏序由末尾 $a_m \leqslant b_m$ 自动蕴含，解耦为单序列 DP | $O(m \cdot n + n^2)$ | 偏序关系传递性化简、状态维度剥离 | `main3.cpp` |
| 解法四：序列翻转拼接（正解） | 倒序拼接为长度 $2m$ 的单一非降序列，隔板法组合数求解 | $O(m)$ | 正式提交主解、极速常数与空间最优 | `main.cpp` / `main.py` |

解法一与解法二基于同一套三维状态定义，展示了如何利用前缀和将双层枚举转移压缩至常数复杂度；解法三利用偏序传递性剥离了双序列的耦合；而解法四实现了认知升华，通过逆序拼接将题目完全还原为经典的可重组合数模型。

---

## 解法一：三维动态规划（直觉建模）

### 思路

::: info 直觉三维状态记录与暴力枚举
设状态 $f[pos, i, j]$ 表示填到第 $pos$ 个位置时，$a_{pos} = i, b_{pos} = j$（$1 \leqslant i \leqslant j \leqslant n$）的合法前缀方案数。根据单调性，上一步状态需满足 $u \in [1, i]$ 且 $v \in [j, n]$。直接对上一层网格进行两重循环求和，单步转移复杂度为 $O(n^2)$。
:::

根据题意，每一步填充仅依赖于前一步的状态：
- $a$ 单调不降：要求上一步 $a_{pos-1} = u \leqslant a_{pos} = i$；
- $b$ 单调不增：要求上一步 $b_{pos-1} = v \geqslant b_{pos} = j$；
- 逐点偏序：每一位置必须满足 $i \leqslant j$。

因此，转移方程为：
$$
f[pos, i, j] = \sum_{u = 1}^{i} \sum_{v = j}^{n} f[pos - 1, u, v]
$$
边界条件为 $pos = 1$ 时，对所有 $1 \leqslant i \leqslant j \leqslant n$，初始化 $f[1, i, j] = 1$。
最终答案即为：
$$
\text{Ans} = \sum_{1 \leqslant i \leqslant j \leqslant n} f[m, i, j] \pmod{10^9 + 7}
$$

该做法逻辑最直观，但因单步枚举耗时过长，适用于小数据验证与对拍。

### 代码

@include-code(./brute.cpp, cpp)

### 复杂度

- **时间复杂度**：状态总数为 $O(m \cdot n^2)$，每个状态需要枚举 $u \in [1, i]$ 和 $v \in [j, n]$ 进行转移，转移耗时 $O(n^2)$，总时间复杂度为 $O(m \cdot n^4)$。在 $n = 1000$ 时会超时。
- **空间复杂度**：由于第 $pos$ 层仅依赖第 $pos - 1$ 层，可滚动数组优化至 $O(n^2)$。

---

## 解法二：二维前缀和加速转移

### 思路

::: info 二维前缀和将矩形区域求和压缩至常数复杂度
观察解法一的转移式，求和部分 $\sum_{u=1}^i \sum_{v=j}^n f[pos-1, u, v]$ 本质上是二维网格 $(u, v)$ 上的一个矩形区域和。在计算第 $pos$ 层之前，先预处理第 $pos-1$ 层的二维前缀/后缀和数组 $S$，单次转移即可降至 $O(1)$。
:::

对上一层的状态定义二维前缀和（第一维前缀、第二维后缀）：
$$
S[u, v] = \sum_{x = 1}^{u} \sum_{y = v}^{n} f[pos - 1, x, y]
$$
利用容斥原理与递推关系，$S[u, v]$ 可在 $O(n^2)$ 内递推求出：
$$
S[u, v] = \Big( S[u - 1, v] + S[u, v + 1] - S[u - 1, v + 1] + f[pos - 1, u, v] \Big) \bmod (10^9 + 7)
$$
求出 $S$ 后，状态转移直接变为常数读取：
$$
f[pos, i, j] = S[i, j]
$$
这样就完全消除了内层的两重暴力循环。

### 代码

@include-code(./main2.cpp, cpp)

### 复杂度

- **时间复杂度**：共执行 $m - 1$ 次层间递推，每层计算前缀和矩阵与状态赋值均需 $O(n^2)$，总时间复杂度为 $O(m \cdot n^2)$。对于 $n = 1000, m = 10$，总运算量约 $10^7$，在 2.0s 内可以顺利通过。
- **空间复杂度**：维护当前层与前缀和矩阵，空间复杂度为 $O(n^2)$。

---

## 解法三：单调性解耦与一维 DP

### 思路

::: info 单调性传递性解耦：中间约束自动满足
由单调性可知序列链条为 $a_1 \leqslant a_2 \dots \leqslant a_m$ 以及 $b_m \leqslant b_{m-1} \dots \leqslant b_1$。只要最终末尾满足 $a_m \leqslant b_m$，根据传递性，对任意位置 $k$ 必有 $a_k \leqslant a_m \leqslant b_m \leqslant b_k$。因此中间过程 $a$ 和 $b$ 互不干涉，可拆分为两个独立的一维序列 DP，最终在末尾枚举拼接。
:::

由于点对约束只需在末尾把关，序列 $a$ 与序列 $b$ 的前 $m$ 步构建完全解耦：
1. **序列 $a$（非降）**：
   设 $f[pos, v]$ 表示长度为 $pos$、末尾元素为 $v$ 的非降序列方案数：
   $$f[pos, v] = \sum_{u = 1}^{v} f[pos - 1, u]$$
   利用一维前缀和，单步转移为 $O(1)$。
2. **序列 $b$（非增）**：
   设 $g[pos, v]$ 表示长度为 $pos$、末尾元素为 $v$ 的非增序列方案数：
   $$g[pos, v] = \sum_{u = v}^{n} g[pos - 1, u]$$
   利用一维后缀和，单步转移同样为 $O(1)$。

3. **合并统计**：
   当填完 $m$ 个位置后，枚举末尾元素 $a_m = i$ 与 $b_m = j$（满足 $1 \leqslant i \leqslant j \leqslant n$）：
   $$
   \text{Ans} = \sum_{1 \leqslant i \leqslant j \leqslant n} f[m, i] \times g[m, j] \pmod{10^9 + 7}
   $$

### 代码

@include-code(./main3.cpp, cpp)

### 复杂度

- **时间复杂度**：
  - 递推求 $f$ 与 $g$ 耗时 $O(m \cdot n)$；
  - 最终合并枚举 $1 \leqslant i \leqslant j \leqslant n$ 耗时 $O(n^2)$；
  - 总时间复杂度为 $O(m \cdot n + n^2)$，运算量进一步减少。
- **空间复杂度**：仅需维护一维状态，空间复杂度降至 $O(m \cdot n)$。

---

## 解法四：序列翻转拼接与隔板法组合数（正解）

### 思路

::: info 翻转拼接构建长非降链，转化为可重组合数
将非增序列 $b$ 倒序排列为 $b_m \leqslant b_{m-1} \dots \leqslant b_1$，与非降序列 $a$ 首尾顺次拼接，整体构成长度为 $2m$ 的单一非降序列 $c$。原问题严格等价于在 $[1, n]$ 中允许重复地选取 $2m$ 个非降元素，由可重组合（隔板法）直接得到闭式解 $\binom{n + 2m - 1}{2m}$。
:::

#### 1. 约束的全局链条化

将题目中的条件完整写出：
- $a$ 是非降序列：$a_1 \leqslant a_2 \leqslant \dots \leqslant a_m$；
- $b$ 是非增序列，倒过来写即为：$b_m \leqslant b_{m-1} \leqslant \dots \leqslant b_1$；
- 解法三已证明：只需保证 $a_m \leqslant b_m$，就能蕴含所有位置的 $a_k \leqslant b_k$。

我们将这两个长度为 $m$ 的序列头尾拼成一个长度为 $2m$ 的大数组 $c$：
$$
c = [a_1, a_2, \dots, a_m, \; b_m, b_{m-1}, \dots, b_1]
$$
观察数组 $c$ 的内部关系：
$$
1 \leqslant a_1 \leqslant a_2 \dots \leqslant a_m \leqslant b_m \dots \leqslant b_1 \leqslant n
$$
这说明：**数组 $c$ 是一个取值于 $[1, n]$、长度恰好为 $2m$ 的单调非降整数序列！**

反之，任意一个满足 $1 \leqslant c_1 \leqslant c_2 \leqslant \dots \leqslant c_{2m} \leqslant n$ 的序列 $c$，截取前半部分作为 $a$、后半部分倒序作为 $b$，都能唯一确定一组完全合法的 $(a, b)$ 对。

#### 2. 可重组合数推导（隔板法映射）

问题转化为：**在集合 $\{1, 2, \dots, n\}$ 中，允许重复地选取 $2m$ 个元素，有多少种不同的选法？**

设选出的单调非降序列为 $1 \leqslant c_1 \leqslant c_2 \leqslant \dots \leqslant c_{2m} \leqslant n$。
我们引入经典差分平移技巧，构造辅助变量 $d_k$：
$$
d_k = c_k + k - 1 \quad (1 \leqslant k \leqslant 2m)
$$
由于 $c_k \leqslant c_{k+1}$，加上严格递增的偏移量后必有：
$$
d_k < d_{k+1}
$$
同时考虑其取值范围：
- 最小值：$d_1 = c_1 + 1 - 1 = c_1 \geqslant 1$；
- 最大值：$d_{2m} = c_{2m} + 2m - 1 \leqslant n + 2m - 1$。

因此，$d_1, d_2, \dots, d_{2m}$ 与“从集合 $\{1, 2, \dots, n + 2m - 1\}$ 中无重复地选出 $2m$ 个元素”建立了**一一对应的双射关系**。

由此直接得出方案数公式为组合数：
$$
\binom{n + 2m - 1}{2m}
$$

计算时仅需计算一次组合数取模，利用逆元或边乘边除，单次耗时 $O(m)$ 即可输出答案。

### 代码

主解分别提供规范的 C++17 实现与极简 Python 3 实现：

C++ 版本：

@include-code(./main.cpp, cpp)

Python 版本：

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：计算组合数 $\binom{n + 2m - 1}{2m}$ 只需循环 $2m$ 次，单次求逆元耗时 $O(\log \text{MOD})$，总时间复杂度为 $O(m \log \text{MOD})$（若直接阶乘预处理或 Python 高精度则为 $O(m)$），耗时不足 1ms。
- **空间复杂度**：仅使用常数个辅助变量，空间复杂度为 $O(1)$。

---

## 复杂度对比

| 解法 | 预处理时间 | 单次转移/求解时间 | 空间复杂度 | $n=1000, m=10$ 实际表现 |
| :--- | :--- | :--- | :--- | :--- |
| 解法一（三维暴力 DP） | $O(1)$ | $O(n^2)$ 转移，总计 $O(m \cdot n^4)$ | $O(n^2)$ | $> 1000$ s（严重超时，仅供验证） |
| 解法二（二维前缀和 DP） | 每层 $O(n^2)$ 计算前缀和 | $O(1)$ 转移，总计 $O(m \cdot n^2)$ | $O(n^2)$ | $\approx 25$ ms |
| 解法三（一维解耦 DP） | 一维前缀和 $O(n)$ | $O(1)$ 转移，合并 $O(n^2)$ | $O(m \cdot n)$ | $\approx 3$ ms |
| 解法四（翻转拼接组合数） | $O(1)$ | 逆元计算 $O(m \log \text{MOD})$ | $O(1)$ | $< 1$ ms |

---

## 总结

1. **从暴力到优化**：面对多维网格转移，识别出求和区域的矩形特征后，利用二维前缀和可将单步转移直接压降一个数量级；
2. **抓住主要矛盾与解耦**：利用偏序关系的传递性，发现只需锁死最紧的边界约束（$a_m \leqslant b_m$），便可将两组相互交织的变量完全解耦为独立的一维子问题；
3. **对称翻转与几何化**：将单调非增序列反向后与非降序列拼接，把看似复杂的成对偏序问题升华为全局单一单调链，最终借由隔板法与可重组合数实现降维打击。
