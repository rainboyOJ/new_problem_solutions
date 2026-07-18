---
oj: "luogu"
problem_id: "P1125"
title: "[NOIP 2008 提高组] 笨小猴"
description: "用 Counter 统计每个字母出现次数，判断最大次数与最小次数的差是否为质数。"
difficulty: "入门"
date: 2026-07-15 20:30
toc: true
tags: ["字符串", "数学", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1125
---

[[TOC]]

### 题意

给定一个只含小写字母的单词。统计每个出现过的字母次数，令 `maxn` 是最大次数，`minn` 是最小次数。如果 `maxn - minn` 是质数，输出 `Lucky Word` 和这个差值；否则输出 `No Answer` 和 `0`。

### 思路

先统计每个字母的出现次数，再从这些次数里取最大值和最小值。注意 `minn` 只在出现过的字母中取最小值，没出现的字母不参与统计。

质数判断只需要试除到平方根：

```text
如果 x < 2，不是质数。
否则检查 2, 3, ..., floor(sqrt(x)) 是否能整除 x。
```

这题数据很小，直接计数和试除即可，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`Counter(word)` 可以直接统计字符频率。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `input().strip()` 读取单词。
- `counter.values()` 得到所有出现过字符的次数。
- `while divisor * divisor <= x` 避免额外导入平方根函数。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

`Counter` 统计频次，`all` 判断质数：

@include-code(./main-pythonic.py, python)

### 复杂度

设单词长度为 `n`，计数时间复杂度是 $O(n)$。差值最多不超过 `n`，试除复杂度是 $O(\sqrt n)$。空间复杂度是 $O(1)$，因为小写字母最多 26 种。

### 总结

频率题先用 `Counter` 把出现次数拿出来，再在次数集合上做数学判断。
