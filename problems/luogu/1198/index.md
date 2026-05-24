---
oj: "luogu"
problem_id: "P1198"
title: "[JSOI2008] 最大数"
date: 2026-01-17 20:30
toc: true
tags: ["单调栈","todo","bit","线段树"]
desc: ""
source: https://www.luogu.com.cn/problem/P1198
---

[[TOC]]

## BIT

看我的写的: [Rbook - 树状数组 区间最值](https://rbook_old.roj.ac.cn/article/faf891be83)

> 注意这个题目,只在尾插入值, 所有我的代码和 [Rbook - 树状数组 区间最值](https://rbook_old.roj.ac.cn/article/faf891be83) 有点区别,但核心思想是一样的 

> 区别在:认为: bit数组的初始值为-INF, update 不停的更新父亲(少写代码),自己体会一下, 


因为我们是**按顺序追加 (Append)** 元素的，之前的元素已经正确更新了 `tree` 数组中的父节点。
所以，当我们加入新元素 `val` 时，只需要**在现有 `tree` 值的基础上取 max** 即可，千万不能直接赋值覆盖。

同时，由于 `tree` 数组一开始被初始化为极小值 (`INF`)，第一次遇到新位置时，`max(INF, val)` 会自动变成 `val`，逻辑是自洽的。

---

### 代码 

@include-code(./bit.cpp,cpp)

### 重点细节复盘

1.  **为什么这个能 AC？**
    *   **Update 修复**：`tree[i] = max(tree[i], val)` 保证了新加入的数 `val` 只是去更新它所属的区间，而不会把那个区间里“以前的较大值”给抹除。
    *   **Append 模式的特殊性**：因为我们是 `1, 2, 3...` 这样填坑的，当我们填 `cnt` 时，`cnt` 左边的所有节点都已经处于“正确维护了最大值”的状态。所以我们只需要向右上传新的最大值即可。

2.  **BIT 做 RMQ 的局限性**
    *   这套逻辑**只适合“末尾追加”**或者**“静态数组”**。
    *   如果是“中间修改一个值”（比如把第 3 个数改大或改小），这套 BIT 代码是无法处理的（改小的情况特别难处理，因为 max 没法逆运算），那时候就必须用线段树。
    *   但对于这道题，BIT 是完美的，且常数极小。


## 线段树

TODO

## 单调栈

TODO: https://www.luogu.com.cn/article/n4jpwmmk
