---
oj: "roj"
problem_id: "3582"
title: "[NOIP2010-提高] 机器翻译"
description: "用队列按进入顺序模拟容量 M 的内存、布尔数组判命中：未命中计数入队，满员淘汰队首，O(N) 求出查词典次数。"
difficulty: "普及-"
date: 2026-10-02 09:04
updated: 2026-10-06 14:35
toc: true
tags: ["模拟", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3582
---

[[TOC]]

## 题目描述

翻译软件逐词翻译文章：内存中有该单词就直接使用；没有就查一次外存词典，并把单词放入内存。内存有 $M$ 个单元，放入新单词前若已存满 $M$ 个，先清空**最早进入内存**的单词腾出单元（命中不改变单词的进入顺序）。单词用不超过 $1000$ 的非负整数编码，相同整数代表同一单词，翻译开始前内存为空，求查词典的总次数。

输入：第一行两个正整数 $M, N$（数据范围 $0 \leqslant M \leqslant 100$，$0 \leqslant N \leqslant 1000$）；第二行 $N$ 个非负整数，按文章顺序给出。输出：一个整数，为查词典的次数。样例输入 $M=3$、序列 `1 2 1 5 4 4 1`，输出 `5`。

## 思路

内存的变化只有"尾部追加新词、头部淘汰最老词"，命中不刷新顺序，所以用队列按进入顺序存单词，命中判断用布尔数组 `in_memory[]` 做 $O(1)$ 完成。逐词扫描：命中则跳过，否则答案加一，满员时先弹出队首再把新词入队，$M=0$ 时只计数不入队。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
