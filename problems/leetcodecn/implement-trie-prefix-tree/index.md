---
oj: "leetcodecn"
problem_id: "implement-trie-prefix-tree"
title: "实现 Trie"
difficulty: "中等"
tags: [Trie, 字典树, 设计, cpp, python]
description: "每个字符沿 next[26] 走，节点维护终点标记。"
---
[[TOC]]
### 题意
实现 Trie（前缀树），支持 insert、search、startsWith。
### 思路
每个节点有 26 个子节点指针（或哈希表），isEnd 标记是否存在完整单词。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
插入/查询 O(len)，空间 O(总字符数 * 26)。
### 总结
Trie 用空间换时间，适合前缀匹配和词频统计。
