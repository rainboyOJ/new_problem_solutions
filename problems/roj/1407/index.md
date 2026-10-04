---
oj: "roj"
problem_id: "1407"
title: "笨小猴"
description: "统计单词中每个字母出现次数，判断出现最多次数与最少次数之差是否为质数。"
difficulty: "入门"
date: 2026-09-30 09:00
updated: 2026-09-30 09:15
toc: true
tags:
  - 质数判定
  - 字符串统计
favorite: false
favorite_reason: ""
categories:
  - 数学
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1407
---

[[TOC]]

## 形式化题目

给定一个仅含小写字母、长度小于 100 的字符串 $s$。设：

- $maxn$ = 所有**在 $s$ 中出现过**的字母中，出现次数最多的那个字母的出现次数；
- $minn$ = 所有**在 $s$ 中出现过**的字母中，出现次数最少的那个字母的出现次数。

若 $maxn - minn$ 是质数，输出 `Lucky Word` 和这个差值；否则输出 `No Answer` 和 `0`。

注意：统计"最少次数"时只考虑出现过的字母，未出现的字母（次数为 0）不参与统计。

## 思路

这是一道纯模拟 + 质数判定的小题。

**第一步：统计每个字母的出现次数。** 用 `str.count` 对每个出现过的字母数一遍即可，长度小于 100，怎么数都很快。

**第二步：求 $maxn$ 和 $minn$。** 在出现过的字母的次数集合上取 `max` 和 `min`。用 `set(s)` 去重后只统计出现过的字母，自然避开了"没出现的字母算 0 次"这个坑。

**第三步：判定 $d = maxn - minn$ 是否为质数。** 由于 $d \le len(s) < 100$，用试除法判定即可：检查 $2 \sim \lfloor\sqrt{d}\rfloor$ ���是否有因子。特别地，$d = 0$ 和 $d = 1$ 不是质数（例如样例 `olympic` 七个字母各出现一次，$d = 0$，输出 `No Answer`）。

以样例 `error` 为例：

| 字母 | e | o | r |
|------|---|---|---|
| 次数 | 1 | 1 | 2 |

$maxn = 2$，$minn = 1$，$d = 2$ 是质数，输出 `Lucky Word` 和 `2`。

复杂度：统计 $O(26n)$，试除 $O(\sqrt{n})$，总体 $O(n)$（$n < 100$），远在限制之内。

## 代码

@include-code(./main.py, python)

## 总结

- 核心是两点细节：一是 `set(s)` 只统计**出现过**的字母再取 min/max；二是差值 $d$ 可能是 0 或 1，试除判质数前要先排除 $d < 2$。
- 长度极小，试除法完全够用，无需筛法。
