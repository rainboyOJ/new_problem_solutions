---
oj: "roj"
problem_id: "1182"
title: "合影效果"
description: "按性别分桶后 male 升序、female 降序两次排序拼接输出，两位小数与单空格分隔。"
difficulty: "入门"
date: 2026-09-29 22:27
updated: 2026-10-05 04:33
toc: true
tags: ["排序", "入门", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1182
---

[[TOC]]

## 题目描述

n 个人（2 ≤ n ≤ 40，至少 1 男 1 女，身高互异）合影，男生全在左并从矮到高、女生全在右并从高到矮。第一行是 n，随后 n 行各为性别（male/female）与身高；输出 n 个身高，保留两位小数、单空格分隔。样例：输入 `6 / male 1.72 / male 1.78 / female 1.61 / male 1.65 / female 1.70 / female 1.56`，输出 `1.65 1.72 1.78 1.70 1.61 1.56`。

## 思路

按性别分两个桶，男生桶升序、女生桶降序，拼接输出即可；n ≤ 40，桶内排序直接手写冒泡。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)