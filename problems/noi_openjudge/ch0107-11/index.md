---
oj: "noi_openjudge"
problem_id: "ch0107-11"
title: "潜伏者"
description: "同时维护密文到明文和明文到密文映射，验证完整双射后翻译电报。"
difficulty: "普及-"
date: 2026-07-30 23:01
updated: 2026-10-07 12:15
toc: true
tags: ["字符串", "映射", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0107-07"
    reason: "B 复用 A 的按字符映射表逐字符翻译这一步，再叠加双向一一映射冲突校验与恰有 26 个密字的检查"
  - oj: "noi_openjudge"
    problem_id: "ch0107-04"
    reason: "B 的双射映射沿用 A 教的字典映射表建模与查表判定（扫描时查表判断是否与已有记录冲突），再叠加双向两表一致性与 26 字母全覆盖校验"
  - oj: "roj"
    problem_id: "1673"
    reason: "B 复用 A 教的「扫描时用字典查表判定已有记录」这一步：A 用它判重复并取首次位置，B 用同一查表判定检验密文→明文与明文→密文两向映射是否与已有记录冲突，再叠加 26 字母全覆盖校验与翻译，属于在 A 基础上叠加额外流程。"
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/11/
---

[[TOC]]

### 题意

已知一条密文及其原文，恢复代换密码并翻译新密文；映射必须是一一对应且覆盖全部 $26$ 个大写字母。

### 思路

`cipher_to_plain` 记录密字对应的原字，`plain_to_cipher` 记录反向关系。扫描已知对应时，两张表都不能和已有记录冲突。最后检查密文字母是否恰有 $26$ 个，才能翻译新信息。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设三行字符串总长度为 $n$，时间复杂度为 $O(n)$，映射空间为 $O(26)$。

### 总结

一一映射校验应同时检查正向和反向，才能发现两个原字共用一个密字。
