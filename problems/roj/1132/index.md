---
oj: "roj"
problem_id: "1132"
title: "石头剪子布"
description: "利用固定克制表把石头/剪子/布的胜负判断转换为 O(1) 查询，再逐局输出结果。"
difficulty: "入门"
date: 2026-09-29 20:25
updated: 2026-10-04 10:45
toc: true
tags: ["模拟", "字符串映射"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1132
---

[[TOC]]

## 形式化题目

给定 $N$ 个二元组 $(S_1, S_2)$，其中每个元素取自集合 $\{\text{Rock}, \text{Scissors}, \text{Paper}\}$。对每组判断是否存在唯一胜者：

- 若 $S_1 = S_2$，则结果为平局；
- 否则按固定克制关系 $\text{Rock} \to \text{Scissors} \to \text{Paper} \to \text{Rock}$，被克制的一方输掉本局。

要求输出每局的胜者或平局。

## 正解

### 思路

石头剪子布的规则是一个固定的**循环克制**关系：

$$
\text{Rock} \text{ 克 } \text{Scissors},\quad
\text{Scissors} \text{ 克 } \text{Paper},\quad
\text{Paper} \text{ 克 } \text{Rock}
$$

判断一局的结果只需两步：

1. **平局检查**：若两人选择相同，直接输出 `Tie`。
2. **胜负检查**：否则查克制表。若 Player2 的选择恰是 Player1 选择克制的对象，则 Player1 胜；反之 Player2 胜。

这个关系是确定且唯一的，不需要枚举或分支比较，直接查表即可。

以样例为例：

| 局 | Player1 | Player2 | 判定 | 输出 |
|---|---|---|---|---|
| 1 | Rock | Scissors | Rock 克 Scissors | Player1 |
| 2 | Paper | Paper | 相同 | Tie |
| 3 | Rock | Paper | Paper 克 Rock | Player2 |

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(N)$，每局判断 $O(1)$。
- **空间复杂度**：$O(1)$，只使用常数级映射表和输入输出缓冲。

## 总结

石头剪子布本质是一个固定的循环克制关系。用字典 `WIN_OVER` 把“谁克谁”显式表达出来，配合平局检查即可在 $O(1)$ 时间内判定一局。整体 $O(N)$ 扫描输入、逐行输出即可。
