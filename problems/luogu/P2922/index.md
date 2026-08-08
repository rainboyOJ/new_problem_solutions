---
oj: "luogu"
problem_id: "P2922"
title: "[USACO08DEC] Secret Message G"
description: "二进制 Trie 同时记录终止数量和子树数量，统计两串中较短者为公共前缀的消息数。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["Trie", "前缀", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2922
---

[[TOC]]

### 题意

对每条暗号，统计有多少消息与它从第一位开始相同，直到两者中较短的一条结束。

### 思路

把所有消息插入二进制 Trie。每个节点记录：

- `terminal_count`：恰好在此结束的消息数；
- `subtree_count`：经过此节点的消息数。

查询暗号时，沿路径每下降一层前，把当前节点终止的消息加入答案，它们是暗号的前缀。若暗号整条路径存在，最后再加当前节点的子树数，它们以暗号为前缀。两部分不会重复。

### Python 知识

- 只有 0/1 两条边，使用 `child_zero`、`child_one` 两个 `array("i")` 比节点字典更紧凑。
- 下标 `0` 统一表示不存在的儿子。
- 查询位先读成列表，即使 Trie 提前失配，也已经正确消耗本行输入。
- `for ... else` 的 `else` 只在循环没有 `break` 时执行，正好处理“暗号完整走完”。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

时间和空间均为所有消息与暗号总位数的 $O(L)$。

### 总结

这类“较短串必须是较长串前缀”的计数，需要同时统计路径上的终止串和终点下方的更长串。
