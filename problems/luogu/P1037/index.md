---
oj: "luogu"
problem_id: "P1037"
title: "[NOIP 2002 普及组] 产生数"
description: "对十个数字求变换传递闭包，再把每一位的可达数字数相乘。"
difficulty: "普及-"
date: 2026-07-17 03:00
updated: 2026-10-18 19:45
toc: true
tags: ["传递闭包", "乘法原理", "位运算", "python", "cpp"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1037
---

[[TOC]]

### 题意

每一位数字可按规则变换任意次，求整个整数能产生多少种不同结果。

### 思路

十个数字上做传递闭包，`reachable[d]` 得到数字 `d` 最终可变成的集合。不同数位独立，根据乘法原理把每一位集合大小相乘。

### Python 知识

- 每个数字集合只需一个整数位掩码。
- `bit_count()` 直接求可达数字种数。
- Python 大整数能直接保存最多 30 位数字产生的巨大答案。

### 代码

#### 位掩码 + 传递闭包（Python 主解）

把 `reachable[d]` 压成一个 10 位掩码，用 Floyd 的三重循环求闭包：中点必须是最外层循环，`start` 能到 `middle` 时把 `middle` 的掩码整个并入。

@include-code(./main.py, python)

#### 位掩码 + 传递闭包（C++）

思路与 Python 主解完全一致，只是用 `long long` 的低 10 位当掩码，`__builtin_popcountll` 数可达数字种数。答案最大约 $10^{30}$，超出 `long long`，所以用 `__int128` 保存并手写输出。

@include-code(./main.cpp, cpp)

#### 集合 + DFS（Python 替代写法）

也可以不做闭包，直接对每个数字从它自己出发 DFS：`nSet[d]` 收集 `d` 在图上能走到的全部数字。`dfs` 靠集合做访问标记，因此环不会无限递归。这个写法更直白地表达“任意次变换”，代价是要真的存 10 个集合。

@include-code(./main-user1.py, python)

### 复杂度

闭包是常数规模，扫描数字串 `O(len(n))`；DFS 写法的图只有 10 个点和至多 15 条边，`O(10 + k)` 预处理后可 `O(len(n))` 回答。

### 总结

每位独立选择时，先求单个符号的闭包，再用乘法原理组合。
