---
oj: "roj"
problem_id: "8016"
title: "家族"
description: "家族数就是网格里字母格的四连通块个数：扫描到未访问的字母格就计数 +1 并洪水填充染色。"
difficulty: "入门"
date: 2026-10-02 17:12
updated: 2026-10-06 17:02
toc: true
tags: ["dfs", "搜索", "连通块"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8016
---

[[TOC]]
## 题目描述
岛屿地图有 $n$ 行（$n \leqslant 100$），每行不超过 200 个字符，各行长度可以不同。格子是空格（大海）、`*`（河流或山丘）或小写字母（一户人家），上下左右共边的两户算相邻，互相可达的人家属于同一个家族，求家族个数。输入第一行是 $n$，接下来 $n$ 行是地图（行首可能有空格）。
```plaintext
输入：          输出：
4               3
*zlw**pxh
l*zlwk*hx*
w*tyy**yyy 
    zzl
```
## 思路
家族就是字母格子的四连通块，`*` 和空格都是断开的障碍。从左到右、从上到下扫描，遇到未访问的字母格就把答案 +1，并用显式栈的洪水填充把整个连通块染色（长链可能让递归爆栈）。注意读入必须保留行首空格，越界按每行实际长度判断。
## 参考代码
@include-code(./main.cpp, cpp)
