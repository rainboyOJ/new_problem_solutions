---
oj: "roj"
problem_id: "1083"
title: "计算星期几"
description: "星期以 7 天为周期，答案是 a^b mod 7 查星期表；用 pow(a,b,7) 模意义快速幂 O(log b) 求余，r=0 时负索引 -1 恰好落到 Sunday。"
difficulty: "入门"
date: 2026-09-29 17:55
updated: 2026-09-29 17:55
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1083
---

[[TOC]]

## 形式化题目

给定正整数 $a$（$a \leqslant 100$）与正整数 $b$（$b \leqslant 10000$），今天是星期日，问过 $a^b$ 天后是星期几（输出英文星期名）。

## 正解

### 思路

**一句话本质**：星期以 $7$ 天为一个周期，答案完全由 $r = a^b \bmod 7$ 决定；用模意义快速幂 `pow(a, b, 7)` 求出 $r$ 后查星期表输出。

先看朴素做法：把 $a^b$ 精确算出来，再看它除以 $7$ 余几。问题在于 $100^{10000}$ 是 $20001$ 位的大数——我们费劲算出的高位数字对"数星期"毫无用处，因为星期是 $7$ 天一循环的：

$$\text{过 } (7k + r) \text{ 天} \quad \Longleftrightarrow \quad \text{过 } r \text{ 天}\qquad (0 \leqslant r < 7)$$

所以答案只依赖 $a^b \bmod 7$。而**同余**的乘法法则告诉我们，取模可以随时做：

$$x \equiv x' \ (\mathrm{mod}\ 7),\ y \equiv y' \ (\mathrm{mod}\ 7) \ \Longrightarrow\ xy \equiv x'y' \ (\mathrm{mod}\ 7)$$

于是不必先算 $a^b$ 再取模，而是每次乘完立即 $\bmod 7$：

```python
r = 1
for _ in range(b):
    r = r * a % 7   # 中间值永远 ≤ 6×100，不必关心 a^b 有多大
```

这一步把"大数瓶颈"消掉了，复杂度 $O(b)$。再把逐次相乘升级为**快速幂**（反复平方，按 $b$ 的二进制位挑着乘），乘法次数降到 $\lceil \log_2 b \rceil \leqslant 14$，复杂度 $O(\log b)$。Python 的三参数内置函数 `pow(a, b, 7)` 干的就是这件事——模意义下的平方求幂，一行完成。

求出 $r$ 之后查表。今天是星期日，过 $r$ 天的对应关系是：

| $a^b \bmod 7$ | 过几天 | 星期 | 代码下标 `r - 1` |
| --- | --- | --- | --- |
| $1$ | $1$ | Monday | $0$ |
| $2$ | $2$ | Tuesday | $1$ |
| $3$ | $3$ | Wednesday | $2$ |
| $4$ | $4$ | Thursday | $3$ |
| $5$ | $5$ | Friday | $4$ |
| $6$ | $6$ | Saturday | $5$ |
| $0$ | $7$ 的整数倍 | Sunday | $-1$（负索引取列表末位） |

其中 $r = 0$ 的行最值得注意：余 $0$ 表示 $a^b$ 恰好是 $7$ 的整数倍，整数个星期后**仍是星期日**，而不是"没有过天"。把 `WEEK` 表按 Monday 开头存放，输出 `WEEK[r - 1]`：$r = 0$ 时 `r - 1 = -1`，Python 的负索引正好落到列表末位的 `Sunday`——特判被下标本身吸收了。

用样例验证：$3^{2000} \bmod 7 = 2$（因为 $3^6 \equiv 1 \pmod 7$，而 $2000 \bmod 6 = 2$，$3^2 \equiv 2$），查表得 Tuesday，与样例输出一致。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间：`pow(a, b, 7)` 为 $O(\log b)$ 次模乘（本题至多 $14$ 次），整体 $O(\log b)$；
- 空间：$O(1)$，一个长度 $7$ 的星期表。

## 总结

- 周期问题先找周期：星期 $\to$ 模 $7$；
- 同余乘法法则保证"边乘边取模"合法，中间值不再膨胀；
- 大指数幂取模用快速幂，Python 里就是三参数 `pow(a, b, m)`；
- 余数为 $0$ 的"整除周期"情形要回到周期起点（Sunday），用 `WEEK[r - 1]` 的负索引一步统一。
