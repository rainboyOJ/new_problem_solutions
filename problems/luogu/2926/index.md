---
oj: "luogu"
problem_id: "P2926"
title: "[USACO08DEC] Patting Heads S"
description: "统计每个数值出现次数，再把每个除数的频次累加到其所有倍数。"
difficulty: "普及/提高-"
date: 2026-07-16 19:20
toc: true
tags: ["约数", "倍数枚举", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2926
---

[[TOC]]

### 题意

每头牛有数值 `Ai`。牛 `i` 会拍所有其它满足 `Ai` 能被 `Aj` 整除的牛，求每头牛拍几头。

### 思路

先统计每个数值 `d` 出现了多少次。若 `d` 存在，那么所有 `d,2d,3d,...` 都能被它整除，所以把 `frequency[d]` 加到这些倍数的约数牛计数中。

完成后，`divisor_count[Ai]` 包含牛 `i` 自己，需要减一。

### Python 知识

- `array('I')` 用紧凑 4 字节整数保存百万范围频次和答案。
- `range(divisor,maximum+1,divisor)` 直接枚举全部倍数。
- 只对实际出现过的 `divisor` 进入倍数循环。
- 生成器逐行输出原顺序答案。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：百万整数数组的内存差异。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：批量答案生成。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

设最大值为 `V`，倍数枚举约 $O(V\log V)$，空间复杂度 $O(V+n)$。

### 总结

不要为每个 `Ai` 单独枚举约数；从“除数贡献给哪些倍数”反向累加，可以复用相同数值的贡献。
