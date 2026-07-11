---
oj: "usaco"
problem_id: "1493"
title: "Printing Sequences"
description: "按 PRINT 数量分成 degree 1/2/3，分别检查全相同、块循环和循环体切分。"
difficulty: "普及/提高-"
date: 2026-07-11 15:14
toc: true
tags: ["递归", "枚举", "思维", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1493
---

[[TOC]]

### 题意

有一种简单语言：

- `PRINT c` 输出一个数字 `c`。
- `REP o ... END` 把内部程序重复执行 `o` 次。

`REP` 数量不限，但 `PRINT` 语句最多只能使用 $K$ 个。给定目标序列，判断能否输出它。

其中 $1 \leqslant K \leqslant 3$。

### 思路

先看一个更贴近程序定义的小数据判断：

@include-code(./brute.cpp, cpp)

这个暴力用 `can_print(l,r,p)` 表示区间 `[l,r]` 能否用不超过 `p` 个 `PRINT` 输出。它枚举两种程序结构：两个子程序拼接，或者某个更短程序被 `REP` 重复。这个模型贴近题意，但正式解法可以利用 $K \leqslant 3$ 写得更直接。

把“能用不超过 $d$ 个 `PRINT` 输出”称为 degree $d$。

#### degree 1

只用一个 `PRINT`，输出的所有数字必须相同。

所以 `check1(l,r)` 只需要检查区间是否全相同。

#### degree 2

两个 `PRINT` 可以形成两个连续片段，然后这个循环体被 `REP` 重复。

把序列压缩成连续块，例如：

```text
1 1 1 2 2 1 1 1 2 2
=> (1,3), (2,2), (1,3), (2,2)
```

如果它是 degree 2，那么块序列应该每隔两个重复一次。也就是第 $i$ 个块要和第 $i+2$ 个块完全相同，块值和块长都要相同。

块数为 1 或 2 时也可以直接输出。

#### degree 3

对 $K=3$，枚举外层 `REP` 的循环体长度 `len`。如果整个序列不是由长度为 `len` 的前缀重复得到，就跳过。

如果找到了一个循环体，还需要判断这个循环体能否拆成：

- degree 1 + degree 2
- 或 degree 2 + degree 1

所以再枚举循环体内部的切分点，调用 `check1` 和 `check2` 即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

$N \leqslant 100$，直接枚举周期长度和切分点可以通过。

`check1` 和 `check2` 都是线性的；`check3` 按官方分析可视为 $O(N^2)$ 级别。

空间复杂度为 $O(N)$。

### 总结

本题的关键是不要枚举程序文本，而是按 `PRINT` 数量分析输出序列的结构。

$K=1$ 是全相同，$K=2$ 是块循环，$K=3$ 则枚举外层循环体并把它拆成 degree 1 与 degree 2 两部分。
