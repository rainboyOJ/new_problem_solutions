---
oj: "luogu"
problem_id: "P3405"
title: "[USACO16DEC] Cities and States S"
description: "用 Counter 统计已出现的城市前缀与州代码，流式累加反向二元组数量。"
difficulty: "普及-"
date: 2026-07-16 18:26
toc: true
tags: ["哈希", "计数", "Counter", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3405
---

[[TOC]]

### 题意

每座城市给出城市名和两字母州代码。若城市 `A` 的前两个字母等于城市 `B` 的州代码，反过来也成立，并且两城不在同一州，则它们构成特殊城市对。求无序对数量。

### 思路

把一座城市压缩成二元组 `(城市名前缀, 州代码)`。

假设当前二元组是 `(prefix,state)`，能和它配对的历史二元组只能是 `(state,prefix)`。因此顺序扫描城市时：

1. 把已经出现的二元组放进计数器 `seen`；
2. 当前答案增加 `seen[state,prefix]`；
3. 再把 `seen[prefix,state]` 加一。

这样每个无序对只会在第二座城市出现时统计一次。若 `prefix==state`，两座匹配城市会来自同一州，不符合题意，必须跳过。

### Python 知识

- `Counter` 是“键到出现次数”的字典，访问不存在的键会得到 `0`，省去初始化判断。
- 元组可以直接作为字典键，`seen[prefix, state]` 等价于 `seen[(prefix,state)]`。
- 输入保留为 `bytes`，`city[:2]` 同样可以切出前两个 ASCII 字节，无需解码。
- `zip(data[1::2], data[2::2])` 把扁平 token 两两配成城市名和州代码。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`Counter` 和字典计数模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`：流式处理与配对思路。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

Counter：

@include-code(./main-pythonic.py, python)

### 复杂度

每座城市只做常数次哈希表操作，期望时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

不要枚举城市对。先找出一个对象的“唯一互补键”，再用计数器查询它此前出现了多少次，就能把二次枚举改成一次扫描。
