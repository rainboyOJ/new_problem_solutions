---
oj: "luogu"
problem_id: "P2670"
title: "[NOIP 2015 普及组] 扫雷游戏"
description: "枚举每个非雷格的八个方向邻格，统计周围地雷数量并生成答案矩阵。"
difficulty: "入门"
date: 2026-07-15 21:22
toc: true
tags: ["模拟", "矩阵", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2670
---

[[TOC]]

### 题意

给出扫雷棋盘，`*` 表示地雷，`?` 表示非雷格。对每个非雷格，输出它周围八个方向中地雷的个数；地雷格仍输出 `*`。

### 思路

先列出八个方向：

```python
(-1,-1), (-1,0), ..., (1,1)
```

枚举每个格子：

- 如果当前是 `*`，答案也是 `*`；
- 否则枚举八个邻格，检查是否在边界内且为 `*`，统计数量。

每一行用字符列表构造，最后 `"".join(current)` 变成输出字符串。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符网格可按行保存为字符串列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：二维矩阵枚举常用 `for row` / `for col` 双循环。
- `0 <= nr < n and 0 <= nc < m` 是常见边界判断。
- `"\n".join(answer)` 一次输出多行。

### 代码

@include-code(./main.py, python)


### 复杂度

每个格子最多检查 8 个方向，时间复杂度是 $O(nm)$，空间复杂度是 $O(nm)$。

### 总结

网格邻域题先固定方向数组，再对每个格子套同一套边界判断和统计逻辑。
