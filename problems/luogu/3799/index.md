---
oj: "luogu"
problem_id: "P3799"
title: "小 Y 拼木棒"
description: "统计各长度频率，按边长枚举两根整边和一对短棒；Python 用对齐切片降低双重枚举的循环常数。"
difficulty: "普及-"
date: 2026-07-15 21:50
toc: true
tags: ["组合计数", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3799
---

[[TOC]]

### 题意

从 $n$ 根带编号的木棒中选择 4 根，把它们拼成一个正三角形，求选法数量对 $10^9+7$ 取模的结果。

即使两根木棒长度相同，只要编号不同，它们仍是不同的选择。数据范围为 $n\leqslant 10^5$，木棒长度不超过 5000。

### 思路

#### 四根木棒必须是什么结构

正三角形有三条等长边，而题目要求恰好选择四根木棒。因此三条边中必然有一条由两根木棒拼成，另外两条边各由一根木棒组成。

将选出的四根木棒长度排序为：

$$
a\leqslant b\leqslant c\leqslant d.
$$

它们能够拼成正三角形，当且仅当：

$$
a+b=c=d.
$$

这里 $c,d$ 是两条完整的边，$a,b$ 拼成第三条边。

#### 朴素枚举

最直接的方法是枚举任意四根木棒，排序后检查 $a+b=c=d$：

@include-code(./brute.py, python)

这个程序与题意完全一致，适合作为随机对拍的可信基线，但时间复杂度为 $O(n^4)$，无法处理 $n=10^5$。

#### 把枚举对象从木棒变成长度

木棒数量很大，但长度只有 $1\sim 5000$。先建立频率表：

```text
count[x] = 长度为 x 的木棒数量
```

枚举正三角形边长 $s$。两条完整边需要选择两根长度为 $s$ 的木棒，选法数为：

$$
\binom{count[s]}{2}=\frac{count[s](count[s]-1)}{2}.
$$

第三条边需要一对满足 $x+y=s$ 的短棒。

- 当 $x<y$ 时，选法数为 $count[x]\times count[y]$。
- 当 $x=y=s/2$ 时，必须从同一长度中选两根不同木棒，选法数为 $\binom{count[s/2]}{2}$。

因此，令 `pair_choices(s)` 表示两根短棒拼出边长 $s$ 的选法数，则：

$$
pair\_choices(s)
=\sum_{1\leqslant x<s-x}count[x]\times count[s-x]
+[s\text{ 为偶数}]\binom{count[s/2]}{2}.
$$

最终答案为：

$$
\sum_{s=2}^{V}\binom{count[s]}{2}\times pair\_choices(s),
$$

其中 $V$ 是最大木棒长度。

例如枚举 $s=4$ 时，只需统计不同长度对 $(1,3)$，然后单独补上相同长度对 $(2,2)$；枚举 $s=5$ 时，只需统计 $(1,4)$ 和 $(2,3)$。始终限定 $x<y$，可以避免把同一对木棒按顺序计算两次。

#### 为什么不会选到同一根木棒

短棒长度 $x,y$ 都是正整数且 $x+y=s$，所以一定有 $x<s$、$y<s$。它们不可能与两根长度为 $s$ 的完整边木棒重合。

当 $x=y$ 时使用组合数而不是平方，保证选择的是两根不同编号的木棒。因此四个位置使用的木棒一定互不相同。

#### 原 Python 为什么容易只有部分分

原代码的组合计数公式是正确的，问题主要在运行常数。它用 Python 双重循环预处理所有 `left + right`，最坏情况下大约执行 625 万次解释器层的乘法、分支和列表访问；在紧时限下，这种写法容易超时。

新代码仍然是 $O(V^2)$，但不再维护完整的 `pair_sum`，而是只在当前边长确实有两根整边时计算短棒对。更重要的是，它把左右频率切片对齐，再使用：

```python
sum(map(mul, left_counts, right_counts))
```

完成逐项乘积求和。切片、`map` 和 `sum` 的主要遍历在 C 层执行，减少了 Python 最内层循环开销。本机最坏频率分布测试中，完整程序由约 `2.05s` 降到约 `0.32s`；具体时间会随解释器和评测机变化。

#### C++ 实现

C++ 可以直接写双重循环。对每个边长 `side`，枚举满足 `left * 2 < side` 的 `left`，令 `right = side - left`，累加：

```text
count[left] * count[right]
```

若 `side` 为偶数，再加入中点的组合数。两个组合数都可能接近 $5\times 10^9$，相乘前必须分别取模，避免 `long long` 溢出。

#### Python 切片如何对应 C++ 循环

Python 中令：

```python
middle = (side + 1) // 2
left_counts = count[1:middle]
right_counts = count[side - 1:side - middle:-1]
```

当 `side = 5` 时，两个切片分别对应长度 `[1, 2]` 和 `[4, 3]`，逐项相乘正好得到：

$$
count[1]count[4]+count[2]count[3].
$$

偶数边长的中点没有放进切片，继续单独使用组合数处理。这样既与 C++ 枚举完全等价，又避免在 Python 中手写最内层循环。

#### 正确性说明

任取一个合法方案，排序后必有 $a+b=c=d=s$。程序枚举到 $s$ 时，会在 $\binom{count[s]}{2}$ 中选到 $c,d$，并在 `pair_choices(s)` 中选到 $a,b$，因此不会漏计。

反过来，程序统计的每一项都包含两根长度为 $s$ 的完整边，以及两根总长度为 $s$ 的短棒，必然能拼成正三角形。不同长度的短棒只按 $x<y$ 统计一次，相同长度用组合数统计，所以不会重计。

### Python 知识

#### 固定值域使用列表频率表

长度上限明确为 5000，使用 `count = [0] * 5001` 比字典或 `Counter` 更直接，下标就是木棒长度，访问开销也更小。

#### `map` 可以并行消费多个序列

`map(mul, left_counts, right_counts)` 每次从两个切片各取一个数，调用一次 `operator.mul`。它返回迭代器，再由 `sum` 完成聚合，不需要创建乘积列表。

#### C++ 到 Python 对照

- C++ 的全局计数数组对应 Python 的整数列表。
- C++ 的 `for (left...)` 对应两个方向相反的对齐切片。
- C++ 使用 `long long` 并防止乘法溢出；Python 整数不会固定宽度溢出，但仍要按题意取模。
- 两种语言中的组合数都写成 `x * (x - 1) // 2` 对应的整数运算。

#### 模仿清单

1. 值域较小时，用列表建立频率表。
2. 无序二元组按 `x < y` 与 `x == y` 分类计数。
3. 两段序列逐项运算时，考虑 `map(现成二元函数, left, right)`。
4. 用小数据 `combinations` 暴力验证组合计数公式。

相关 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：频率统计容器的选择。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：`map` 的多序列映射和惰性迭代。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`：`operator.mul` 与组合枚举工具。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 竞赛代码中的性能常数意识。

### 代码

#### C++17 正解

@include-code(./main.cpp, cpp)

#### Python 正解

@include-code(./main.py, python)

### 复杂度

设最大木棒长度为 $V\leqslant 5000$。

- 统计频率需要 $O(n)$ 时间。
- 枚举所有边长和短棒对共需要 $O(V^2)$ 时间。
- C++ 和 Python 正解的总时间复杂度均为 $O(n+V^2)$，空间复杂度均为 $O(V)$。
- `brute.py` 的时间复杂度为 $O(n^4)$，只用于小数据验证。

Python 每轮创建的两个切片最多占用 $O(V)$ 临时空间，用完即可回收，因此峰值空间仍为 $O(V)$。

### 总结

本题的决定性观察是：四根木棒拼正三角形，排序后一定满足 $a+b=c=d$。利用长度值域只有 5000，把枚举四根木棒改成枚举边长和短棒长度对，就能将复杂度降到 $O(n+V^2)$。

C++ 直接使用双循环即可；Python 在算法正确的基础上还要控制解释器循环常数，通过对齐切片、`map(operator.mul, ...)` 和 `sum` 批量完成乘积求和，才能更稳妥地通过紧时限测试。
