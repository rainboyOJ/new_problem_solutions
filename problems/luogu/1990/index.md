---
oj: "luogu"
problem_id: "P1990"
title: "覆盖墙壁"
description: "使用 2×N 多米诺与 L 形砖铺法递推，满足 f[n]=2f[n-1]+f[n-3]，每步只保留最后四位。"
difficulty: "普及-"
date: 2026-07-15 22:15
toc: true
tags: ["动态规划", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1990
---

[[TOC]]

### 题意

用 `2x1` 砖和 L 形三格砖覆盖 `2 x N` 的墙壁，砖可以旋转，问覆盖方案数的最后四位。

### 思路

这是经典的 `2 x N` 铺砖递推。设 `dp[n]` 表示覆盖 `2 x n` 墙壁的方案数。

初始：

```text
dp[0] = 1
dp[1] = 1
dp[2] = 2
```

对 `n >= 3`，递推为：

```text
dp[n] = 2 * dp[n-1] + dp[n-3]
```

题目只要求最后四位，所以每次递推后对 `10000` 取模即可。

#### 小 DP 表

| n | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| dp[n] | 1 | 1 | 2 | 5 | 11 |

题面也给出 `2x3` 有 `5` 种覆盖方法，与表格一致。

### Python 知识

- 用列表保存 `dp`，递推时直接按下标访问前三项。
- `% 10000` 保留最后四位。
- 输出时不用补前导零，直接 `print(dp[n])`。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

时间复杂度为 $O(N)$，空间复杂度为 $O(N)$。也可以滚动数组优化到 $O(1)$。

### 总结

这题重点是识别铺砖递推，并且从一开始就按题目要求保留最后四位，避免大数增长。
