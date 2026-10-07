---
oj: "roj"
problem_id: "3651"
title: "[noip2017-提高] 奶酪"
description: "并查集维护相切/相交的空洞，上下表面挂虚拟节点，平方比较后判断是否同根。"
difficulty: "普及"
date: 2026-10-02 12:59
updated: 2026-10-06 02:35
toc: true
tags: ["并查集", "图论", "连通性", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
common: []
recommend: []
source: https://roj.ac.cn/problem/3651
---

[[TOC]]

## 题目描述

一块高度为 $h$ 的奶酪，下表面 $z=0$，上表面 $z=h$，内部有 $n$ 个半径同为 $r$ 的球形空洞。第 $i$ 个空洞球心为 $(x_i,y_i,z_i)$。Jerry 能从下表面经过空洞跑到上表面，当且仅当存在一列空洞，相邻两个空洞相切或相交（球心距离 $\le 2r$），且最下面的空洞与下表面相切或相交（$z_i \le r$），最上面的空洞与上表面相切或相交（$z_i + r \ge h$）。

输入输出见 problem.md，数据范围 $n \le 1000$，$T \le 20$，坐标与 $h,r$ 可达 $10^9$。

## 思路

把每个空洞看成节点，相切/相交就连边，上下表面分别作为虚拟节点。用整数平方比较避免浮点误差；按 $z$ 排序后只检查同窗口内的球对，再求虚拟节点是否同根。

## 参考代码

@include-code(./main.cpp, cpp)
