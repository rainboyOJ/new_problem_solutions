---
oj: "roj"
problem_id: "1368"
title: "对称二叉树(tree_c)"
description: "顺序存储中位置 k 的左右孩子在 2k+1 与 2k+2，每对相邻位置就是一对兄弟，逐对判断是否同空或同非空即可 O(n) 判定。"
difficulty: "入门"
date: 2026-09-30 07:28
updated: 2026-10-05 12:14
toc: true
tags: ["二叉树", "顺序存储", "模拟"]
favorite: false
favorite_reason: ""
categories: ["数据结构"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1368
---

[[TOC]]

## 题目描述

给定二叉树的顺序存储串 `s`，结点按层、从左到右依次写出，空位置记作 `#`。若每个结点要么孩子齐全、要么没有孩子，则称该树对称。判断该树是否对称，输出 `Yes` 或 `No`。

样例输入 `ABCDE` 对应树 `A(B(D,E),C)`，每个非叶子结点都孩子齐全，输出 `Yes`。

## 思路

位置 `k` 的左右孩子固定落在 `2k+1` 与 `2k+2`，因此相邻位置 `(1,2)`、`(3,4)`、... 正好是一对对兄弟。把串补到长度 `2n` 后，逐对检查：若同一对里一个为空、一个非空，则不对称；全部同空或同非空则对称。末尾补 `#` 只产生同空对，不影响结果。

## 参考代码

@include-code(./main.cpp, cpp)
