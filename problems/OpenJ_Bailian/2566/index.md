---
oj: "OpenJ_Bailian"
problem_id: "1041"
title: "John&#39;s trip"
date: 2026-01-08 17:11
toc: true
tags: ["双指针"]
desc: ""
source: https://vjudge.net/problem/OpenJ_Bailian-2566#author=DeepSeek_zh
---

[[TOC]]

## 题目解析

- 区间和转成 前缀和

**基于排序前缀和 + 双指针（尺取法）**的解法是解决此类“最接近子段和”问题的标准且高效的方法。


## 1. 题目解析：寻找最接近目标值的子段和

### 核心思想

题目的目标是找到一个子段 `[l, r]`，使得其和 `sum(l, r)` 的绝对值最接近给定的目标值 `t`。

1. 转化子段和为前缀和差：

任何子段和都可以表示为两个前缀和的差：



$$Sum(l, r) = Pre[r] - Pre[l-1]$$



这意味着我们需要在 $Pre$ 数组中找到两个下标 $i$ 和 $j$ ($i \neq j$)，使得 $|(Pre[j] - Pre[i]) - t|$ 最小。

2. 为什么需要排序？

原始的前缀和数组是无序的，暴力枚举所有 $(i, j)$ 对的时间复杂度是 $O(N^2)$，对于 $N=100,000$ 来说会超时。

通过对 Pre 数组进行排序（并记录原始下标），我们可以利用单调性。排序后，随着下标 $j$ 的增加，$Pre[j]$ 是递增的。

3. 双指针（尺取法）策略：

你的代码采用了一种非常直观的双指针策略：

- **固定左端点 `i`**：遍历排序后的数组。
- **移动右端点 `j`**：寻找与 $Pre[i]$ 的差最接近 $t$ 的 $Pre[j]$。
- 由于数组已排序，对于固定的 $i$，随着 $j$ 增大，区间和 `val = Pre[j] - Pre[i]` 是**单调递增**的。
  - 如果 `val < t`：说明当前的和还不够大，我们需要更大的 $Pre[j]$，所以 `j` 继续往右跑。
  - 如果 `val >= t`：说明当前的和已经达到或超过了 $t$。
    - 此时 `val - t` 是非负的。
    - 如果继续增大 `j`，`val` 会更大，偏离 `t` 更远。
    - **因此**，一旦遇到 `val >= t`，这就是当前 `i` 能找到的“右侧最近点”，记录答案后直接 `break`，处理下一个 `i`。
- 为什么 j 不需要回退（或只需微调）？

代码中巧妙地使用了 j = max(j, i + 1)。

- 当 `i` 增加时，$Pre[i]$ 变大（因为排过序）。
- 那么 $Pre[j] - Pre[i]$ 会变小。
- 如果之前 `val >= t` 刚好停下，现在 `val` 变小了，可能变得小于 `t`，也可能依然大于 `t` 但更接近。所以 `j` 只需要从上一次的位置（或者 `i+1`）继续尝试，不需要从头开始找。

------

## 2. 代码


