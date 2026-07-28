---
oj: "leetcodecn"
problem_id: "two-sum"
title: "两数之和"
description: "遍历数组时用哈希表保存值到下标的映射，在线查找当前数所需的补数。"
difficulty: "入门"
date: 2026-07-28 18:13
toc: true
tags: ["哈希表", "数组", "python", "cpp"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/two-sum/
---

[[TOC]]

### 题意

给定整数数组 `nums` 和整数 `target`，找出两个不同下标 `i`、`j`，使得 `nums[i] + nums[j] = target`，并返回这两个下标。

题目保证答案唯一，因此找到第一组合法下标后即可返回。LeetCode 使用函数签名提交，不需要自行读取标准输入。

### 思路

最直接的办法是枚举所有满足 `i < j` 的下标对，逐一检查两数之和：

@include-code(./brute.cpp, cpp)

这种做法不会漏掉任何下标对，但需要检查 $O(n^2)$ 个候选，无法满足进阶要求。

优化的关键是：扫描到当前值 `value` 时，只需知道它的补数 `target - value` 是否在前面出现过。用字典 `index_by_value` 保存“已经扫描过的值到下标”的映射，就能平均 $O(1)$ 完成一次查找。

代码必须先查询补数，再记录当前值。这样字典中只有当前下标之前的元素，不会把同一个位置使用两次；对于 `[3, 3]` 这样的重复值，第一个 `3` 会先被记录，扫描到第二个 `3` 时便能正确返回两个不同下标。

若唯一答案的下标为 $p < q$，扫描到 $q$ 时，`nums[p]` 已经存入字典，并且恰好等于 `target - nums[q]`，所以算法一定会找到答案。返回的两个下标对应的值之和等于目标值，因此返回结果也一定合法。

Python 中，`enumerate(nums)` 同时取得下标和值；`complement in index_by_value` 利用字典的平均 $O(1)$ 成员查询。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

另一种思路是排序后双指针：先对数组排序（同时保留原始下标），再用左右指针向中间扫描。排序 $O(n \log n)$，扫描 $O(n)$，总时间复杂度 $O(n \log n)$。

@include-code(./two-pointer.cpp, cpp)

### 复杂度

- 时间复杂度：平均 $O(n)$，每个元素只扫描一次，每次字典查询和插入平均为 $O(1)$。
- 空间复杂度：$O(n)$，最坏情况下字典保存前面所有元素。

### 总结

当题目要求寻找满足关系的一对元素时，可以把“枚举另一个元素”改成“查询另一个元素”。本题把补数作为查询键，用额外的哈希表空间将二重枚举优化为一次扫描。
