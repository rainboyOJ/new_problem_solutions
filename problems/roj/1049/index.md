---
oj: "roj"
problem_id: "1049"
title: "晶晶赴约会"
description: "读入一个 1..7 的整数表示周一到周日，若落在晶晶有课的 1、3、5 则输出 NO，否则输出 YES。"
difficulty: "入门"
date: 2026-09-29 16:21
updated: 2026-10-04 23:29
toc: true
tags: ["入门", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1049
---
[[TOC]]

## 题目描述

晶晶每周的 1、3、5 有课必须上课，朋友约她下周去看展览，请帮她判断能否接受邀请：能接受输出 `YES`，不能输出 `NO`（大小写敏感）。输入一行整数 `d`，`1` 到 `7` 分别表示周一到周日；输出按判断结果输出 `YES` 或 `NO`。样例：输入 `2`，输出 `YES`。

## 思路

把题面直译成一次三路判断即可：读入 `d`，若 `d` 等于 1、3、5 之一则输出 `NO`，否则输出 `YES`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)