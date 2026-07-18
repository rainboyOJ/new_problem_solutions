---
oj: "luogu"
problem_id: "P3879"
title: "[TJOI2010] 阅读理解"
description: "用 defaultdict 建立单词到文章编号列表的倒排索引，并在每篇文章内先去重。"
difficulty: "普及-"
date: 2026-06-21 01:30
toc: true
tags: ["字符串", "哈希", "倒排索引", "defaultdict", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3879
---

[[TOC]]

### 题意

给出 `n` 篇文章的单词。每次查询一个单词，按升序输出它出现过的文章编号；同一文章重复出现只输出一次编号，不存在则输出空行。

### 思路

查询方向是“由单词找文章”，因此预处理一个倒排索引：

```text
单词 -> 出现过的文章编号列表
```

读第 `article_id` 篇文章时，先用 `set` 对该篇单词去重，再把编号追加到每个单词的列表。文章按 `1..n` 顺序处理，所以列表天然递增，不需要额外排序。

查询时直接取得对应列表。`defaultdict(list)` 对未出现的单词自动给出空列表，连接后自然得到题目要求的空行。

### Python 知识

- `defaultdict(list)` 省去“键不存在就先建立空列表”的分支。
- `set(words)` 只去掉同一篇文章内的重复，不影响文章编号顺序。
- `articles[word].append(article_id)` 是典型的一对多索引写法。
- 生成器表达式按查询顺序生成每一行答案，再统一用换行连接。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`defaultdict`、集合和一对多映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器式批量输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

defaultdict：

@include-code(./main-pythonic.py, python)

### 复杂度

设所有输入和查询单词的总字符数为 `L`，建立和查询哈希索引的期望时间为 $O(L)$，另加实际输出规模；空间复杂度为 $O(L)$。

### 总结

这题不是必须使用 Trie。Python 字典直接把完整单词映射到文章列表，既精确又简洁；每篇先去重是避免重复文章编号的关键。
