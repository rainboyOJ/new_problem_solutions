---
oj: "luogu"
problem_id: "P1618"
title: "三连击（升级版）"
description: "枚举比例倍数生成三个三位数，再检查拼接后的 9 个数字是否恰好是 1 到 9。"
difficulty: "入门"
date: 2026-07-15 21:30
toc: true
tags: ["枚举", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1618
---

[[TOC]]

### 题意

把数字 `1..9` 分成三组，组成三个三位数。要求这三个三位数的比例为 `A:B:C`，按第一个数升序输出所有方案。无解输出 `No!!!`。

### 思路

如果三个数比例为 `A:B:C`，它们一定可以写成：

```text
A * times, B * times, C * times
```

因此可以枚举倍数 `times`。为了让第一个数和第三个数都是三位数，倍数范围可以压缩为：

```text
ceil(100 / A) .. floor(999 / C)
```

对每个倍数，拼接三个数的十进制表示。如果拼接后长度为 `9`，并且数字集合正好是 `{1,2,...,9}`，说明每个数字恰好出现一次且没有 `0`。

当 `A = 0` 时，第一个数只能是 `0`，不可能是三位数，所以直接无解。

### Python 知识

- `f"{x}{y}{z}"` 可以把三个整数拼接成一个字符串。
- `set(digits) == set("123456789")` 用集合检查是否只包含 `1..9`。
- 同时检查 `len(digits) == 9`，可以排除重复数字导致集合相同但长度不对的情况。
- `(100 + a - 1) // a` 是整数上取整写法。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

倍数范围最多几百个，时间复杂度可以看作 $O(1)$。空间复杂度为输出方案数量。

### 总结

这题不要直接枚举所有三位数三元组。抓住比例关系后，只需要枚举一个倍数，再做数字合法性检查。
