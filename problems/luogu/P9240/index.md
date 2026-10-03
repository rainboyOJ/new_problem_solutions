---
oj: "luogu"
problem_id: "P9240"
title: "[蓝桥杯 2023 省 B] 冶炼金属"
description: "由 B=⌊A/V⌋ 反推出每条记录的 V 区间 [⌊A/(B+1)⌋+1, ⌊A/B⌋]，答案就是所有区间的交集。"
difficulty: "普及-"
date: 2026-10-02 15:07
updated: 2026-10-03 11:38
toc: true
tags: ["数学", "枚举", "整除", "区间", "推导"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P9240
---

[[TOC]]

## 形式化题目

有一个正整数转换率 $V$。给出 $N$ 条互相独立的记录 $(A_i, B_i)$，含义是：投入 $A_i$ 个普通金属 O，恰好冶炼出 $B_i$ 个特殊金属 X。由于不足 $V$ 个 O 无法继续冶炼，这条记录成立等价于

$$B_i = \left\lfloor \frac{A_i}{V} \right\rfloor .$$

求所有满足这 $N$ 个等式的正整数 $V$ 中，最小的那个和最大的那个。数据保证至少存在一个合法的 $V$。

把每条记录看作对 $V$ 的一个限制，题目就是求这些限制的公共解集的左右端点。

## 暴力解法

### 思路

最直接的做法：既然 $V$ 是一个正整数，就把所有可能的 $V$ 试一遍。对每个候选的 $v$，逐条检查 $\lfloor A_i / v \rfloor$ 是否等于 $B_i$；全部相等就说明 $v$ 可行，用可行 $v$ 的最小值和最大值更新答案。

枚举的上界是多少？由 $B_i = \lfloor A_i / v \rfloor$ 可知 $v \cdot B_i \leqslant A_i$，即 $v \leqslant A_i / B_i$（题目保证 $B_i \geqslant 1$）。对每条记录都成立，所以 $v$ 不会超过 $\min_i \lfloor A_i / B_i \rfloor$，枚举到它即可；在这个范围内暴力一定不会漏解。

这个解法完全忠实于题意，但它把「答案是一个区间」这件事用最笨的方式找了出来：一条一条地试。

### 代码

@include-code(./brute.cpp, cpp)

### 复杂度

枚举上界为 $\min_i \lfloor A_i/B_i\rfloor \leqslant 10^9$，每轮检查 $N$ 条记录，时间复杂度 $O(N \cdot \min_i \lfloor A_i/B_i \rfloor)$，空间复杂度 $O(N)$。

### 瓶颈

瓶颈是**逐个枚举 $V$ 的取值**。最坏情况下 $V$ 的候选多达 $10^9$ 个，而题目只有 $N \leqslant 10^4$ 条记录，完全没必要为每条记录都单独试一遍。

## 正解

### 思路

暴力的浪费之处在于：它假设「$V$ 是否合法」只能一个一个试。事实上每条记录单独就能把 $V$ 卡在一个连续区间里，$N$ 条记录的限制合起来仍然是一个区间，根本不需要枚举。

**关键观察**：$\lfloor A/V \rfloor = B$ 可以去掉取整符号，化成一对不等式。

$$B = \left\lfloor \frac{A}{V} \right\rfloor \iff B \leqslant \frac{A}{V} < B+1 .$$

把 $V > 0$ 乘到两边（不等号方向不变）：

$$B \cdot V \leqslant A < (B+1)\cdot V .$$

再把它拆成两个关于 $V$ 的方向：

- 由 $A < (B+1)V$ 得 $V > \dfrac{A}{B+1}$。因为 $V$ 是整数，这等价于

$$V \geqslant \left\lfloor \frac{A}{B+1} \right\rfloor + 1 ;$$

- 由 $B \cdot V \leqslant A$ 得 $V \leqslant \dfrac{A}{B}$。因为 $V$ 是整数，这等价于

$$V \leqslant \left\lfloor \frac{A}{B} \right\rfloor .$$

于是每条记录对应一个闭区间

$$\left[\, \left\lfloor \frac{A_i}{B_i+1} \right\rfloor + 1,\ \left\lfloor \frac{A_i}{B_i} \right\rfloor \,\right],$$

而 $V$ 合法当且仅当它落在这个区间里。这里的「$\iff$」是双向的：上面每一步都是等价变形，所以区间内的每个整数 $v$ 都真的满足 $\lfloor A/v \rfloor = B$，不会多解也不会漏解。

$N$ 条记录要同时满足，$V$ 就必须落在所有区间的**交集**里。答案是所有区间左端点的最大值 $L = \max_i \mathrm{lo}_i$ 和右端点的最小值 $R = \min_i \mathrm{hi}_i$，输出 $L$ 与 $R$。题目保证有解，所以一定有 $L \leqslant R$。

为什么所有合法解一定连成一段、从而答案就是交集的端点？因为满足单条记录的 $V$ 集合本身就是个区间，区间之交仍是区间，所以最小的合法 $V$ 就是 $L$，最大的合法 $V$ 就是 $R$。

用样例 $\left\lfloor 75/20 \right\rfloor = 3,\ \left\lfloor 53/20 \right\rfloor = 2,\ \left\lfloor 59/20 \right\rfloor = 2$ 验算一遍：

| $i$ | $A_i$ | $B_i$ | $\mathrm{lo}_i = \lfloor A_i/(B_i+1)\rfloor + 1$ | $\mathrm{hi}_i = \lfloor A_i/B_i \rfloor$ |
| --- | --- | --- | --- | --- |
| 1 | 75 | 3 | $\lfloor 75/4 \rfloor + 1 = 19$ | $\lfloor 75/3 \rfloor = 25$ |
| 2 | 53 | 2 | $\lfloor 53/3 \rfloor + 1 = 18$ | $\lfloor 53/2 \rfloor = 26$ |
| 3 | 59 | 2 | $\lfloor 59/3 \rfloor + 1 = 20$ | $\lfloor 59/2 \rfloor = 29$ |

左端点最大值是 $L = \max(19, 18, 20) = 20$，右端点最小值是 $R = \min(25, 26, 29) = 25$，与样例输出 `20 25` 一致。可以看到第三条记录把下界顶到 $20$，第一条记录把上界压到 $25$，区间被「夹」了出来。

### 代码

@include-code(./main.cpp, cpp)

两个边界细节：$B_i + 1$ 最大是 $10^9 + 1$，$A_i$ 最大 $10^9$，除法结果不溢出；用 `long long` 保存答案以防中间量比较时出错。初始令 `min_v = 1`、`max_v` 为一个足够大的数（大于 $10^9$），再依次取交，就不需要单独处理「第一条记录」这种特殊情况。

### 复杂度

每条记录只做两次整数除法，总时间复杂度 $O(N)$，空间复杂度 $O(1)$。与暴力的 $O(N \cdot 10^9)$ 相比，枚举被彻底消掉了。

## 总结

这道题的转化只有一步，但很值得记住：**看到整除等式，就去掉取整符号换成一上一下两个不等式**。

$$\left\lfloor \frac{A}{V} \right\rfloor = B \iff B \leqslant \frac{A}{V} < B+1 \iff \left\lfloor \frac{A}{B+1} \right\rfloor + 1 \leqslant V \leqslant \left\lfloor \frac{A}{B} \right\rfloor$$

把它用在每条记录上，题目就从「枚举转换率」变成了「对 $N$ 个区间求交」：交集的左端点即最小解，右端点即最大解。$N \geqslant 1$ 且 $B_i \geqslant 1$ 保证了区间总是存在，题面「保证有解」则保证交集非空。

更一般地，凡是形如「对每条形如 $\lfloor A/V \rfloor = B$ 的记录求 $V$ 的可行范围」的题，都可以先用这组不等式把每个变量的可行值收成一个区间，再对这些区间取交或做扫描，而不要真的去枚举。
