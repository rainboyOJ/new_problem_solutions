---
oj: "roj"
problem_id: "1637"
title: "「一本通 6.4 练习 1」荒岛野人"
description: "从小到大枚举山洞数 M，利用扩展欧几里得算法求解线性同余方程，检验任意两野人是否在共同有生之年相遇。"
difficulty: "提高"
date: 2026-09-30 23:23
updated: 2026-10-07 13:50
toc: true
tags:
  - 数论
  - 扩展欧几里得
  - 同余方程
  - 枚举
favorite: false
favorite_reason: ""
categories:
  - 算法竞赛
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1637
---

[[TOC]]

## 形式化题目

给定 $N$ 个个体，每个个体 $i$（$1 \le i \le N$）具有三个属性 $(C_i, P_i, L_i)$，在模 $M$ 的环形空间上（编号 $1, 2, \dots, M$）按年份 $x \in [0, L_i]$ 运动，第 $x$ 年的位置为 $(C_i + x \cdot P_i - 1) \bmod M + 1$。

求最小的正整数 $M$，使得：
1. $M \ge \max_{1 \le i \le N} C_i$；
2. 对于任意两个个体 $i \neq j$，在整数区间 $x \in [0, \min(L_i, L_j)]$ 上，不存在整数 $x$ 使得：
   $$C_i + x \cdot P_i \equiv C_j + x \cdot P_j \pmod M$$

保证有解且 $M \le 10^6$。

## 正解：枚举山洞数 + 扩展欧几里得（exgcd）检验

### 思路

因为初始时每个野人分别住在不同的山洞中，山洞总数必须不小于所有初始位置的最大值，即 $M \ge \max_{1 \le i \le N} C_i$。

要求最小合法的 $M$，且保证 $M \le 10^6$，我们可以从 $M = \max C_i$ 开始依次递增枚举 $M$。对于每个 $M$，检验所有两两野人组合 $(i, j)$ 是否存在相遇冲突：

考虑野人 $i$ 与野人 $j$，设他们在第 $x$ 年位于同一山洞，则有：
$$C_i + x \cdot P_i \equiv C_j + x \cdot P_j \pmod M$$

移项整理为标准的线性同余方程：
$$(P_i - P_j) x \equiv C_j - C_i \pmod M$$

记 $A = P_i - P_j$，$B = C_j - C_i$，$g = \gcd(A, M)$。根据裴蜀定理与同余方程性质：
1. 若 $B \bmod g \neq 0$，则方程无整数解，说明在该模数 $M$ 下，两野人永不相遇。
2. 若 $B \bmod g = 0$，由扩展欧几里得算法求出特解后，最小非负整数解为：
   $$x = \left( x_0 \cdot \frac{B}{g} \bmod \left|\frac{M}{g}\right| + \left|\frac{M}{g}\right| \right) \bmod \left|\frac{M}{g}\right|$$
   - 如果 $x \le \min(L_i, L_j)$，说明该最小非负解落在两人的共同寿命期内，发生了冲突，当前 $M$ 不合法，立即跳出尝试下一个 $M$。
   - 如果 $x > \min(L_i, L_j)$，由于后续解均满足 $x + k \cdot \left|\frac{M}{g}\right| \ge x > \min(L_i, L_j)$（$k \ge 0$），因此在两人的共同寿命期内绝无相遇可能。

只要存在任意一对野人相遇，当前 $M$ 就非法；若所有 $\binom{N}{2}$ 对野人均不相遇，则当前 $M$ 即为满足条件的最小山洞数。

### 冲突判定与相遇过程图示

以样例 $N=3$ 为例，当 $M=6$ 时各野人每年的轨迹如下表：

| 年份 $x$ | 野人 1 位置 ($C_1=1, P_1=3, L_1=4$) | 野人 2 位置 ($C_2=2, P_2=7, L_2=3$) | 野人 3 位置 ($C_3=3, P_3=2, L_3=1$) | 冲突检测 |
| :---: | :---: | :---: | :---: | :---: |
| 0 | 1 | 2 | 3 | 无冲突 |
| 1 | 4 | 3 | 5 | 无冲突 |
| 2 | 1 | 4 | 已去世 | 无冲突 |
| 3 | 4 | 5 | 已去世 | 无冲突 |
| 4 | 1 | 已去世 | 已去世 | 无冲突 |

同余方程检验的判断流程可表示为：

```mermaid
flowchart TD
    Start[固定山洞数 M] --> LoopPair[枚举野人对 i, j]
    LoopPair --> Eq["方程 (P_i - P_j)x ≡ C_j - C_i (mod M)"]
    Eq --> Exgcd[调用扩展欧几里得求 gcd 与特解]
    Exgcd --> CheckDiv{B 是否被 gcd 整除?}
    CheckDiv -- 否 --> NoMeet[该对永远不相遇，继续下一对]
    CheckDiv -- 是 --> CalcMinX[计算最小非负整数解 x]
    CalcMinX --> CheckLife{x <= min(L_i, L_j)?}
    CheckLife -- 是 --> Collide[在有生之年相遇! M 非法]
    CheckLife -- 否 --> NoMeet
    Collide --> NextM[M 自增, 重新检验]
    NoMeet --> AllChecked{所有对均检验完毕?}
    AllChecked -- 否 --> LoopPair
    AllChecked -- 是 --> Success[找到最小合法 M, 输出并结束]
```

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O((M_{ans} - \max C_i) \cdot N^2 \log M)$。每次检验最多需检查 $\binom{N}{2} \le 105$ 对野人，单次扩展欧几里得为 $O(\log M)$。实际运行时由于剪枝效率极高，不合法的 $M$ 往往在前几对检验中就会被快速淘汰，能在时限内迅速找到解。
- 空间复杂度：$O(N)$，仅存储 $N$ 个野人的初始信息与常数变量开销。

## 总结

本题将环形追及相遇问题转化为模 $M$ 意义下的线性同余方程求解，通过扩展欧几里得算法快速求出最小非负整数解，判断解是否落在共同寿命区间内。结合 $N \le 15$ 的极小数据规模，外层直接递增枚举 $M$ 并配合极强的冲突早停剪枝即可高效求解。
