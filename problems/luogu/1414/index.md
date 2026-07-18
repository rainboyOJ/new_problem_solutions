---
oj: "luogu"
problem_id: "P1414"
title: "又是毕业季II"
description: "倍数枚举统计每个约数能覆盖多少能力值，再把答案从大人数向小人数传播。"
difficulty: "普及+/提高"
date: 2026-07-16 19:20
toc: true
tags: ["最大公约数", "倍数枚举", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1414
---

[[TOC]]

### 题意

对每个 `k=1..n`，从能力值中选 `k` 个，使它们的 gcd 最大，输出这个最大值。

### 思路

若有至少 `k` 个能力值是 `d` 的倍数，就能从中选 `k` 个，它们的 gcd 至少为 `d`。因此枚举 `d`，累加 `d,2d,...` 的出现次数 `count`，说明 `d` 可供最多 `count` 人使用。

先令 `answer[count]` 记录恰好这个覆盖数下最大的 `d`。一个约数能覆盖 `count` 人，也一定能覆盖任意更少人数，所以再从 `n-1` 向 `1` 做：

```text
answer[k]=max(answer[k],answer[k+1])
```

### Python 知识

- 两个 `array('I')` 紧凑保存百万值域频次和至多一万项答案。
- `range(d,maximum+1,d)` 枚举 `d` 的全部倍数。
- 逆序传播用 `range(n-1,0,-1)`。
- `map(str,answer[1:])` 转换后按行连接。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：值域数组内存。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：倍数贡献累计。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

设最大能力值为 `V`，时间复杂度 $O(V\log V+n)$，空间复杂度 $O(V+n)$。

### 总结

把“选哪些人”反转为“某个候选 gcd 能整除多少能力值”，组合选择问题就变成了倍数计数。
