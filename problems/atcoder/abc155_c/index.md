---
oj: "atcoder"
problem_id: "abc155_c"
title: "C - Poll"
description: "统计每个字符串出现次数，输出最高频的字符串（字典序）。"
difficulty: "入门"
date: 2026-07-10 22:28
toc: true
tags: ["haskell", "排序", "map"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abc155/tasks/abc155_c
---

[[TOC]]

### 题意

$N$ 个字符串，输出出现次数最多的所有字符串，按字典序升序。

### 思路

**写法一：sort + group**

`sort ss` 把相同字符串排到一起，`group` 把它们压缩成组，每组长度就是频次，`map head` 取每组代表的字符串，筛选出最长组。

**写法二：Map 计数**

```haskell
Map.fromListWith (+) [(s, 1) | s <- ss]
```

这行是计数核心。`fromListWith` 遍历列表，遇到相同的 key 就把新旧 value 通过 `(+)` 合并。
等价于 C++ 的 `map[s]++`，但 Haskell 用纯函数式的一次性构建。

具体流程：

| 步骤 | 代码 | 含义 |
|------|------|------|
| 构建频次 Map | `Map.fromListWith (+) [(s,1) \| s <- ss]` | 每个字符串作为 key，出现一次加 1 |
| 找最大频次 | `maximum (Map.elems freq)` | 取出所有 value，取最大值 |
| 筛选最高频字符串 | `[s \| (s,c) <- Map.toList freq, c == maxCnt]` | 遍历所有 (key, value)，保留频次等于最大值的 |
| 字典序排序 | `sort` | 题目要求字典序输出 |

### 代码

@include-code(./main.hs, haskell)

@include-code(./main2.hs, haskell)

### 复杂度

时间复杂度 $O(N \log N)$，空间复杂度 $O(N)$。

### 总结

计数两种思路：`sort + group` 直接利用排序聚合同类项，`Map.fromListWith (+)` 用哈希表统计频次。
