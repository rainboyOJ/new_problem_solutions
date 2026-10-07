---
oj: "roj"
problem_id: "1804"
title: "最大真因数"
description: "合数 n 的最大真因数是 n 除以它的最小质因子，于是求区间内合数按最小质因子分组后的商之和，用 min_25 筛在 O(n^{3/4}/log n) 内算出前缀和再作差。"
difficulty: "提高+/省选-"
date: 2026-10-08 04:13
updated: 2026-10-08 04:13
toc: true
tags:
  - 数学
  - 数论
  - 筛法
  - Min_25 筛
  - python
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1804
---

[[TOC]]

## 形式化题目

给定正整数 $l \le r$，对 $[l, r]$ 中的每个合数取其最大真因数（不超过自身的最大因数），
求这些最大真因数之和。记 $\operatorname{spf}(n)$ 为 $n$ 的最小质因子，答案为

$$
S(l, r) \;=\; \sum_{\substack{l \le n \le r \\ n \text{ 为合数}}} \frac{n}{\operatorname{spf}(n)} .
$$

数据范围：$1 \le l \le r \le 5 \times 10^9$。

## 正解

### 思路

**先化简单个合数。** 若 $n$ 是合数，把它的因数从小到大排列。设 $p = \operatorname{spf}(n)$，
则 $n/p$ 一定是最小的真因数 $1$ 之外**最大**的那一个：
若还有真因数 $d > n/p$，那么 $n/d < p$ 也是 $n$ 的因数，与 $p$ 是最小质因子矛盾。
所以每个合数 $n$ 的贡献只有 $\dfrac{n}{p}$ 这一项，"最大真因数"这个说法本身可以直接删掉。

**朴素做法与瓶颈。** 最直接的是线性筛（欧拉筛）预处理出 $1 \sim r$ 每个数的最小质因子，
一边筛一边把合数的 $n/p$ 累加进前缀和，最后输出两个前缀之差，$O(r)$ 时间、$O(r)$ 空间。
$r \le 10^7$ 时它轻松通过前 6 个测试点；但第 8、10 个测试点 $r \le 5 \times 10^9$，
数组要开 $5 \times 10^9$ 个元素（十几 GB），时间也远超 2 s。
注意第 8 个测试点是 $l = 1,\ r = 5 \times 10^9$ 的整个前缀区间，
"只筛 $[l, r]$" 的区间筛在这里没有任何可省的余地。
瓶颈很清楚：**我们被迫显式枚举了每一个数，而真正需要枚举的东西少得多。**

**关键观察：最小质因子的种类极少。** 合数 $n \le N$ 必有 $\operatorname{spf}(n) \le \sqrt{n} \le \sqrt{N}$。
当 $N = 5 \times 10^9$ 时 $\sqrt{N} \approx 70710$，这段范围内的质数只有 **7004 个**。
换句话说，全部合数只能按 7004 种最小质因子分类。

于是把合数**按最小质因子分组**来数：对固定的质数 $p$，最小质因子恰为 $p$ 的合数都能唯一写成

$$
n = p \cdot m, \qquad p \le m \le \left\lfloor \frac{N}{p} \right\rfloor, \qquad \operatorname{spf}(m) \ge p ,
$$

（$m \ge p$ 保证 $n$ 是合数，$\operatorname{spf}(m) \ge p$ 保证 $p$ 真的是 $n$ 的最小质因子。）
这一组合数的贡献之和就是商 $m$ 的和，即

$$
\sum_{p \le \sqrt{N}} \;\; \sum_{\substack{p \le m \le \lfloor N/p \rfloor \\ \operatorname{spf}(m) \ge p}} m .
$$

到这里问题变成：**对每个 $p \le \sqrt{N}$，求 $1 \sim \lfloor N/p \rfloor$ 中剔除所有小于 $p$ 的质数的倍数之后剩余元素的和。**
这正是埃氏筛的作用，只是我们关心的不是"剩了哪些数"，而是"剩下的数之和"。

