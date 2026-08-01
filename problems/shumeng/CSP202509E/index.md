---
oj: "shumeng"
problem_id: "CSP202509E"
title: "造题计划（下）"
description: "把余额 DP 维护成离散凸函数，用斜率堆完成拉格朗日最优化并二分可行题数。"
date: 2026-07-31 16:22
toc: true
tags: ["斜率优化", "凸函数", "拉格朗日"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202509E
difficulty: "提高+/省选-"
---

[[TOC]]

### 题意

每天小 C 至多造一道题，小 F 至多验一道题；同一天上午造题、下午验题是允许的。每道题必须先造后验，总花费不超过 `m`，求最多完成的题数。

### 思路

把“已经造出但还没有验”的题数作为状态。小数据可以递归枚举每天的四种选择：

@include-code(./brute.cpp, cpp)

给每完成一道题奖励 `lambda`，把验题费用改为 `b_i-lambda`。处理完前 `i` 天后，令 `F_i[h]` 为余额为 `h` 时的最小调整费用。`F_i[h]` 关于 `h` 是离散凸函数，记相邻斜率为

$$D_h=F_i[h]-F_i[h-1].$$

一天的转移只会让斜率序列发生以下变化：

1. 计算 `center=min(0,a_i+b_i-lambda)`；
2. 若最小斜率小于 `lower=center-(b_i-lambda)`，删除它并插入 `lower`，同时调整 `F[0]`；
3. 插入 `upper=a_i-center`。

因此用一个小根堆维护斜率即可，每天只进行常数次堆操作。堆中的值同时保存调整费用和在费用相同时优先选择的题数。

`F_n[0]` 给出固定 `lambda` 下最优的 `cost-lambda*count`。随着 `lambda` 增大，最优题数单调不减；二分 `lambda`，找到调整后费用仍不超过预算的最大斜率，再还原实际费用即可得到最大可行题数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

一次拉格朗日求解为 `O(n log n)`，二分奖励后总复杂度为 `O(n log n log V)`，空间复杂度为 `O(n)`。

### 总结

题目的先造后验约束自然形成余额 DP。关键观察是这个 DP 的离散凸性，使得整张状态表可以压缩为有序斜率；拉格朗日奖励再把“最大数量且有预算”转成一维参数搜索。
