---
oj: "luogu"
problem_id: "P2234"
title: "[HNOI2002] 营业额统计"
description: "离线压缩营业额，用 Fenwick 树动态寻找已出现值中的前驱和后继并累加最近差。"
difficulty: "普及+/提高"
date: 2026-07-16 18:10
toc: true
tags: ["树状数组", "离散化", "前驱后继", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2234
---

[[TOC]]

### 题意

第一天波动值为当天营业额。此后每天的波动值是它与此前任意一天营业额的最小绝对差，求所有波动值之和。

### 思路

在一组有序数中，离新值最近的旧值只可能是它的前驱或后继。问题变成动态维护已出现营业额，并查询前后两个值。

Python 标准库没有平衡树。因为所有营业额已在输入中，可以先 `sorted(set(values))` 离散化，再用 Fenwick 树记录哪些不同值已经出现。

对一个首次出现的值：

1. 前缀和得到比它小的已出现值数量 `less`；
2. Fenwick 的 `kth(less)` 找前驱，`kth(less+1)` 找后继；
3. 取两个差值的较小者；
4. 把当前排名加入树。

重复营业额的波动为零，不必重复加入只记录“是否出现”的树。

### Python 知识

- `sorted(set(values))` 同时完成去重和排序。
- 字典推导式建立“原值到离散排名”的映射。
- `seen` 集合用平均 $O(1)$ 判断重复值。
- `index & -index` 是 Fenwick 树的 lowbit；`kth` 用二进制倍增寻找第 k 个已出现排名。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：排序与规范化。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合与字典。

### 代码

@include-code(./main.py, python)


### 复杂度

离散化为 $O(n\log n)$，每个不同值查询和插入为 $O(\log n)$；总时间 $O(n\log n)$，空间 $O(n)$。

### 总结

动态最近值只需前驱和后继。缺少标准平衡树时，“已知全部值 + 坐标压缩 + Fenwick 第 k 小”是可靠的 Python 替代方案。
