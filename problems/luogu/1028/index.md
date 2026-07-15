---
oj: "luogu"
problem_id: "P1028"
title: "[NOIP 2001 普及组] 数的计算"
description: "设 dp[x] 为以 x 开头的合法数列数量，递推为 1 加上所有不超过 x/2 的后继状态数量。"
difficulty: "普及-"
date: 2026-07-15 22:00
toc: true
tags: ["动态规划", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1028
---

[[TOC]]

### 题意

从一个数 `n` 开始构造数列。每次可以在末尾加入一个正整数，但新加入的数不能超过当前最后一项的一半。问一共有多少个合法数列。

### 思路

设 `dp[x]` 表示以 `x` 作为当前最后一项时，后面还能形成多少种合法后续。

最短的数列是只保留 `x` 本身，所以先有 `1` 种。

如果继续添加，新数可以是：

```text
1..x//2
```

因此：

```text
dp[x] = 1 + dp[1] + dp[2] + ... + dp[x//2]
```

从小到大计算 `dp[x]`，答案是 `dp[n]`。

#### 小 DP 表

| x | 可接的新数 | dp[x] |
|---|---|---|
| 1 | 无 | 1 |
| 2 | 1 | 2 |
| 3 | 1 | 2 |
| 4 | 1,2 | 4 |
| 5 | 1,2 | 4 |
| 6 | 1,2,3 | 6 |

样例 `n=6`，答案为 `6`。

### Python 知识

- 用列表 `dp = [0] * (n + 1)` 保存递推结果。
- `value // 2` 是整数除法，对应“不超过一半”。
- 从小到大填表，可以保证用到的 `dp[next_value]` 已经算好。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。`n <= 1000` 可以通过。

### 总结

这题的状态不是“整条数列”，而是“当前最后一个数是多少”。抓住这一点后递推很直接。
