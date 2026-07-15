---
oj: "luogu"
problem_id: "P1065"
title: "[NOIP 2006 提高组] 作业调度方案"
description: "按给定顺序逐个安排操作，在工件前序完成后寻找目标机器最早连续空闲时间段。"
difficulty: "普及/提高-"
date: 2026-06-19 02:34
toc: true
tags: ["模拟", "调度", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1065
---

[[TOC]]

### 题意

有 `m` 台机器和 `n` 个工件。每个工件有 `m` 道工序，每道工序指定机器和加工时间。题目给出安排顺序，要求每次把当前工序尽量早地插入目标机器的空闲时间段，同时满足同一工件前序工序已完成。

### 思路

用三个数组维护状态：

- `next_operation[job]`：某个工件下一道要安排的工序编号；
- `job_finish_time[job]`：某个工件上一道工序完成时间；
- `busy[machine][time]`：某台机器某个时刻是否被占用。

处理安排顺序中的一个工件 `job` 时：

1. 找到它当前工序的目标机器和加工时长；
2. 开始时间不能早于 `job_finish_time[job]`；
3. 从这个时间开始向后找，直到找到一段长度为 `duration` 的连续空闲时间；
4. 标记这段机器时间为占用；
5. 更新工件完成时间和答案。

这正好模拟了题目要求的“尽量靠前插入”。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行整数矩阵可以逐行 `input().split()`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：二维列表要逐行创建，避免浅拷贝。
- 布尔矩阵 `busy[machine][time]` 适合表示时间轴占用。
- 遇到冲突时把 `start` 推到冲突时间之后，可以减少无效检查。

### 代码

@include-code(./main.py, python)

### 复杂度

设最终时间轴长度为 `T`，共有 `n*m` 个操作。直接时间轴模拟复杂度约为 $O(nmT)$，本题数据范围很小，可以通过。空间复杂度是 $O(mT)$。

### 总结

调度题不要急着找复杂算法。题目已经规定唯一的靠前插入规则，按顺序找目标机器最早可行空档即可。
