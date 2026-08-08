---
oj: "luogu"
problem_id: "P2580"
title: "于是他错误的点名开始了"
description: "分别用合法姓名集合和已点名集合区分 WRONG、OK 与 REPEAT。"
difficulty: "普及-"
date: 2026-07-16 19:57
toc: true
tags: ["集合", "字符串", "状态记录", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2580
---

[[TOC]]

### 题意

每次读到一个姓名：不在名单输出 `WRONG`，第一次点到合法姓名输出 `OK`，之后再次点到输出 `REPEAT`。

### 思路

维护两个集合：

- `valid`：完整合法名单，始终不变；
- `called`：已经正确点到过的姓名。

按 `name not in valid`、`name in called` 的顺序判断即可。只有输出 `OK` 时才加入 `called`，错误姓名重复出现仍然应输出 `WRONG`。

### Python 知识

- 集合推导式 `{next(data) for ...}` 直接读取名单。
- `bytes` 可作为集合键，不必为每个姓名解码成 Unicode 字符串。
- `set.add` 记录已出现状态，平均复杂度 $O(1)$。
- 答案列表最后用换行连接，避免频繁输出。

### 代码

@include-code(./main.py, python)

### 复杂度

设姓名总字符数为 $L$，期望时间和空间均为 $O(L)$。

### 总结

C++ 常把本题作为 Trie 模板；Python 中完整字符串集合就是更自然的等价数据结构。
