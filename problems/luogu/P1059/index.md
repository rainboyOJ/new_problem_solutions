---
oj: "luogu"
problem_id: "P1059"
title: "[NOIP 2006 普及组] 明明的随机数"
description: "用 set 去重，再用 sorted 得到从小到大的不同随机数。"
difficulty: "入门"
date: 2026-06-19 01:32
toc: true
tags: ["排序", "去重", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1059
---

[[TOC]]

### 题意

给出 `N` 个 `1..1000` 的随机整数。去掉重复数字后，按从小到大输出。

### 思路

Python 中 `set(numbers)` 可以去重，但集合本身没有固定顺序。再用 `sorted(...)` 排序：

```python
unique_numbers = sorted(set(numbers))
```

然后输出不同数字个数和排序后的列表即可。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 适合判重和去重。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted()` 返回一个新的有序列表。
- `print(*unique_numbers)` 按空格展开输出列表。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

set 去重 sorted：

@include-code(./main-pythonic.py, python)


### 复杂度

设输入数量为 `N`，去重和排序总复杂度为 $O(N\log N)$，空间复杂度为 $O(N)$。

### 总结

去重后排序是 Python 的常见组合：`sorted(set(a))`。注意集合去重后要排序，不能直接输出集合。
