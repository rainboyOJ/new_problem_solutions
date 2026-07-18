---
oj: "luogu"
problem_id: "P4956"
title: "[COCI 2017/2018 #6] Davor"
description: "把 52 周存钱总额化为 N=364X+1092K，从大到小枚举 X 找到合法 K。"
difficulty: "入门"
date: 2026-07-15 18:39
toc: true
tags: ["数学", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4956
---

[[TOC]]

### 题意

每周七天存的钱分别是：

```text
X, X+K, X+2K, ..., X+6K
```

一共存 `52` 周，给出总额 `N`，求满足条件的 `X` 和 `K`。如果有多组答案，要求输出最大的 `X`，同时 `K` 最小。

### 思路

先把一周的总额合并：

```text
7X + (0+1+2+3+4+5+6)K = 7X + 21K
```

一年 `52` 周，所以：

```text
N = 52 * (7X + 21K) = 364X + 1092K
```

题目限制 `X <= 100`，范围很小。为了得到最大的 `X`，直接从 `100` 到 `0` 倒着枚举 `X`。对每个 `X`，检查剩下的钱是否能被 `1092` 整除，且 `K > 0`。

第一个找到的合法 `X` 就是最大 `X`，对应的 `K` 也满足题目要求。

这题的枚举空间很小，正解已经是直接枚举，不创建额外 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `int(input())` 读取总额。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：本题只用整数加减乘除，Python `int` 足够稳定。
- `range(100, -1, -1)` 表示从 `100` 倒着枚举到 `0`。
- `rest % 1092 == 0` 用来判断能否整除。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

枚举倒推：

@include-code(./main-pythonic.py, python)

### 复杂度

最多枚举 `101` 个 `X`，时间复杂度是 $O(1)$，空间复杂度是 $O(1)$。

### 总结

这题先做代数化简，再利用 `X` 范围很小倒序枚举。倒序枚举让“最大 `X`”这个要求自然满足。
