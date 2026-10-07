---
oj: "roj"
problem_id: "1456"
title: "图书管理"
description: "用 unordered_set 维护图书集合，add 插入，find 查询。"
difficulty: "入门"
date: 2026-09-30 11:39
updated: 2026-10-06 00:13
toc: true
tags:
  - 字符串
  - 哈希表
favorite: false
favorite_reason: ""
categories:
  - 数据结构
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1456
---

[[TOC]]

## 题目描述

维护一个动态字符串集合，初始为空。依次处理 $n$ 条指令：`add s` 表示加入书名为 $s$ 的书，`find s` 表示查询是否存在该书。书名可能包含空格，区分大小写。对每个 `find` 输出 `yes` 或 `no`。

## 思路

用 `unordered_set<string>` 保存已添加的书名，`add` 时插入，`find` 时直接判断是否存在；每行读取时先读操作符，再用 `getline` 读取剩余内容作为书名。

## 参考代码

@include-code(./main.cpp, cpp)
