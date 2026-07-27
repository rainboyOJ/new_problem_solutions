---
oj: "luogu"
problem_id: "P5741"
title: "【深基7.例10】旗鼓相当的对手 - 加强版"
description: "用元组保存学生成绩，枚举所有学生对并检查三科分差和总分分差。"
difficulty: "普及-"
date: 2026-07-15 21:15
toc: true
tags: ["模拟", "枚举", "结构体", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5741
---

[[TOC]]

### 题意

给出按字典序排列的学生信息。如果两个学生每一科分差都不超过 `5`，且总分分差不超过 `10`，就输出这对学生姓名。输出顺序也要按字典序组合顺序。

### 思路

输入姓名已经按字典序排列。因此只要按下标枚举 `i < j` 的学生对，输出顺序就满足题目要求。

把判断封装成函数：

```python
is_close(left, right)
```

它检查：

- 三科分差都不超过 `5`；
- 总分分差不超过 `10`。

`N <= 1000`，枚举所有学生对是 $O(N^2)$，可以接受。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：`for i in range(n)` 与 `for j in range(i+1, n)` 是枚举无序点对的常用写法。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组可保存固定字段记录。
- `abs(a - b)` 计算分差。
- 把总分和判断逻辑封装成函数，可以让双重循环更清楚。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

枚举所有学生对，时间复杂度是 $O(N^2)$，保存学生信息空间复杂度是 $O(N)$。

### 总结

当输入顺序已经满足输出顺序时，不必额外排序。直接按 `i < j` 枚举学生对，既避免重复，也保证姓名顺序。
