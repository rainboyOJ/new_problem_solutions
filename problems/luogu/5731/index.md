---
oj: "luogu"
problem_id: "P5731"
title: "【深基5.习6】蛇形方阵"
description: "用方向数组按右、下、左、上的顺序行走，遇到边界或已填格就右转。"
difficulty: "入门"
date: 2026-07-15 18:54
toc: true
tags: ["模拟", "矩阵", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5731
---

[[TOC]]

### 题意

给出 `n`，输出一个 `n * n` 的蛇形方阵。从左上角填 `1` 开始，按顺时针方向填完整个矩阵。每个数字占 `3` 个字符宽度。

### 思路

用二维列表 `matrix` 保存方阵，未填的位置为 `0`。

蛇形填数的方向顺序固定为：

```text
右 -> 下 -> 左 -> 上
```

所以准备方向数组：

```text
[(0, 1), (1, 0), (0, -1), (-1, 0)]
```

每填完一个数，先尝试沿当前方向走到下一格。如果下一格越界，或者已经填过数，就把方向右转一格，再计算下一格。

最后输出矩阵时，每个数字用 `f"{value:3d}"` 保证宽度为 `3`。

这题是矩阵模拟和格式化输出练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：二维矩阵可以用列表推导式创建。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `"".join(...)` 拼接一整行输出。
- `directions[direction]` 用下标选择当前方向。
- `direction = (direction + 1) % 4` 表示按顺时针右转。
- `f"{value:3d}"` 表示整数右对齐，占 `3` 个字符宽度。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

方向数组蛇形：

@include-code(./main-pythonic.py, python)

### 复杂度

每个格子填一次，时间复杂度是 $O(n^2)$，矩阵空间复杂度是 $O(n^2)$。

### 总结

蛇形矩阵的关键是“尝试前进，不能走就右转”。用方向数组可以避免写四段重复逻辑。
