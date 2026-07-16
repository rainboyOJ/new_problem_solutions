---
oj: "luogu"
problem_id: "P4551"
title: "最长异或路径"
description: "把树上路径异或转为两个根前缀异或，再用 01-Trie 求最大异或对。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["01-Trie", "异或", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4551
---

[[TOC]]

### 题意

求带权树上任意两点间路径边权异或和的最大值。

### 思路

令 `xor_from_root[u]` 为根到 `u` 的边权异或。两点路径的公共部分异或两次被抵消，因此：

```text
xor_path(u, v) = xor_from_root[u] ^ xor_from_root[v]
```

问题变为在所有根前缀异或值中找最大异或对。逐个扫描值，在 01-Trie 中优先走与当前位相反的儿子，查询它与此前值能得到的最大异或，然后插入当前值。

### Python 知识

- 显式栈遍历树，避免递归深度限制。
- 算出根异或后 `del graph`，在创建最多约 310 万个 Trie 节点前释放邻接表。
- `array("I")` 保存无符号异或值，两个 `array("i")` 保存 Trie 儿子。
- 条件表达式选择当前位对应的儿子数组。

### 代码

@include-code(./main.py, python)

### 复杂度

树遍历 $O(n)$，每个值处理 31 位，总时间 $O(31n)$，空间 $O(31n)$。

### 总结

树上异或题先尝试定义根前缀值；路径问题常会立刻化成普通数组上的异或配对。
