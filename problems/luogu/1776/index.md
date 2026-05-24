---
oj: "luogu"
problem_id: "P1776"
title: "宝物筛选"
date: 2026-01-04 17:14
toc: true
tags: ["多重背包"]
desc: "多重背包模板题目"
source: https://www.luogu.com.cn/problem/P1776
---

[[TOC]]

## 题目解析

这是一道典型的**多重背包问题**。

问题描述：给定 $n$ 种物品，每种物品有价值 $v_i$、重量 $w_i$ 和数量 $m_i$。有一个容量为 $W$ 的背包，要求选择物品装入背包，使得在总重量不超过 $W$ 的前提下，总价值最大。

朴素的动态规划做法是三重循环：枚举物品种类 $i$，枚举背包容量 $j$，枚举当前物品选择的数量 $k$。状态转移方程为：

$dp[j] = \max(dp[j], dp[j - k \cdot w_i] + k \cdot v_i)$，其中 $1 \le i \le n$，$0 \le j \le W$，$0 \le k \le m_i$ 且 $k \cdot w_i \le j$。

这种做法的时间复杂度是 $O(W \times \sum m_i)$。根据题目数据范围，$W \le 4 \times 10^4$，$\sum m_i \le 10^5$，最坏情况下计算量会达到 $4 \times 10^9$ 级别，超时无疑。因此我们需要进行优化。

下面分别介绍两种常见的优化方法：二进制拆分优化和单调队列优化。

------

## 方法一：二进制拆分优化 (Binary Splitting Optimization)

### 1. 原理解析

多重背包问题的瓶颈在于物品数量的限制。如果我们能把第 $i$ 种物品的 $m_i$ 件拆分成若干组，每一组看作是一个全新的“0/1 背包”物品（只能选或不选），那么问题就转化为了 0/1 背包问题。

如何拆分最高效？利用二进制的思想。任何一个正整数 $m$ 都可以表示为若干个 $2$ 的幂次方的和。我们可以将 $m_i$ 件物品拆分成数量分别为 $1, 2, 4, 8, \dots, 2^k, R$ 的若干组，其中 $2^k \le m_i$ 且 $1+2+4+\dots+2^k+R = m_i$，$R$ 是剩下的余数（可能为 0）。

例如，若某物品有 13 件，我们可以拆分成数量为 1, 2, 4, 6 的四组新物品。

- 第 1 组：重量 $1 \cdot w_i$，价值 $1 \cdot v_i$
- 第 2 组：重量 $2 \cdot w_i$，价值 $2 \cdot v_i$
- 第 3 组：重量 $4 \cdot w_i$，价值 $4 \cdot v_i$
- 第 4 组：重量 $6 \cdot w_i$，价值 $6 \cdot v_i$

通过组合这四组新物品（选或不选），我们可以凑出 $0$ 到 $13$ 之间任意数量的原物品。

### 2. 复杂度分析

对于每种物品 $m_i$，拆分后的新物品数量大约是 $\log_2(m_i)$ 个。总的新物品数量 $N'$ 大约是 $\sum \log_2(m_i)$。在最坏情况下（例如 $N$ 较小而 $m_i$ 很大），$N'$ 的上界大约是 $N \times \log(\max m_i)$。

对于题目数据，$\sum m_i \le 10^5$，拆分出来的新物品总数通常不会超过 $10^5$（实际上远小于这个数，大约在 $N \times 17$ 左右）。

转化后的 0/1 背包时间复杂度为 $O(W \times N')$。这个复杂度通常足以通过此题。

### 3. C++ 代码实现


@include-code(./1.cpp,cpp)

------

## 方法二：单调队列优化 (Monotonic Queue Optimization)

### 1. 原理解析

让我们回到朴素的状态转移方程：

$dp[j] = \max_{0 \le k \le m_i} \{ dp_{prev}[j - k \cdot w_i] + k \cdot v_i \}$

观察这个方程，当我们在计算 $dp[j], dp[j+w_i], dp[j+2w_i], \dots$ 时，我们会发现它们依赖的状态在不断“滑动”。

我们可以按照容量 $j$ 对 $w_i$ 取模的余数 $r$ ($0 \le r < w_i$) 来进行分组。对于固定的余数 $r$，容量 $j$ 可以表示为 $j = q \cdot w_i + r$，其中 $q$ 是商。

我们将方程中的 $j$ 替换掉，并将上一层状态记为 $dp_{pre}$：

$dp[q \cdot w_i + r] = \max_{0 \le k \le m_i} \{ dp_{pre}[(q - k) \cdot w_i + r] + k \cdot v_i \}$

令 $k' = q - k$，则 $k = q - k'$。当 $k$ 的范围是 $[0, m_i]$ 时，$k'$ 的范围是 $[q - m_i, q]$。方程变换为：

$dp[q \cdot w_i + r] = \max_{q - m_i \le k' \le q} \{ dp_{pre}[k' \cdot w_i + r] + (q - k') \cdot v_i \}$

$dp[q \cdot w_i + r] = \max_{q - m_i \le k' \le q} \{ dp_{pre}[k' \cdot w_i + r] - k' \cdot v_i \} + q \cdot v_i$

现在核心看大括号里的部分。对于一个固定的余数 $r$，随着商 $q$ 的增加，我们需要在范围 $[q - m_i, q]$ 内找到一个 $k'$，使得 $dp_{pre}[k' \cdot w_i + r] - k' \cdot v_i$ 的值最大。这正是一个经典的**滑动窗口最大值**问题，可以使用单调队列在 $O(1)$ 的均摊时间内解决。

我们需要维护一个单调递减队列，队列中存储的是商的下标 $k'$。队列里的元素对应的值（即 $dp_{pre}[k' \cdot w_i + r] - k' \cdot v_i$）是单调递减的。

