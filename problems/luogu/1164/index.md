---
oj: "luogu"
problem_id: "P1164"
title: "小 A 点菜"
description: "把每种菜看成只能选一次的物品，倒序做计数 0/1 背包，统计恰好花完 M 元的方案数。"
difficulty: "普及-"
date: 2026-06-19 14:47
toc: true
tags: ["动态规划", "01背包", "背包", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1164
---

[[TOC]]

### 题意

有 `N` 种菜，每种菜只有一份，价格为 `a_i`。手里有 `M` 元，问有多少种选菜方案，使总价格恰好等于 `M`。

### 思路

这是 0/1 背包的计数版本。

设 `dp[money]` 表示已经处理过若干道菜后，恰好花掉 `money` 元的方案数。

初始化：

```text
dp[0] = 1
```

表示什么都不点时，花 `0` 元有一种方案。

处理价格为 `price` 的菜时，如果点这道菜，那么所有原本恰好花 `money - price` 元的方案，都能扩展成恰好花 `money` 元的方案：

```text
dp[money] += dp[money - price]
```

因为每道菜只能点一次，所以 `money` 必须倒序枚举。

#### 样例 DP 表格

样例价格为 `1,1,2,2`，目标 `4`：

| 处理菜品 | dp[0] | dp[1] | dp[2] | dp[3] | dp[4] |
|---|---|---|---|---|---|
| 初始 | 1 | 0 | 0 | 0 | 0 |
| 1 | 1 | 1 | 0 | 0 | 0 |
| 1 | 1 | 2 | 1 | 0 | 0 |
| 2 | 1 | 2 | 2 | 2 | 1 |
| 2 | 1 | 2 | 3 | 4 | 3 |

答案为 `dp[4] = 3`。

### Python 知识

- `dp = [0] * (target + 1)` 创建一维背包数组。
- `range(target, price - 1, -1)` 是倒序枚举金额，保证每道菜只用一次。
- Python 整数能直接保存答案；题目也保证答案不超过 32 位整数。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)


### 复杂度

时间复杂度为 $O(NM)$，空间复杂度为 $O(M)$。

### 总结

看到“每个物品最多选一次，恰好凑出某个和，问方案数”，就可以往计数 0/1 背包上想。

### 一图流解析

保留已有一图流图片，作为读完正文后的复盘。

![一图流解析](./one-page-explainer.png)
