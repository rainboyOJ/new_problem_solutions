---
oj: "leetcodecn"
problem_id: "lru-cache"
title: "LRU 缓存"
description: "哈希表 O(1) 找节点，双向链表按最近使用顺序维护，头为新、尾为旧。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["设计", "哈希表", "链表", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/lru-cache/
---

[[TOC]]

### 题意

实现 LRU（最近最少使用）缓存。get 和 put 都必须 O(1)。

### 思路

`unordered_map` + `list`：map 记录 key 到链表节点迭代器的映射，list 维护 (key,value) 按最近使用的顺序排列。访问或更新时将节点移到链表头部，淘汰时删除链表尾部。

Python 直接用 `OrderedDict`。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(1) get 和 put。
- 空间复杂度：O(capacity)。

### 总结

LRU 是"哈希表 + 双向链表"的组合数据结构经典案例。哈希表提供 O(1) 查找，链表维护顺序信息。
