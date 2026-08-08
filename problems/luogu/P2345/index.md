---
oj: "luogu"
problem_id: "P2345"
title: "[USACO04OPEN] MooFest G"
description: "按 v 排序消掉 max，每头牛只与前面牛配对，两个树状数组维护坐标数量与坐标和。"
difficulty: "普及+/提高"
date: 2026-08-05 14:35
toc: true
tags: ["树状数组", "排序", "前缀和"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2345
---

[[TOC]]

### 题意

$n$ 头奶牛，第 $i$ 头坐标 $x_i$（互不相同）、听力 $v_i$。每对奶牛 $(i,j)$ 交流音量 = $\max\{v_i, v_j\} \times |x_i - x_j|$。求所有点对音量之和。

数据范围：$n \leqslant 2 \times 10^4$，$v_i, x_i \leqslant 2 \times 10^4$。

### 思路

**一句话本质**：音量公式里的 $\max\{v_i, v_j\}$ 是障碍——按 $v$ 排序后，处理每头牛时它和"前面所有牛"的贡献中 $\max$ 就是它自己的 $v$，问题退化成"对每个 $x_i$，统计前面牛中左边/右边的数量与坐标和"，用两个树状数组 $O(\log n)$ 完成。

先看最直接的暴力：

@include-code(./brute.cpp, cpp)

暴力枚举所有 $\binom{n}{2}$ 个点对，$O(n^2)$，$n = 2 \times 10^4$ 时 $2 \times 10^8$ 次计算，不可行。

**$\max\{v_i, v_j\}$ 怎么消掉？**

如果让听力小的先被处理，那它和听力大的牛配对时，$\max$ 一定是大的一方。把牛按 $v$ **从小到大排序**，依次处理。处理到第 $i$ 头牛时，它和前面 $i-1$ 头牛的贡献都是 $v_i \times |x_i - x_j|$——$\max$ 被排序消掉了。

**剩下的 $|x_i - x_j|$ 怎么统计？**

对第 $i$ 头牛，它和前面所有牛的贡献：

$$v_i \times \sum_{j < i} |x_i - x_j|$$

绝对值拆成左右两边：坐标比 $x_i$ 小的牛（数量 $c_l$、坐标和 $s_l$）贡献 $x_i \cdot c_l - s_l$；坐标比 $x_i$ 大的牛（$c_g$、$s_g$）贡献 $s_g - x_i \cdot c_g$。于是只需要维护：前面牛的坐标中，**小于某个值的数量与坐标和**——标准的树状数组前缀查询。

**为什么用两个树状数组？**

坐标范围只有 $2 \times 10^4$，直接以坐标为下标：

- `bit_cnt` 维护坐标出现次数（查 $c_l$）；
- `bit_sum` 维护坐标值之和（查 $s_l$）。

查询 $x_i - 1$ 的前缀得到"左边"，总数减去左边得到"右边"：

```cpp
long long cnt_less = query(bit_cnt, x - 1);
long long sum_less = query(bit_sum, x - 1);
long long cnt_greater = cnt_all - cnt_less;      // cnt_all = i-1
long long sum_greater = sum_all - sum_less;

ans += 1LL * v * (x * cnt_less - sum_less + sum_greater - x * cnt_greater);
```

处理完当前牛再把它插入两个 BIT，保证"前面"的含义正确。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序 $O(n \log n)$，每头牛两次查询 + 两次更新 $O(\log n)$，总 $O(n \log n)$。空间 $O(n)$。

### 总结

这题的核心套路是**按排序消掉 $\max$**：公式里有 $\max\{v_i, v_j\}$ 这种"看双方"的量时，按它排序可以让处理到每个元素时只看它和前面的关系。剩下的"统计前面小于/大于某个值的数量与和"，是树状数组的经典场景。

## 图示解析

这张图展示按 v 排序后，处理第 4 头牛时前面牛的统计：

```text
按 v 排序后的牛： (v,x)
  (2,6) (2,5) (3,1) (4,3)
    ↑     ↑     ↑     ↑
   已插入 BIT    当前牛 v=4, x=3

前面牛中：x < 3 的有 (3,1)  → cnt_less=1, sum_less=1
          x > 3 的有 (2,6),(2,5) → cnt_greater=2, sum_greater=11
贡献 = 4 × [(3×1-1) + (11-3×2)] = 4 × (2+5) = 28
```

读图方法：每头牛只和前面（v 更小）的牛配对，$\max$ 就是它自己的 v；绝对值靠"左边坐标和"和"右边坐标和"分别结算，两个 BIT 各司其职。
