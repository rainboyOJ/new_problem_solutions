---
oj: "noi_openjudge"
problem_id: "ch0113-07"
title: "玛雅历"
description: "将 Haab 日期换算为总天数，再按 Tzolkin 的 13、20、260 周期取模。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "日期", "映射", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/07/
---

[[TOC]]

### 题意

把 Haab 历日期转换为 Tzolkin 历日期。

### 思路

建立 Haab 月名到编号的映射，先算从世界开始经过的总天数。Tzolkin 的数字周期为 13、名称周期为 20、年份周期为 $13\times20=260$，因此分别取模和整除即可。

### 代码

## Python代码

@include-code(./main.py, python)

### 复杂度

每个日期时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

跨历法转换的核心是先统一到从起点开始的总天数。
