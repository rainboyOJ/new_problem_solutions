---
oj: "roj"
problem_id: "1806"
title: "计算器"
description: "三问合一：快速幂求 y^z mod P；扩展 BSGS 求 y^x≡z (mod P) 的最小非负解；扩展 Lucas 拆质数幂加 CRT 求 C(z,y) mod P。"
difficulty: "提高+/省选-"
date: 2026-10-08 04:23
updated: 2026-10-08 04:23
toc: true
tags:
  - 数学
  - 数论
  - 快速幂
  - BSGS
  - 扩展卢卡斯
  - 中国剩余定理
  - python
favorite: false
favorite_reason: ""
categories:
  - 数学
  - 数论
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1806
---

[[TOC]]

## 形式化题目

每次询问给出四个整数 $type, y, z, P$（$P \geqslant 1$），按 $type$ 回答：

$$
\begin{aligned}
type = 1:&\quad y^z \bmod P;\\[2pt]
type = 2:&\quad \text{满足 } y^x \equiv z \pmod P \text{ 的最小非负整数 } x
   \text{（不存在则输出 \texttt{Math Error}）};\\[2pt]
type = 3:&\quad \binom{z}{y} \bmod P \quad (\text{即题面 } C_z^y \text{，}z \text{ 中取 } y \text{ 的组合数}).
\end{aligned}
$$

约束：$y, z, P \leqslant 10^9$，询问总数 $N \leqslant 500$；$P$ **不保证**是质数，但若 $P$ 为合数，
把 $P$ 分解为 $\prod_i p_i^{a_i}$ 后保证每个质数幂 $p_i^{a_i} \leqslant 10^5$。时限 1 s，内存 256 MB。

三问都不含任何交互，可以各自独立求解，最后把答案按输入顺序输出。

## 解法总览

三问共用同一份程序，但用的是三套互不相干的技巧，瓶颈也各不相同，所以分开成三节：

| 询问 | 朴素瓶颈 | 正解技巧 | 单次复杂度 |
| --- | --- | --- | --- |
| $type=1$ | 乘 $z$ 次，$O(z)$，$z \leqslant 10^9$ | 二进制拆分（快速幂） | $O(\log z)$ |
| $type=2$ | 逐 $x$ 试到出现循环，$O(P)$ | 折半枚举（扩展 BSGS） | $O(\sqrt P)$ |
| $type=3$ | 阶乘数值爆炸；$P$ 非质数时逆元可能不存在 | 扩展 Lucas + CRT | $O\!\big(\sum_i p_i^{a_i} + \log P\big)$ |

## 问题一：$y^z \bmod P$

### 思路

把指数 $z$ 按二进制拆开。设 $z = \sum_k 2^k b_k$，则

$$y^z = \prod_{k:\, b_k = 1} y^{2^k}.$$

而 $y^{2^{k+1}} = \big(y^{2^k}\big)^2$，所以只要不断把底数自乘，就能在 $O(\log z)$ 内
凑出全部需要的次幂。实现上就是标准的平方取幂：从低位往高位扫 $z$，当前位为 1 时把底数
乘进答案，每一位都把底数平方。

边界要注意 $z = 0$ 时答案为 $1 \bmod P$（包括 $P = 1$ 时输出 $0$），以及所有乘法都在
$10^{18}$ 量级，必须全程 64 位整数。

### 复杂度

单次 $O(\log z)$ 时间、$O(1)$ 空间。

## 问题二：$y^x \equiv z \pmod P$ 的最小非负解

### 思路

**先处理 $y$ 与 $P$ 不互质的情形。** 此时 $y$ 关于 $P$ 没有逆元，直接套 BSGS 会在"乘逆元"
这一步崩掉。记 $d = \gcd(y, P)$：当 $x \geqslant 1$ 时 $d \mid y^x$，所以必须有 $d \mid z$，
否则无解；若 $d \mid z$，把同余式两边和模数同时除以 $d$，并记下"已经提出来的系数"

$$k \leftarrow k \cdot \frac{y}{d}, \qquad P \leftarrow \frac{P}{d}, \qquad z \leftarrow \frac{z}{d}, \qquad cnt \leftarrow cnt + 1,$$

其中 $k$ 按新的（更小的）模数取模。反复做直到 $\gcd(y, P) = 1$，此时原方程等价于

