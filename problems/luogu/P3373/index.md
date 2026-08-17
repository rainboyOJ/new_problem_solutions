---
oj: "luogu"
problem_id: "P3373"
title: "【模板】线段树 2"
description: "把区间乘和区间加统一成仿射懒标记，维护模意义下的区间和。"
difficulty: "普及/提高-"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "懒标记", "区间乘", "区间加", "取模", "python"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P3372"
    reason: "单懒标记区间加升级为乘加双懒标记，需要先掌握 P3372 骨架"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3373
---

[[TOC]]

### 题意

支持区间乘、区间加和区间求和，所有结果对给定模数取模。

### 思路

把每个元素的待执行操作写成 `v -> v * mul + add`。当前节点整段应用 `(mul, add)` 时，区间和变为 `sum * mul + length * add`；旧标记 `(old_mul, old_add)` 与新标记复合为 `mul = old_mul * mul`、`add = old_add * mul + add`。

### Python 知识

- 在更新处及时 `% modulus`，避免大整数继续膨胀。
- `list(map(int, input().split()))` 同时兼容三种不同长度的操作行。
- 用平行列表保存 `sum`、`multiply`、`addition`，避免大量节点对象。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树 `O(n)`，每次操作 `O(log n)`，空间 `O(n)`。

### 总结

区间乘加的懒标记本质是函数复合；先写出代数公式，再实现线段树会更可靠。
