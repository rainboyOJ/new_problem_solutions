---
oj: "roj"
problem_id: "1358"
title: "中缀表达式值(expr)"
description: "用记号类别状态机校验中缀表达式，再经调度场算法转后缀、用操作数栈求值；任一环节非法输出 NO。"
difficulty: "普及-"
date: 2026-09-30 06:50
updated: 2026-10-07 13:50
toc: true
tags: ["栈", "表达式求值", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1331"
    reason: "B 把 A 教的后缀表达式栈式归约（先弹右再弹左）当作流水线最后一段直接复用，代码里 eval_postfix 的 rhs,lhs=stack.pop(),stack.pop() 就是 A 的 eval 那一步，只是前面多叠了状态机校验和调度场转后缀；B 总结也自认「[[roj/1331]] 正是这条链路的后半段」。"
  - oj: "roj"
    problem_id: "1354"
    reason: "A 教的「中途弹空（右括号多余）与扫完栈非空（左括号多余）两类失败点即配对非法」正是 B 的 tokenize 合法性子过程用的那一步（代码 depth==0 拒右括号、结束后 depth 非 0 拒），B 只把它简化成单类型计数器再叠加记号类别状态机、调度场转后缀与操作数栈求值。"
  - oj: "luogu"
    problem_id: "P1739"
    reason: "B 的 tokenize 合法性子过程直接沿用 A 教的「单计数器记录未匹配左括号、过程中不得为负、末尾归零」这一配对判定（代码里的 depth：expect_operand 位置遇 ) 而 depth==0 判 NO，扫描结束 depth 非 0 判 NO），只在此之上叠加记号类别状态机、调度场转后缀与操作数栈求值。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1358
---

[[TOC]]

## 题目描述

输入一个以 `@` 结束的中缀表达式（运算数为 `0-9` 组成的整数，可带一元负号 `-`；运算符有 `+ - * /`；含小括号），判断它是否合法：不合法输出 `NO`，合法则转成后缀形式并用栈求出结果（整数除法向零取整）。

输入格式：一行以 `@` 结束的字符串。输出格式：合法时输出一行整数，否则输出一行 `NO`。样例输入 `1+2*8-9@`，样例输出 `8`。

## 思路

用「当前位置该出现运算数还是运算符」一个状态校验合法性：运算数位只接受数字、`(` 和一元负号（`-4`、`2*-3` 合法），运算符位只接受二元运算符和 `)`，配合 `depth` 判括号配对，非法即输出 `NO`。合法时用调度场算法把中缀记号按优先级转成后缀，再用一个操作数栈从左到右归约求值，三步各扫描一遍，复杂度 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
