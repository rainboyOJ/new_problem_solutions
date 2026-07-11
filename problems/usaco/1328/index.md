---
oj: "usaco"
problem_id: "1328"
title: "Pareidolia"
description: "把每个左端点的贪心匹配看成 token，扫描字符串时同步推进 waiting 状态并统计完成贡献。"
difficulty: "普及+/提高"
date: 2026-07-11 21:17
toc: true
tags: ["字符串", "贪心", "模拟", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1328
---

[[TOC]]

### 题意

对一个字符串 $s$，$B(s)$ 表示从 $s$ 中删除若干字符后，最多能得到多少个连续重复的 `"bessie"`。

给定字符串 $t$，要求计算所有连续子串 $s$ 的 $B(s)$ 之和。

### 思路

先看小数据做法：枚举所有子串，直接在子串上贪心匹配 `"bessie"`。

@include-code(./brute.cpp, cpp)

固定一个子串时，贪心是最优的：尽量早地找 `b`，再尽量早地找 `e`、`s`、`s`、`i`、`e`。越早完成一份 `"bessie"`，留给后面的字符就越多。

暴力的问题是子串太多。我们换个角度，把每个左端点的贪心过程看成一个 token。

`waiting[i]` 表示有多少个 token 正在等待 `"bessie"` 的第 `i` 个字符：

| 状态 | 含义 |
| --- | --- |
| `waiting[0]` | 等待 `b` |
| `waiting[1]` | 已匹配 `b`，等待第一个 `e` |
| `waiting[2]` | 已匹配 `be`，等待第一个 `s` |
| `waiting[3]` | 已匹配 `bes`，等待第二个 `s` |
| `waiting[4]` | 已匹配 `bess`，等待 `i` |
| `waiting[5]` | 已匹配 `bessi`，等待最后的 `e` |
| `waiting[6]` | 刚完成一份 `"bessie"` |

扫描到位置 `i` 时：

1. 新增一个 token，表示从 `i` 开始的子串左端点。
2. 如果当前字符等于 token 等待的字符，就把这些 token 推进一格。
3. 如果有 token 到达 `waiting[6]`，说明它们在位置 `i` 完成了一份 `"bessie"`。

在位置 `i` 完成一份 `"bessie"` 的 token，对所有右端点 `i,i+1,\ldots,n-1` 都会多贡献一次，所以答案增加：

```text
waiting[6] * (n - i)
```

然后这些 token 回到 `waiting[0]`，继续寻找下一份 `"bessie"`。

注意更新时要从后往前扫 `"bessie"` 的字符，避免同一个字符在一次循环里被同一个 token 使用多次。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个字符只检查 `"bessie"` 的 6 个位置。

时间复杂度为 $O(n)$。

空间复杂度为 $O(1)$。

### 总结

本题的核心是把“所有子串”转成“所有左端点的贪心过程”。

每个左端点对应一个 token，`waiting` 数组同时维护所有 token 的进度。完成一次 `"bessie"` 时，它会对所有未来右端点贡献一次，因此直接加上剩余右端点数量。
