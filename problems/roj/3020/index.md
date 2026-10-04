---
oj: "roj"
problem_id: "3020"
title: "国王游戏"
description: "通过邻项微扰（微扰法/交换参数法）证明最优排列为按大臣左右手乘积升序排序，并结合高精度整除求解答案。"
difficulty: "普及+/提高-"
date: 2026-10-01 10:25
updated: 2026-10-01 10:25
toc: true
tags:
  - 贪心
  - 高精度
  - 邻项交换法
favorite: false
favorite_reason: ""
categories:
  - 算法竞赛进阶指南
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3020
---

[[TOC]]

## 形式化题目

给定正整数 $n$，以及国王的左右手数值对 $(a_0, b_0)$，和 $n$ 位大臣的数值对 $(a_1, b_1), (a_2, b_2), \dots, (a_n, b_n)$。

国王始终排在队伍首位（位置 $0$）。若将 $n$ 位大臣排成一个队伍序列 $p_1, p_2, \dots, p_n$，则第 $i$ 位大臣（位置 $i$）获得的金币数为：
$$w_i = \left\lfloor \frac{a_0 \prod_{j=1}^{i-1} a_{p_j}}{b_{p_i}} \right\rfloor$$

请确定大臣的一个排列 $p$，使得获得奖赏最多的大臣所获奖赏尽可能小，即求出：
$$\min_{p} \max_{1 \le i \le n} w_i$$

## 正解

### 思路

本题要求在所有可能的大臣排列中最小化获得金币的最大值，是一个典型的**排列决策问题**。我们可以使用**邻项交换法（Exchange Argument）**推导出最优的排队准则。

#### 1. 邻项交换法推导

假设当前排列中，有两个相邻的大臣排在第 $i$ 位和第 $i+1$ 位。

记排在他们前面的所有人（包括国王）左手上的数的乘积为 $P$。交换他们两人的位置，不会影响排在第 $i$ 位之前的大臣，也不会改变排在第 $i+1$ 位之后大臣前面的左手乘积（因为 $P \cdot a_i \cdot a_{i+1} = P \cdot a_{i+1} \cdot a_i$）。

因此，交换只可能改变这两位大臣自身的金币数。

- **交换前**（大臣 $i$ 在前，大臣 $i+1$ 在后）：
  - 大臣 $i$ 的金币：$w_i = \left\lfloor \frac{P}{b_i} \right\rfloor$
  - 大臣 $i+1$ 的金币：$w_{i+1} = \left\lfloor \frac{P \cdot a_i}{b_{i+1}} \right\rfloor$
  - 这两人中的最大金币为：
    $$M_1 = \max\left(\left\lfloor \frac{P}{b_i} \right\rfloor, \left\lfloor \frac{P \cdot a_i}{b_{i+1}} \right\rfloor\right)$$

- **交换后**（大臣 $i+1$ 在前，大臣 $i$ 在后）：
  - 大臣 $i+1$ 的金币：$w'_{i+1} = \left\lfloor \frac{P}{b_{i+1}} \right\rfloor$
  - 大臣 $i$ 的金币：$w'_i = \left\lfloor \frac{P \cdot a_{i+1}}{b_i} \right\rfloor$
  - 这两人中的最大金币为：
    $$M_2 = \max\left(\left\lfloor \frac{P}{b_{i+1}} \right\rfloor, \left\lfloor \frac{P \cdot a_{i+1}}{b_i} \right\rfloor\right)$$

#### 2. 比较两状态的最大值

为了让整体最大值不增加，我们需要寻找使 $M_1 \le M_2$ 的条件。

将四项均乘以 $\frac{b_i b_{i+1}}{P}$（在实数范围上比较关键项大小）：
- 交换前的两项等价于：$b_{i+1}$ 与 $a_i b_i$
- 交换后的两项等价于：$b_i$ 与 $a_{i+1} b_{i+1}$

因为 $a_i, a_{i+1} \ge 1$，显然有：
$$a_i b_i \ge b_i, \quad a_{i+1} b_{i+1} \ge b_{i+1}$$

若满足：
$$a_i b_i \le a_{i+1} b_{i+1}$$
则有：
$$b_{i+1} \le a_{i+1} b_{i+1} \quad \text{且} \quad a_i b_i \le a_{i+1} b_{i+1}$$
故：
$$\max(b_{i+1}, a_i b_i) \le a_{i+1} b_{i+1} \le \max(b_i, a_{i+1} b_{i+1})$$
由此得到 $M_1 \le M_2$。

这说明：**只要大臣 $i$ 的 $a_i b_i$ 不超过大臣 $i+1$ 的 $a_{i+1} b_{i+1}$，大臣 $i$ 排在前面就绝不劣于排在后面**。

#### 3. 贪心策略

依据全序关系，我们只需将所有大臣按照 $a_i \times b_i$ **从小到大升序排序**即可得到全局最优解。

最后按排好的顺序依次维护前缀乘积 $P$ 并计算每个大臣的 $\lfloor P / b_i \rfloor$，取最大值作为答案。

### 图示解析

以样例输入为例说明排序过程与各大臣所获金币的计算：

- 国王：$(a_0=1, b_0=1)$
- 大臣 1：$(a=2, b=3) \implies a \times b = 6$
- 大臣 2：$(a=7, b=4) \implies a \times b = 28$
- 大臣 3：$(a=4, b=6) \implies a \times b = 24$

按照 $a \times b$ 升序排序后的队伍如下表所示：

| 排位 | 人员 | $(a, b)$ | $a \times b$ | 前面所有人的左手乘积 $P$ | 获得金币 $\lfloor P / b \rfloor$ |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 0 | 国王 | $(1, 1)$ | - | - | - |
| 1 | 大臣 1 | $(2, 3)$ | 6 | $1$ | $\lfloor 1 / 3 \rfloor = 0$ |
| 2 | 大臣 3 | $(4, 6)$ | 24 | $1 \times 2 = 2$ | $\lfloor 2 / 6 \rfloor = 0$ |
| 3 | 大臣 2 | $(7, 4)$ | 28 | $1 \times 2 \times 4 = 8$ | $\lfloor 8 / 4 \rfloor = 2$ |

所有大臣获得金币的最大值为 $2$。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：
  1. 排序的时间复杂度为 $O(n \log n)$。
  2. 遍历大臣计算前缀积与整除：在大整数运算下，数字位数为 $L \le 4000$，高精度乘以/除以单精度数值的单次复杂度为 $O(L)$。总时间复杂度为 $\sum_{i=1}^n O(i) = O(n^2)$。在 $n \le 1000$ 的约束下，计算耗时仅几十毫秒，远在 $1000\text{ ms}$ 时限内。
- **空间复杂度**：存储大臣列表与数千位高精度整数仅需 $O(n)$ 空间，满足 $128\text{ MB}$ 内存限制。

## 总结

国王游戏是经典的“邻项微扰（微扰法/交换法）”证明贪心正确性的代表题型。通过考察相邻两个元素的交换对局部最大值的影响，消去无关项，提炼出仅与单个元素属性相关的排序关键字 $a_i \times b_i$。在实现层面，利用 Python 原生支持的高精度大整数可以极为简洁地完成大数连乘与整除。
