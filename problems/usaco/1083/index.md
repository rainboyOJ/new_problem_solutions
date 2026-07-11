---
oj: "usaco"
problem_id: "1083"
title: "Uddered but not Herd"
description: "把字母映射到 cowphabet 中的位置，统计听到字符串相邻字母位置不递增的断点数。"
difficulty: "入门"
date: 2026-07-11 13:40
toc: true
tags: ["字符串", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1083
---

[[TOC]]

### 题意

给定牛文字母表的顺序，以及 Farmer John 听到的一串字母。

Bessie 会一遍一遍完整唱这个字母表，Farmer John 可能漏听其中一些字母。求至少唱了几遍，才能让听到的字符串成为这些歌声的子序列。

### 思路

#### 暴力想法

可以枚举 Bessie 唱了几遍，把多遍 cowphabet 拼起来，然后判断听到的字符串是否是它的子序列：

@include-code(./brute.cpp, cpp)

这种方法符合题意，但还可以更直接。

#### 统计断点

记录每个字母在 cowphabet 中的位置。

在同一遍 cowphabet 里，听到的字母位置必须严格递增。如果相邻两个听到的字母满足：

```text
pos[heard[i]] <= pos[heard[i-1]]
```

说明第 `i` 个字母不能继续放在当前这一遍中，必须开启下一遍。

所以答案就是：

```text
1 + 位置序列中非递增断点的数量
```

样例中 cowphabet 是普通顺序，`mood` 的位置变化为：

```text
m -> o 递增
o -> o 不递增，开启新一遍
o -> d 倒退，开启新一遍
```

所以答案是 3。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设听到的字符串长度为 $M$，时间复杂度为 $O(M)$。

使用长度为 26 的位置数组，空间复杂度为 $O(1)$。

### 总结

这题的关键是把自定义字母表转成位置数组。

同一遍字母歌内部，听到的字母位置必须严格递增；每出现一次不递增，就必须多唱一遍。
