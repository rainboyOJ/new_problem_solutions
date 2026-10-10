---
oj: "roj"
problem_id: "3572"
title: "[NOIP2009-提高] 潜伏者"
description: "扫描样例对建立“原字母→密字”字典，同一原字母冲突或 26 字母不成双射即输出 Failed，否则用逆表逐字符翻译电报。"
difficulty: "普及-"
date: 2026-10-02 08:25
updated: 2026-10-06 14:14
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3572
---

[[TOC]]

## 题目描述

$S$ 国用大写字母替换密码：每个字母对应唯一密字，不同字母密字不同，密字可与原字母相同。给出一对已掌握的等长加密串与原串（第 1、2 行，长度 $1$ 到 $100$）以及待破译电报（第 3 行），要求破译密码并翻译电报；若推断时出现矛盾，或 $A$-$Z$ 中有字母未在原串出现，输出 `Failed`，否则输出电报的原文。

样例 1：`AA` / `AB` / `EOWIE` → `Failed`；样例 2：`QWERTYUIOPLKJHGFDSAZXCVBN` / `ABCDEFGHIJKLMNOPQRSTUVWXY` / `DSLIEWO` → `Failed`；样例 3：`MSRTZCJKPFLQYVAWBINXUEDGHOOILSMIJFRCOPPQCEUNYDUMPP` / `YIZSDWAHLNOVFUCERKJXQMGTBPPKOIYKANZWPLLVWMQJFGQYLL` / `FLSO` → `NOIP`。

## 思路

按位扫描样例对，记录「原字母 → 密字」及逆表「密字 → 原字母」：同一原字母映射到不同密字、或不同原字母共用同一密字，都判 `Failed`；扫描后若 $26$ 个字母未全部出现也输出 `Failed`。否则密码表是双射，逆表对任意密字都有定义，逐字符翻译电报即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
