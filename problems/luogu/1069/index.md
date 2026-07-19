---
oj: "luogu"
problem_id: "P1069"
title: "[NOIP 2009 普及组] 细胞分裂"
description: "把目标试管数 M=m1^m2 分解成质因子需求，再看每种细胞的分裂因子 Si 每秒能提供多少对应指数，最早时间就是这些需求的最大上取整。"
difficulty: "普及+/提高"
date: 2026-06-20 12:13
toc: true
tags: ["数论", "质因数分解", "整除", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1069
---

[[TOC]]

### 题意

给出 `N` 种细胞。  
第 `i` 种细胞经过 `1` 秒，会从 `1` 个分裂成 `S_i` 个；经过 `t` 秒后，就会变成：

`S_i^t`

个同种细胞。

现在要求把培养皿中的细胞平均分入：

`M = m1^m2`

个试管中。  
也就是说，细胞总数必须被 `M` 整除。

问选择哪一种细胞培养，能让这个时刻最早到来；如果所有细胞都做不到，输出 `-1`。

### 思路

先看一个可以直接验证想法的小数据暴力：

@include-code(./brute.cpp, cpp)

`brute.cpp` 直接模拟：

- 当前细胞数对 `M` 的余数是多少
- 每过一秒就乘一个 `S_i`
- 如果余数第一次变成 `0`，就说明这时能整除 `M`

这个思路很贴近题意，但正式数据里 `M` 大到根本存不下，显然不能这样做。

#### 关键转化：整除只和质因子指数有关

把：

`M = m1^m2`

先做质因数分解。

假设：

`m1 = p1^a1 * p2^a2 * ...`

那么：

`M = p1^(a1*m2) * p2^(a2*m2) * ...`

也就是说，最终需要的只是每个质因子的指数够不够。

#### 一种细胞在 t 秒后能提供什么？

如果第 `i` 种细胞的分裂因子 `S_i` 中，某个质因子 `p` 的指数是 `c`，那么：

`S_i^t`

里这个质因子的指数就是：

`c * t`

所以只要满足：

`c * t >= need`

这个质因子的需求就够了。

因此对某个细胞来说，最早可行时间就是：

`max( ceil(need_j / cnt_j) )`

其中：

- `need_j` 表示 `M` 对第 `j` 个质因子的需求指数
- `cnt_j` 表示 `S_i` 中这个质因子的指数

如果某个必须的质因子在 `S_i` 里一次都没有出现，那这类细胞永远无解。

#### 最后怎么选？

对每一种细胞都算出：

- 它是否可行
- 如果可行，最早是多少秒

最后取最小值即可。

#### 特殊情况：M = 1

如果 `m1 = 1`，那么 `M = 1`。

初始时只有 `1` 个细胞，本来就能整除 `1`，所以答案直接是 `0`。

### Python 知识

- `factorize(base, exponent)` 在分解 `m1` 时直接把指数乘上 `m2`，无需构造巨大的 `M`。
- `for ... else` 表达“所有必须质因子都检查成功”：中途 `break` 的细胞不会进入 `else`。
- `(required+available-1)//available` 是整数上取整模板。
- 用 `None` 表示尚无可行细胞，避免设置超大哨兵。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：任意精度整数与哨兵状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：批量整数读取。

### 代码

@include-code(./main.py, python)


### 复杂度

- 时间复杂度：$O(\sqrt{m1} + N \cdot k \cdot \log S)$
- 空间复杂度：$O(k)$

其中 `k` 是 `m1` 的不同质因子个数，实际非常小。

### 总结

这题本质不是在模拟细胞个数，而是在比较“质因子指数增长速度”。

一旦把 `M` 和 `S_i` 都放到质因数分解的视角下，问题就会变成一个很直接的最大值计算。


### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
