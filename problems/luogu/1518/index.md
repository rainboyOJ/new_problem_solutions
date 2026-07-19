---
oj: "luogu"
problem_id: "P1518"
title: "[USACO2.4] 两只塔姆沃斯牛 The Tamworth Two"
description: "同时模拟牛和 Farmer 的位置与方向，用状态集合检测循环，若同格则输出分钟数。"
difficulty: "普及-"
date: 2026-07-15 21:48
toc: true
tags: ["模拟", "状态", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1518
---

[[TOC]]

### 题意

在 `10*10` 网格中，牛和 Farmer 初始都朝北。每分钟二者同时行动：前方可走就前进一步，否则原地顺时针转 90 度。若某分钟结束后同格，输出分钟数；若永远不会相遇，输出 `0`。

### 思路

一个对象的状态由三部分组成：

```text
行、列、方向
```

牛和 Farmer 的整体状态就是二者状态合在一起。网格和方向都是有限的，如果某个整体状态第二次出现，之后会完全重复，说明永远不会相遇。

所以流程是：

1. 用 `move(row, col, direction)` 模拟单个对象移动一分钟；
2. 每分钟前把整体状态放入 `seen`；
3. 同时移动牛和 Farmer；
4. 若同格，输出分钟数；
5. 若状态重复，输出 `0`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 适合记录访问过的状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：状态若含多个字段，可用元组保存并放入集合。
- 方向数组 `directions = [(-1,0),(0,1),(1,0),(0,-1)]` 配合 `(direction+1)%4` 表示右转。
- `0 <= nr < 10` 是网格边界判断。

### 代码

@include-code(./main.py, python)


### 复杂度

整体状态数最多为 `10*10*4*10*10*4`，时间和空间复杂度都是常数级。

### 总结

有限状态模拟题要主动记录状态。一旦状态重复，后续轨迹必然循环，可以安全判定无解。
