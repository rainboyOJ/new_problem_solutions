---
oj: "luogu"
problem_id: "P1177"
title: "【模板】排序"
description: "读入所有数字后调用 list.sort 原地升序排序，再按空格输出。"
difficulty: "普及-"
date: 2026-07-06 20:42
updated: 2026-10-07 10:45
toc: true
tags: ["排序", "模板题", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1177
---

[[TOC]]

### 题意

给出 `n` 个整数，把它们从小到大排序后输出。

### 思路

Python 列表自带排序方法：

```python
numbers.sort()
```

它会原地把列表按升序排列。数据量 `n <= 10^5`，直接使用内置排序即可。

历史目录中保留了 C++ 文件；本文以 Python 模板写法为准，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`list.sort()` 原地排序，`sorted()` 返回新列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数可以用 `sys.stdin.buffer.read().split()` 读取。
- `print(*numbers)` 默认用空格分隔输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sorted 快读：

@include-code(./main-pythonic.py, python)

### STL 写法

C++ 里这道题的标准写法是 `vector` + `sort`：题目只说“读入 $N$ 个数”，个数由输入决定，所以用 `vector<ll>` 逐个 `push_back` 装下数据，再调 `sort(v.begin(), v.end())` 从小到大排好，最后按空格输出。`sort` 默认按 `<` 比较，正好就是题目要求的升序，不用自己写比较规则。和上面的 Python 写法相比，思路完全一样（读入、调用库排序、输出），差别只在 C++ 要显式选择区间 `[v.begin(), v.end())` 并自己控制输出空格。

对应的 cppbook 章节：[sort：把数据按规则排序](https://cppbook.roj.ac.cn/stl/algorithm/sort/)

@include-code(./main-stl.cpp, cpp)

### 复杂度

Python 内置排序时间复杂度是 $O(n\log n)$，空间复杂度由排序实现决定，保存输入需要 $O(n)$。

### 总结

排序模板题的 Python 写法就是读入列表、调用 `sort()`、输出。重点是分清 `sort()` 会修改原列表且返回 `None`。
