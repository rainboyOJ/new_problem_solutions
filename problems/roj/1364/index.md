---
oj: "roj"
problem_id: "1364"
title: "二叉树遍历(flist)"
description: "层序保证祖先先于子孙：中序区间中层序排名最小的字符就是子树根，递归切分输出先序。"
difficulty: "入门"
date: 2026-09-30 07:15
updated: 2026-10-05 12:07
toc: true
tags: ["入门", "二叉树", "树的遍历", "递归", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1364
---

[[TOC]]

## 题目描述

给定一棵二叉树的中序遍历和层序遍历字符串（字符互不重复），输出其先序遍历字符串。

输入两行，分别为中序序列和层序序列；输出一行先序序列。例如中序 `DBEAC`、层序 `ABCDE` 输出 `ABDEC`。

## 思路

层序遍历中祖先一定排在子孙前面，所以任意中序区间对应的子树根，就是该区间字符中层序排名最小的那个。先输出根，再按根在中序中的位置切分左右两段递归。

## 参考代码

@include-code(./main.cpp, cpp)
