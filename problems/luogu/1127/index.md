---
oj: "luogu"
problem_id: "P1127"
title: "词链"
description: "把单词建成首尾字母间的有向边，用有序 Hierholzer 算法构造字典序最小欧拉路。"
difficulty: "普及+/提高"
date: 2025-12-23 10:35
toc: true
tags: ["欧拉路", "Hierholzer", "字符串", "python"]
categories: []
pre:
  - oj: "HDU"
    problem_id: "1116"
    reason: "先掌握有向图欧拉路径的入度/出度判定条件，再学 Hierholzer 算法输出字典序最小路径。"
common:
  - oj: "HDU"
    problem_id: "1116"
    reason: "同为有向图欧拉路径问题，HDU 1116 只判定存在性，P1127 额外要求输出路径。"
recommend: []
source: https://www.luogu.com.cn/problem/P1127
---

[[TOC]]

### 题意

把所有单词各使用一次排成链，使前一个单词末字母等于后一个单词首字母。输出字典序最小的词链，不存在则输出 `***`。

### 思路

把 26 个字母看成点，每个单词看成从首字母到末字母的有向边。“每个单词恰好一次”就变成经过每条边恰好一次的欧拉路。

先检查度数：

- 欧拉路径恰有一个点 `out-in=1`、一个点 `in-out=1`，其余平衡；
- 欧拉回路所有点入度等于出度，此时从最小的有出边字母开始；
- 其它情况无解。

每个字母的出边按单词降序保存，尾部就是当前字典序最小的单词。非递归 Hierholzer 不断取尾部边，走不动时回退并把进入该点的单词加入结果。最后反转后序结果。

即使度数合法，图也可能不连通；因此最后还要检查结果是否恰好包含 `n` 条边。包含不足就输出 `***`。

### Python 知识

- `word[0]-97` 和 `word[-1]-97` 把小写字节映射到 `0..25`。
- `edges.sort(reverse=True)` 配合 `pop()`，既取得最小边又避免列表头部删除的线性移动。
- `vertex_stack` 与 `word_stack` 平行维护当前路径，替代可能达到 1000 层的递归。
- `b".".join(reversed(route))` 直接连接字节单词并输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：降序保存、尾部弹出模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度和列表删除成本。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

排序所有单词需要 $O(n\log n)$，Hierholzer 遍历 $O(n)$；空间复杂度 $O(n)$。

### 总结

建模的关键是“单词是边，不是点”。度数决定欧拉路起点，有序取边决定字典序，结果边数负责最终连通性检查。
