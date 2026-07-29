---
oj: "leetcodecn"
problem_id: "rotate-array"
title: "轮转数组"
description: "三次反转：整体反转，再分别反转前 k 和后 n-k；先取 k %= n。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "数学", "双指针", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/rotate-array/
---

[[TOC]]

### 题意

将数组右移 k 步，原地修改。

### 思路

暴力每次移动一位 O(nk)。三次反转法 O(n) 时间 O(1) 空间：先整体反转，再反转前 k 个，再反转后 n-k 个。原理：右移 k 步相当于把后 k 个元素移到前面。

也可以用额外数组存结果再复制回来 O(n) 空间。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)，每个元素被反转两次。
- 空间复杂度：O(1)。

### 总结

三次反转是"分段交换"的经典手法。类似思路也用于单词反转、循环移位等场景。
