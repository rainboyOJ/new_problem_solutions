---
oj: "roj"
problem_id: "3560"
title: "ISBN 号码"
description: "按 ISBN-10 规则取前 9 位数字乘 1~9 求和后模 11，余 10 记为 X，与原识别码比较决定输出 Right 或补正后的完整 ISBN。"
difficulty: "入门"
date: 2026-10-02 07:36
updated: 2026-10-06 13:51
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3560
---

[[TOC]]

## 题目描述

ISBN 由 9 位数字、1 位识别码和 3 个分隔符组成，格式如 `x-xxx-xxxxx-x`；识别码算法是前 9 位数字依次乘 $1 \sim 9$ 求和后对 11 取余，余数 10 记作大写 `X`。

输入一行格式合法的 ISBN 串；识别码正确输出 `Right`，否则输出补正后的完整 ISBN（保留 `-`）。样例：`0-670-82162-4` 输出 `Right`，`0-670-82162-0` 输出 `0-670-82162-4`。

## 思路

按定义模拟：去掉 `-` 后的前 9 位数字依次乘 $1 \sim 9$ 求和，对 11 取余即得正确识别码，余 10 记作 `X`。与输入识别码相同输出 `Right`，否则输出前缀加正确识别码。

## 参考代码

@include-code(./main.cpp, cpp)
