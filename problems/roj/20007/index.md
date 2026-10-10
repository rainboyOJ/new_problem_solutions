---
oj: "roj"
problem_id: "20007"
title: "擂台赛"
description: "碰撞掉头等价于互相穿过并交换编号：终态位置多重集合就是各自直走 T 秒的结果，两次排序后按初始位置排名对应状态，再按输入编号还原输出。"
difficulty: "普及-"
date: 2026-10-02 19:36
updated: 2026-10-06 08:58
toc: true
tags: ["模拟", "排序", "思维"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20007
---

[[TOC]]

## 题目描述

$[0,L]$ 上 $N$ 只速度为 1 的蚂蚁（位置 $p_i$、方向 R/L）相遇即反向，走出 $[0,L]$ 跌落（恰在端点不算）。求 $T$ 秒后每只蚂蚁状态：跌落输出 `Down`，同位置输出 `位置 Same`，否则 `位置 方向`。

## 思路

碰撞掉头等价于蚂蚁互穿并交换编号，故直走 $T$ 秒的位置集合即真实终态位置集合；同速下蚂蚁相对顺序不变，按初始排名与直走位置排序一一对应，回填各输入编号即可判断 `Down`/`Same`/方向。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
