---
oj: "luogu"
problem_id: "P1786"
title: "帮贡排序"
description: "先按帮贡和输入顺序给可调整成员重新分配职位，再按职位、等级和输入顺序排序输出。"
difficulty: "普及-"
date: 2026-07-15 21:48
updated: 2026-10-06 07:45
toc: true
tags: ["排序", "模拟", "结构体", "python"]
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0110-03"
    reason: "B 复用 A 的负号改降序、多关键字压成一条元组排序键的写法，扩成职位高低、等级、输入顺序三级规则"
recommend: []
source: https://www.luogu.com.cn/problem/P1786
common:
  - oj: "luogu"
    problem_id: "P1104"
    reason: "同难度同型题（M5 自 pre 移入；master 重新定级后两者同档）：B 复用 A 的把多级比较规则翻译成元组排序键（负号降序、输入顺序兜底）这一步，做先重排职位再全体输出的两阶段排序"
  - oj: "luogu"
    problem_id: "P1093"
    reason: "同难度同型题（M5 自 pre 移入；master 重新定级后两者同档）：B 沿用 A 的多规则压成排序键元组、降序取负升序用原值、末位输入序号兜底这一步，套在两段排序上再叠加职位重分配"
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

@include-code(./main.cpp, cpp)


### 复杂度

成员数最多 110，排序复杂度是 $O(n\log n)$，空间复杂度是 $O(n)$。

### 总结

本题是典型的两阶段排序模拟：先重新分配职位，再按展示规则排序。把每个排序规则写成清楚的 `key` 元组即可。
