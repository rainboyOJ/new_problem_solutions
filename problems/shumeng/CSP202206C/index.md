---
oj: "shumeng"
problem_id: "CSP202206C"
title: "角色授权"
description: "建立授权对象到角色的反向索引，再取用户和当次用户组关联角色的权限并集。"
difficulty: "普及+/提高"
date: 2026-07-31 16:21
toc: true
tags: ["哈希", "集合", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202206C
---

[[TOC]]

### 题意

用户、用户组通过角色关联获得权限。角色权限由操作、资源类型和资源名称三张清单描述，通配符 `*` 可匹配任意操作或类型，空资源名称清单表示任意名称。

### 思路

把每条角色关联的授权对象建立反向索引：用户名使用 `u:` 前缀，用户组使用 `g:` 前缀，值为可获得的角色编号。查询时只查用户名和当次用户组，去重后逐个检查角色的三项清单；任意一个角色允许该操作就输出 `1`。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设一次查询涉及的不同角色数为 `k`，用户组数为 `g`，时间复杂度为 $O(g+k)$ 的哈希集合查询，空间复杂度为 $O(n+m\cdot ns)$。

### 总结

每次查询的用户组信息独立使用，不能缓存同名用户此前的组；角色权限判断是多个关联角色权限的并集。
