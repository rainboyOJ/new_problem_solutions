---
oj: "leetcodecn"
problem_id: "group-anagrams"
title: "字母异位词分组"
description: "为每个单词构造 26 字母计数 key，哈希到同一组；异位词一定有相同的字母构成。"
difficulty: "中等"
date: 2026-07-28 21:58
toc: true
tags: ["哈希表", "字符串", "排序", "cpp"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/group-anagrams/
---

[[TOC]]

### 题意

给定字符串数组 `strs`，把字母异位词分在同一组。可以按任意顺序返回结果。

字母异位词（anagram）指由相同字母重新排列形成的词，例如 `"eat"`、`"tea"`、`"ate"`。

### 思路

最直接的做法是：对每个字符串排序，排序结果相同的词就是异位词。

@include-code(./brute.cpp, cpp)

排序需要 $O(k \log k)$ 处理一个词，总复杂度 $O(n \cdot k \log k)$。对于 $n \le 10^4$、$k \le 100$ 可以接受，但并非最优。

优化的关键是：异位词的字母构成完全一样，因此可以用 26 个字母的计数作为分组 key。构造 key 的时间只需 $O(k)$，且 key 长度固定（26 个计数值串接）。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

另一种备选方案是用质数乘积做 key——每个字母映射到一个质数，乘积相同的词一定是异位词。但 $k=100$ 时乘积可能溢出 64 位整数，需要大整数或模数，不推荐。

### 复杂度

- 时间复杂度：$O(n \cdot k)$，每个词需要一次 $O(k)$ 的计数和 key 构造。
- 空间复杂度：$O(n \cdot k)$，哈希表存储所有词的 key 和分组结果。

### 总结

把"排序比较"转化为"计数比较"是处理异位词的常用手法，核心是定义一个函数 $f(s)$，使得 $f(s_1) = f(s_2)$ 当且仅当 $s_1, s_2$ 是异位词。
