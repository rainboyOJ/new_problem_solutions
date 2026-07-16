---
oj: "luogu"
problem_id: "P2651"
title: "添加括号III"
description: "把 a2 约去 a1 和后续所有数能提供的质因子，剩余分母为 1 时存在整数括号方案。"
difficulty: "普及+/提高"
date: 2026-07-16 19:20
toc: true
tags: ["最大公约数", "分数", "思维", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2651
---

[[TOC]]

### 题意

给出连续除法 `a1/a2/.../an`，可以任意添加括号，问能否使结果成为整数。

### 思路

通过括号 `a1/(a2/a3/a4/...)`，`a3..an` 都有机会进入总分子。因此可行的充要条件是：`a2` 的全部质因子幂能由 `a1*a3*...*an` 约掉。

不直接计算巨大乘积。先令：

```text
denominator=a2/gcd(a1,a2)
```

再依次用每个后续数与当前分母的 gcd 约分。最后分母等于 1 则输出 `Yes`。

### Python 知识

- `math.gcd` 让约分直接作用于剩余分母。
- 列表切片取得每组表达式，读取指针处理变长测试用例。
- 逐步约分避免构造可能极大的乘积，虽然 Python 支持大整数，也应控制不必要运算。
- 条件表达式生成 `Yes/No`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：大整数不代表应忽略算法规模。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：变长多组输入。

### 代码

@include-code(./main.py, python)

### 复杂度

每个数参与一次 gcd，总时间复杂度 $O(n\log V)$，额外空间为当前测试用例切片 $O(n)$。

### 总结

括号结构看似很多，但能否为整数只取决于第二项分母能否被其它项完全约掉。
