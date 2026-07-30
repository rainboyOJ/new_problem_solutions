---
oj: "noi_openjudge"
problem_id: "ch0304-2729"
title: "Blah数集"
description: "题意与原解析均从本地 OpenJudge 缓存迁移。"
difficulty: "未知"
date: 2026-07-30 23:01
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0304/2729/
---

<!-- generated from noiopenjudge local cache -->

[[TOC]]

### 题意

完整题面见同目录的 `problem.md`。

### 思路

#### 解析

经过普通队列输出数据后,发现普通队列不正正确



发现由$4$生成的$9$比较$3$生成的$10$要大,根据做题目的经验,这个题目肯定有数学规律,
进一步输出数据,找规律.

根据数据范围,知道,最终的代码一定是$O(n)$的,$O(nlogn)$都不行,所以不能使用优先队列,这暗示我们,产生的数据可以按某种方式有序,不需要进行比较.

1. 每一次产生的两个数$a < b$ 一定成立
2. 每一次都应该由最小的数首开两个新的数$a,b$

每一次产生的两新的数,和原来的已经产生的数,有什么关系,


使用数学归纳法证明



设$x \geqslant a,y \geqslant b$,且取$t = min(a,b)$,且$t \leqslant z$,$z$ 是生成$x,y$的元素


$$
x = 2 \times z +1 \\
y = 3 \times z +1 \\
$$

现在取$t$,得到$A = 2 \times t + 1, B = 3\times t +1$,显然

$$
A  \leqslant x \Rightarrow 2\times t + 1 \leqslant 2\times z +1 \\
B  \leqslant y \Rightarrow 3\times t + 1 \leqslant 3\times z +1
$$

显然成立

这就说明如果原来的双队列成立(单个队列都是单调的),则从取双队列头的最小值,产生新的值,然后把值各自加入到队列尾部,
得到的新的双队列也成立.




#### 错误的代码


使用优先队列,超时.

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
