---
oj: "luogu"
problem_id: "P1563"
title: "[NOIP 2016 提高组] 玩具谜题"
description: "把玩具小人看成环形序列，根据当前朝向和指令方向是否相同，用取模更新位置。"
difficulty: "普及-"
date: 2026-06-19 00:49
toc: true
tags: ["模拟", "环形处理", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1563
---

[[TOC]]

### 题意

有 `n` 个玩具小人围成一圈，每个小人有朝向和职业。从第一个小人开始，依次执行 `m` 条向左或向右数的指令。朝内和朝外的小人左右方向相反，要求输出最后到达的小人的职业。

### 思路

输入的小人按逆时针顺序给出。把当前位置记为下标 `position`。

关键结论：

- 当前小人的朝向 `facing` 和指令方向 `turn` 相同，则下标减少；
- 二者不同，则下标增加。

更新时用取模处理环形：

```python
position = (position - step) % n
position = (position + step) % n
```

注意一条指令只看“出发位置”小人的朝向，不会在走的过程中不断改变方向。历史目录中保留 C++ 文件，本文以 Python 代码为准。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：混合字符串和整数时，先 `split()` 再转换整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组 `(direction, name)` 可保存固定字段记录。
- `% n` 是环形下标更新的核心。
- `people[position][1]` 取出当前位置职业名。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

读入 `n` 个小人并执行 `m` 条指令，时间复杂度是 $O(n+m)$，空间复杂度是 $O(n)$。

### 总结

这题的重点不是一步一步数，而是把左右方向统一成环形下标变化。判断真实方向后，取模更新即可。
