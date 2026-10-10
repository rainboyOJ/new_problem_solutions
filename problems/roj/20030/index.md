---
oj: "roj"
problem_id: "20030"
title: "异或查询"
description: "通过 Lucas 定理将二维组合数递推转换为按位与条件，再利用高低位分块优化枚举，实现 $O((n+q)2^8)$ 复杂度。"
difficulty: "省选/NOI-"
date: 2026-10-09 21:43
updated: 2026-10-09 21:43
toc: true
tags:
  - Lucas 定理
  - 高低位分块
  - 子集枚举
favorite: false
favorite_reason: ""
categories:
  - 算法竞赛
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20030
---

[[TOC]]

## 形式化题目

给定一个长度为 $N$ 的数组 $a_0, a_1, \dots, a_{N-1}$，有一个无限大的二维数组 $f$，定义如下：

- $f_{0, i} = a_i$  $(0 \le i \le N-1)$
- 对于 $j \ge 1$，且 $i+j \le N-1$，有 $f_{j, i} = f_{j-1, i} \oplus f_{j-1, i+1}$

给定 $Q$ 次查询，每次查询给出一对 $(x, y)$，输出 $f_{x, y}$ 的值。

保证查询满足 $0 \le x, y$ 且 $x+y \le N-1$。

**数据范围**：
- $N, Q \le 100,000$

## 正解

### 思路

根据题目的递推式 $f_{j, i} = f_{j-1, i} \oplus f_{j-1, i+1}$，可以发现它的结构类似于杨辉三角（二项式系数）。如果我们把它展开，可以得到 $f_{x, y}$ 的一般表达式：

$$ f_{x, y} = \bigoplus_{k=0}^{x} \left[ \binom{x}{k} \bmod 2 \equiv 1 \right] a_{y+k} $$

即，$f_{x, y}$ 是 $a_{y+k}$ 的异或和，其中 $k$ 必须满足 $\binom{x}{k}$ 是奇数。

由 **Lucas 定理**，$\binom{x}{k} \bmod 2 \equiv 1$ 等价于二进制下 $k$ 是 $x$ 的子集（即 `(k & x) == k`）。
所以：

$$ f_{x, y} = \bigoplus_{k \subseteq x} a_{y+k} $$

现在问题变成了求所有满足 $k$ 是 $x$ 的子集的 $a_{y+k}$ 的异或和。
每次查询如果直接枚举 $x$ 的子集，最坏情况下 $x$ 的二进制中有 16 个 1，枚举次数为 $2^{16} = 65536$，这在 $Q=10^5$ 的情况下会超时。

**高低位分块优化：**

我们把 $x$ 拆成高位和低位两部分。取块大小 $B = 8$ 位，即 $2^8 = 256$。
把 $x$ 拆成 $x_1 = \lfloor x / 256 \rfloor$ 和 $x_2 = x \bmod 256$。
那么 $x = (x_1 \ll 8) + x_2$。$k$ 也可以拆成 $k_1$ 和 $k_2$，其中 $k_1 \subseteq x_1$ 且 $k_2 \subseteq x_2$。

因此有：
$$ f_{x, y} = \bigoplus_{k_1 \subseteq x_1} \bigoplus_{k_2 \subseteq x_2} a_{y + (k_1 \ll 8) + k_2} $$
$$ f_{x, y} = \bigoplus_{k_1 \subseteq x_1} f_{x_2, y + (k_1 \ll 8)} $$

我们可以在 $O(N \cdot 2^8)$ 的时间内预处理出所有 $f_{j, i}$，其中 $0 \le j < 256$。
预处理的转移方程可以通过 $O(1)$ 的 lowbit 操作实现：$f_{j, i} = f_{j \setminus \text{lowbit}(j), i} \oplus f_{j \setminus \text{lowbit}(j), i+\text{lowbit}(j)}$。

对于每次查询，由于 $x_2 < 256$，我们只需要枚举 $x_1$ 的所有子集 $k_1$。$x_1$ 的最大值为 $10^5 \gg 8 \approx 390$，二进制下最多有 8 位为 1，枚举子集的时间复杂度不超过 $2^8 = 256$。

总时间复杂度为预处理 $O(N \cdot 2^8)$ 和查询 $O(Q \cdot 2^8)$，可以通过此题。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**：
  预处理部分对于每一个 $0 \le j < 2^8$，计算了 $N$ 个状态，时间复杂度为 $O(N \cdot 2^8)$。
  每次查询枚举高位子集，最多枚举 $2^8$ 个子集，时间复杂度为 $O(Q \cdot 2^8)$。
  总时间复杂度为 $O((N+Q)2^8)$。
- **空间复杂度**：
  预处理数组 `f` 需要大小为 $2^8 \times N$，空间复杂度为 $O(N \cdot 2^8)$，约 25MB，符合要求。

## 总结

1. **算法核心**：通过 Lucas 定理将组合数模 2 的问题转化为子集枚举，再通过高低位分块思想，平衡预处理与查询的时间，将查询复杂度从 $O(Q \cdot 2^{\text{popcount}(x)})$ 优化为 $O((N+Q)2^{8})$。
2. **证据层升级与对拍结论**：本题不再是无数据题。官方提供的大数据样例 `xor.in/xor.ans`（规模 $N=Q=100,000$）在验证中与 `main.cpp` 和 `main.py` 的输出逐字节一致。worker 跨源对拍结论表明代码在大规模数据下表现优异且正确。
3. **数据规模与块大小**：$N=Q=100,000$，这恰好适合块大小取 $B=8$（即 256）。预处理复杂度为 $N \times 256$，查询复杂度不超过 $256$，常数很小，足以在限定时间内通过。
4. **溢出处理（T9 五项）**：本题递推只涉及异或操作，没有加减乘除。由于异或操作本质上是不进位加法，其中间结果始终不会超过操作数原有的最大位宽（$a_i$ 为普通整数范围内），所以使用 32 位整型 `int` 即可，不会发生溢出。
