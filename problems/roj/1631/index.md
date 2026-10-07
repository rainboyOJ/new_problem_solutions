---
oj: "roj"
problem_id: "1631"
title: "「一本通 6.4 例 1」青蛙的约会"
description: "把 t 次跳跃后相遇写成同余方程 (m-n)t≡y-x(mod L)，用扩展欧几里得求特解，再按周期 L/gcd 归一化出最小非负解；gcd 不整除差值则无解。"
difficulty: "普及+/提高-"
date: 2026-09-30 23:07
updated: 2026-10-07 13:50
toc: true
tags: ["数论", "扩展欧几里得", "同余方程", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1631
---

[[TOC]]

## 形式化题目

环长为 $L$ 的圆周上有两个动点，初始位置 $x$、$y$（$x \neq y$），每一步分别前进 $m$、$n$。求最小的非负整数 $t$，使得

$$x + mt \equiv y + nt \pmod{L}$$

若这样的 $t$ 不存在，输出 `Impossible`。数据范围：$0 \leqslant x, y < 2 \times 10^9$，$0 < m, n, L < 2 \times 10^9$。

## 正解

### 思路

**朴素做法与瓶颈。** 最直接的想法是模拟：每一步让两只青蛙各前进一次，检查位置是否相同。单次跳跃后 A 领先 B 的距离减少 $m - n$（模 $L$ 意义下），所以相遇时间 $t$ 最大可能达到 $L$，而 $L < 2 \times 10^9$——模拟一步一查是 $O(L)$，必然超时。必须从"一步一跳"升级到"解方程"。

**把相遇写成同余方程。** 相遇条件是两者位置模 $L$ 相等：

$$x + mt \equiv y + nt \pmod{L}$$

移项，未知数只有 $t$：

$$(m - n)\,t \equiv y - x \pmod{L}$$

这是一个标准的**线性同余方程** $at \equiv c \pmod{L}$，其中 $a = m - n$，$c = y - x$。数据范围在 $2 \times 10^9$ 级别，Python 的整数不受影响，关键是求出 $t$ 的算法要降到 $O(\log L)$——这正是扩展欧几里得（exgcd）的用武之地。

**用 exgcd 解同余方程。** 设 $g = \gcd(a, L)$。由 Bézout 定理，exgcd 能求出整数 $s$ 使 $a \cdot s + L \cdot (\text{某整数}) = g$，即

$$a \cdot s \equiv g \pmod{L}$$

- **有解判定**：同余方程 $at \equiv c \pmod L$ 有解当且仅当 $g \mid c$。直观理解：$at - c$ 必须是 $L$ 的倍数，而 $g$ 同时整除 $a$ 与 $L$，所以 $g$ 必须整除 $c$。若 $g \nmid c$，输出 `Impossible`。
- **求特解**：当 $g \mid c$ 时，把 Bézout 等式两边同乘 $c / g$，得特解 $t_0 = s \cdot \dfrac{c}{g}$，它满足 $a\,t_0 \equiv c \pmod L$。

**从特解到最小非负解。** 若 $t_0$ 是解，则 $t_0 + k \cdot \dfrac{L}{g}$ 也都是解（因为 $a \cdot \dfrac{L}{g}$ 恰好是 $L$ 的 $a/g$ 倍，模 $L$ 为 $0$）。所以全部解构成公差为 $\dfrac{L}{g}$ 的等差数列，最小非负解就是

$$t = t_0 \bmod \frac{L}{g}$$

**实现的两个细节。** 其一，$a = m - n$ 可能是负数（两只青蛙谁快谁慢不确定），Python 的 `%` 对负数返回非负余数，所以先做 $a \leftarrow (m-n) \bmod L$、$c \leftarrow (y-x) \bmod L$，把方程化成 $0 \leqslant a < L$、$0 \leqslant c < L$ 的标准形式，后续取模方向不会出错。其二，exgcd 递归返回的 $s$ 符号不定，最后一步统一 `% step` 归一化即可，无需手动调整符号。

**用样例验证推导。** 样例 $x=1, y=2, m=3, n=4, L=5$：方程为 $(-1)t \equiv 1 \pmod 5$，化成标准形 $a = 4,\ c = 1$，$g = \gcd(4,5) = 1$，特解 $s = 4$（$4 \times 4 = 16 \equiv 1$），周期 $L/g = 5$，答案 $4 \bmod 5 = 4$。逐跳模拟也能对上：第 $t$ 跳后 A 在 $(1+3t) \bmod 5$、B 在 $(2+4t) \bmod 5$，逐项列出：

| $t$ | A：$(1+3t) \bmod 5$ | B：$(2+4t) \bmod 5$ | 是否相遇 |
| --- | --- | --- | --- |
| 0 | 1 | 2 | 否 |
| 1 | 4 | 1 | 否 |
| 2 | 2 | 0 | 否 |
| 3 | 0 | 4 | 否 |
| 4 | **3** | **3** | ✅ 首次相遇 |

观察重点：每一行 A 与 B 的差恰好减少 $1$（即 $m-n$ 的模 $L$ 效果），差值 $4, 3, 2, 1, 0$ 走完一个周期才追上——这正是方程 $4t \equiv 1 \pmod 5$ 的几何含义。当 $g > 1$ 时差值每次减少 $g$ 的倍数，差值永远落在 $g$ 的剩余类里，$g \nmid c$ 时就永远追不上，这解释了 `Impossible` 的来源。

### 代码

@include-code(./main.py, python)

代码要点与上文推导一一对应：

- `exgcd` 用递归实现 Bézout：边界 $b=0$ 时 $g=a,\ s=1$；回代时下层解 $(s, t)$ 变换为 $(t,\ s - a // b \times t)$。
- 主流程先把 $a$、$c$ 归一化到 $[0, L)$，再用 `c % g` 判无解；有解时特解 $s \cdot (c/g)$ 对周期 `L // g` 取模，直接得到最小非负解。

### 复杂度

- 时间复杂度：exgcd 的递归深度与辗转相除相同，为 $O(\log \min(a, L))$，其余步骤都是常数次大整数运算，总体 $O(\log L)$，远优于朴素模拟的 $O(L)$。
- 空间复杂度：递归栈 $O(\log L)$；改成迭代可以降到 $O(1)$，但递归写法与推导对应更直接。

## 总结

- 相遇条件 $\Leftrightarrow$ 线性同余方程 $(m-n)t \equiv y-x \pmod L$，是"循环追赶"类问题的标准转化。
- 解同余方程三步：exgcd 求 $g$ 与 Bézout 系数 → $g \mid c$ 判有解 → 特解乘 $c/g$ 后对周期 $L/g$ 取模得最小非负解。
- 负系数、大数取模是本题两个易错点：先 `% L` 化标准形，最后统一 `% step` 归一化，可以避免所有符号分类讨论。
