---
oj: "luogu"
problem_id: "P1255"
title: "数楼梯"
description: "用斐波那契式递推统计到达第 n 阶的走法，利用 Python 大整数直接处理 n 到 5000 的答案。"
difficulty: "入门"
date: 2026-07-15 21:50
toc: true
tags: ["动态规划", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1255
---

[[TOC]]

### 题意

楼梯有 `n` 阶，每次可以走 `1` 阶或 `2` 阶。问走到第 `n` 阶有多少种不同走法。

### 思路

设 `dp[i]` 表示走到第 `i` 阶的方案数。

最后一步只有两种可能：

- 从第 `i-1` 阶走 1 阶；
- 从第 `i-2` 阶走 2 阶。

所以：

```text
dp[i] = dp[i-1] + dp[i-2]
```

初始：

```text
dp[1] = 1
dp[2] = 2
```

#### 小 DP 表

| i | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| dp[i] | 1 | 2 | 3 | 5 | 8 |

样例 `n=4`，答案为 `5`。

### Python 知识

- Python 的 `int` 支持大整数，适合这类高精度递推题。
- 只需要保留前两项 `previous` 和 `current`，不用保存整个 DP 数组。
- `previous, current = current, previous + current` 是 Python 常见的状态滚动写法。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

### 总结

这题是斐波那契递推。Python 的大整数让它比 C++ 高精度写法简单很多。
