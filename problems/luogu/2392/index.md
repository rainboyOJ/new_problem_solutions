---
oj: "luogu"
problem_id: "P2392"
title: "kkksc03 考前临时抱佛脚"
description: "每科独立做子集划分，用可达时间集合寻找最接近总时间一半的分配。"
difficulty: "普及-"
date: 2026-07-15 21:50
toc: true
tags: ["动态规划", "背包", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2392
---

[[TOC]]

### 题意

有 4 科题目，每科必须单独完成。做同一科时，左右脑可以同时做两道题，相当于把这一科的题目分给两个处理器，耗时是两边总时间的较大值。

求 4 科总耗时最小值。

### 思路

每科互不影响，可以分别求最优耗时后相加。

对一科题目，问题变成：把若干时间分成两组，使两组总和尽量接近。设总和为 `total`，如果一组时间为 `left`，另一组就是 `total-left`，这一科耗时：

```text
max(left, total - left)
```

用集合 `reachable` 表示“当前能凑出的左脑时间”。初始只有 `{0}`。每加入一道题 `time`，新的可达时间包括：

```text
原来的 current
current + time
```

#### 小 DP 表

例如某科时间为 `[4, 3]`：

| 已处理题目 | reachable |
|---|---|
| 无 | `{0}` |
| 加入 4 | `{0, 4}` |
| 加入 3 | `{0, 3, 4, 7}` |

总和为 `7`，选择 `left=3` 或 `4`，耗时都是 `4`。

### Python 知识

- `set` 很适合保存“能凑出的所有时间”。
- `reachable |= {current + time for current in reachable}` 表示把新可达状态合并回集合。
- 每科写成函数 `subject_time(times)`，主流程只负责读入和累加。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

每科总时间最多 `20 * 60 = 1200`，集合状态数不超过总时间加一。时间复杂度约为 $O(4 \cdot s \cdot sum)$，空间复杂度为 $O(sum)$。

### 总结

“左右脑同时做”本质是把任务划分成两组，使较大的一组尽量小，也就是接近一半的子集和问题。
