---
oj: "roj"
problem_id: "1178"
title: "成绩排序"
description: "把学生按成绩降序排序，同分时按姓名字典序升序输出。"
difficulty: "入门"
date: 2026-09-29 22:16
updated: 2026-10-04 10:19
toc: true
tags:
  - 排序
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1178"
---

[[TOC]]

## 形式化题目

给定 $n$ 个二元组 $(\text{name}_i, \text{score}_i)$，其中 $\text{name}_i$ 为只含字母的字符串且长度不超过 20，$\text{score}_i$ 为 $[0,100]$ 内的整数。要求按如下严格弱序排序后输出全部记录：

$$
i \prec j \iff
    (\text{score}_i > \text{score}_j) \;\lor\;
    (\text{score}_i = \text{score}_j \;\land\; \text{name}_i < \text{name}_j)
$$

## 正解

### 思路

把比较规则直接编码成 Python 的排序键。成绩需要降序，于是取 $-\text{score}$ 作为第一关键字；同分时要求姓名字典序升序，于是把名字作为第二关键字。调用 `students.sort(key=lambda x: (-x[1], x[0]))` 即可一次得到目标序列，随后按行输出。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \log n)$，其中 $n < 20$。
- 空间复杂度：$O(n)$，用于存储学生列表与输出结果。

## 总结

本题是排序规则定制的基础练习。把“成绩高优先、同分字典序小优先”写成单一键值函数，就能用通用排序算法得到正确答案；核心在于把降序转成取负数后的升序。