**用埃氏筛 DP 把"剩下的和"滚出来。** 令 $g_j(w)$ 表示 $2 \sim w$ 中**质数或最小质因子 $> p_{j-1}$** 的数之和，
即筛掉前 $j-1$ 个质数的倍数后剩下的数值和（$p_i$ 表示第 $i$ 个质数）。初始时一个质数都没筛，
$2 \sim w$ 全体保留：

$$
g_1(w) = 2 + 3 + \cdots + w = \frac{w(w+1)}{2} - 1 .
$$

（减去 $1$ 是把 $1$ 摘出去；$1$ 既不是质数也不是合数，从头到尾都不参与统计，
所以 $g$ 里始终只有 $\ge 2$ 的数，取答案时不必再处理 $m = 1$ 的边界。）
从 $p_{j-1}$ 跨到 $p_j$ 时，被新划去的数是 $p_j m$（$m \ge p_j$ 且 $\operatorname{spf}(m) \ge p_j$），其和恰为
$p_j \big( g_j(\lfloor w/p_j \rfloor) - sp_{j-1} \big)$，其中 $sp_{j-1} = p_1 + \cdots + p_{j-1}$
是要从 $g_j(\lfloor w/p_j \rfloor)$ 里扣掉的**小于 $p_j$ 的质数**：筛掉前 $j-1$ 个质数的倍数之后，
这些质数仍然留在 $g_j$ 里，但它们作为 $m$ 只会给出 $n = p_j m$，
其最小质因子其实是那个更小的 $q$，不属于第 $j$ 组，所以要减掉。
因此

$$
g_{j+1}(w) = g_j(w) - p_j \Big( g_j\!\left(\left\lfloor \frac{w}{p_j} \right\rfloor\right) - sp_{j-1} \Big) .
$$

只有 $w \ge p_j^2$ 时才需要转移：$w < p_j^2$ 意味着 $\lfloor w/p_j \rfloor < p_j$，这一段里已经不存在以 $p_j$ 为最小质因子的数了。

**答案怎么取。** 把上面的求和式代进去：对每个 $p_j \le \sqrt{N}$，
第 $j$ 组合数（最小质因子恰为 $p_j$）的贡献就是
$g_j(\lfloor N/p_j \rfloor) - sp_{j-1}$——仍然留在 $g$ 里的那些数恰好是「质数或 $\operatorname{spf} \ge p_j$」，
扣掉小于 $p_j$ 的质数之后剩下的正是合法的商 $m$（$m \ge p_j$ 自动成立，因为 $2 \le m < p_j$ 的数要么有
$\operatorname{spf} < p_j$ 已被筛走，要么本身就是被扣掉的质数）。合并即有

$$
F(N) \;=\; \sum_{p_j \le \sqrt{N}} \left( g_j\!\left(\left\lfloor \frac{N}{p_j} \right\rfloor\right) - sp_{j-1} \right),
\qquad S(l, r) = F(r) - F(l-1) .
$$

这也是实现里直接 `ans += d`（$d = g - sp_{j-1}$）的原因：$g$ 已经摘掉了 $1$，不必再减一次。

**状态只有 $2\sqrt{N}$ 个。** 需要转移的状态永远是 $w = \lfloor N/i \rfloor$ 这种形状，
取值不超过 $2\sqrt{N} \approx 141421$ 个。把 $w > \sqrt{N}$ 的状态按 $i$ 编号放进 `g1[i]`
（此时 $w = \lfloor N/i \rfloor$，$i \le N/(\sqrt{N}+1)$ 恰好覆盖所有这种状态），
$w \le \sqrt{N}$ 的状态直接拿 $w$ 当下标放进 `g2[w]`；
查询 $g_j(\lfloor w/p \rfloor)$ 时看 $\lfloor w/p \rfloor$ 落在哪一半即可，无需哈希表。

**为什么是 $O(N^{3/4}/\log N)$。** 转移次数等于满足 $p_j^2 \le w$ 的 (质数, 状态) 对的数量，
按 min_25 筛的标准分析为 $O(N^{3/4}/\log N)$，$N = 5 \times 10^9$ 时约几百万次，
实测不到 30 ms，离 2 s 的时限很远。空间只要 $O(\sqrt{N})$，约 3 MB。

