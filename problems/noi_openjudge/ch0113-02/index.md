---
oj: "noi_openjudge"
problem_id: "ch0113-02"
title: "不吉利日期"
description: "按月份顺序推进星期几，检查每月 13 日是否为星期五。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "日期", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/02/
---

[[TOC]]

### 题意

已知平年一月一日是星期几，输出当月 13 日恰好为星期五的月份。

### 思路

从一月到十二月顺序模拟。若本月一日为 `weekday`，则 13 日晚 12 天；本月结束后再加上本月天数，得到下月一日星期。题目编号星期为 1 到 7，因此每次取模后加回 1。

### 代码

## Python代码

@include-code(./main.py, python)

### 复杂度

固定模拟 12 个月，时间和空间复杂度均为 $O(1)$。

### 总结

日期模拟先明确“当前变量表示哪一天”，可避免加减一天的偏移错误。
