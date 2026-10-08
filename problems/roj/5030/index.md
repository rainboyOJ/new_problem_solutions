---
oj: "roj"
problem_id: "5030"
title: "【例4.14】百钱买百鸡"
description: "通过两层循环枚举鸡翁和鸡母的数量，根据百鸡计算鸡雏数量，并判断钱数是否等于一百。"
difficulty: "入门"
date: 2026-10-08 19:48
updated: 2026-10-08 19:48
toc: true
tags:
  - 暴力枚举
favorite: false
favorite_reason: ""
categories:
  - 基础算法
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/5030
---

[[TOC]]

## 形式化题目

已知鸡翁每只 $5$ 钱，鸡母每只 $3$ 钱，鸡雏 $3$ 只 $1$ 钱。
现有 $100$ 钱，要买 $100$ 只鸡。
求鸡翁（$rooster$）、鸡母（$hen$）、鸡雏（$chick$）各买多少只？
要求按照鸡翁数量从小到大输出所有可行解。

即求满足以下条件的所有非负整数解 $(rooster, hen, chick)$：
1. $rooster + hen + chick = 100$
2. $5 \times rooster + 3 \times hen + \frac{chick}{3} = 100$
3. $chick \bmod 3 = 0$

输出格式：每行输出一组解的 $rooster, hen, chick$，用空格分隔，末尾带有单个换行，按 $rooster$ 升序排列。

## 正解

### 思路

这是一道经典的枚举题目。
朴素的做法是写三重循环，分别枚举 $rooster, hen, chick$，但这样时间复杂度是 $O(100^3)$，不够优。

**优化思路**：
1. 由于总数为 $100$，只要确定了 $rooster$ 和 $hen$，$chick$ 的值就固定为 $100 - rooster - hen$。这样可以省去 $chick$ 的枚举，将复杂度降为两重循环。
2. 进一步缩小枚举范围：
   - 鸡翁 $5$ 钱一只，最多买 $100 / 5 = 20$ 只，因此循环条件为 $rooster \times 5 \le 100$。
   - 鸡母 $3$ 钱一只，最多买 $100 / 3 = 33$ 只，因此循环条件为 $hen \times 3 \le 100$。
3. 对每个确定的 $rooster$ 和 $hen$，求出 $chick = 100 - rooster - hen$。判断是否满足：
   - $chick \ge 0$
   - $chick$ 是 $3$ 的倍数（因为鸡雏是按 $3$ 只一组卖的）
   - $5 \times rooster + 3 \times hen + chick / 3 = 100$
如果全满足，则找到了一组解。题目要求按依次由小到大输出，我们的外层循环正是以 $rooster$ 从小到大枚举的，所以天然给出了升序输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**：$O(N \times M)$，其中 $N = 20, M = 33$。外层循环执行 $21$ 次，内层循环执行 $34$ 次，总共约进行 $700$ 次判断，复杂度为常数级别 $O(1)$，非常小。
- **空间复杂度**：$O(1)$，只需常数级别的变量用于循环和计算。

## 总结

经典的一道利用等式约束减少循环层数的枚举题。
关键点及容易踩坑的地方如下：
1. **隐藏条件与等价方程**：本题等价于解三元一次方程组：
   $$rooster + hen + chick = 100$$
   $$5 \times rooster + 3 \times hen + \frac{chick}{3} = 100$$
   将第一个式子的 $chick$ 代入第二个式子，可以消元得到：
   $$7 \times rooster + 4 \times hen = 100$$
   由此可得 $rooster$ 必须是 4 的倍数（因为 $4 \times hen$ 和 $100$ 都是 4 的倍数）。所以解的 $rooster$ 只能是 $0, 4, 8, 12, \dots$。这也解释了为何最终只有这 4 组解（$16 \times 7 > 100$ 已经被排除）。
2. **截断除法陷阱**：鸡雏的价值是 $\frac{1}{3}$ 钱一只，说明鸡雏的数量 $chick$ 必须是 $3$ 的倍数。必须加上 `chick % 3 == 0` 的判断。如果不用这个判断，而是直接算整数除法 `chick / 3` 或向下取整 `chick // 3`，在 C++ 和 Python 中会发生截断，从而把本来不成立的解（花费变少）错误地判定为等于 $100$。
3. **输出顺序与格式**：题目要求依次由小到大输出。通过将 $rooster$ 放在外层循环从小到大枚举，输出天然就是按 $rooster$ 升序的。另外，每行输出三个数并用空格隔开，末尾单个换行，且不要带有多余空行。