```cpp
/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-14 15:38:03
 * * 题目解析：
 * 本题利用“前缀和”将子段和转化为两点之差。
 * 通过对前缀和数组进行排序，将问题转化为：
 * 在有序数组中找到两点差值最接近 t 的一对点。
 * 使用双指针（尺取法）在 O(N) 时间内解决单次查询。
 */
#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5; // 数组大小，稍微开大一点防止越界
int n,k,t;

// 存储前缀和信息的结构体
struct node {
    ll sum; // 前缀和的值
    ll id;  // 对应的原始下标（0到n）
    // 重载小于号，用于 sort 排序
    bool operator<(const node &t) const {
        return sum < t.sum;
    }
};

node pre[maxn]; // 前缀和数组

// 初始化函数：读取数据并预处理
void init(){
    // 0号前缀和为0，原始下标为0
    pre[0].id = 0; pre[0].sum = 0;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        pre[i].id  = i;
        pre[i].sum = pre[i-1].sum + t; // 计算前缀和
    }

    // 关键步骤：按前缀和大小排序
    // 排序后，pre[i] 与 pre[i+1] 的值在数值上是紧邻的
    std::sort(pre,pre+1+n);

    #ifdef DEBUG
    // 调试输出排序后的数组
    for(int i = 0;i <= n ;++i ) cout << pre[i].sum << "\t";
    std::cout  << "\n";
    for(int i = 0;i <= n ;++i ) cout << pre[i].id<< "\t";
    std::cout  << "\n";
    #endif
}

// 手写绝对值函数
ll _abs(ll v) {
    return v < 0 ? -v : v;
}

// 处理每一次查询
void solve() {
    std::cin >> t;
    // 虽然题目说 t 是非负整数，但为了通用性，取绝对值是个好习惯
    // if( t < 0 ) t *= -1; 

    int l, r; // 最终答案的左右边界（原始下标）
    ll min_abs_val = 1e16; // 初始化最小差值为一个很大的数，防止第一次比较失败
    ll ans; // 最终的最接近的子段和
    int j = 0; // 右指针

    // 外层循环枚举左指针 i
    for(int i = 0; i <= n; i++) 
    {
        // 优化点：j 不需要每次从 i+1 开始。
        // j 保持单调递增（或者保持在 i 的右边）。
        // 这一步确保区间不为空，且利用了之前的进度。
        j = max(j, i + 1);

        // 内层循环移动 j
        for( ; j <= n ; j++ ) {
            // 计算当前两个前缀和的差值（即排序后的某个区间和）
            // 因为已排序且 j > i，所以 val >= 0
            ll val = pre[j].sum - pre[i].sum;

            // 计算该区间和与目标 t 的距离
            ll diff = _abs(val - t);

            // 如果找到了更优解（距离更小）
            if( diff < min_abs_val ) {
                ans = val;        // 记录该和
                min_abs_val = diff; // 记录最小距离
                l = pre[i].id;    // 记录原始下标起点
                r = pre[j].id;    // 记录原始下标终点
            }

            // 核心剪枝逻辑：
            // 因为 i 固定时，随着 j 增加，val (pre[j]-pre[i]) 是单调递增的。
            // 如果 val 已经 >= t，说明我们已经跨过了 t。
            // 再往后找，val 只会更大，diff = val - t 只会更大。
            // 所以当前 j 就是 i 对应的最佳“右侧”匹配点，无需继续内层循环。
            if( val >= t ) break; 
        }
    }

    // 输出处理：
    // 前缀和 pre[r] - pre[l] 表示的是原数组 (min_id + 1) 到 max_id 的和
    if( l > r) std::swap(l, r);
    l++; // 下标修正，题目要求从 1 开始
    
    std::cout << ans << " " << l << " " << r << "\n";
}

signed main () {
    // 关闭同步，加速 IO
    ios::sync_with_stdio(false); cin.tie(0);
    
    while (1) {
        std::cin >> n >> k;
        // 结束条件
        if( n == 0 && k == 0 ) break;
      
        init(); // 读取数组并排序
        
        // 处理 k 次查询
        for(int i = 1; i <= k; ++i) 
        {
            solve();
        }
    }
    
    return 0;
}
```

## 复杂度分析

1. **时间复杂度**：
   - **排序**：`init()` 中的 `sort` 耗时 $O(N \log N)$。
   - **查询**：`solve()` 中虽然有两层循环，但 `i` 遍历 $0 \dots N$，`j` 也最多遍历 $0 \dots N$（因为 `j` 不怎么回退，或者即使回退也是常数级的操作）。平均来看，单次查询接近 $O(N)$。
   - 总复杂度：$O(N \log N + K \cdot N)$。对于题目给定的范围（$N=10^5$），这是完全可以接受的。
2. **空间复杂度**：
   - 使用了 `pre` 数组存储前缀和，空间为 $O(N)$。

