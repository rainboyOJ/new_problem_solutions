---
oj: "HDU"
problem_id: "6273"
title: "Master of GCD"
date: 2026-01-01 12:44
toc: true
tags: ["数论","差分"]
desc: ""
source: https://vjudge.net/problem/HDU-6273#author=DeepSeek_zh
---

[[TOC]]

这道题目考察的是**差分数组（Difference Array）**与**数论（GCD性质）**的结合。

### 核心思路

1. **分解问题**：
   - 题目中所有的操作都是乘以 $2$ 或 $3$。这意味着数组中的每个数字 $a_i$ 最终都可以表示为 $2^{A_i} \times 3^{B_i}$ 的形式。
   - 求整个序列的最大公约数（GCD），等价于求序列中所有数字在质因数分解后，各质因子指数的**最小值**。
   - 即：$GCD = 2^{\min(A_1, \dots, A_n)} \times 3^{\min(B_1, \dots, B_n)}$。
2. **转化操作**：
   - 由于是对指数求最小值，我们可以将**区间乘法**转化为**区间加法**。
   - 当操作是 `l r 2` 时，相当于区间 $[l, r]$ 内所有数字的质因子 $2$ 的指数加 $1$。
   - 当操作是 `l r 3` 时，相当于区间 $[l, r]$ 内所有数字的质因子 $3$ 的指数加 $1$。
3. **使用差分数组**：
   - 由于涉及大量的区间修改，使用**差分数组**可以将区间操作的时间复杂度从 $O(N)$ 降为 $O(1)$。
   - 我们需要两个差分数组：`diff2` 维护质因子 $2$ 的指数变化，`diff3` 维护质因子 $3$ 的指数变化。
   - **修改**：对于区间 $[l, r]$ 加 $1$，执行 `diff[l]++` 和 `diff[r+1]--`。
   - **还原**：最后对差分数组求前缀和，即可得到每个位置的实际指数值。
4. **计算结果**：
   - 遍历还原后的数组，分别找到 $2$ 的指数最小值和 $3$ 的指数最小值。
   - 利用快速幂计算最终模 $998244353$ 的结果。

------

### C++ 代码实现

C++

```
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MOD = 998244353;

// 快速幂函数，计算 (base^exp) % MOD
long long qpow(long long base, long long exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;

    // 定义两个差分数组，分别记录2的指数和3的指数
    // 大小设为 n+2 防止 r+1 越界
    vector<int> diff2(n + 2, 0);
    vector<int> diff3(n + 2, 0);

    for (int i = 0; i < m; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        if (x == 2) {
            diff2[l]++;
            diff2[r + 1]--;
        } else if (x == 3) {
            diff3[l]++;
            diff3[r + 1]--;
        }
    }

    // 计算2的指数的最小值
    int min_exp2 = INT_MAX;
    int current_exp2 = 0;
    
    // 计算3的指数的最小值
    int min_exp3 = INT_MAX;
    int current_exp3 = 0;

    // 遍历1到n，利用前缀和还原每个位置的指数，并同时维护最小值
    for (int i = 1; i <= n; ++i) {
        current_exp2 += diff2[i];
        min_exp2 = min(min_exp2, current_exp2);

        current_exp3 += diff3[i];
        min_exp3 = min(min_exp3, current_exp3);
    }

    // 计算最终结果: (2^min_exp2 * 3^min_exp3) % MOD
    long long ans = (qpow(2, min_exp2) * qpow(3, min_exp3)) % MOD;
    
    cout << ans << endl;
}

int main() {
    // 优化输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

### 代码详解

1. 数据结构：

   使用 vector<int> diff2 和 diff3。大小设为 $n+2$ 是为了处理 $1$-based 索引以及差分数组在 $r+1$ 处的边界情况，避免越界。

2. **差分更新**：

   C++

   ```
   diff2[l]++;
   diff2[r + 1]--;
   ```

   这是标准的差分操作。如果题目输入是 `1 5 2`，表示第1到第5个数都乘以2（指数+1），我们在 `diff2[1]` 加1，在 `diff2[6]` 减1。

3. 还原与求最值：

   在 for 循环中，current_exp2 += diff2[i] 实际上就是在做前缀和。

   - 第 $i$ 个位置实际的 $2$ 的指数 $A_i = \sum_{k=1}^{i} diff2[k]$。
   - 我们在计算前缀和的过程中直接取 `min`，避免了先存储整个数组再遍历一遍，节省空间和时间。

4. 快速幂：

   由于指数可能很大（最大可达 $m=100000$），直接计算 $2^{100000}$ 会溢出，必须使用快速幂并在每一步进行取模运算。

### 复杂度分析

- **时间复杂度**：
  - 处理 $m$ 次操作：$O(m)$。
  - 还原数组并找最小值：$O(n)$。
  - 快速幂计算：$O(\log(\min\_exp)) \approx O(\log m)$。
  - 总复杂度：$O(n + m)$。对于 $10^5$ 的数据量，这完全可以在1秒内运行完成。
- **空间复杂度**：
  - 使用了两个长度为 $n$ 的数组，复杂度为 $O(n)$。

这个解法完美契合题目的“差分”提示，且逻辑清晰高效。
