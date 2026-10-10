---
oj: "roj"
problem_id: "1639"
title: "Biorhythms 生理周期"
description: "把三个周期高峰同天写成同余方程组，用中国剩余定理（CRT）求出周期 23×28×33=21252 内的唯一解，再对给定时间做环形减法得到下一次同天的距离。"
difficulty: "普及"
date: 2026-09-30 23:31
updated: 2026-10-06 01:36
toc: true
tags:
  - 数论
  - 中国剩余定理
  - 同余方程
favorite: false
favorite_reason: ""
categories:
  - 算法竞赛
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1639
---

[[TOC]]

## 题目描述

人生三体力、情商、智商的高峰周期分别为 23、28、33 天，每个周期从 0 天起算并在周期长度处同时达到高峰。给定三个高峰出现的日子与目标日子 $d$（均为出生后天数），求下一个三高峰同日距出生多少天（$-1$ 为终止）。

## 思路

三高峰同日即解同余方程组 $x \equiv p \pmod{23/28/33}$，由中国剩余定理得模 $M=23\times28\times33$ 的唯一解，再加减 $M$ 调整到 $d$ 之后的最小正解（结果 $\le M$ 保证在 int 范围内）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
