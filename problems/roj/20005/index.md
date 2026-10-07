---
oj: "roj"
problem_id: "20005"
title: "史莱姆鱼"
description: "相邻交换算出差值 2(t_i c_j − t_j c_i)，按比值 t_i/c_i 升序排序后一次线性扫描即得最少体力。"
difficulty: "普及-"
date: 2026-10-02 19:28
updated: 2026-10-07 12:15
toc: true
tags: ["贪心", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1319"
    reason: "B 复用了 A 的相邻逆序对交换论证：先把交换差值归到邻对本身、证明交换严格变优，再据此确定排序键，只是把 A 的『按接水时间升序』换成按比值 t_i/c_i 升序。"
common: []
recommend: []
source: https://roj.ac.cn/problem/20005
---

[[TOC]]

## 题目描述
阿什尼要运 $n$ 条史莱姆鱼回饭店：运第 $i$ 条鱼需要 $2t_i$ 个单位时间（往返），鱼会随时间变重——在时刻 $T$ 开始运第 $i$ 条鱼要消耗 $T\cdot c_i$ 的体力。第一条鱼在时刻 0 开始运送，体力为 0。选择合适的运送顺序，求最少消耗的总体力。

输入：第一行一个整数 $n$；接下来 $n$ 行，每行两个整数 $t_i, c_i$。输出：一个整数，表示最少消耗的体力。数据范围：$n \leqslant 10^5$，$t_i \leqslant 2\times 10^6$，$c_i \leqslant 100$。

样例输入 `6\n3 1 2 5 2 3 3 2 4 1 1 6`，样例输出 `86`。

## 思路
设相邻两条鱼 $i$（先）、$j$（后），它们之前的鱼共耗时 $T$，两条鱼贡献的体力相减得 $(i\text{ 先})-(j\text{ 先})=2(t_ic_j-t_jc_i)$，与其余鱼无关；因此若 $t_ic_j>t_jc_i$（即 $t_i/c_i>t_j/c_j$）交换后更优，最优顺序就是按 $t_i/c_i$ 升序。比较用交叉相乘 $t_ic_j$ 与 $t_jc_i$，避免浮点误差和 $c_i=0$ 的除零。排序后从时刻 0 顺序扫描：先累加当前开始时刻乘 $c_i$，再把时刻推进 $2t_i$，答案用 `long long`（最大约 $4\times10^{18}$）。

## 参考代码
@include-code(./main.cpp, cpp)

