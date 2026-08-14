---
oj: "luogu"
problem_id: "P1873"
title: "[COCI 2011/2012 #5] EKO / 砍树"
description: "二分锯片高度，扫描树高判断当前高度能否得到至少 M 米木材，寻找最大可行高度。"
difficulty: "普及/提高-"
date: 2026-06-18 19:54
toc: true
tags: ["二分答案", "模拟", "python"]
categories: []
pre: []
common:
  - oj: "OpenJ_Bailian"
    problem_id: "4135"
    reason: "同为二分答案模板题，P1873 为最简入门，4135 在此基础上加入贪心分段验证。"
recommend: []
source: https://www.luogu.com.cn/problem/P1873
---

[[TOC]]

### 题意

有 `N` 棵树，每棵树有一个高度。锯片高度设为 `H` 后，只有高于 `H` 的部分会被锯掉。

要求找到最大的整数高度 `H`，使得锯下来的木材总长度至少为 `M`。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素解枚举每个可能高度，计算能得到多少木材。它能帮助理解题意，但正式做法应该利用单调性。

设：

```text
check(H) = 锯片高度为 H 时，能否得到至少 M 米木材
```

当 `H` 越高，锯下来的木材只会越少。因此 `check(H)` 的结果一定形如：

```text
true true true ... true false false ...
```

我们要找的是最后一个 `true`，也就是最大可行高度。

rbook《二分查找》文章中把这类问题归为“二分答案”：直接求最优值不方便，但给定一个答案可以快速检查。

#### 样例中的高度检查

样例树高为：

```text
20 15 10 17
```

这张表展示几个高度能得到的木材。

| 锯片高度 `H` | 得到木材 | 是否至少 `7` |
| --- | --- | --- |
| `14` | `6+1+0+3=10` | 是 |
| `15` | `5+0+0+2=7` | 是 |
| `16` | `4+0+0+1=5` | 否 |

所以最大可行高度是 `15`。

### Python 知识

- `sum(max(0, height - cut) for height in heights)` 直接表达“每棵树贡献超过锯片的部分”。
- 判定只需要总和，不需要保存每棵树被砍下的长度，因此生成器比列表更合适。
- 上取中点 `(left + right + 1) // 2` 用于寻找最后一个可行整数，避免只剩两个候选时死循环。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器与 `sum` 的聚合模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：百万级整数输入使用缓冲区读取。

### 代码

@include-code(./main.cpp, cpp)

Python 教学版本：

### Python 代码

@include-code(./main.py, python)


### 复杂度

- 每次检查扫描所有树，复杂度 $O(N)$。
- 二分高度需要 $O(log maxH)$ 次检查。
- 总时间复杂度 $O(N log maxH)$。
- 空间复杂度 $O(N)$。

### 总结

这题是二分答案入门题。

核心判断是：高度越高，得到木材越少。这个单调性让我们可以在高度范围上二分，找到最高的、仍然能满足需求的锯片高度。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
