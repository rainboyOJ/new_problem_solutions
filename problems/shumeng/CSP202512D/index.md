---
oj: "shumeng"
problem_id: "CSP202512D"
title: "C 形阵"
description: "将 C 形阵参数化为指数向量，利用乘法函数前缀和与 Min_25 筛统计所有方案及完美方案。"
difficulty: "未知"
date: 2026-07-31 16:22
toc: true
tags: ["数论", "Min_25 筛", "乘法函数", "质因数分解", "容斥"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202512D
---

[[TOC]]

## 形式化题目

七元组 $(A,B,C,D,E,F,G)$ 为正整数且满足

$$
\frac{A}{B}=\frac{B}{C},\qquad
\frac{E}{F}=\frac{F}{G},\qquad
A B C = C D E = E F G
$$

大小定义为 $B$，价值为 $D$。求所有大小不超过 $n$ 的 C 形阵价值之和（$op=0$），或其中满足 $|\{A,B,C,D,E,F,G\}|=6$ 的完美 C 形阵价值之和（$op=1$），对 $998244353$ 取模。

## 思路

### 参数化

由 $\frac{A}{B}=\frac{B}{C}$ 得 $AC=B^2$，由 $ABC=EFG$ 结合比例关系可得 $B=F$。固定 $B=b$ 后，选择 $C,E$ 即可确定全部七个数：

$$
A=\frac{b^2}{C},\quad G=\frac{b^2}{E},\quad D=\frac{b^3}{CE}
$$

对每个质因子 $p^e \parallel b$，令 $x=v_p(C)-e$、$y=v_p(E)-e$，则 $-e \le x,y \le e$ 且 $x+y \le e$，并且 $v_p(D)=e-x-y$。因此每个方案的价值 $D$ 是乘法函数，总答案是一个乘法函数前缀和。

### 完美条件的容斥

除 $B=F$ 外其余六个数两两不同，等价于指数向量 $(x_p),(y_p)$ 不满足六种关系：$X=0$、$Y=0$、$X=Y$、$X=-Y$、$Y=-2X$、$X=-2Y$。任意两个坏关系的交集都是 $X=Y=0$，由容斥得到完美答案：

$$
total - 2A - B - C - 2D + 5Z
$$

其中六项分别是总方案数及各类坏关系对应的乘法函数前缀和。

### Min_25 筛

对每个素数幂预计算局部函数值，用 Min_25 筛得到质数部分的基函数前缀，再递归枚举最小质因子统计 6 个乘法函数的前缀和。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设 $N=n$，Min_25 预处理为 $O(\sqrt N)$ 级别，递归按整除分块状态进行，空间复杂度为状态数级别，可支持 $n \le 10^7$。

## 总结

先把数阵条件化成质因子指数上的局部选择，使答案成为乘法函数前缀和；完美条件用六种线性关系的容斥处理，避免逐方案判重。Min_25 筛负责在超大上界下高效计算质数部分贡献。