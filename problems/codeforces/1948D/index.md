---
oj: "codeforces"
problem_id: "1948D"
title: "Tandem Repeats?"
description: "固定半长把两半逐位比较折成一条相容数组 + 连续 q 个 1 即命中 + 位置压成 bitmask，移位与运算一次算出整排并倍增判连续 1"
difficulty: "1700"
date: 2026-11-04 16:49
updated: 2026-11-08 16:24
toc: true
tags: ["字符串", "枚举", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: ["rbook1:continuous_segment_dp", "rbook1:lcp_dp"]
rbookLinks:
  - id: "rbook1:continuous_segment_dp"
    reason: "本题把两半逐位比较折成 0/1 匹配序列，再要求连续 d 个 1，正是这篇「连续段 DP」的核心套路"
  - id: "rbook1:lcp_dp"
    reason: "本题就是固定距离扫描 LCP 表对角线、统计连续匹配对的直接应用；文中有专门一节对照本题与 ABC141 E 的条件差异"
pre: []
common: []
recommend: []
source: "https://vjudge.net/problem/CodeForces-1948D#author=translator:1281309:zh"
---

[[TOC]]

## 形式化题目

给定长度为 $n$ 的字符串 $s$，字符取自小写字母与通配符 `?`，每个 `?` 可以独立替换成任意小写字母。求替换后 $s$ 中最长的**串联重复**子串长度，不存在时输出 0。

串联重复指长度 $2q$ 的字符串，前一半与后一半逐位相同。它只要求作为连续子串出现，不必覆盖整个串。把替换吸收进比较关系，记

$$
\operatorname{compat}(i, j) \iff s[i] = s[j] \ \lor\ s[i] = \texttt{?} \ \lor\ s[j] = \texttt{?},
$$

即两位在替换后可以相同。要求的是

$$
\max\Bigl\{\, 2q \ \Big|\ \exists\, st,\ \forall\, 0 \leqslant k < q:\ \operatorname{compat}(st+k,\ st+k+q) \,\Bigr\}.
$$

约束：$1 \leqslant t \leqslant 1000$，$1 \leqslant n \leqslant 5000$，所有测试串长度之和 $\leqslant 5000$，时间限制 2 秒。

## 暴力解法

!!! info 固定半长 $q$，把两半的逐位比较折成一条 0/1 数组，问题变成找长度 $q$ 的连续 1。
枚举 $q$、起点 $st$、内部第 $k$ 位是 $O(n^3)$。固定 $q$ 后，被比较的位置对全是 $(i,\ i+q)$ 这种固定间距，可以一次算完整条相容数组 $b_q[i] = \operatorname{compat}(i,\ i+q)$。于是「存在起点使两半全相容」等价于「$b_q$ 中存在长度 $q$ 的连续 1」，用 $f[i] = f[i-1]+1$ 或 $0$ 递推一遍即可判定。单个 $q$ 是 $O(n)$，总计 $O(n^2)$。
!!!

### 思路

先看 $O(n^3)$ 为什么不行：$q$ 与 $st$ 各有 $O(n)$ 种，每次还要比 $O(q)$ 位，满规模约 $10^{11}$ 次比较。

瓶颈在于「同一个位置对 $(i,\ i+q)$ 被不同的 $st$ 反复比较」。固定 $q$ 后把结果一次算出来，定义

$$
b_q[i] = \bigl[\, \operatorname{compat}(i,\ i+q) \,\bigr], \qquad 0 \leqslant i < n - q .
$$

这样「存在 $st$ 使 $b_q[st..st+q-1]$ 全为 1」就等价于要求的串联重复。再用 $f[i]$ 累计以 $i$ 结尾的连续 1 长度：$b_q[i]=1$ 时 $f[i]=f[i-1]+1$，否则 $f[i]=0$；某个 $f[i]$ 达到 $q$，就命中长度 $2q$。

以 $s = \texttt{zaabaabz}$、$q = 3$ 为例：

| $i$ | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| $s[i]$ | z | a | a | b | a |
| $s[i+3]$ | b | a | a | b | z |
| $b_3[i]$ | 0 | 1 | 1 | 1 | 0 |

$b_3[1..3]$ 全为 1，对应子串 $s[1..6] = \texttt{aabaab}$，长度 6。

有一处容易写错：$f$ 只和 $b_q$ 的前一位比较，不要再拿 $s[i]$ 与 $s[i-q]$ 比。$+q$ 的比较在 $b_q$ 里已经做完，重复比较会把下标关系搞乱。

### 代码

@include-code(./main.py, python)

C++ 是同一套写法，$O(n^2)$ 的简单循环本身就够快，不需要位运算：

@include-code(./main.cpp, cpp)

### 复杂度

$q$ 有 $O(n)$ 个取值，每个 $q$ 建两个长度 $O(n)$ 的数组各扫一遍，时间 $O(n^2)$，空间 $O(n)$。

### 瓶颈

阶数没问题，代价在**每次基本操作由 Python 解释器执行**：每个 $q$ 新建两个长度为 $n-q$ 的列表，一次列表推导（每步三次字符串比较加分支）加一次逐格写入的 `for` 循环，满规模约 $1.2 \times 10^7$ 次字节码调度，本地实测 2～3 秒，超出限制。同一份代码用 C++ 写只要几十毫秒，所以下面的优化只针对 Python。

## 正解

!!! info 把相容数组压进一个整数，让整条数组的构造和连续 1 判定都在 C 层一次完成。
对每个字符建位置 bitmask $M_c$，第 $i$ 位为 1 表示 $s[i]=c$，记 $Q$ 为 `?` 的掩码。一个 $q$ 只需 $|\Sigma|+2$ 次大整数运算就能算出整条 $b_q$：$b_q = (Q \mid Q \gg q) \mid \bigvee_c \bigl(M_c \mathrel{\&} (M_c \gg q)\bigr)$。连续 1 用倍增：每轮 $m \leftarrow m \mathrel{\&} (m \gg L)$，$L=1,2,4,\ldots$，把长度 $L$ 的连续 1 合并成 $2L$，约 $\log q$ 次移位即可判出长度 $q$。再让 $q$ 从 $\lfloor n/2 \rfloor$ 递减、命中即停。骨架与暴力版相同，只是内层换了执行者。
!!!

### 思路

**第一步：位置压成 bitmask。** 对每个字符 $c$ 建整数 $M_c$，第 $i$ 位为 1 当且仅当 $s[i]=c$。于是「某位等于某个字符」变成「某位为 1」，逐位比较变成移位与按位与。

**第二步：一次算出整条 $b_q$。** 相容有三种情况，各对应一段位运算：

$$
b_q \;=\; \bigl(Q \mid (Q \gg q)\bigr) \;\Big|\; \bigvee_{c \in \Sigma} \bigl(M_c \mathrel{\&} (M_c \gg q)\bigr).
$$

$Q \gg q$ 的第 $i$ 位为 1 表示 $s[i+q]=\texttt{?}$；$M_c \mathrel{\&} (M_c \gg q)$ 的第 $i$ 位为 1 表示 $s[i]=s[i+q]=c$。合起来正好是 $\operatorname{compat}(i,\ i+q)$：两边都是 `?`、或有一边是 `?`、或两边同字母。一个 $q$ 只需要 $|\Sigma|+2 \leqslant 29$ 次大整数运算，而不是 $n$ 次字符比较。

**第三步：倍增判连续 1。** 令 $m$ 为 $b_q$ 的 bitmask，反复执行 $m \leftarrow m \mathrel{\&} (m \gg L)$，$L=1,2,4,\ldots$。执行一轮后第 $i$ 位为 1 当且仅当原 $b_q[i-1..i]$ 全为 1；执行 $k$ 轮后当且仅当原 $b_q[i-2^k+1..i]$ 全为 1。把 $L$ 倍增到不超过 $q$ 的最大 2 的幂，还差 $r = q-L$ 位，再补一次 $m \mathrel{\&}= m \gg r$ 即可判定。

**第四步：$q$ 从大到小枚举。** 只关心最长的答案，所以从 $q = \lfloor n/2 \rfloor$ 递减，命中即停；当前 $2q$ 已不大于已知答案时直接跳出。

**判据为什么成立。** 条件是「$b_q[st..st+q-1]$ 全为 1」，目标是「$s[st..st+2q-1]$ 替换后成为串联重复」。

**充分性（条件成立 $\Rightarrow$ 目标成立）**：

- $b_q[st+k]=1$ 说明 $\operatorname{compat}(st+k,\ st+k+q)$，两位相等或至少一边是 `?`。
- 逐对替换：相等则不动；一边是 `?` 就换成另一边的字母；两边都是 `?` 就都换成同一个字母。
- 每一对占据两个互不重叠的位置，替换之间不会冲突。
- 替换后两半逐位相同，子串成为长度 $2q$ 的串联重复。

**必要性（目标成立 $\Rightarrow$ 条件成立）**：

- 目标成立意味着存在替换使 $s[st+k]=s[st+k+q]$ 对所有 $0 \leqslant k < q$ 成立。
- 替换只改动 `?`，所以替换前这两位要么本来就相等，要么至少有一个是 `?`。
- 这正是 $\operatorname{compat}(st+k,\ st+k+q)$，即 $b_q[st+k]=1$；$k$ 取遍 $0..q-1$ 即得条件。

两个方向合起来，判据与目标严格等价。倍增法只是把「逐位加 1」换成「按 2 的幂合并区间」，命中的 $q$ 集合与递推完全一致。

### 代码

@include-code(./main-optimize.py, python)

C++ 同一套位运算写法，用 `std::bitset` 代替 Python 的任意精度整数，移位与按位与都是 64 位并行：

@include-code(./main-optimize.cpp, cpp)

### 复杂度

时间 $O(n^2 \log n / w)$，$w$ 是单次位运算并行处理的位数：Python 大整数按 30 位一个 digit，$w=30$；C++ 的 `bitset` 按机器字并行，$w=64$。空间是每字符一个 bitmask，$O(n)$ 位。实际跑起来远好于上界：$q$ 递减、命中即停、$2q \leqslant ans$ 剪枝三条一起生效，随机数据很早就退出。满规模 $n=5000$ 实测 Python 约 0.03～0.07 秒（朴素版 2～3 秒），C++ 位运算版 1～10 毫秒（朴素版 6～34 毫秒）。

C++ 提交其实直接用朴素版就够，位运算版的收益主要在周期性强的数据和压住最坏情况。

## 总结

- 关键转化是固定半长 $q$，把「两半逐位比较」折成相容数组 $b_q$，原问题变成「$b_q$ 中是否存在长度 $q$ 的连续 1」，$O(n^3)$ 降到 $O(n^2)$。
- 递推只用 $b_q$ 的前一位，$+q$ 的比较已经在 $b_q$ 里完成，不要重复拿 $s[i]$ 与 $s[i-q]$ 比。
- 判据是充要条件：充分性靠「逐对替换互不冲突」，必要性靠「替换只影响 `?`」。
- 优化全在实现层，阶数不变：位置压成 bitmask 让整条 $b_q$ 一次算出，倍增法把连续 1 判定压到 $O(\log q)$ 次移位，再加 $q$ 递减与剪枝。
- 边界：$n < 2$ 时答案为 0；`main.py` 在这里会因 `max([])` 崩溃，其余实现都显式处理。
- 验证：官方样例四份实现均输出 `6 4 10 0`；Python 侧以独立 $O(n^3)$ 枚举为基准，随机数据比对无差异；C++ 两份只核对样例与手工用例，未做随机对拍，也未使用官方完整测试数据。
