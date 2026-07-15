---
oj: "luogu"
problem_id: "P2550"
title: "[AHOI2001] 彩票摇奖"
description: "把中奖号码存成集合，统计每张彩票与它的交集大小并映射到对应奖项。"
difficulty: "入门"
date: 2026-07-15 18:48
toc: true
tags: ["模拟", "集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2550
---

[[TOC]]

### 题意

给出 `7` 个中奖号码和 `n` 张彩票。每张彩票也有 `7` 个号码。匹配 `7` 个是特等奖，匹配 `6` 个是一等奖，依次到匹配 `1` 个是六等奖。输出每个奖项各有多少张彩票。

### 思路

题目不关心号码顺序，只关心是否出现，所以用集合最自然。

把中奖号码存成 `winning`。对每张彩票，把它也转成集合 `ticket`，两者交集：

```text
winning & ticket
```

就是命中的号码集合。交集大小 `match_count` 表示命中几个号码。

输出顺序是命中 `7,6,5,4,3,2,1` 个，因此数组下标可以写成：

```text
answer[7 - match_count] += 1
```

如果 `match_count = 0`，没有奖项，不统计。

这题是集合统计练习，正解已经直接对应题意，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(int, input().split())` 读取号码。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 适合做去重和成员关系判断。
- `winning & ticket` 是集合交集。
- `len(...)` 得到命中号码个数。
- `print(*answer)` 按空格输出七个奖项数量。

### 代码

@include-code(./main.py, python)

### 复杂度

每张彩票只有 `7` 个号码，单张处理是常数时间。总时间复杂度是 $O(n)$，空间复杂度是 $O(1)$。

### 总结

这题的关键是看出“顺序无关”。用集合求交集，可以直接得到命中号码数量。
