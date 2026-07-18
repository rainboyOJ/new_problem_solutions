---
oj: "luogu"
problem_id: "P5723"
title: "【深基4.例13】质数口袋"
description: "从小到大试除判断质数，只在加入后总和不超过 L 时放入口袋。"
difficulty: "入门"
date: 2026-07-15 18:26
toc: true
tags: ["数学", "数论", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5723
---

[[TOC]]

### 题意

从 `2` 开始依次考虑自然数。如果一个数是质数，就尝试把它放进口袋。

口袋中所有质数的和不能超过 `L`。要求按从小到大的顺序输出能放下的所有质数，最后再输出质数个数。

### 思路

关键是两件事：

1. 从小到大枚举候选数；
2. 只在“加入这个质数后总和仍然不超过 `L`”时，才真正把它加入答案。

判断质数时，只需要试除到 `sqrt(x)`。如果 `x` 有一个大于 `sqrt(x)` 的因子，那么它必然还有一个小于 `sqrt(x)` 的配对因子，所以前面已经会被发现。

循环条件写成：

```text
while total + candidate <= limit:
```

这里的 `candidate` 是当前自然数。即使它不是质数，循环里也会继续向后找；如果它是质数，则检查加入后是否超重。

这题的朴素想法就是按题意枚举和试除，Python 教学版不额外创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：本题输出多行答案，可以先把字符串放入列表，最后 `"\n".join(...)` 一次输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`math.isqrt(x)` 返回整数平方根，避免浮点误差。
- `range(3, isqrt(x) + 1, 2)` 只枚举奇数因子，跳过所有偶数。
- `primes.append(str(candidate))` 提前转成字符串，是为了最后能直接用 `join` 拼接输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

质数筛选累加：

@include-code(./main-pythonic.py, python)

### 复杂度

设最终检查到的最大候选数为 `m`。每个候选数试除到平方根，时间复杂度可以粗略看作 $O(m\sqrt m)$；在 `L <= 10^5` 的范围内足够。空间复杂度是 $O(c)$，其中 `c` 是输出的质数个数。

### 总结

本题把“质数判断”和“累计容量限制”放在一起考察。实现时要先判断是不是质数，再判断加入后是否超过 `L`。
