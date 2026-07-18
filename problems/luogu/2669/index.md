---
oj: "luogu"
problem_id: "P2669"
title: "[NOIP 2015 普及组] 金币"
description: "把每天模拟改成按工资段累加，每段贡献为实际天数乘当前金币数。"
difficulty: "入门"
date: 2026-06-18 20:48
toc: true
tags: ["模拟", "数学", "循环", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2669
---

[[TOC]]

### 题意

第 `1` 段连续 `1` 天每天发 `1` 枚金币，第 `2` 段连续 `2` 天每天发 `2` 枚金币，第 `3` 段连续 `3` 天每天发 `3` 枚金币，依次类推。

给出天数 `k`，求前 `k` 天总共发了多少枚金币。

### 思路

可以逐天模拟，但更直接的做法是按“段”处理：

- 当前段金币数是 `value`；
- 这一段最多持续 `value` 天；
- 如果剩余天数不足一整段，就只取剩下的 `k` 天；
- 本段贡献是 `days * value`。

因此每轮取：

```text
days = min(剩余天数, 当前段长度)
```

然后把 `days * value` 加入答案，并减少剩余天数。循环结束时，所有前 `k` 天都已经统计完。

这是一道直接模拟题。Python 教学版不创建 `brute.py`，因为逐天暴力和分段模拟都在表达同一个发放规则，额外代码对理解帮助不大。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `int(input())` 读取单个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：这里用到整数乘法和 `min`，Python 的 `int` 不会溢出。
- `while k > 0:` 可以把 `k` 直接作为“剩余未处理天数”，每轮让它减少。
- `min(k, value)` 是处理最后一段不完整情况的常见写法。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

按天发金币：

@include-code(./main-pythonic.py, python)

### 复杂度

循环次数等于处理过的工资段数，大约是 $O(\sqrt{k})$；空间复杂度是 $O(1)$。

### 总结

把“每天发多少”改写成“每一段贡献多少”，代码会比逐天模拟更短，也自然处理最后一段不足整段的情况。
