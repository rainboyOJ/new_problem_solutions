---
oj: "roj"
problem_id: "1255"
title: "迷宫问题"
description: "固定 5×5 迷宫 BFS 求唯一最短路，入队时记录前驱并兼作访问标记，到终点后回溯再反转输出路径。"
difficulty: "入门"
date: 2026-09-30 02:01
updated: 2026-10-05 07:11
toc: true
tags: ["搜索", "BFS", "网格", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
common: []
recommend: []
source: https://roj.ac.cn/problem/1255
---

[[TOC]]

## 题目描述

给定一个 $5 \times 5$ 的迷宫，每个格子为 `0`（通路）或 `1`（墙壁）。每一步只能向上、下、左、右移动到相邻的通路格，不能斜走。求从左上角 $(0,0)$ 到右下角 $(4,4)$ 的最短路线，并按顺序输出路径上的每个坐标。数据保证最短路线唯一。

## 思路

把每个通路格看成图中的一个顶点，四方向相邻的通路格之间连一条长度为 $1$ 的边，于是原问题变成无权图最短路问题。用 BFS 按层扩展，每个格子第一次入队时即得到最短步数；入队时记录其前驱格子（同时作为访问标记），到达终点后沿前驱链回溯到起点，再反转即可得到唯一最短路径。

## 参考代码

@include-code(./main.cpp, cpp)
