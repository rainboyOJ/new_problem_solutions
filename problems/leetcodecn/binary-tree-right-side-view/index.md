---
oj: leetcodecn; problem_id: binary-tree-right-side-view; title: 二叉树右视图
difficulty: 中等; tags: [二叉树, BFS, DFS, cpp, python]
description: BFS 每层最后一个，或 DFS 先右后左首次到达深度时记录。
---
[[TOC]]
### 题意
返回二叉树从右侧看到的节点值。
### 思路
BFS 层序遍历取每层最后一个。DFS 先右后左，首次到达某深度时记录。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(n)。
### 总结
右视图本质是"每层最右侧节点"。
