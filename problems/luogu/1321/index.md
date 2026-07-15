---
oj: "luogu"
problem_id: "P1321"
title: "单词覆盖还原"
description: "枚举每个可能起点，只要 boy 或 girl 的对应位置有一个可见字符，就说明这里曾贴过一个单词。"
difficulty: "普及-"
date: 2026-06-19 09:12
toc: true
tags: ["字符串", "模拟", "推导", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1321
---

[[TOC]]

### 题意

最初有一个全是 `.` 的字符串，之后多次把 `boy` 或 `girl` 贴到某些位置。后贴的单词可能覆盖之前的字符，但每个贴过的单词最终至少有一个字符没有被覆盖。给出最终字符串，求一共贴过多少个 `boy` 和多少个 `girl`。

### 思路

如果某个 `boy` 从位置 `i` 开始贴，那么最终至少会留下下面三个位置中的一个可见字符：

```text
s[i] == 'b' 或 s[i+1] == 'o' 或 s[i+2] == 'y'
```

因此枚举所有可能起点 `i`，只要满足上面任意一个条件，就说明这里曾经贴过一个 `boy`。

`girl` 同理：

```text
s[i] == 'g' 或 s[i+1] == 'i' 或 s[i+2] == 'r' 或 s[i+3] == 'l'
```

这题的推导比代码更重要；最终做法就是按起点扫描，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串支持下标访问。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单行字符串直接用 `input()`。
- `range(len(s) - 2)` 保证访问 `i+2` 不越界。
- 用多个 `or` 表达“对应位置至少留下一个字符”。

### 代码

@include-code(./main.py, python)

### 复杂度

设字符串长度为 `n`，扫描 `boy` 和 `girl` 各一遍，时间复杂度是 $O(n)$，空间复杂度是 $O(1)$。

### 总结

覆盖还原题要抓住题目保证：每个贴上的单词至少留下一个字符。于是从“完整单词是否出现”转成“某个起点的对应位置是否至少命中一个字符”。
