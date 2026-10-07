---
oj: "noi_openjudge"
problem_id: "ch0112-08"
title: "Vigenère密码"
description: "按循环密钥反向平移密文字母，同时保留密文中的大小写。"
difficulty: "普及-"
date: 2026-07-30 23:01
updated: 2026-10-06 07:45
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0107-09"
    reason: "B 把 A 的「字母按字母表循环移位、越过 z/Z 回绕」这一步推广成任意位移模 26 并按大小写选 ASCII 基准，逐字符映射的处理框架完全相同"
  - oj: "luogu"
    problem_id: "P1914"
    reason: "B 沿用 A 的字符编号与 ASCII 基准互转加位移取模 26 的做法，把凯撒平移扩成密钥循环的 Vigenere 解密并处理大小写基准"
  - oj: "noi_openjudge"
    problem_id: "ch0107-10"
    reason: "B 的逐字母解密复用 A 的「字母转 0-25 下标、减位移、模 26 回绕、转回字符」这一步，只是把固定位移 5 换成按 key[i%len] 变化的位移，再叠加 A 未教的大小写 ASCII 基准选择与循环密钥取模。"
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/08/
---

[[TOC]]

### 题意

给定 Vigenere 密钥和密文，解密得到原明文；密钥忽略大小写，输出保持密文位置的大小写。

### 思路

将密钥字母转成 $0$ 到 $25$ 的位移量。第 `i` 个密文使用 `key[i % len(key)]`，解密就是字母编号减去位移后模 26。根据密文字母大小写选择对应的 ASCII 基准值。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

循环密钥可由下标对密钥长度取模实现，无需真的扩展字符串。
