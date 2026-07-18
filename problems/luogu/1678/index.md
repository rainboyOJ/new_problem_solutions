---
oj: "luogu"
problem_id: "P1678"
title: "烦恼的高考志愿"
description: "排序学校分数线后，对每个学生二分找到左右相邻候选，累加最近分数线差值。"
difficulty: "普及-"
date: 2026-06-18 19:23
toc: true
tags: ["二分", "排序", "模拟", "python"]
categories: []
pre: []
common:
  - oj: "atcoder"
    problem_id: "abc248_d"
    reason: "同为在有序数组中使用二分查找定位目标值的应用。"
recommend: []
source: https://www.luogu.com.cn/problem/P1678
---

[[TOC]]

### 题意

有 `m` 所学校，每所学校有一个预计分数线；有 `n` 位学生，每位学生有一个估分。

对每位学生，要推荐一所分数线和他的估分差距最小的学校。这个最小差值就是该学生的不满意度。

要求输出所有学生不满意度之和。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素做法对每个学生枚举所有学校，求最小绝对差。这个做法是 $O(nm)$，在 `n,m <= 100000` 时会超时。

把学校分数线排序后，对于一个学生分数 `x`，离它最近的学校只可能在分界点两侧：

- 第一个 `>= x` 的学校；
- 这个学校前面的学校。

rbook《二分查找》文章中把这类问题归为“最近元素”：先用 `lower_bound` 找分界点，再比较前驱和当前位置。

#### 样例查找过程

样例学校分数线排序后为：

```text
513 567 598 689
```

这张表展示每个学生的左右候选和不满意度。

| 学生估分 | 右侧第一个不小于它的分数线 | 左侧相邻分数线 | 最小差值 |
| --- | --- | --- | --- |
| `500` | `513` | 无 | `13` |
| `600` | `689` | `598` | `2` |
| `550` | `567` | `513` | `17` |

总不满意度是 `13 + 2 + 17 = 32`。

### Python 知识

- `sorted(...)` 返回新的有序学校列表，保留输入切片的原值。
- `bisect_left` 等价于 C++ 的 `lower_bound`；返回位置左右两侧就是最近值的全部候选。
- `math.inf` 作为不存在的左/右候选距离，使边界和普通情况共用一次 `min`。
- `sum(map(dissatisfaction, students))` 表达“逐个映射不满意度，再求和”。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted` 的返回值和排序语义。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：已有命名函数时使用 `map`。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

bisect：

@include-code(./main-pythonic.py, python)

### 复杂度

- 排序学校分数线需要 $O(m log m)$。
- 每个学生做一次二分，需要 $O(log m)$，总共 $O(n log m)$。
- 总时间复杂度 $O(m log m + n log m)$。
- 空间复杂度 $O(n + m)$。

### 总结

这题的关键是把“最近”转成有序数组上的分界点问题。

二分找到第一个不小于目标值的位置后，不要只看这个位置，还要看它前面的那个位置。最近元素一定在这两个候选中。
