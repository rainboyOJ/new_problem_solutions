---
oj: "luogu"
problem_id: "B2005"
title: "字符三角形"
description: "读入一个字符，利用字符串乘法输出 1、3、5 个字符组成的等腰三角形。"
difficulty: "入门"
date: 2026-07-15 23:33
toc: true
tags: ["入门", "字符串", "输出", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/B2005
---

[[TOC]]

### 题意

输入一个字符，用它输出高为 `3`、底边长为 `5` 的等腰字符三角形。

例如输入 `*`，输出：

```text
  *
 ***
*****
```

### 思路

三角形一共三行：

1. 第一行：两个空格，再输出 `1` 个字符；
2. 第二行：一个空格，再输出 `3` 个字符；
3. 第三行：输出 `5` 个字符。

本题只是按规则构造固定小图案，不需要暴力程序。

### Python 知识

- `input().strip()` 读取一行并去掉换行。
- 字符串可以乘整数，`ch * 3` 表示把字符重复三次。
- f-string 可以把变量嵌入字符串，例如 `f"  {ch}"`。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度是 $O(1)$，空间复杂度是 $O(1)$。

### 总结

Python 的字符串乘法很适合写这种小图案题：字符重复几次，就直接写 `ch * 次数`。
