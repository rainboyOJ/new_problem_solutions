---
oj: "luogu"
problem_id: "P3879"
title: "[TJOI2010] 阅读理解"
description: "用 defaultdict 建立单词到文章编号列表的倒排索引，并在每篇文章内先去重。"
difficulty: "普及-"
date: 2026-06-21 01:30
toc: true
tags: ["字符串", "哈希", "倒排索引", "trie", "字典树", "defaultdict", "python", "cpp"]
favorite: true
favorite_reason: "倒排索引入门，C++ Trie 自动带有word的hash"
categories: []
pre:
  - oj: "luogu"
    problem_id: "P1481"
    reason: "Trie / 字符串前缀匹配的入门题"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3879
---

[[TOC]]

### 题意

给出 `n` 篇文章的单词。每次查询一个单词，按升序输出它出现过的文章编号；同一文章重复出现只输出一次编号，不存在则输出空行。

### 思路

两种做法，模型完全一样：单词 → 文章编号列表。

#### Python 字典

查询方向是"由单词找文章"（给定一个词，问在哪几篇里出现过）。自然的做法是预处理一个**倒排索引**：

> **正排**（文章→单词）：第 1 篇文章有单词 {a, b, c}，第 2 篇有 {b, d}……
> **倒排**（单词→文章）：单词 a 出现在 {1}，b 出现在 {1, 2}，c 出现在 {1}，d 出现在 {2}……

"倒排"就是把映射方向反过来——不是"这篇文章有什么词"，而是"这个词在哪几篇文章里"：

```text
单词 -> 出现过的文章编号列表
```

读第 `article_id` 篇文章时，先用 `set` 对该篇单词去重，再把编号追加到每个单词的列表。文章按 `1..n` 顺序处理，所以列表天然递增，不需要额外排序。

查询时直接取得对应列表。`defaultdict(list)` 对未出现的单词自动给出空列表，连接后自然得到题目要求的空行。

#### C++ 字典树（Trie）

对于 C++，用字典树统一管理字符串，每个节点存储它代表的单词出现在哪些文章中。

插入时沿着单词往下走，走到结尾节点后把当前文章编号加入 `belong` 列表。由于同一篇文章的同一个词可能多次出现，文章编号按 `1..n` 顺序插入，只需检查列表尾部是否相同即可去重。

查询时沿 Trie 找到结尾节点，输出其 `belong` 列表；找不到时输出空行。

### Python 知识

- `defaultdict(list)` 省去“键不存在就先建立空列表”的分支。
- `set(words)` 只去掉同一篇文章内的重复，不影响文章编号顺序。
- `articles[word].append(article_id)` 是典型的一对多索引写法。
- 生成器表达式按查询顺序生成每一行答案，再统一用换行连接。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`defaultdict`、集合和一对多映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器式批量输出。

### 代码

Python（字典 + 倒排索引）：

@include-code(./main.py, python)

C++（字典树）：

@include-code(./main.cpp, cpp)


### 复杂度

设所有输入和查询单词的总字符数为 $L$。

| 做法 | 时间 | 空间 |
|------|------|------|
| Python dict | $O(L)$ 期望 | $O(L)$ |
| C++ Trie | $O(L)$ | $O(L \times 26)$ 节点数 |

### 总结

Python 字典直接把完整单词映射到文章列表，既精确又简洁；每篇先去重是避免重复文章编号的关键。C++ 用 Trie 做同样的事，优势在字符串前缀共享和稳定的时间表现。
