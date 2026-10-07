---
oj: "luogu"
problem_id: "P1808"
title: "单词分类"
description: "把每个单词内部字母排序成标准形，用集合统计不同标准形的个数，就是不同类别数。"
difficulty: "普及-"
date: 2026-06-19 10:19
updated: 2026-10-06 07:45
toc: true
tags: ["字符串", "排序"]
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0111-08"
    reason: "B 沿用 A 的把元素放入集合自动去重这一步数不同标准形个数，先给单词内部字母排序归一再入集合"
  - oj: "noi_openjudge"
    problem_id: "ch0110-09"
    reason: "B 复用 A 教的「set 自动去重、按排序结果作标准形」这一步（单词排序后入 set 数集合大小），再叠加 A 未教的字母异位词标准形与数类别数的目标。"
recommend: []
source: https://www.luogu.com.cn/problem/P1808
common:
  - oj: "luogu"
    problem_id: "P1059"
    reason: "同难度同型题（M5 自 pre 移入；master 重新定级后两者同档）：B 复用 A 教的「用 set 自动去重、以排序结果作标准形」这一步（把单词排序后插入 set 数集合大小），再叠加 A 未教的字母异位词标准形与输出类别数的目标。"
---

[[TOC]]

### 题意

给出 `n` 个只含大写字母的单词。

如果两个单词中每个字母出现次数完全相同，就把它们归为同一类。

要求输出总共有多少类。

### 思路

这题的关键是给每个单词找一个统一的“标准形”。

最直接的教学版写法如下：

@include-code(./brute.cpp, cpp)

把单词内部字母排序后：

- 同类单词一定变成同一个字符串；
- 不同类单词一定变成不同字符串。

所以我们只要：

1. 对每个单词排序；
2. 把排序结果放入集合；
3. 输出集合大小。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n * L log L)$
- 空间复杂度：$O(nL)$

其中 `L` 是单词长度。

### 总结

这题本质上是在数“有多少种不同的标准形”。

把异位词问题转成排序后去重，是最直接也最稳的写法。
