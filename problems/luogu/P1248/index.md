---
oj: "luogu"
problem_id: "P1248"
title: "加工生产调度"
description: "按 a≤b 与 a>b 把作业分成前后两段、分别按 a 升序与 b 降序排序（Johnson 规则） + 顺序模拟两台机器更新完成时刻求最短总时间"
difficulty: "提高"
date: 2026-11-09 20:50
updated: 2026-11-09 20:53
toc: true
tags: ["贪心", "排序", "模拟", "流水作业调度"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
rbookLinks: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1248
---

[[TOC]]

## 形式化题目

有 $n$ 个作业，第 $i$ 个作业是有序对 $(a_i, b_i)$，表示它先在机器 A 上加工 $a_i$ 时间，再在机器 B 上加工 $b_i$ 时间，两道工序的先后顺序不能调换。两台机器都是单台串行设备：同一时刻每台机器只能加工一个作业，作业一旦上机不会被中途打断。

要选定 $1 \sim n$ 的一个排列作为加工顺序。把作业按该顺序依次送进两台机器，每个作业在 A 上加工完才进入 B，A、B 各自按顺序加工。从第一个作业上机开始，到最后一个作业在 B 上加工完毕为止，这段时间是总加工时间。求一种使总加工时间最短的排列，并输出最短时间。原题把作业称为“产品”，把两台机器称为“A、B 车间”，下文沿用作“产品、车间”叫法时含义相同。

## 正解

!!! info 用交换论证把相邻两作业的先后转成 min 判据，进而得到 Johnson 分组排序规则。
固定一个加工顺序后，总时间可以一遍递推算出：A 上累加 $a_i$，B 上取“B 已空闲”与“A 已加工完”的较大者再加 $b_i$。调整顺序只是重排同一批作业，关键只需决定任意两个相邻作业谁先谁后。把两种先后下的 B 完成时刻相减化简，得到一条充分判据：只要 $\min(a_i,b_j)\leqslant\min(a_j,b_i)$，把 $i$ 放前面就不会更差。把这条判据套用到全局，得到：$a_i\leqslant b_i$ 的作业排在前面且按 $a_i$ 升序，$a_i>b_i$ 的作业排在后面且按 $b_i$ 降序。排序后顺序模拟一遍即为答案，复杂度 $O(n\log n)$。
!!!

### 思路

先看给定一个顺序后怎么算总时间。设 `finish_a` 是机器 A 加工完当前作业的时刻，`finish_b` 是机器 B 加工完当前作业的时刻。对顺序中的每个作业：

- `finish_a += a_i`：A 上连续加工，收到当前作业就紧接着上一个加工完的时刻开始，所以 A 的完成时刻直接累加 $a_i$。
- `finish_b = max(finish_b, finish_a) + b_i`：当前作业进入 B 时有两个约束，B 必须已经把前一个作业加工完（空闲时刻 `finish_b`），且这个作业在 A 上已经加工完（`finish_a`）。两者取较大者才是 B 能开始加工它的时刻，再加 $b_i$ 得到 B 对它加工完的时刻。

走完整个顺序后，`finish_b` 就是总加工时间。这一步只是把题目给的流水线过程原样模拟，$O(n)$。

难点在于顺序。$n$ 最多 $1000$，枚举 $n!$ 种排列再逐个模拟是不可能的。注意到换顺序并不改变“哪些作业、各自的 $a_i$ 和 $b_i$”，只是重排，所以真正要决定的是两个作业谁先谁后。于是问题的核心变成一条局部判据：

> 对任意两个相邻的作业 $i, j$，什么时候把 $i$ 排在 $j$ 前面不会更差？

设在这两个作业之前，A 能在时刻 $P$ 开始加工、B 能在时刻 $T$ 开始加工。先 $i$ 后 $j$ 时，B 加工完 $j$ 的时刻是三步递推展开的结果：

$$
C(i,j)=\max\bigl(T+b_i,\; P+a_i+b_i,\; P+a_i+a_j\bigr)+b_j .
$$

把 $i$、$j$ 交换成先 $j$ 后 $i$，同理：

$$
C(j,i)=\max\bigl(T+b_j,\; P+a_j+b_j,\; P+a_i+a_j\bigr)+b_i .
$$

这两式里 $P+a_i+a_j$ 是两项共有的部分（两种顺序 A 上都是先做完这两个作业，完成时刻相同）。把两式相减、按 $\min(a_i,b_j)$ 与 $\min(a_j,b_i)$ 的大小分情形化简，得到经典的 Johnson 交换引理：

$$
\min(a_i,b_j)\leqslant\min(a_j,b_i)\ \Longrightarrow\ C(i,j)\leqslant C(j,i).
$$

这条判据是单向的，它给出的是“把 $i$ 排前面不劣”的一个充分条件，这正是排序需要的东西。反过来不必成立：当两个最小值相等时，两式化简后完全相同，两种顺序的总时间一样，可以任意排；而当 $\min(a_i,b_j)<\min(a_j,b_i)$ 时，交换也确实不会让总时间变差，只是未必严格变小（两种顺序可能恰好算出同一个值）。所以下文统一按“不劣”来用，不要求严格变优。

这条引理不是凭上面的“分情形化简”一句话就能信的。把两个完成时刻各拆成三个候选里取最大：

- 先 $i$ 后 $j$：三个候选是 $T+b_i+b_j$（B 等前一个作业）、$P+a_i+b_i+b_j$（B 等 $i$ 在 A 上做完）、$P+a_i+a_j+b_j$（B 等 $j$ 在 A 上做完）；
- 先 $j$ 后 $i$：对应三个是 $T+b_i+b_j$、$P+a_j+b_i+b_j$、$P+a_i+a_j+b_i$。

两边第一个候选完全一样（都是 $T+b_i+b_j$），只需比后两个。注意到 $\min(a_i,b_j)\leqslant\min(a_j,b_i)$ 恰好等价于下面四种情形至少成立一种：

1. $a_i\leqslant a_j$ 且 $a_i\leqslant b_i$；
2. $a_i\leqslant a_j$ 且 $b_j\leqslant b_i$；
3. $b_j\leqslant a_j$ 且 $a_i\leqslant b_i$；
4. $b_j\leqslant a_j$ 且 $b_j\leqslant b_i$。

逐情形看，先 $i$ 后 $j$ 的两个候选总有一个先 $j$ 后 $i$ 的候选压在它上面：

- 情形 1：由 $a_i\leqslant a_j$ 得 $P+a_i+b_i+b_j\leqslant P+a_j+b_i+b_j$，由 $a_i\leqslant b_i$ 得 $P+a_i+a_j+b_j\leqslant P+a_j+b_i+b_j$，两个候选都不超过对方的第二项。
- 情形 2：由 $a_i\leqslant a_j$ 得 $P+a_i+b_i+b_j\leqslant P+a_j+b_i+b_j$，由 $b_j\leqslant b_i$ 得 $P+a_i+a_j+b_j\leqslant P+a_i+a_j+b_i$，两个候选分别不超过对方的后两项。
- 情形 3：由 $a_i\leqslant b_i$ 得 $P+a_i+a_j+b_j\leqslant P+a_j+b_i+b_j$，由 $b_j\leqslant a_j$ 得 $P+a_i+b_i+b_j\leqslant P+a_i+a_j+b_i$。
- 情形 4：由 $b_j\leqslant b_i$ 得 $P+a_i+a_j+b_j\leqslant P+a_i+a_j+b_i$，由 $b_j\leqslant a_j$ 得 $P+a_i+b_i+b_j\leqslant P+a_i+a_j+b_i$。

四种情形下，先 $i$ 后 $j$ 的两个候选各自都不超过先 $j$ 后 $i$ 的某个候选。取最大值时，后者至少能达到前者的上界，所以 $C(i,j)\leqslant C(j,i)$。这就是引理的证明。反过来，当条件不成立时四种情形全不成立，可能两种顺序算出同一个值（不劣但也不必更优），这正是后文只谈“不劣”、不谈“严格更优”的原因。

有了这条判据，就把它用到全局。单看判据只是两两比较，但它可以整理成一条不需要反复比较的排序规则。把作业分成两段：$a_i\leqslant b_i$ 的叫前段，$a_i>b_i$ 的叫后段。下面说明这套分组排序正好让每一对相邻作业都满足判据。

- **前段整体排在后段之前。** 取前段作业 $j$（$a_j\leqslant b_j$）与后段作业 $i$（$b_i<a_i$）。要说明 $j$ 排在 $i$ 前不劣，需 $\min(a_j,b_i)\leqslant\min(a_i,b_j)$。由 $j$ 在前段，$\min(a_j,b_i)\leqslant a_j\leqslant b_j$；由 $i$ 在后段，$\min(a_j,b_i)\leqslant b_i<a_i$。两条合起来看，$\min(a_j,b_i)$ 同时不超过 $b_j$ 和 $a_i$，也就小于等于 $\min(a_i,b_j)$。
- **前段内部按 $a$ 升序。** 取前段中 $a_i\leqslant a_j$ 的两个作业。因为前段 $a_j\leqslant b_j$，所以 $\min(a_i,b_j)=a_i$。又 $a_i\leqslant a_j$ 且 $a_i\leqslant b_i$，故 $a_i\leqslant\min(a_j,b_i)$。于是 $\min(a_i,b_j)\leqslant\min(a_j,b_i)$，$i$ 排前面。
- **后段内部按 $b$ 降序。** 取后段中 $b_i\geqslant b_j$ 的两个作业。因为后段 $a_i>b_i\geqslant b_j$ 且 $a_j>b_j$，所以 $\min(a_i,b_j)\leqslant b_j$，而 $\min(a_j,b_i)\geqslant b_j$（两个数 $a_j$、$b_i$ 都不小于 $b_j$）。于是 $\min(a_i,b_j)\leqslant\min(a_j,b_i)$，$i$ 排前面。

三步合起来：把前段按 $a$ 升序、后段按 $b$ 降序、前段整体放前面，得到的顺序中任意两项只要前者排在后者之前，就都满足判据（不只限于相邻两项）。于是从任何一个排列出发，用相邻交换把它冒泡成这个顺序，每次交换的那一对都是“后者本应在前”，满足判据，总时间只降不升。因此这个顺序达到最小总时间。

把它落成比较器：前段优先于后段；同类中前段按 $a_i$ 升序、后段按 $b_i$ 降序。排序后顺序模拟即得总时间和顺序。

以样例 $a=(3,5,8,7,10)$、$b=(6,2,1,4,9)$ 走一遍分组：

| 作业 | $a_i$ | $b_i$ | 段 | 段内依据 |
| --- | --- | --- | --- | --- |
| 1 | 3 | 6 | 前段 | $a\leqslant b$，按 $a$ 升序排第 1 |
| 5 | 10 | 9 | 后段 | $a>b$，$b=9$ 最大，排前 |
| 4 | 7 | 4 | 后段 | $b=4$，次之 |
| 2 | 5 | 2 | 后段 | $b=2$ |
| 3 | 8 | 1 | 后段 | $b=1$ 最小，排后 |

得到顺序 $1\ 5\ 4\ 2\ 3$，模拟得总时间 $34$，与样例一致。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序是 $O(n\log n)$，顺序模拟一遍是 $O(n)$，总时间 $O(n\log n)$，空间 $O(n)$。$n\leqslant 1000$ 时绰绰有余。

## 总结

双机流水作业调度只有两台机器、每台单串行，是本类问题中多项式可解的情形。先把“总时间”化成一遍可计算的递推，再用交换论证把“选最优排列”降成“相邻两作业谁先谁后”，得到 $\min(a_i,b_j)\leqslant\min(a_j,b_i)\Rightarrow C(i,j)\leqslant C(j,i)$ 这条充分判据，最后把判据整理成“前段 $a$ 升序、后段 $b$ 降序、前段在前”的分组排序规则。三台及以上机器的流水作业调度才会变成 NP-hard，胜负在于能不能抓住这条局部判据把它推广到全局。
