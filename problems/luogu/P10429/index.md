---
oj: "luogu"
problem_id: "P10429"
title: "[蓝桥杯 2024 省 B] 拔河"
description: "枚举右段左端点，用 multiset 维护左半区间内全部子段和，二分逼近使两段力量和的差最小。"
difficulty: "普及+/提高-"
date: 2026-11-06 21:10
updated: 2026-11-06 21:10
toc: true
tags: ["前缀和","枚举","二分","set"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
rbookLinks: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P10429
---

[[TOC]]

## 形式化题目

<!-- 由 oj-problem-analysis-writer 填写：去除背景，描述计算任务的数学结构。不写IO格式和数据范围。
     用树/点/边/权值/颜色/路径点集等抽象对象，不搬题面故事词（题面词汇只留一句桥接说明）；
     每条操作或约束写成「中文动作 + 形式化式子」两层。 -->

<!--
正文布局尚未确定。
oj-problem-analysis-writer 必须先读取 problem.md、约束、子任务、已有代码与过程文档，
再从“直接正解型、暴力到正解型、并列多解法型、子任务递进型”中选择布局，
重写本注释所在位置。不要把 new-problem.py 的脚手架当作最终文章结构。
正式主解必须通过 @include-code(./main.<ext>, <lang>) 出现在所选布局的代码小节中。
-->

## 总结

<!-- 由 oj-problem-analysis-writer 填写 -->
