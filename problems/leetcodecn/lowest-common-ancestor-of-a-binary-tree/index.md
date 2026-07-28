---
oj: leetcodecn; problem_id: lowest-common-ancestor-of-a-binary-tree; title: 二叉树 LCA
difficulty: 中等; tags: [二叉树, 递归, DFS, cpp, python]
description: 后序返回是否找到 p/q；左右均找到则当前为 LCA。
---
[[TOC]]
### 题意
找二叉树中两个节点的最近公共祖先（LCA）。
### 思路
后序 DFS：如果当前节点是 p 或 q 则返回自身；左右子树各返回一个非空结果则当前为 LCA；否则返回非空的一侧。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(height)。
### 总结
LCA 的递归写法极其简洁，核心是"两侧都不空则当前是答案"。
