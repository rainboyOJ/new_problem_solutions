---
oj: "luogu"
problem_id: "P1185"
title: "绘制二叉树"
description: "按层数公式计算满二叉树画布坐标，递归绘制节点和斜边，并跳过被删除的整棵子树。"
difficulty: "普及+/提高"
date: 2026-07-16 18:17
toc: true
tags: ["二叉树", "递归", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1185
---

[[TOC]]

### 题意

按固定 ASCII 规则绘制 `m` 层满二叉树，并删除指定节点、它的所有后代以及与父节点的连线。

### 思路

画布高度和宽度为：

$$
height=3\times2^{m-2},\qquad width=2\times height-1
$$

根位于 `(0,width//2)`。除叶层外，第 `level` 层节点行号为 `height-3*2^(m-level-1)`，叶层在最后一行。父子节点横向偏移恰好等于纵向行差，因此连线上的每一步同时改变一行一列。

用满二叉树堆编号表示节点：第 `level` 层第 `index` 个节点编号是 `2^(level-1)+index-1`。先递归把删除节点的整个子树加入集合；绘制时若孩子已删除，就连线和子树都跳过。

### Python 知识

- 二维画布必须写成 `[[" "]*width for _ in range(height)]`，保证各行独立。
- `deleted` 集合保存堆编号，判断某棵子树是否绘制。
- 三元组 `(child,direction,slash)` 把左右孩子的对称绘制合并成同一循环。
- 最后按固定宽度 `"".join(row)` 输出，保留题目要求的行尾空格。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：二维列表独立行。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：递归树状态。

### 代码

@include-code(./main.py, python)


### 复杂度

画布大小为 $O(4^m)$ 个字符，绘制和输出均与画布大小同阶；递归深度 $O(m)$。

### 总结

ASCII 绘树的难点是先推导稳定坐标。用堆编号管理删除、用行差同时决定横向偏移后，左右子树可以统一递归绘制。
