---
oj: "shumeng"
problem_id: "CSP202506D"
title: 月票发行
description: "用有限状态自动机统计连续自由字母段，并以线性递推和 Kitamasa 处理超长段。"
date: 2026-07-31 16:21
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202506D
difficulty: "未知"
---

[[TOC]]

### 题意

长度为 `n` 的字符串中有若干位置固定为 `#`，其余位置填写小写字母。统计同时含有 `ccf`、`cspark`，且存在 `ccf` 在前、`cspark` 在后的字符串数量。

### 思路

固定的 `#` 不属于模式字符，并且会清空模式匹配后缀，所以把字符串按 `#` 分成自由字母段。全局只需维护三种状态：尚未出现 `ccf`、已经出现 `ccf` 但尚未成功、已经满足条件。

对一个自由段，使用前缀自动机记录 `ccf/cspark` 的匹配后缀。需要的段计数序列包括：没有 `ccf`、没有 `cspark`、以及段内不存在先 `ccf` 后 `cspark`。这些固定维数状态的计数满足低阶线性递推；长度不大时直接预计算，长度较大时用 Kitamasa 求第 `L` 项。处理每个自由段后更新全局三种状态，遇到 `#` 只重置匹配后缀。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预计算复杂度为 `O(常数*100000)`；每个较长自由段用 `O(log n)` 的线性递推求项，整体复杂度为 `O(m log n)`，空间复杂度为 `O(100000)`。

### 总结

固定字符把长字符串切成独立段，有限自动机的计数序列可以用线性递推跨过很长的自由区间。
