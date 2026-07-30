---
oj: "noi_openjudge"
problem_id: "ch0113-04"
title: "垂直直方图"
description: "统计各大写字母频次，自最高频向下逐层打印星号。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/04/
---

[[TOC]]

### 题意

统计四行文本中 A 到 Z 的出现次数，输出从上到下的垂直直方图。

### 思路

先用 `Counter` 统计频次，最高频决定图的高度。对每一层 `level`，当某字母频次不少于该层就输出 `*`，否则输出空格；每行右侧无意义空格用 `rstrip` 删除。

### 代码

## Python代码

@include-code(./main.py, python)

### 复杂度

设最高频为 $h$，时间复杂度为 $O(26h)$，空间复杂度为 $O(26)$。

### 总结

按高度从大到小打印，可以直接得到竖直图形，不必额外旋转矩阵。
