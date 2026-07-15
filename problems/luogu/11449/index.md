---
oj: "luogu"
problem_id: "P11449"
title: "Roundabout Rounding"
description: "链式舍入与直接舍入不同的数恰好落在每个位数下 [44...45, 49...9] 的区间中，逐段计数即可。"
difficulty: "普及-"
date: 2026-07-11 12:32
toc: true
tags: ["数学", "模拟", "usaco", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P11449
---

[[TOC]]

### 同题说明

洛谷 P11449 与 USACO 1443 是同一道题，完整题目解析请见：

- [[problem: usaco,1443]]

### 题意

给定正整数 $N$，求 $[2, N]$ 中有多少个整数 $x$，使得将 $x$ **直接舍入**到 $10^P$ 与**链式舍入**到 $10^P$ 的结果不同。其中 $P$ 是满足 $10^P \geqslant x$ 的最小正整数。

- **直接舍入**到 $10^b$：看从右往左第 $b$ 位数字 $d$，若 $d \geqslant 5$ 则加 $10^b$，然后把最低 $b$ 位全部置 $0$。
- **链式舍入**到 $10^b$：先舍入到 $10^1$，再舍入到 $10^2$，……，最后舍入到 $10^b$。

### 思路

先看暴力模拟，帮助理解两种舍入的区别：

@include-code(./brute.py, python)

这个暴力对每个 $x$ 模拟两种舍入过程，时间复杂度 $O(N \log N)$，只能跑小数据。

#### 关键观察

手动枚举小数据可以发现规律：

| $P$ | 不同的 $x$ 范围 | 个数 |
|-----|----------------|------|
| 2 | $[45, 49]$ | 5 |
| 3 | $[445, 499]$ | 55 |
| 4 | $[4445, 4999]$ | 555 |

**规律**：对于 $P = d$（$d \geqslant 2$），链式舍入与直接舍入不同的数恰好是：

$$
x \in [L_d,\; U_d] = [4\underbrace{44\ldots4}_{d-2\text{ 个}}5,\; 4\underbrace{99\ldots9}_{d-1\text{ 个}}]
$$

个数为 $\dfrac{5 \times (10^{d-1} - 1)}{9}$。

#### 为什么是这个区间

- **直接舍入**到 $10^d$ 只看第 $d$ 位（最高位）。最高位 $\geqslant 5$ 则结果为 $10^d$，否则为 $0$。
- **链式舍入**会从低位向高位逐级进位。当最高位恰好是 $4$ 时，低位的连锁进位可能把它推成 $5$，使链式结果变成 $10^d$，而直接舍入仍是 $0$。
- 最高位 $< 4$ 时，即使低位全部进位也推不到 $5$；最高位 $\geqslant 5$ 时，直接和链式都得到 $10^d$。所以只有最高位 $= 4$ 时才可能不同。
- 低位需要满足"链式舍入能产生进位"的条件，这恰好是一个递归结构：$d-1$ 位低位数 $\geqslant L_{d-1}$ 时才会进位。

#### 最终做法

对每个 $d$ 从 $2$ 到 $10$，预计算 $L_d$ 和 $U_d$，然后对每个查询 $N$：

$$
\text{ans} = \sum_{d=2}^{10} \max(0,\; \min(U_d, N) - L_d + 1)
$$

其中 $L_d = \dfrac{40 \times (10^{d-1} - 1)}{9} + 5$，$U_d = 5 \times 10^{d-1} - 1$。

### Python 知识

本题用到的 Python 模式：

1. **`sys.stdin.buffer.read().split()`**：一次读入全部输入并按空白切分，比逐行 `input()` 快很多。参见 [Python 竞赛输入输出与字符串处理](/program_language/python/input_output_and_strings/) 中"按 token 读取整份输入"一节。
2. **`'\n'.join(out)`**：先把所有答案攒到列表，最后一次性拼接输出，避免多次 `print` 的开销。
3. **预计算查找表**：`LU` 列表在循环外一次性算好所有 $(L_d, U_d)$，每个查询只做常数次比较。
4. **Python 大整数**：$10^9$ 的幂运算在 Python 中自动处理，不需要担心溢出。

C++ → Python 对照：

| C++ | Python |
|-----|--------|
| `scanf` / `cin` | `sys.stdin.buffer.read().split()` |
| `printf` / `cout` | `sys.stdout.write('\n'.join(...))` |
| `long long` | `int`（自动大整数） |
| 数组预计算 | 列表 + 循环 |

模仿清单：

```python
# 一次读入全部 token
data = sys.stdin.buffer.read().split()

# 攒答案再一次性输出
out = []
out.append(str(ans))
sys.stdout.write('\n'.join(out) + '\n')

# 整除代替浮点
L = 4 * 10 * (10**(d-1) - 1) // 9 + 5
```

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间：预计算 $O(\log N_{\max})$，每个查询 $O(\log N)$，总计 $O(T \log N)$
- 空间：$O(\log N_{\max})$ 存查找表 + $O(T)$ 存输出

### 总结

这道题的核心是发现"链式进位"的递归结构：只有最高位为 $4$ 且低位足够大时，链式舍入才会通过逐级进位把最高位推过 $5$ 的门槛。找到这个区间后，问题退化为简单的区间计数。
