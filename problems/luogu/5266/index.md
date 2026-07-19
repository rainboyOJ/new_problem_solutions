---
oj: "luogu"
problem_id: "P5266"
title: "【深基17.例6】学籍管理"
description: "用字典建立姓名到成绩的映射，直接完成增改查删和人数统计。"
difficulty: "入门"
date: 2026-07-16 18:26
toc: true
tags: ["字典", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5266
---

[[TOC]]

### 题意

维护学生姓名和成绩，支持插入或修改、查询、删除，以及输出当前学生人数。

### 思路

姓名唯一确定一名学生，成绩是随姓名保存的值，正好对应字典的 `key -> value` 模型：

- `students[name]=score`：插入新学生或覆盖旧成绩；
- `name in students`：判断学生是否存在；
- `students[name]`：取得成绩；
- `del students[name]`：删除；
- `len(students)`：当前人数。

逐条模拟即可，不需要自己实现哈希表。

### Python 知识

- 字典赋值天然同时覆盖“插入”和“修改”两种情况。
- 查询前先用 `in` 判断，避免不存在的键触发 `KeyError`。
- `del mapping[key]` 删除指定键值对，`len(mapping)` 直接得到记录数。
- 姓名保留为 `bytes` 也可以作为字典键，减少批量输入后的解码工作。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典的增删改查模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：按不同操作参数个数解析 token。

### 代码

@include-code(./main.py, python)


### 复杂度

每次操作期望时间复杂度 $O(1)$；字典最多保存 $O(q)$ 名学生，空间复杂度 $O(q)$。

### 总结

先识别数据模型：唯一姓名是键，成绩是值。Python 字典已经完整提供这类管理系统需要的操作。
