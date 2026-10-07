---
oj: "luogu"
problem_id: "P1093"
title: "[NOIP 2007 普及组] 奖学金"
description: "把学生保存为记录，按总分降序、语文降序、学号升序排序后输出前五名。"
difficulty: "普及-"
date: 2026-06-19 01:35
updated: 2026-10-07 10:17
toc: true
tags: ["排序", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1093
---

[[TOC]]

### 题意

每个学生有语文、数学、英语三科成绩。先计算总分，再按总分高、语文高、学号小的顺序排序，输出前五名的学号和总分。

### 思路

每个学生保存为：

```python
(student_id, total, chinese)
```

排序规则可以直接写成 `key` 元组：

```python
(-total, -chinese, student_id)
```

总分和语文要降序，所以加负号；学号要升序，直接使用原值。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：多关键字排序可以用元组 `key`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：每行三个整数用 `map(int, input().split())`。
- `students[:5]` 取排序后的前五名。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

多关键字 sort：

@include-code(./main-pythonic.py, python)

### STL 写法

把排序规则写成函数对象：结构体 `StudentCmp` 重载 `operator()`，回答“第一个学生是否应该排在第二个前面”。把它交给 `sort` 后，总分降序、语文降序、学号升序三条要求逐条落进 `operator()` 的分支，排序结果唯一确定。和上面 Python 用 `key` 元组加负号的写法相比，这里的分支更像是在逐条翻译题目里的排序规则。

对应的 cppbook 章节：[比较规则与函数对象](https://cppbook.roj.ac.cn/stl/function-objects/)

@include-code(./main-stl.cpp, cpp)

### 复杂度

排序 `n` 名学生，时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

排序题最重要的是把关键字顺序写对。降序字段取负，升序字段保持原值，是 Python 多关键字排序的常用写法。
