---
oj: "luogu"
problem_id: "P5318"
title: "【深基18.例3】查找文献"
description: "先把每个点的邻接表按升序排序，再用逆序压栈实现非递归 DFS，用队列实现 BFS。"
difficulty: "入门"
date: 2026-06-19 19:24
toc: true
tags: ["图论", "DFS", "BFS", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5318
---

[[TOC]]

### 题意

给出一个有向图，从 `1` 号点出发，分别输出：

- 按题目要求进行的 DFS 遍历顺序
- 按题目要求进行的 BFS 遍历顺序

如果某一步有多个可选点，必须先访问编号较小的那个。

### 思路

最直接的做法就是照定义写 DFS 和 BFS。

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 用递归 DFS 和普通队列 BFS 实现了最直观的版本，适合小图对拍。

真正需要注意的是访问顺序和栈深：

1. 邻接表必须先按升序排序
2. BFS 直接按升序扩展邻居即可
3. 正式解里的 DFS 不建议用递归，因为 `n` 可达 `1e5`

这张图展示样例结构：

```dot
digraph G {
  1 -> 2;
  1 -> 3;
  1 -> 4;
  2 -> 5;
  2 -> 6;
  3 -> 7;
  4 -> 7;
  4 -> 8;
  7 -> 8;
}
```

从图里可以看出，BFS 很自然是一层一层访问；而 DFS 则需要优先深入编号更小的后继。所以正式解采用“邻接表升序 + 逆序压栈”的方式，用显式栈模拟递归 DFS 的顺序。

### Python 知识

- `deque` 的 `popleft()` 是 $O(1)$，适合作为 BFS 队列。
- 非递归 DFS 用列表作栈；邻接表升序后以 `reversed(graph[node])` 逆序压栈，弹出时才会优先访问小编号。
- `bytearray(n+1)` 比 Python 布尔列表更紧凑，适合十万点访问标记。
- 逐行读入百万条边，避免 `read().split()` 同时保留两百万个临时 token。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` 队列和容器选择。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度与输入内存。

### 代码

@include-code(./main.py, python)


### 复杂度

建图后需要对各邻接表排序，然后各做一次 DFS 和 BFS。时间复杂度上界为 $O(m\log m+n+m)$，空间复杂度 $O(n+m)$。

### 总结

这题本身不难，关键在两个实现细节：邻接表要排序，非递归 DFS 要逆序压栈。把这两个点处理好，答案就稳定了。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
