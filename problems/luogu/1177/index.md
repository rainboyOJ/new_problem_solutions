---
oj: "luogu"
problem_id: "P1177"
title: "【模板】排序"
description: "读入所有数字后调用 list.sort 原地升序排序，再按空格输出。"
difficulty: "普及-"
date: 2026-07-06 20:42
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


### 复杂度

Python 内置排序时间复杂度是 $O(n\log n)$，空间复杂度由排序实现决定，保存输入需要 $O(n)$。

### 总结

排序模板题的 Python 写法就是读入列表、调用 `sort()`、输出。重点是分清 `sort()` 会修改原列表且返回 `None`。
