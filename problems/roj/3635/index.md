---
oj: "roj"
problem_id: "3635"
title: "[noip2016-普及] 回文日期"
description: "回文条件把月日钉死在年份的倒序上：枚举年份、还原月日并校验真实日期，落在区间内则计数。"
difficulty: "普及-"
date: 2026-10-02 11:56
updated: 2026-10-06 15:33
toc: true
tags: ["枚举", "回文", "日期与日历", "python"]
favorite: false
favorite_reason: ""
categories:
  - "日期与日历"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3635
---

[[TOC]]

## 题目描述

用 8 位数字 `YYYYMMDD` 表示日期，若这 8 位顺读倒读相同则称回文日期。给定两个真实日期 $d_1 \le d_2$，求 $[d_1,d_2]$ 内真实存在的回文日期个数。月份天数按公历规则，闰年为 4 的倍数且非 100 的倍数，或 400 的倍数。样例 1 输入 `20110101 / 20111231`，输出 `1`；样例 2 输入 `20000101 / 20101231`，输出 `2`。

## 思路

回文要求 `MMDD` 等于年份的倒序，因此年份一旦确定，月日就唯一确定。枚举起止年份之间至多 9000 个年份，倒序取出月日，先判月份是否在 $1\sim12$，再按当月天数（2 月结合闰年）判日期是否存在，拼回 8 位日期落在区间内即计数。

## 参考代码

@include-code(./main.cpp, cpp)
