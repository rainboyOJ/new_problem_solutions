---
oj: "luogu"
problem_id: "P1161"
title: "开灯"
description: "用集合保存当前开着的灯，每次操作到某灯就按存在性切换其开关状态。"
difficulty: "入门"
date: 2026-07-15 18:54
toc: true
tags: ["模拟", "集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1161
---

[[TOC]]

### 题意

初始所有灯都是关的。每次操作给出实数 `a` 和整数 `t`，依次切换编号：

```text
floor(a), floor(2a), ..., floor(ta)
```

所有操作完成后，题目保证恰好只有一盏灯是开的，输出它的编号。

### 思路

灯只关心“当前是否开着”。可以用集合 `on_lights` 保存所有当前开着的灯。

当某盏灯被按一次：

- 如果它已经在集合里，说明原来开着，按完变关，从集合删除；
- 如果它不在集合里，说明原来关着，按完变开，加入集合。

这正好是“切换状态”的含义。

所有操作结束后，集合里只剩一个元素，用 `next(iter(on_lights))` 取出来输出。

这题是集合模拟开关状态，不创建额外 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：每行混合实数和整数时，可以先 `split()` 再分别转换。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 适合保存当前打开的灯，并支持快速增删查。
- `int(a * k)` 对正数等价于向下取整。
- `next(iter(on_lights))` 从只含一个元素的集合中取出这个元素。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

集合对称差 `on_lights ^= {light}` 一键切换开关：

@include-code(./main-pythonic.py, python)

### 复杂度

总操作次数为 `T = sum(t_i)`，每次集合增删查均摊 $O(1)$，总时间复杂度是 $O(T)$。空间复杂度取决于同时开着的灯数量，最坏 $O(T)$。

### 总结

开关题最适合用集合表示“当前为开”的对象。每次被按到就把成员关系反转，最后集合中剩下的就是答案。
