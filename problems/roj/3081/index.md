---
oj: "roj"
problem_id: "3081"
title: "乳草的入侵"
description: "八连通网格上从起点做 BFS 求最晚被占领格子的层数，起点算第 0 周，答案即所有格子距离的最大值。"
difficulty: "普及-"
date: 2026-10-01 15:14
updated: 2026-10-06 02:35
toc: true
tags: ["搜索", "广度优先搜索", "BFS"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1335"
    reason: "B 的八连通 BFS 直接用 A 教的「扩展条件里一次挡掉越界与障碍、入队即标记」这一网格搜索骨架（B 代码同样先判 in_map 再把 dist 置为 week+1 后 append），A 还点明八连通只需扩 DIRS；B 只把栈换成队列并叠加层数记录与取全图最大值，得到最晚占领周数。"
  - oj: "roj"
    problem_id: "1255"
    reason: "B 直接复用 A 教的网格 BFS 中首次入队即最短步数这一层数判定，只把四连通换成八连通并把单点到点距离改为全图最大层数"
  - oj: "roj"
    problem_id: "1329"
    reason: "B 的八连通 BFS 直接复用 A 教的「入队即标记、每格至多入队一次」这一 BFS 不变式来替代逐周全图重扫，只在其上叠加八方向扩散与取最大层数作为答案，属同为 BFS 模板但强度提升一级的台阶关系。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3081
---

[[TOC]]

## 题目描述

$X$ 列 $Y$ 行的网格，`.` 为草地、`*` 为大石。乳草第 $0$ 周占领格 $(M_x,M_y)$，此后每周向八连通相邻的草地扩散（保证最终全部被占领），求完全占领所需的星期数。首行输入 $X,Y,M_x,M_y$，随后 $Y$ 行地图；输出一个整数。$1\le X,Y\le100$。样例输入 `4 3 1 1` / `....` `..*.` `.**.`，输出 `4`。

## 思路

从起点做八连通 BFS，每个格子被占领的星期数就是它到起点的最短路层数（起点为第 $0$ 周）。石头不入队，答案取所有格子的最大层数。

## 参考代码

@include-code(./main.cpp, cpp)
