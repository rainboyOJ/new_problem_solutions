---
oj: "luogu"
problem_id: "P2678"
title: "[NOIP 2015 提高组] 跳石头"
description: "二分最短跳跃距离，贪心统计给定距离下最少需要移走的石头数。"
difficulty: "普及/提高-"
date: 2026-06-18 20:04
toc: true
tags: ["二分答案", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2678
---

[[TOC]]

### 题意

有一条长为 `L` 的河道，起点和终点固定，中间有 `N` 块岩石。
你最多可以移走 `M` 块中间岩石，要求剩余相邻点之间的最短跳跃距离尽可能大。

### 思路

先看一个可以直接验证想法的朴素解：

在小数据上，我们可以把答案 `d` 从小到大往上试，只要它还可行就继续增大，直到第一次不可行。
前一个可行值就是答案。

@include-code(./brute.cpp, cpp)

下面是另一种「01 序列」风格的暴力写法。它按石头编号依次决定移走或保留，递归生成完整选择后，叶子节点统一检查移走数量是否不超过 `M`，并统计当前最短跳跃距离：

<details>
<summary>另一种暴力写法：01 序列</summary>

@include-code(./brute_01_style.cpp, cpp)

</details>

这个朴素解的问题在于，`d` 的范围最大可以到 `L`，直接枚举会太慢。
但它已经把题目拆成了两个部分：

1. 固定一个距离 `d`，怎么判断它能不能做到；
2. 如何更快地找到最大的可行 `d`。

对于第一个问题，排序后从左到右贪心扫描即可。
如果当前石头和上一个保留点的距离已经小于 `d`，那这块石头只能删除。
这样一来，固定 `d` 时需要删除的最少石头数就能被算出来。

有了这个可行性判断以后，就可以对答案二分。
因为 `d` 越大越难满足，所以“是否可行”具有单调性：
可行的 `d` 之前都可行，不可行的 `d` 之后都不可行。

### Python 知识

- `stones = positions + [length]` 把终点并入同一次扫描，避免循环结束后再写一段特殊判断。
- Python 的 `for position in stones` 直接遍历位置值，不需要维护 C++ 数组下标。
- `previous` 保存上一个保留点；距离不足时只增加删除数，否则更新保留点。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：按 token 读取整数并用切片取得石头位置。

### 代码

@include-code(./main.py, python)

### 复杂度

排序复杂度是 $O(N log N)$。
每次检查是 $O(N)$，二分次数是 $O(log L)$。

所以总时间复杂度是 $O(N log N + N log L)$，空间复杂度是 $O(N)$。

### 总结

这题的关键是把“最短跳跃距离最大化”转成“答案二分”。
对于固定距离，用贪心扫描统计最少删除数，就能快速判断这个距离是否可行。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
