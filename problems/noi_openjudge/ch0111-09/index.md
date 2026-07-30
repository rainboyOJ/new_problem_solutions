---
oj: "noi_openjudge"
problem_id: "ch0111-09"
title: "膨胀的木棍"
description: "二分圆弧半径，使弦长对应的圆弧长度等于热胀后的木棍长度。"
difficulty: "普及+/提高"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "几何", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/09/
---

[[TOC]]

### 题意

木棍受热后长度增加，但两端仍固定在原位置。把它看成圆弧，求圆弧中点相对原直线的偏移量。

### 思路

热胀后的弧长为 $S=(1+nC)L$。设圆弧半径为 $r$，弦长为 $L$，圆弧长度是 $2r\arcsin(L/(2r))$。半径越大弧长越小，因此二分半径使弧长等于 $S$，最后偏移量为 $r-\sqrt{r^2-(L/2)^2}$。长度不变时偏移量为零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

固定进行 200 次二分，时间复杂度和空间复杂度均为 $O(1)$。

### 总结

圆弧模型把“热胀弯曲”转化为单调的几何方程，适合实数二分。
