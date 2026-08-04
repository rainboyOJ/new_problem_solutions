---
oj: "codeforces"
problem_id: "25E"
title: "Test"
description: "枚举三个字符串的拼接顺序，用 KMP 求相邻字符串的最大后缀前缀重叠。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "最短公共超串", "全排列", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://codeforces.com/problemset/problem/25/E
---

[[TOC]]

### 题意

求包含给定三个字符串作为子串的最短字符串长度。

### 思路

先说人话：只有 3 个串，顺序只有 $3!=6$ 种，枚举不是难点；真正的难点是把**两个串之间的重叠**用 KMP 在 $O(L)$ 内算出来——而 KMP 的 border 本来只认识"一个串自己"。

#### 从两个串说起：重叠是什么

先退化到只有 A、B 两个串（保留机制的最简情形）：最短超串就是让 A 的**后缀**尽量叠进 B 的**前缀**，合并结果 = `A + B[k:]`，其中 $k$ = 满足"A 的后缀 = B 的前缀"的最大长度。

"后缀 = 前缀"正是 KMP 里 border 的定义——但 border 说的是**同一个串**的前缀等于后缀，这里却是 A 和 B 两个不同的串，一步跨不过去。

#### 双串重叠：拼串降维成单串 border

解法是把两个串的关系压成一个串的性质：对 `B + separator + A` 求前缀函数。分隔符 `\0` 不在小写字母表里，border 不可能跨过它，所以整串的最长 border 恰好就是"B 的前缀 = A 的后缀"——**最后一个 `pi` 值就是最大重叠 $k$**。（代码用等价写法：把 `right` 当模式串在 `left` 上走一遍 KMP 自动机，扫描结束时的 `j` 就是重叠长度。）

这里"先判包含、再算重叠"的顺序很重要：如果 B 已经被 A 包含，直接取 A 即可；此时若先算重叠，KMP 的 `j` 会走满整个 B，结果就是错的。

#### 三个串：枚举顺序 + 贪心为什么安全

固定顺序后每次取最大重叠叠加，6 种顺序全试一遍取最短。会不会担心"前两个串少叠一点，好让第三个串叠得更多"？不会：贪心合并后的串**以 right 为前缀**，所以它与下一个串的重叠只会 ≥ right 与下一个串的重叠——局部取最大重叠，全局不会变差（stays ahead）。

边界情形顺带检查：完全不同字母时重叠为 0，退化成普通拼接；一个串完全包含另一个串时，取较长者即可。

### Python 知识

- `itertools.permutations(strings)` 直接生成 6 种排列。
- `right in left` 使用 Python 底层字符串搜索处理包含关系。
- `min(generator)` 不需要保存所有候选超串。
- `bytes` 可以直接拼接并用 `b"\0"` 作为安全分隔符。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

教学对照版：只用 `string::find` 与 `substr` 比较、不用 KMP，重叠部分最坏 $O(L^2)$：

@include-code(./main-str-find.cpp, cpp)

### 复杂度

排列数为常数，每次合并线性，总时间 $O(|s_1|+|s_2|+|s_3|)$，辅助空间同阶。

### 总结

三个字符串时，枚举顺序比设计复杂状态更直接；KMP 则把最大重叠从平方比较降为线性。
