---
oj: "luogu"
problem_id: "P5739"
title: "【深基7.例7】计算阶乘"
description: "用递归函数表达 n! = n * (n-1)!，在 n=1 时返回 1。"
difficulty: "入门"
date: 2026-07-15 21:08
toc: true
tags: ["递归", "数学", "函数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5739
---

[[TOC]]

### 题意

输入一个正整数 `n`，输出 `n!`。题目挑战尝试不使用循环完成。

### 思路

阶乘的递归定义是：

```text
1! = 1
n! = n * (n-1)!  (n > 1)
```

把这个定义直接写成函数：

```python
def factorial(n):
    if n == 1:
        return 1
    return n * factorial(n - 1)
```

因为 `n <= 12`，递归深度很小，不需要调整递归限制。

这题是递归函数练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 整数不会溢出，适合直接计算小范围阶乘。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：单个整数输入用 `int(input())`。
- 递归函数必须有明确的终止条件，否则会无限调用。
- Python 函数用 `return` 把计算结果交回上一层。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

math.factorial：

@include-code(./main-pythonic.py, python)


### 复杂度

递归调用 `n` 层，时间复杂度是 $O(n)$，递归栈空间复杂度是 $O(n)$。

### 总结

递归适合直接表达“当前问题依赖更小的同类问题”。阶乘是最基础的递归例子：先写终止条件，再写递推关系。