$$k \cdot y^{\,x - cnt} \equiv z \pmod P .$$

每轮消因子后立刻检查 $k \equiv z \pmod P$ 是否成立：若成立说明 $x = cnt$ 已经是解，
而且它是当前能找到的最小候选，可以直接返回。$k$ 的初值是 $1$，所以 $x = 0$ 的情形
（即 $z \equiv 1$）必须在最开始单独判掉，否则消因子会改写 $z$ 和 $P$ 而错过它。

**再处理 $\gcd(y, P) = 1$ 的情形，用 BSGS。** 取 $m = \lceil \sqrt P \rceil$，把未知指数写成
$x - cnt = i \cdot m - j$（$0 \leqslant j \leqslant m$，$1 \leqslant i \leqslant m$），则方程变成

$$k \cdot (y^m)^i \equiv z \cdot y^{\,j} \pmod P .$$

右边只依赖 $j$，只有 $m + 1$ 种取值，所以先把所有 $z \cdot y^j \bmod P$ 存进一张哈希表
（记为"小步"）；左边只依赖 $i$，枚举 $i$ 并查表即可。两侧各 $O(\sqrt P)$ 次乘法，
把 $O(P)$ 的枚举压到 $O(\sqrt P)$。

**哈希表里同值必须保留最大的 $j$。** $y$ 的阶可能小于 $m$，于是同一个值会被多个 $j$ 命中。
由 $x = i m - j + cnt$ 可知，同值时 $j$ 越大 $x$ 越小，所以插入时直接覆盖成更大的 $j$
（小步按 $j$ 升序插入，后写覆盖先写，天然保留最大 $j$）。这是本题最容易写错的一处：
若保留最小的 $j$，答案会偏大甚至超过阶而判成无解。

$P = 1$ 时所有同余式恒成立，最小解是 $x = 0$，需要在一开始就返回。

### 复杂度

消因子至多 $O(\log P)$ 轮，每轮 $O(\log P)$；BSGS 建表与枚举各 $O(\sqrt P)$。
单次时间 $O(\sqrt P)$，空间 $O(\sqrt P)$（不超过约 $3.2 \times 10^4$ 个键值对）。

## 问题三：$\binom{z}{y} \bmod P$

### 思路

$P$ 不保证是质数，所以既不能直接用阶乘除阶乘（数值太大），也不能直接对分母求逆元
（分母可能与 $P$ 不互质）。两层拆解：

**第一层：把 $P$ 拆成质数幂再用 CRT 合并。** 设 $P = \prod_i p_i^{a_i}$，各 $p_i^{a_i}$
两两互质。分别求出 $\binom{z}{y} \bmod p_i^{a_i}$ 后，用中国剩余定理合并：

$$x \leftarrow x + M \cdot \Big( (r_i - x) \bmod p_i^{a_i} \Big) \cdot \big(M^{-1} \bmod p_i^{a_i}\big), \qquad M \leftarrow M \cdot p_i^{a_i},$$

其中 $M$ 是已合并部分的模数（始终与下一个 $p_i^{a_i}$ 互质，逆元存在）。

**第二层：对单个质数幂 $p^a$ 求 $\binom{z}{y}$，即扩展 Lucas。** 关键是把阶乘里所有 $p$
因子单独剥离出来。定义 $f(n)$ 为 $n!$ 去掉全部质因子 $p$ 之后模 $p^a$ 的值。在模 $p^a$
意义下，与 $p$ 互质的数之乘积以 $p^a$ 为周期，于是

$$f(n) = \Big(\prod_{1 \leqslant i \leqslant p^a,\, p \nmid i} i\Big)^{\lfloor n/p^a \rfloor}
        \cdot \prod_{1 \leqslant i \leqslant n \bmod p^a,\, p \nmid i} i
        \cdot f(\lfloor n/p \rfloor) \pmod{p^a},$$

最后一项来自把所有 $p$ 的倍数各提出一个 $p$ 之后剩下的 $(\lfloor n/p \rfloor)!$。
用长度为 $p^a + 1$ 的前缀积表把两个乘积段落压成 $O(1)$（题面保证 $p^a \leqslant 10^5$，
表很短）。$n!$ 中 $p$ 的个数用 Legendre 公式算：

$$v_p(n!) = \sum_{k \geqslant 1} \Big\lfloor \frac{n}{p^k} \Big\rfloor .$$

