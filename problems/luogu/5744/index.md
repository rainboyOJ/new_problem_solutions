---
oj: "luogu"
problem_id: "P5744"
title: "【深基7.习9】培训"
description: "用元组表示学员记录，函数返回年龄加一且成绩提升 20% 后不超过 600 的新记录。"
difficulty: "入门"
date: 2026-07-15 21:22
toc: true
tags: ["模拟", "结构体", "函数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5744
---

[[TOC]]

### 题意

给出若干学员的姓名、年龄、成绩。培训一年后，年龄加一，成绩提升 `20%`，但最高不超过 `600`。输出培训后的信息。

### 思路

Python 中可以用元组保存一条学员记录：

```python
(name, age, score)
```

写函数 `train(student)`，返回新的记录：

- 年龄 `age + 1`；
- 成绩 `min(600, int(score * 1.2))`。

本题成绩保证是 5 的倍数，提升 20% 后仍为整数。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组适合保存固定字段记录。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：混合字段先 `split()` 再转换整数。
- `min(600, value)` 可以表达“不超过 600”。
- 函数返回元组，可以一次返回多个字段。

### 代码

@include-code(./main.py, python)


### 复杂度

每名学员只处理一次，时间复杂度是 $O(n)$，空间复杂度是 $O(1)$。

### 总结

结构体训练题在 Python 中可以先用元组模拟记录，再用函数接收记录并返回更新后的记录。
