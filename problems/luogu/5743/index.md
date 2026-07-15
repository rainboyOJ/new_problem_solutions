---
oj: "luogu"
problem_id: "P5743"
title: "【深基7.习8】猴子吃桃"
description: "从第 n 天剩 1 个桃子倒推，每往前一天执行 peaches=(peaches+1)*2。"
difficulty: "入门"
date: 2026-07-15 21:22
toc: true
tags: ["递推", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5743
---

[[TOC]]

### 题意

猴子每天吃掉当前桃子的一半再多吃一个。第 `n` 天早上只剩 1 个桃子，求最开始有多少个桃子。

### 思路

正向吃桃不方便，因为不知道初始值。反过来想：如果某天早上剩 `peaches` 个，那么前一天早上吃之前应有：

```text
(peaches + 1) * 2
```

从第 `n` 天的 `1` 个桃子开始，倒推 `n-1` 次即可。

这题是倒推递推练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：单个整数输入用 `int(input())`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 整数适合直接做递推乘法。
- `for _ in range(n - 1)` 表示重复执行固定次数，不关心循环变量。

### 代码

@include-code(./main.py, python)

### 复杂度

循环 `n-1` 次，时间复杂度是 $O(n)$，空间复杂度是 $O(1)$。

### 总结

遇到“最后剩多少，求最开始多少”的题，常常从末尾倒推更自然。
