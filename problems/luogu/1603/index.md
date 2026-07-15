---
oj: "luogu"
problem_id: "P1603"
title: "斯诺登的密码"
description: "把数字单词映射成数字后平方模 100，格式化为两位块排序拼接并去掉整体前导零。"
difficulty: "普及-"
date: 2026-06-19 10:16
toc: true
tags: ["字符串", "模拟", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1603
---

[[TOC]]

### 题意

给出一句英文句子。先找出其中所有表示数字的单词，把每个数字平方后对 `100` 取模，得到若干个两位数。然后重新排列这些两位数，拼出尽可能小的密码。

### 思路

先用字典保存单词到数字的映射。每遇到一个合法数字单词，就计算：

```text
value * value % 100
```

题目要求把结果当作两位数，例如 `1` 要看成 `01`，`4` 要看成 `04`。在 Python 中可以写成：

```python
f"{x:02d}"
```

因为每一段长度都固定为两位，想让拼接后的整体最小，只需要把这些两位字符串升序排序，再拼起来。最后把整体前导零删除；如果删完为空，就输出 `0`。

这题不需要枚举排列，排序就是正解。历史目录中保留 C++ 暴力文件，本文不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：普通 `dict` 适合保存单词到数字的映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`parts.sort()` 对等长字符串升序排序。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`split()` 拆分单词，`"".join(...)` 拼接答案。
- `f"{x:02d}"` 把整数格式化成至少两位，不足补前导零。

### 代码

@include-code(./main.py, python)

### 复杂度

句子只有 6 个单词，时间和空间都可视为 $O(1)$。若按单词数 `m` 计，排序复杂度是 $O(m\log m)$。

### 总结

这题表面像全排列，关键观察是每一块都是两位。等长块要拼出最小结果，直接升序排序即可。
