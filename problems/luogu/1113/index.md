---
oj: "luogu"
problem_id: "P1113"
title: "[USACO02FEB] 杂务"
description: "利用准备工作编号必然更小的输入顺序，直接计算每项任务的最早完成时间。"
difficulty: "普及/提高-"
date: 2025-12-28 09:04
toc: true
tags: ["DAG", "动态规划", "拓扑序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1113
---

[[TOC]]

### 题意

每项杂务有耗时和若干准备工作。工人数量无限，没有依赖关系的工作可同时进行。求全部杂务完成的最短时间。

### 思路

令 `finish[u]` 表示任务 `u` 的最早完成时刻。它必须等所有准备工作结束后才能开始，因此：

$$finish[u]=duration[u]+\max_{v\in pre(u)}finish[v]$$

没有准备工作时，最大值按 `0` 计算。

题目保证任务按 `1..n` 输入，任务 `u` 的准备工作编号都小于 `u`，所以输入顺序已经是拓扑序。读完一行就能立即算出 `finish[u]`，不必额外建图和拓扑排序。

样例的 DP 状态如下：

| 任务 | 准备工作最晚完成 | 自身耗时 | `finish` |
| --- | ---: | ---: | ---: |
| `1` | `0` | `5` | `5` |
| `2` | `5` | `2` | `7` |
| `4` | `5` | `6` | `11` |
| `6` | `max(7,11)=11` | `8` | `19` |
| `7` | `max(10,12,19)=19` | `4` | `23` |

最终答案是所有 `finish` 的最大值 `23`。

### Python 知识

- 用 `while data[pos]` 读取以 `0` 结尾、长度不固定的准备工作列表。
- `max(current,finish[pre])` 流式维护最晚完成时间，不必保存准备工作。
- `max(finish)` 直接得到所有任务全部结束的时刻。
- 充分利用输入顺序，可以同时省去邻接表、入度数组和队列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：终止标记序列的解析。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：避免不必要的大型图结构。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

设准备关系总数为 `e`，时间复杂度 $O(n+e)$，只保存完成时间，空间复杂度 $O(n)$。

### 总结

依赖 DP 首先要找拓扑顺序。本题已经按拓扑序输入，识别这一点后，可以边读边转移，代码比通用拓扑模板更短。
