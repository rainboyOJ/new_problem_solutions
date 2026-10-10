---
oj: "roj"
problem_id: "3143"
title: "「Jury Compromise」 陪审团"
description: "选 M 人使控辩总分差最小、总分和最大：以 diff=D-P 为状态维度的 01 背包（分层 DP），逐人更新并记录成员位掩码，O(N·M·range)。"
difficulty: "省选/NOI-"
date: 2026-10-01 20:45
updated: 2026-10-10 11:30
toc: true
tags:
  - "DP"
  - "背包DP"
  - "状态记录"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3143
---

[[TOC]]

## 形式化题目

$N$ 个候选人各有控方分 $p_i$、辩方分 $d_i$（$0\le p_i,d_i\le 20$）。选出 $M$ 人，最小化 $|\sum p - \sum d|$；并列时最大化 $\sum p + \sum d$；再并列按题面字典序输出成员编号。

## 正解

### 思路

#### 1. 以「分差」为状态的 01 背包

令 $\text{diff} = D-P$，目标是让 $|\text{diff}|$ 最小。直接枚举子集是 $2^N$；用 DP：

$$f[j][\text{diff}] = \text{恰好选 } j \text{ 人、分差为 diff 时的最大总分和}(P+D)$$

$j=1..M$ 分层，每人是 01 物品（$\Delta\text{diff}=d_i-p_i$，$\Delta\text{sum}=d_i+p_i$）。转移从 $f[j-1]$ 来，$j$ 从大到小滚动防止同人选两次。

#### 2. 记录成员集合

状态里额外保存**成员位掩码**（$N\le 200$ 时用 Python 整数当位集）。并列时按题面字典序规则决出：先按 $|d_i-p_i|$ 降序处理候选人（分歧大的先定下来），保证位掩码并列比较稳定。

#### 3. 答案提取

在 $f[M]$ 里扫 $|\text{diff}|$ 最小者（并列取总分最大），按位掩码还原编号序列输出。

### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(N \cdot M \cdot R)$，$R$ 为 diff 值域（$\le 40M$）。
- **空间复杂度**：$O(M \cdot R)$。

## 总结

- 「选 k 个使差值最小、和最大」= 以差值为费用、和为价值的**双维度 01 背包**。
- 并列决策需要稳定的打破顺序：按 $|d_i-p_i|$ 降序处理 + 位掩码比较是简洁做法。
- Python 的任意精度整数天然适合做 200 位以内的成员位集。