### 2. 复杂度分析

- 外层循环枚举物品种类：$N$ 次。

- 中层循环枚举余数：$w_i$ 次。

- 内层循环枚举商：$W / w_i$ 次。

- 单调队列操作是均摊 $O(1)$ 的。

  总时间复杂度 = $\sum_{i=1}^N (w_i \times \frac{W}{w_i}) = \sum_{i=1}^N W = O(N \times W)$。

  代入数据 $100 \times 4 \times 10^4 = 4 \times 10^6$，这个复杂度非常优秀，是多重背包问题的最优解法之一。

### 3. C++ 代码实现

为了方便理解，使用两个数组 `dp` 和 `pre_dp` 来分别表示当前层和上一层的状态。也可以通过使用一维数组和临时变量来实现滚动数组优化空间。


```cpp
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int n, W;
int v[105], w[105], m[105];
// dp[j] 表示容量为 j 时的最大价值
int dp[40005];
// pre_dp 用于存储上一轮物品处理后的状态，用于辅助单调队列计算
int pre_dp[40005];

// 计算单调队列中用于比较的值
inline int calc_val(int idx, int weight, int value, int r) {
    return pre_dp[idx * weight + r] - idx * value;
}

int main() {
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> W;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> w[i] >> m[i];
    }

    // 初始化 dp 数组为 0
    fill(dp, dp + W + 1, 0);

    // 枚举每一种物品
    for (int i = 1; i <= n; ++i) {
        // 备份上一轮的状态
        copy(dp, dp + W + 1, pre_dp);
        // 枚举余数 r
        for (int r = 0; r < w[i]; ++r) {
            deque<int> dq; // 单调队列存储的是商的下标 q
            // 枚举商 q，对应的容量是 j = q * w[i] + r
            for (int q = 0; q * w[i] + r <= W; ++q) {
                int current_capacity = q * w[i] + r;
                int current_val_for_compare = calc_val(q, w[i], v[i], r);

                // 1. 入队操作：维护队列单调递减性
                // 如果队尾元素对应的值小于等于当前值，则队尾元素永远不会成为最大值，弹出
                while (!dq.empty() && calc_val(dq.back(), w[i], v[i], r) <= current_val_for_compare) {
                    dq.pop_back();
                }
                dq.push_back(q);

                // 2. 出队操作：检查队头是否滑出窗口范围
                // 窗口大小为 m[i]+1，有效范围是 [q - m[i], q]
                if (dq.front() < q - m[i]) {
                    dq.pop_front();
                }

                // 3. 更新 DP 状态
                // 队头保存的是窗口内的最优 k'
                int best_k_prime = dq.front();
                // 代入公式：dp[j] = (pre_dp[k'*w+r] - k'*v) + q*v
                // 化简后为：dp[j] = pre_dp[k'*w+r] + (q - k') * v
                // 其中 (q - k') 就是选择当前物品的数量
                dp[current_capacity] = pre_dp[best_k_prime * w[i] + r] + (q - best_k_prime) * v[i];
            }
        }
    }

    cout << dp[W] << endl;

    return 0;
}
```

## 总结

对于多重背包问题：

1. **数据范围较小**时，可以直接用朴素的三重循环 $O(W \sum m_i)$。
2. **一般数据范围**（如本题，$W$ 中等，$\sum m_i$ 较大），推荐使用**二进制拆分优化**，转化为 0/1 背包，复杂度 $O(W \sum \log m_i)$，实现简单，不易出错。
3. **对时间要求极高**或数据范围更大时，使用**单调队列优化**，复杂度 $O(NW)$，是理论上的最优复杂度，但实现细节较多，推导公式需要仔细。
