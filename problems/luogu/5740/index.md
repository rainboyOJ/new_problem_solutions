---
oj: "luogu"
problem_id: "P5740"
title: "【深基7.例9】最厉害的学生"
description: "用元组保存学生记录，顺序扫描并维护总分最高且最先出现的学生。"
difficulty: "入门"
date: 2026-07-15 21:15
toc: true
tags: ["模拟", "结构体", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5740
---

[[TOC]]

### 题意

给出若干名学生的姓名和三科成绩。输出总分最高的学生信息；如果总分相同，输出输入中靠前的那位。

### 思路

Python 里可以用元组保存一名学生：

```python
(name, chinese, math, english)
```

顺序读入每名学生，计算三科总分。只有当当前学生总分严格大于 `best_total` 时，才更新答案。这样如果总分相同，就会自然保留先出现的学生。

这题是记录数据和维护最大值练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行中混合字符串和整数时，先 `split()` 再分别转换。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组适合保存固定结构的一条记录。
- `best_student = (name, chinese, math, english)` 保存当前最优记录。
- 只在 `total > best_total` 时更新，保留并列时靠前者。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

扫描 `N` 名学生，每名学生只处理常数个字段，时间复杂度是 $O(N)$，空间复杂度是 $O(1)$。

### 总结

结构体入门题在 Python 中可以先用元组表达记录。维护“最先出现的最大值”时，并列不更新即可。
