---
oj: "luogu"
problem_id: "P4305"
title: "[JLOI2011] 不重复数字"
description: "利用字典保持插入顺序的特性，用 dict.fromkeys 一步完成保序去重。"
difficulty: "入门"
date: 2026-06-21 13:40
toc: true
tags: ["哈希", "去重", "字典", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4305
---

[[TOC]]

### 题意

多组数据。删除数列中重复出现的数字，每个数字只保留第一次出现的位置，并按原顺序输出。

### 思路

集合能去重，但不能用来表达“保留第一次出现的顺序”。Python 字典会保留键的插入顺序，而同一个键再次插入不会改变原位置，所以：

```python
dict.fromkeys(values)
```

产生的键顺序恰好就是保序去重结果。数字保持为输入得到的 `bytes`，可直接 `b" ".join(...)`，无需先转 `int` 再转回字符串。

注意数据规模：`T <= 50`、`n <= 5e4`，总数可达约 `2.5e6` 个数。若每组都切片拷贝 token、或反复 `print`，容易在后几档数据 TLE（常见停在 60 分）。更稳的写法是：

1. 一次 `sys.stdin.buffer.read().split()`；
2. 用 `islice(it, n)` 顺序消费当前组，避免切片复制；
3. `dict.fromkeys` 保序去重；
4. `stdout.buffer` 批量写出。

### Python 知识

- `dict.fromkeys(iterable)` 用可迭代对象依次建立字典键。
- Python 3.7 起，字典保持插入顺序是语言保证。
- `bytes` 可哈希，因此既能做字典键，也能直接参与 `b" ".join`。
- `itertools.islice(it, n)` 从迭代器取下一段，不创建中间列表拷贝。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典保序去重模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字节串连接输出。

### 代码

@include-code(./main.py, python)


### 复杂度

一组长度为 `n` 的数据，期望时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

“去重且保留第一次出现顺序”是 `dict.fromkeys` 的典型场景。它比手写 `seen` 集合循环更短，同时准确表达目的。
