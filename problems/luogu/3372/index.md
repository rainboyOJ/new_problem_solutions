---
oj: "luogu"
problem_id: "P3372"
title: "【模板】线段树 1"
description: "区间加与区间和模板题，可用懒标记线段树或两个 Fenwick 树维护。"
difficulty: "普及/提高-"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "懒标记", "树状数组", "区间加", "区间求和", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3372
---

[[TOC]]

### 题意

维护数列，支持区间加法和区间求和。

### 思路

#### 懒标记线段树

节点保存覆盖区间的和。整段加 `value` 时，区间和增加 `length * value`，并把 `value` 记在懒标记中；只有在需要访问孩子时才下传。区间查询和修改都只访问对数个节点。

#### 双树状数组

设差分数组 `d[i] = a[i] - a[i-1]`。区间 `[l,r]` 加 `value` 只改变 `d[l]` 和 `d[r+1]`。

一棵 Fenwick 维护 `d[i]`，另一棵维护 `i*d[i]`。原数组前缀和满足：

$$
\begin{aligned}
prefix(x)
&=\sum_{i=1}^{x}a_i \\
&=(x+1)\sum_{i=1}^{x}d_i-\sum_{i=1}^{x}i\cdot d_i
\end{aligned}
$$

因此区间和仍为 `prefix(r) - prefix(l-1)`。这个做法只适用于本题的区间加与区间和；如果还要处理区间赋值或乘法，应使用线段树。

### Python 知识

- `sys.stdin.buffer.readline` 减少大量操作的输入开销。
- 用几个同长度列表保存线段树字段，比为每个节点创建对象更省内存。
- `if query_left <= middle` 和 `if middle < query_right` 只递归到真正相交的子树。

### 代码

#### 懒标记线段树

@include-code(./main.py, python)

原有 C++ 模板仍保留：

@include-code(./main.cpp, cpp)

#### 双树状数组

@include-code(./fenwick.cpp, cpp)

### 复杂度

- 懒标记线段树：建树 `O(n)`，每次操作 `O(log n)`，空间 `O(n)`。
- 双树状数组：当前实现逐点初始化为 `O(n log n)`，每次操作 `O(log n)`，空间 `O(n)`。

### 总结

懒标记线段树把整段修改记在区间节点上；双树状数组则把区间加拆成差分边界，并用两个差分前缀量还原区间和。两种方法都能完成本题，但维护的信息不同。
