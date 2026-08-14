---
oj: "luogu"
problem_id: "P1217"
title: "[USACO1.5] 回文质数 Prime Palindromes"
description: "利用偶数位回文除 11 外都不是质数的性质，只构造少量奇数位回文再试除判素。"
difficulty: "普及/提高-"
date: 2026-06-18 22:15
toc: true
tags: ["数论", "枚举", "构造", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1217
---

[[TOC]]

### 题意

给出区间 `[a,b]`，输出其中所有既是回文数、又是质数的整数，每个数单独一行。

### 思路

如果从 `a` 到 `b` 逐个扫描，再分别判断回文和质数，区间最大可以到 `10^8`，Python 和 C++ 都会做很多无用检查。

更好的方向是：不要在区间中寻找回文数，而是直接构造回文数。

一个关键性质是：

- 除了 `11` 以外，所有偶数位回文数都能被 `11` 整除，因此不可能是质数。

所以需要检查的候选只剩：

1. 一位数回文；
2. 特判 `11`；
3. 奇数位回文。

奇数位回文可以由一个“前半部分种子”构造出来：

| 种子 | 构造结果 |
| --- | --- |
| `12` | `121` |
| `305` | `30503` |
| `9999` | `9999999` |

对种子字符串 `s`，构造式是：

```text
s + s[-2::-1]
```

也就是保留最后一位作为中心，再把中心左边的部分反向接到右侧。

最后按从小到大的种子枚举回文数，落在 `[a,b]` 中时再用试除法判断质数即可。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(int, input().split())` 读取一行两个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：用 `math.isqrt` 做精确整数平方根，质数试除时不依赖浮点数。
- `text[-2::-1]` 是切片写法：从倒数第二个字符开始，向左反向取到开头。
- 把答案先存成字符串列表，最后 `"\n".join(answer)` 输出，适合这种多行结果。

### 代码

@include-code(./main.py, python)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### Pythonic 写法

回文 + 质数：

@include-code(./main-pythonic.py, python)

### 复杂度

最多枚举 `10` 到 `9999` 的种子，构造出的奇数位回文覆盖到 `10^8` 以内。每个候选数用试除法判断质数，单次复杂度是 $O(\sqrt x)$。空间复杂度是 $O(c)$，其中 `c` 是输出答案个数。

### 总结

这题的关键不是把判素数写得很快，而是先把候选数量降下来。看出偶数位回文数的整除性质后，只构造奇数位回文，就能避免扫描整个大区间。