令 $e = v_p(z!) - v_p(y!) - v_p((z-y)!)$，它就是组合数中因子 $p$ 的净次数。于是

$$\binom{z}{y} \equiv p^{e} \cdot f(z) \cdot f(y)^{-1} \cdot f(z-y)^{-1} \pmod{p^a} .$$

此时 $f(\cdot)$ 都与 $p$ 互质，逆元用扩展欧几里得求，一定存在。
若 $e \geqslant a$ 则 $p^e \equiv 0 \pmod{p^a}$，组合数直接是 $0$，不必再算逆元。

边界：$P = 1$ 输出 $0$；$y > z$ 输出 $0$；$y = 0$ 或 $y = z$ 输出 $1 \bmod P$。
$P$ 本身是质数（$P \leqslant 10^9$）时表开不下，改用 **Lucas 定理**逐位计算：
把 $z, y$ 写成 $P$ 进制，逐位求小组合数相乘，某一位上 $y_i > z_i$ 则整体为 $0$；
小组合数里 $a < P$，分母 $k!$ 与 $P$ 互质，用费马小定理求逆元即可。

### 复杂度

分解 $P$ 为 $O(\sqrt P)$；对每个质数幂，$f$ 的递归层数是 $O(\log_p z)$，
建表 $O(p^a)$；CRT 合并 $O(\omega(P) \log P)$，其中不同质因子数 $\omega(P) \leqslant 9$。
单次时间 $O\!\big(\sum_i p_i^{a_i} + \log P\big)$，空间 $O(\max_i p_i^{a_i})$。

## 完整程序

三问写在同一份程序里，按 $type$ 分派后顺序输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

Python 版与 C++ 版是同一套算法：快速幂直接用内置 `pow`（同样是平方取幂，$O(\log z)$）；
BSGS 的小步表用 `dict` 存"值 → 最大的 $j$"；扩展 Lucas 用 `@cache` 缓存单个周期内
与 $p$ 互质之数的乘积。算法阶数与 C++ 完全一致，没有为了速度降级成暴力。
实测在随仓 10 个数据点上 C++ 全部 $0.01 \sim 0.1$ s，Python 0.01 s（$type=1,2$ 点）
到 0.8 s（`problem10`，150 组混合顶格）。

### 复杂度

记 $\omega(P)$ 为 $P$ 的不同质因子个数，$\mathrm{pk}(P) = \max_i p_i^{a_i}$：

- 时间：$type=1$ 为 $O(\log z)$；$type=2$ 为 $O(\sqrt P)$；
  $type=3$ 为 $O(\sqrt P + \sum_i p_i^{a_i} \log_p z + \omega(P) \log P)$。
- 空间：$type=2$ 的哈希表 $O(\sqrt P)$（约 $3.2 \times 10^4$ 项），
  $type=3$ 的前缀积表 $O(\mathrm{pk}(P))$（$\leqslant 10^5$）。
- 整体远低于 1 s / 256 MB 的限制。

## 总结

三个子问题都靠"换一个坐标系"把规模降下来：快速幂换到二进制位，BSGS 换到
$i \cdot \sqrt P - j$ 的两侧分解，扩展 Lucas 换到"质数幂 + 剥离 $p$ 因子"的坐标系。
写实现时三处最容易错的边界是：

1. $type=2$ 中 $x = 0$ 必须在消因子之前判掉，且消因子每一轮都要检查 $k \equiv z$；
2. BSGS 的哈希表同值要保留**最大**的 $j$，否则最小解不成立；
3. $type=3$ 中 $e \geqslant a$（组合数被 $p^a$ 整除）要提前返回 $0$，不能去求不存在的逆元。

--- 

> **数据来源说明**：素材源目录 `new_ROJ/problems/1806/` 内含 `data.py` 数据生成脚本，
> 随仓 10 个测试点及其 `.out` 均由该脚本自造（`std.cpp` 跑出并做了正向校验），
> 题面亦属网络重建版本，出题意图可能与官方原题存在偏差。本人在实现时已把
> `main.cpp` / `main.py` 与随仓 `.out` 逐点比对（10/10 一致），并另用暴力程序对
> $type=2$（枚举最小 $x$）、$type=3$（Python 大整数 `comb` 取模）做了小规模对拍。
