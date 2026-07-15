---
oj: "luogu"
problem_id: "P1428"
title: "小鱼比可爱"
description: "对每条小鱼枚举它左边的所有小鱼，统计可爱程度严格更小的数量。"
difficulty: "入门"
date: 2026-07-15 18:44
toc: true
tags: ["模拟", "枚举", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1428
---

[[TOC]]

### 题意

给出从左到右 `n` 条小鱼的可爱程度。每条小鱼只能看到自己左边的小鱼，要求输出每条小鱼左边有多少条小鱼的可爱程度严格小于它。

注意相等不算“不如自己可爱”。

### 思路

数据范围只有 `n <= 100`，可以直接按定义做双重循环。

对第 `i` 条小鱼，枚举所有 `j < i` 的小鱼。如果：

```text
cuteness[j] < cuteness[i]
```

就把计数加一。把每个位置的计数放入 `answer`，最后一行输出。

这题是数组枚举入门，正解就是直接实现定义，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `list(map(int, input().split()))` 读取一行整数数组。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：`range(i)` 可以枚举当前位置左边的下标 `0..i-1`。
- `answer.append(count)` 把当前小鱼的答案加入列表。
- `print(*answer)` 会用空格输出列表中的所有元素。

### 代码

@include-code(./main.py, python)

### 复杂度

双重循环枚举左侧元素，时间复杂度是 $O(n^2)$；答案数组需要 $O(n)$ 空间。

### 总结

这题的关键是保持“只看左边”和“严格小于”两个条件。范围很小，直接枚举比引入复杂数据结构更适合入门学习。
