---
oj: "luogu"
problem_id: "P1786"
title: "帮贡排序"
description: "先按帮贡和输入顺序给可调整成员重新分配职位，再按职位、等级和输入顺序排序输出。"
difficulty: "普及-"
date: 2026-07-15 21:48
toc: true
tags: ["排序", "模拟", "结构体", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1786
---

[[TOC]]

### 题意

帮派成员有姓名、职位、帮贡和等级。帮主和副帮主职位不能调整；其他人先按帮贡从高到低、输入顺序从前到后排序，重新分配职位。最后按职位高低、等级从高到低、输入顺序从前到后输出。

### 思路

每个成员用字典保存：

```python
name, role, contribution, level, index
```

第一阶段：筛出可调整成员，排序关键字为：

```python
(-contribution, index)
```

然后按名额依次分配 `HuFa`、`ZhangLao`、`TangZhu`、`JingYing`、`BangZhong`。

第二阶段：全体成员排序，关键字为：

```python
(role_rank[role], -level, index)
```

其中 `role_rank` 表示职位从高到低的顺序。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：多关键字排序可以用元组作为 `key`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典适合保存一条记录的多个字段。
- 数字前加负号可以把升序排序变成降序效果。
- Python 排序稳定，但这里显式加入 `index` 更清楚。

### 代码

@include-code(./main.py, python)

### 复杂度

成员数最多 110，排序复杂度是 $O(n\log n)$，空间复杂度是 $O(n)$。

### 总结

本题是典型的两阶段排序模拟：先重新分配职位，再按展示规则排序。把每个排序规则写成清楚的 `key` 元组即可。
