---
oj: "shumeng"
problem_id: "CSP202403B"
title: "相似度计算"
description: "统一将单词转为小写后分别去重，再用集合查询交集并由容斥公式得到并集。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["字符串", "集合", "哈希表"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202403B
---

[[TOC]]

### 题意

给出两篇文章的单词序列，忽略大小写后分别得到单词集合 $A,B$，输出 $|A\cap B|$ 和 $|A\cup B|$。

### 思路

先看使用有序集合去重的朴素实现：

@include-code(./brute.cpp, cpp)

读入每个单词时先把 `A` 到 `Z` 转为 `a` 到 `z`，再分别插入两张集合。遍历第一张集合统计其中也出现在第二张集合的单词数，得到交集大小；并集使用容斥公式：

$$|A\cup B|=|A|+|B|-|A\cap B|。$$

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设总输入单词数为 $n+m$。使用哈希集合的平均时间复杂度为 $O(n+m)$，空间复杂度为 $O(n+m)$；单词长度最多 10，大小写转换的开销包含在常数中。

### 总结

集合统计题要先明确“同一个元素”的判定规则。本题的大小写归一化必须在插入集合前完成，否则同一单词会被错误地分成多个元素。
