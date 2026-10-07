---
oj: "roj"
problem_id: "3030"
title: "火车进栈"
description: "DFS 按「先出栈、后进栈」分支天然按字典序枚举出站序列，收满前 20 个立即整树剪枝。"
difficulty: "普及-"
date: 2026-10-01 11:03
updated: 2026-10-06 02:35
toc: true
tags: ["栈", "dfs", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1354"
    reason: "A 教的“栈空弹栈即非法”这一括号合法性失败点，正是 B 第一步把火车进出站归约为合法括号序列时所用的“栈不能空着出”约束（代码用 if stack 保证不空弹），B 在此合法性骨架上再叠加字典序 DFS 枚举与前 20 整树剪枝。"
  - oj: "leetcodecn"
    problem_id: "valid-parentheses"
    reason: "B 的第一步直接沿用 A 教的括号合法性判定（栈空不能出栈），把火车进出站序列归约为合法括号序列结构，再在其上叠加字典序 DFS 枚举与剪枝。"
  - oj: "luogu"
    problem_id: "P1739"
    reason: "B 的第一步把火车进出站操作序列翻译成合法括号结构，直接复用 A 教的「扫描中 balance 不能为负」这一前缀非负判定，再叠加 A 未教的 DFS 按「先出栈后进栈」字典序枚举与收满 20 个整树剪枝。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3030
---

[[TOC]]

## 题目描述

$n$ 列火车按 $1\sim n$ 的顺序依次进站，车站是一个栈。每次可以选择让下一列火车进栈，或让栈顶火车出站。按字典序输出前 20 种可能的出站序列，每行一种、无空格。$1\le n\le 20$。

样例输入 `3`，输出 `123`、`132`、`213`、`231`、`321`。

## 思路

每个状态优先尝试「出栈」再「进栈」，DFS 到达叶子的顺序就是出站序列的字典序；收满 20 个后立即剪枝返回。

## 参考代码

@include-code(./main.cpp, cpp)