**实现要点。** 三条容易踩的坑：

1. **必须用高精度整数。** $g_1$ 的初值是 $\frac{w(w+1)}{2} - 1$，先算 $w(w+1)$ 的话
   $w = 5 \times 10^9$ 时约 $2.5 \times 10^{19}$，直接超出 64 位；即使按 $w(w+1)/2 - 1$ 先除后减，
   结果 $1.25 \times 10^{19}$ 也已接近 `unsigned long long` 上限、且远超市面上 `long long` 的
   $9.2 \times 10^{18}$。所以本题的 `main.cpp` 里 `g1`、`g2`、`ans`、`sp` 全用 `__int128`，
   最后手写 128 位输出。答案本身最大只有 $4.1 \times 10^{18}$（即样例 5 风格的点），
   落在 `long long` 内，但**中间量不落在**，所以不能省。
2. **`g2` 必须倒序更新。** 转移要读 $g_j(\lfloor w/p \rfloor)$，而 $\lfloor w/p \rfloor < w$。
   `g2` 按下标递增访问，所以从大到小扫，读到的才是上一阶段的旧值；
   `g1` 是**递减**的 $w$，从小 $i$ 往大 $i$ 扫，$\lfloor w/p \rfloor$ 对应的 $g1$ 下标更大、还没被更新，天然安全。
3. **$N < 4$ 直接返回 0。** 此时区间里没有合数；$l = 1$ 时 $l - 1 = 0$ 也要能吃下。

> 说明：本题在仓库素材源（`new_ROJ/problems/1804/`）里带有自造数据生成脚本 `data.py`
> 与 `config.json`，`data/` 是据此生成的 10 个点，题面文本与"信息学奥赛一本通·高手训练篇"
> 同源（该题即 FJWC2018 / BZOJ 5244《最大真因数》）。因此数据规模与官方原题可能不完全一致，
> 题解以本仓库 `data/` 为准。素材里的 `std.cpp` 与本文结论一致（同样按最小质因子分组做 min_25 筛），
> 但它用 `__int128` 存全部状态且在 $i=1$ 处累加贡献，本文的 `main.cpp` 是独立实现。

### 代码

Python 短解法：

@include-code(./main.py, python)

C++ 正式解：

@include-code(./main.cpp, cpp)

### 复杂度

- 时间：$O\!\left(\dfrac{N^{3/4}}{\log N}\right)$，其中 $N = r$；常数部分是 $2\sqrt{N}$ 个状态上的
  埃氏筛转移。$N = 5 \times 10^9$ 时实际转移数百万次，C++ 实测 < 30 ms，
  Python 实测约 1.2 s（本题允许 Python 慢，算法与 C++ 同阶，未做任何降级）。
- 空间：$O(\sqrt{N})$。$N = 5\times10^9$ 时状态数 $2\sqrt{N} \approx 1.4 \times 10^5$，
  质数表 7004 个，共计几 MB，远低于 512 MB。

## 总结

- **先把"最大真因数"翻译成 $n / \operatorname{spf}(n)$**，题目里"真因数""最大"这些字眼就没有了，
  剩下的只是一个关于最小质因子的求和。
- **计数对象从"数"换成"最小质因子"**：合数只有 $\sqrt{N}$ 以内的质数那么多种最小质因子，
  这一步是全部优化的来源。凡是 $N$ 很大而"每个数的某个局部特征只取少数几种值"的题，
  都值得先做这个转换。
- **埃氏筛的 DP 视角**：$g_{j+1}(w) = g_j(w) - p_j\big(g_j(\lfloor w/p_j \rfloor) - sp_{j-1}\big)$
  把"二次筛"变成了"筛掉的部分用上一阶段的值直接算"，这就是 min_25 筛的核心，
  也是它能把状态压缩到 $2\sqrt{N}$ 个的原因。
- **溢出比超时更容易翻车**：$w = 5 \times 10^9$ 时 $w(w+1)/2$ 已在 64 位边界，
  只需 $g$ 数组用 128 位、最终答案用 64 位输出即可，不必全盘 128 位。
