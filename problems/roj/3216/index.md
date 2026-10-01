---
oj: "roj"
problem_id: "3216"
title: "「John's trip」 约翰的旅行"
description: "无向连通图求字典序最小的欧拉回路（按边编号）：Hierholzer 迭代版 + 每步贪心选编号最小的可用边 + 下标前进摊还，O(m log m)。"
difficulty: "省选/NOI-"
date: 2026-10-02 02:45
updated: 2026-10-02 03:10
toc: true
tags:
  - "图论"
  - "欧拉回路"
  - "Hierholzer"
  - "贪心"
favorite: false
favorite_reason: ""
categories:
  - "图论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3216
---

[[TOC]]

## 形式化题目

无向连通图，$m$ 条街道（编号 1..m）连接 $n$ 个路口。求从起点出发**每条边恰好一次**回到起点的回路，输出**字典序最小**的边编号序列；不存在输出 `Round trip does not exist.`。

## 正解

### 思路

#### 1. 欧拉回路存在性

无向图存在欧拉回路 $\iff$ 每个顶点度数为偶数。

#### 2. Hierholzer + 字典序贪心

标准 Hierholzer：从起点出发随意走，走不动时回溯记录边。要让输出字典序最小，只需**每一步贪心选当前可用的编号最小的边**：

- 每个顶点的邻接表按**边编号升序**排序；
- 迭代版用显式栈模拟递归，`pos[u]` 记录 $u$ 的邻接表扫描到哪了（跳过的边不再回看），摊还 $O(1)$；
- 回溯收集的边序逆序，整体翻转即回路正序。

#### 3. 街道编号任意

输入的街道编号是任意整数（不一定 1..m），用集合判重。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(m\log m)$（排序）+ $O(m)$（Hierholzer）。
- **空间复杂度**：$O(m)$。

## 总结

- 「字典序最小欧拉回路」= Hierholzer + **每步贪心选最小编号边** + 邻接表预排序。
- 迭代版 Hierholzer 用显式栈 + `pos` 下标前进，避免递归爆栈并把跳过代价摊还掉。
- 度数奇偶是欧拉回路存在性的唯一判据（连通图）。
