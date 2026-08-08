---
oj: "luogu"
problem_id: "P1055"
title: "[NOIP 2008 普及组] ISBN 号码"
description: "跳过分隔符取数字，按权值求和对 11 取模，比较并替换最后一位校验码。"
difficulty: "入门"
date: 2026-07-15 18:17
toc: true
tags: ["python", "入门", "字符串", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1055
---

[[TOC]]

### 题意

输入形如 `x-xxx-xxxxx-x` 的 ISBN。前 9 个数字按权值 `1..9` 求和，再对 `11` 取模得到校验码；余数为 `10` 时校验码是 `X`。如果输入校验码正确输出 `Right`，否则输出修正后的 ISBN。

### 思路

字符串里 `-` 不参与计算。可以用列表推导式取出所有数字字符：

```python
digits = [int(ch) for ch in isbn if ch.isdigit()]
```

前 9 个数字参与加权求和，最后一位只是原校验码。算出正确校验码后，与 `isbn[-1]` 比较；不一致时用 `isbn[:-1] + correct` 替换最后一位。

这题已有旧 C++ 版本；本篇改成 Python 教学，重点是字符串扫描、列表推导式和切片替换。

### Python 知识

- `ch.isdigit()` 判断字符是不是数字。
- 列表推导式可以一边过滤一边转换：`[int(ch) for ch in isbn if ch.isdigit()]`。
- `sum(digits[i] * (i + 1) for i in range(9))` 表示加权求和。
- `isbn[:-1] + correct` 保留最后一位前面的部分，再拼上正确校验码。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串操作、切片和 `isdigit`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器表达式与 `sum`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：读取字符串与输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

enumerate 加权校验：

@include-code(./main-pythonic.py, python)


### 复杂度

ISBN 长度固定，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

字符串模拟题先分清哪些字符参与计算，哪些只是格式。Python 的 `isdigit()`、切片和推导式能把这个过程写得很直接。
