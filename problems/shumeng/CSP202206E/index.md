---
oj: "shumeng"
problem_id: "CSP202206E"
title: "PS 无限版"
description: "把平面操作统一为仿射变换，在线段树中维护区间的一次矩和二次矩并懒惰复合变换。"
difficulty: "提高+/省选-"
date: 2026-07-31 16:21
toc: true
tags: ["数据结构", "线段树", "仿射变换", "线性代数", "计算几何"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202206E
---

[[TOC]]

## 形式化题目

给定 $n$ 个平面点，支持对编号连续区间执行平移、旋转、放缩、关于直线对称、投影五种修改操作，并查询区间点集的重心，或到指定点 $(a,b)$ 的距离平方和。

坐标和操作参数都是实数，任意时刻点坐标绝对值不超过 $10^6$；$n\le 5\times 10^5$，操作数不超过 $2\times 10^4$，因此不能每次操作都逐点修改。

## 思路

先看逐点执行操作的朴素程序，它只在数据很小时可行，但能直观对应题目语义：

@include-code(./brute.cpp, cpp)

正解的关键是把五种几何操作统一成同一个数学形式，再用线段树批量维护。

### 统一表示平面操作

把点写成列向量 $p=(x,y)^T$。五种修改都可以写成仿射变换：

$$p' = Mp+v,$$

其中 $M$ 是 $2\times2$ 矩阵，$v$ 是平移向量。例如：

- 平移 $(a,b)$：$M=I$，$v=(a,b)^T$；
- 绕 $(a,b)$ 逆时针旋转 $\theta$：
  $M=\begin{bmatrix}\cos\theta&-\sin\theta\\\sin\theta&\cos\theta\end{bmatrix}$，$v=(a,b)^T-M(a,b)^T$；
- 绕 $(a,b)$ 放缩 $\lambda$：$M=\lambda I$，$v=(1-\lambda)(a,b)^T$。

令直线方向单位向量为 $u=(\cos\theta,\sin\theta)^T$，直线上点 $p_0=(0,y_0)^T$。投影的线性部分是 $uu^T$，对称的线性部分是 $2uu^T-I$，两者的平移部分都为 $p_0-Mp_0$。

若连续执行两个变换 $T_1(p)=M_1p+v_1$ 和 $T_2(p)=M_2p+v_2$，合成结果仍是仿射变换：

$$T_1(T_2(p))=(M_1M_2)p+(M_1v_2+v_1)。$$

因此线段树的懒标记只需保存一个仿射变换。

### 维护区间矩

对每个线段树节点维护一次矩与二次矩：

$$(N,S_x,S_y,S_{xx},S_{yy},S_{xy})
=\left(m,\sum x_i,\sum y_i,\sum x_i^2,\sum y_i^2,\sum x_iy_i\right)。$$

设一次仿射变换为 $x'=ax+by+u$、$y'=cx+dy+v$，那么整段覆盖时矩可以整体更新：

$$
\begin{aligned}
S_x'&=aS_x+bS_y+Nu,\\
S_y'&=cS_x+dS_y+Nv,\\
S_{xx}'&=a^2S_{xx}+b^2S_{yy}+2abS_{xy}+2u(aS_x+bS_y)+Nu^2,\\
S_{yy}'&=c^2S_{xx}+d^2S_{yy}+2cdS_{xy}+2v(cS_x+dS_y)+Nv^2,\\
S_{xy}'&=acS_{xx}+(ad+bc)S_{xy}+bdS_{yy}\\
&\quad+u(cS_x+dS_y)+v(aS_x+bS_y)+Nuv。
\end{aligned}
$$

这样整段覆盖时只更新节点统计量和懒标记，不需要访问区间内的每个点。

### 回答查询

- 重心：$\left(\dfrac{S_x}{N},\dfrac{S_y}{N}\right)$。
- 到 $(a,b)$ 的距离平方和：$S_{xx}+S_{yy}-2aS_x-2bS_y+N(a^2+b^2)$。

区间查询用线段树合并矩；下传懒标记前先把同一个仿射变换应用到左右儿子。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

建树时间为 $O(n)$。每次区间修改或查询访问 $O(\log n)$ 个线段树节点，每个节点的矩更新和合并都是 $O(1)$，总时间复杂度为 $O((n+q)\log n)$，空间复杂度为 $O(n)$。

## 总结

这道题的关键是把“对很多点做同一个几何操作”转成“对点集的低阶矩做一次更新”。仿射变换保证二阶矩仍能用有限个统计量表示，线段树负责组织区间覆盖与查询。使用 `long double` 可以减少大数二次矩在展开式中相减时的精度损失。