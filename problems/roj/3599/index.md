---
oj: "roj"
problem_id: "3599"
title: "国王游戏"
description: "交换论证：大臣按左右手数字之积 a_i×b_i 从小到大排队，最大奖赏最小；乘积用 Python 大整数顺扫一遍统计。"
difficulty: "提高"
date: 2026-10-02 09:53
updated: 2026-10-10 11:30
toc: true
tags: ["贪心", "排序", "数学"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3599
---

[[TOC]]

## 形式化题目

国王写下一对整数 $(a_0, b_0)$，另有 $n$ 位大臣各写下一对整数 $(a_i, b_i)$。把 $n$ 位大臣排成一个排列 $p$，排在位置 $k$ 的大臣获得的金币数为

$$
\left\lfloor \frac{\prod_{j<k} a_{p_j}}{b_{p_k}} \right\rfloor,
$$

即排在他前面的所有人（含国王）左手数字的乘积除以他自己右手数字，向下取整。求一个排列，使获得金币最多的大臣所得最少，输出这个最小值。

样例：国王 $(1,1)$，三位大臣 $(2,3),(7,4),(4,6)$。按 $1,2,3$ 排列时各人得到 $\lfloor 1/3\rfloor=0$、$\lfloor 2/4\rfloor=0$、$\lfloor 14/6\rfloor=2$，最大值为 $2$，这就是答案。

<!-- 样例推演：三种排列的最大值对比，观察"乘积小的人靠前"的趋势 -->
| 排列 | 各大臣金币 | 最大值 |
| --- | --- | --- |
| $1,2,3$ | $\lfloor 1/3\rfloor=0,\ \lfloor 2/4\rfloor=0,\ \lfloor 14/6\rfloor=2$ | **2** |
| $2,3,1$ | $\lfloor 1/6\rfloor=0,\ \lfloor 2/4\rfloor=0,\ \lfloor 14/3\rfloor=4$ | 4 |
| $3,2,1$ | $\lfloor 1/6\rfloor=0,\ \lfloor 4/4\rfloor=1,\ \lfloor 28/3\rfloor=9$ | 9 |

同一个样例换个排列最大值就从 $2$ 涨到 $9$：左手乘积越攒越大，靠后的人很容易被"撑爆"，所以谁站前面并不随意——这正是下面贪心要回答的问题。

## 暴力解法

### 思路

$n \leqslant 10$ 或 $n \leqslant 20$ 时直接枚举全排列：对每个排列从左往右累乘左手数字，算出每个人的金币数，取最大值；所有排列的最大值再取最小即为答案。前 $40\%$ 的数据（$n \leqslant 20$、$a,b<8$）都能轻松通过。

### 代码

暴力思路略（前 40% 的全排列枚举按上述思路用 `itertools.permutations` 即可，无独立教学价值，也不参与对拍，故不保留代码文件）。

### 复杂度

每个排列需要 $O(n)$ 次大整数乘除，共 $n!$ 个排列，总复杂度 $O(n \cdot n!)$，只适用于 $n \leqslant 10 \sim 20$。

### 瓶颈

瓶颈在于把 $n$ 个大臣的所有站法当成彼此独立的方案逐个尝试，完全没有利用"相邻两人交换后，其他人的金币数都不变"这一局部结构。所有最优排列里一定存在一个可以通过不断交换相邻元素得到的形态，因此只需弄清**相邻两人谁站前面更好**，就能一次性定下整支队伍的顺序。

## 正解

### 思路

先做一步关键观察：设某相邻两人的左手数、右手数分别为 $(a_i, b_i)$、$(a_j, b_j)$，他们前面所有人（含国王）左手乘积为 $P$。交换这两个人，队伍里**其他**大臣面前的乘积不变，金币数不变；受影响的只有这两人的金币数：

| 位置 | 左手乘积 | 除以的右手数 | 金币数 |
| --- | --- | --- | --- |
| $i$ 在前（原序） | $P$ | $b_i$ | $\left\lfloor P / b_i \right\rfloor$ |
| $j$ 在后（原序） | $P \cdot a_i$ | $b_j$ | $\left\lfloor P a_i / b_j \right\rfloor$ |
| $j$ 在前（交换后） | $P$ | $b_j$ | $\left\lfloor P / b_j \right\rfloor$ |
| $i$ 在后（交换后） | $P \cdot a_j$ | $b_i$ | $\left\lfloor P a_j / b_i \right\rfloor$ |

我们要证：**当 $a_i b_i \leqslant a_j b_j$ 时，保持 $i$ 在前不会让两人的最大金币数变大**，即

$$
\max\left(\left\lfloor \frac{P}{b_i} \right\rfloor, \left\lfloor \frac{P a_i}{b_j} \right\rfloor\right)
\leqslant
\max\left(\left\lfloor \frac{P}{b_j} \right\rfloor, \left\lfloor \frac{P a_j}{b_i} \right\rfloor\right).
$$

$\lfloor\cdot\rfloor$ 单调不减，先比较去掉取整的实数值。两边同乘正数 $\dfrac{b_i b_j}{P}$（$P > 0$），消去公共因子，等价于

$$
\max\left(b_j,\ a_i b_i\right) \leqslant \max\left(b_i,\ a_j b_j\right).
$$

由 $a_i, a_j \geqslant 1$ 知 $b_j \leqslant a_j b_j$、$b_i \leqslant a_i b_i$。若 $a_i b_i \leqslant a_j b_j$，则左边两项 $b_j \leqslant a_j b_j$ 与 $a_i b_i \leqslant a_j b_j$ 都不超过右边，不等式成立；反之若 $a_i b_i > a_j b_j$，则左边 $\geqslant a_i b_i$，而右边两项 $b_i \leqslant a_i b_i$、$a_j b_j < a_i b_i$ 都严格更小，此时交换两人反而严格更优。综合两种情况：**乘积小的人站前面总是不更差**。

于是把所有大臣按 $a_i \times b_i$ 从小到大排序（乘积相同时任意顺序均可——此时两种站法同样好），依次排成一排，国王仍在最前面。任意排列都能经有限次相邻交换变成这个排序，而每次交换都不让最大值变大，所以排序后的队伍就是最优队伍之一。

最后扫一遍排序结果：维护一个累乘变量（初始为国王左手数 $a_0$），第 $k$ 位大臣的金币数为 $\lfloor$ 当前乘积 $/ b_k \rfloor$，取最大值，随后把他的左手数乘进累乘变量。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

排序 $O(n \log n)$；扫一遍的过程中，累乘变量最多达到 $(10^4)^{1001}$ 量级（约 $10^{4000}$，上千位的十进制大数）。Python 的整数乘除法天然支持大数，一次大数运算约 $O(D)$（$D$ 为位数），总复杂度 $O(n \log n + n \cdot D)$；对 $n \leqslant 1000$ 绰绰有余，远低于 $1000\text{ ms}$ 的限制。若在 C++ 中实现，需要手写高精度乘大整数、除小整数（压位存储），同样是 $O(n \log n + n \cdot D)$。

## 总结

- 核心是**邻项交换排序（交换论证）**：只比较相邻两人，推出"$a_i b_i$ 小的站前面"这一全局排序依据，与"区间调度按右端点排序"是同一套方法论。
- 影响某人金币数的只有他前面的左手乘积和他自己的右手数，交换相邻两人不影响其他人，这是整个论证成立的支点。
- 用 Python 做这类高精度贪心题非常划算：大整数乘除开箱即用，代码只剩排序加一次线性扫描。
