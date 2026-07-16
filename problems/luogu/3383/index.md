---
oj: "luogu"
problem_id: "P3383"
title: "【模板】线性筛素数"
description: "用纯标准库奇数分段筛处理 10^8 上界，并以紧凑整数数组保存查询所需的前若干个素数。"
difficulty: "普及+/提高"
date: 2026-06-18 22:35
toc: true
tags: ["数论", "素数", "分段筛", "bytearray", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3383
---

[[TOC]]

### 题意

给出上界 `n=10^8` 和若干询问，每次输出第 `k` 小的素数。

### 思路

Python 不能用普通整数列表保存一亿个筛标记。代码采用奇数分段埃氏筛：

1. 先筛出不超过 `sqrt(n)` 的基础素数；
2. 每次只处理约一百万个奇数 `low,low+2,...,high`；
3. 对每个奇基础素数，把块内倍数对应的切片批量置零；
4. 用 `bytearray.find(1)` 在底层查找仍为素数的位置；
5. 只保存到询问所需的最大排名即可。

块内下标 `index` 对应整数 `low+2*index`。若质数 `p` 的第一个奇倍数位置是 `index`，后续奇倍数下标相差 `p`，因此可以写成 `flags[index::p]=0`。

这种实现没有第三方依赖，完整上限实测约使用 36 MB 内存。

### Python 知识

- `bytearray` 每个标记仅一字节，扩展切片赋值在底层批量完成筛除。
- `array('I')` 以 4 字节无符号整数保存约 576 万个素数，显著小于 Python 整数列表。
- `bytearray.find(1,start)` 避免逐字节 Python 循环寻找未标记位置。
- 只筛奇数，数值跨度与数组下标之间用 `number=low+2*index` 转换。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 对象内存和底层切片性能。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量查询批量输出。

### 代码

@include-code(./main.py, python)

### 复杂度

筛法时间复杂度约 $O(n\log\log n)$，查询 $O(1)$；空间为基础素数、一个分块和所需质数表，约 $O(\sqrt n+B+\pi(n))$。

### 总结

同一个算法在 Python 中还要重新设计存储。分段、奇数压缩、`bytearray` 切片和紧凑 `array` 共同解决了一亿范围的时间与内存问题。

### 一图流解析

下面保留原题解已有的复盘图片，本轮未重新生成。

![一图流解析](./one-page-explainer.png)
