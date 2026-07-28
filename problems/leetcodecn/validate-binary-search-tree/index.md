---
oj: leetcodecn; problem_id: validate-binary-search-tree; title: 验证 BST
difficulty: 中等; tags: [BST, 递归, cpp, python]
description: 递归传 (low, high) 开区间，中序遍历必须严格递增。
---
[[TOC]]
### 题意
判断二叉树是否为有效的 BST。
### 思路
递归传上下界，每个节点值必须在 (lo, hi) 开区间内。中序遍历检验严格递增也行。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(height)。
### 总结
BST 的递归定义就是检验算法：左子树所有值 < 根 < 右子树所有值。
