---
oj: "leetcodecn"
problem_id: "move-zeroes"
title: "移动零"
description: "双指针：write 指针收集非零元素，剩余补零，保持非零相对顺序。"
difficulty: "简单"
date: 2026-07-28 22:03
toc: true
tags: ["双指针", "数组", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/move-zeroes/
---

[[TOC]]

### 题意

将数组中的 0 全部移到末尾，同时保持非零元素的相对顺序。要求原地修改。

### 思路

维护一个 `write` 指针，指向下一个非零元素应该放置的位置。遍历数组，遇到非零元素就写入 `write` 位置并递增。遍历结束后，`write` 之后的位置全部置零。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

也可以交换而非覆盖，写法更简洁但多一次赋值。

### 复杂度

- 时间复杂度：O(n)，每个元素至多处理一次。
- 空间复杂度：O(1)，只使用几个指针。

### 总结

"收集"型双指针适用于把满足某一条件的元素集中到数组前部，剩余位置用默认值填充。
