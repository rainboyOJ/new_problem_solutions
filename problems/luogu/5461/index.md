---
oj: "luogu"
problem_id: "P5461"
title: "赦免战俘"
description: "从全 1 矩阵开始递归处理方阵，每次把当前区域左上四分之一改成 0。"
difficulty: "普及-"
date: 2026-07-15 21:15
toc: true
tags: ["递归", "矩阵", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5461
---

[[TOC]]

### 题意

有一个 `2^n * 2^n` 的方阵。每次把当前方阵分成四个等大的小方阵，左上角小方阵全部赦免，剩下三个小方阵继续递归执行同样操作。输出最终矩阵，`0` 表示赦免，`1` 表示未赦免。

### 思路

先把整个矩阵初始化为 `1`。定义递归函数：

```python
pardon(top, left, size)
```

表示处理左上角为 `(top, left)`、边长为 `size` 的子方阵。

如果 `size == 1`，无法继续划分，直接返回。否则令 `half = size // 2`：

1. 把当前区域左上 `half * half` 的格子改成 `0`；
2. 对右上、左下、右下三个子方阵递归处理。

这题递归过程本身就是正解，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：二维列表应使用列表推导式逐行创建，避免浅拷贝问题。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`print(*row)` 可以按空格输出一行数字。
- `2 ** n` 表示 $2^n$。
- 递归函数参数保存当前子问题的位置和规模。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

矩阵大小为 `S = 2^n`。每个格子最多被赋值一次为 `0`，输出也需要处理 `S^2` 个格子，时间复杂度是 $O(S^2)$，空间复杂度是 $O(S^2)$。

### 总结

递归矩阵题要把“当前处理哪一块”写进函数参数。初始化全 1，再递归覆盖左上块为 0，能直接对应题意。
