---
oj: "luogu"
problem_id: "P1305"
title: "新二叉树"
description: "用字典保存每个字母节点的左右孩子，递归按根、左、右拼出前序遍历。"
difficulty: "入门"
date: 2026-07-16 18:17
toc: true
tags: ["二叉树", "递归", "字典", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1305
---

[[TOC]]

### 题意

每行给出一个节点及其左右孩子，`*` 表示空节点，第一行节点为根。输出前序遍历。

### 思路

字典 `children[node]=(left,right)` 保存树结构。前序遍历定义为“根、左、右”，因此递归函数直接返回：

```text
node + preorder(left) + preorder(right)
```

遇到 `*` 返回空串。

### Python 知识

- 三字符字符串可直接解包为 `node,left,right`。
- 字典用字符节点作键，比为 26 个字母手动换算下标更自然。
- `root = root or node` 只在第一行记录根。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串解包与拼接。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

每个节点访问一次，时间复杂度 $O(n)$；字典与递归栈空间 $O(n)$。

### 总结

节点标签不是连续整数时，字典能直接保存树；递归代码则几乎逐字对应前序遍历定义。
