---
oj: "luogu"
problem_id: "P1597"
title: "语句解析"
description: "按分号拆出赋值语句，用字典保存 a,b,c 当前值，顺序模拟变量或数字赋值。"
difficulty: "入门"
date: 2026-06-19 09:22
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1597
---

[[TOC]]

### 题意

给出一串简化 PASCAL 赋值语句。只有 `a,b,c` 三个变量，初始值都是 `0`。每条语句形如 `[变量]:=[变量或一位整数];`。要求按顺序执行后输出 `a,b,c`。

### 思路

用字典保存当前变量值：

```python
values = {"a": 0, "b": 0, "c": 0}
```

输入语句都以分号结尾，可以先用 `split(";")` 拆开。对一条非空语句，例如 `a:=3`：

- `statement[0]` 是左边变量；
- `statement[3]` 是右边内容。

右边如果是数字，就转成整数；否则就是变量名，取它当前的值。

这题是固定格式字符串模拟，不创建 `brute.py`。历史 C++ 文件保留但不作为本文代码。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`split(";")` 可以按分号拆分语句。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：普通 `dict` 适合保存变量名到当前值的映射。
- `right.isdigit()` 判断右边是否为数字字符。
- `print(values["a"], values["b"], values["c"])` 会默认用空格分隔输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

`partition` 解析赋值语句：

@include-code(./main-pythonic.py, python)

### 复杂度

设代码长度为 `n`，每个字符只被解析常数次，时间复杂度是 $O(n)$，空间复杂度是 $O(1)$。

### 总结

这题不需要真正写语法分析器。题目已经固定了语句格式，只要按分号拆开，再取固定位置模拟赋值即可。
