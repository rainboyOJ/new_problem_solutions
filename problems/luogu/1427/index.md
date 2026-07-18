---
oj: "luogu"
problem_id: "P1427"
title: "小鱼的数字游戏"
description: "读入以 0 结尾的整数序列，删除结尾标记后反转列表并输出。"
difficulty: "入门"
date: 2026-07-15 18:44
toc: true
tags: ["模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1427
---

[[TOC]]

### 题意

输入一串整数，最后一个 `0` 表示结束标记，不属于要输出的数字。要求把前面的数字倒序输出。

### 思路

这一题可以直接把整行读成列表。

因为题目保证只有末尾一个 `0`，所以：

1. 用 `numbers.pop()` 删除最后的 `0`；
2. 用 `numbers.reverse()` 原地反转列表；
3. 用 `print(*numbers)` 输出。

这题主要训练列表的删除、反转和展开输出，不创建额外 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `list(map(int, input().split()))` 读取整行整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：整行整数且换行无特殊意义时，可以直接按空白切分。
- `numbers.pop()` 删除并返回列表最后一个元素。
- `numbers.reverse()` 原地反转列表。
- `print(*numbers)` 按空格输出列表内容。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

切片反向：

@include-code(./main-pythonic.py, python)

### 复杂度

设输入数字个数为 `n`。反转和输出都是 $O(n)$，空间复杂度是 $O(n)$。

### 总结

这题是典型的列表操作练习。先去掉结束标记，再反转真正的数据，逻辑会很清楚。
