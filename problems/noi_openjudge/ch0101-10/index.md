---
oj: "noi_openjudge"
problem_id: "ch0101-10"
title: "超级玛丽游戏"
description: "把题面给定的多行 ASCII 字符画原样保存并一次输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["输出", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/10/
---

[[TOC]]

### 题意

本题没有输入。严格按照样例输出给定的多行超级玛丽字符画，任何一行的前导空格、内部空格、标点和行尾都不能改变。

### 思路

把整幅字符画保存在一个三引号字符串中，再一次 `print` 输出。三引号字符串会保留每一行中的空格和换行，适合这种固定多行文本。

字符串的开头紧贴第一行内容，避免多出空行；每行末尾也不写空格。`print` 只在最后补上一个换行，不会改动中间各行的布局。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

字符画长度是常数，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

固定字符画题没有算法难点，关键在于逐行、逐字符复制。多行文本在 Python 中可用三引号字符串保存，提交前必须检查行首和行尾空格。
