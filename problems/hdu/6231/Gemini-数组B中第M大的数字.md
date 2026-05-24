# 数组B中第M大的数字


这是一个非常经典的算法问题，融合了**二分答案（Binary Search on Answer）**、\*\*前缀和（Prefix Sum）**以及**树状数组（Fenwick Tree / Binary Indexed Tree）\*\*的知识点。

下面我将分步为你解析这个问题的解题思路，并提供完整的 C++ 代码。

### 核心解题思路

#### 1\. 问题分析

我们要找数组  $B$  中的第  $M$  大的数。 数组  $B$  的大小可能非常大（接近  $O\left(N^{2}\right)$ ），直接生成数组  $B$  并排序会超时（TLE）且爆内存（MLE）。

#### 2\. 二分答案

当我们要找“第  $K$  大”或“最大值最小”这类问题时，通常可以考虑**二分答案**。 假设我们猜测答案是  $X$ ：

*   如果数组  $B$  中大于等于  $X$  的元素个数  $\ge M$ ，说明真正的答案一定  $\ge X$ ，我们应该尝试更大的值。
*   反之，说明答案  $<X$ ，我们要尝试更小的值。

通过二分，我们将问题转化为了：**如何快速计算数组  $B$  中有多少个元素大于等于  $X$ ？**

#### 3\. `check(X)` 函数的设计

数组  $B$  中的元素来源于：所有长度  $\ge K$  的子区间中的第  $K$  大数字。 如果一个子区间的第  $K$  大数字  $\ge X$ ，这意味着**该子区间内至少有  $K$  个数字  $\ge X$ **。

我们可以构建一个辅助的 0/1 数组（或者利用前缀和思想）： 对于原数组  $A$ ，如果  $A\left[i\right]\ge X$ ，记为 1，否则记为 0。 设  $S$  为这个 0/1 数组的前缀和数组。 $S\left[i\right]$  表示  $A\left[1..i\right]$  中有多少个数  $\ge X$ 。

对于任意区间  $\left[L,R\right]$ ，其包含的  $\ge X$  的数的个数为  $S\left[R\right]-S\left[L-1\right]$ 。 我们需要统计满足以下两个条件的区间  $\left[L,R\right]$  的数量：

1.  区间长度合法： $R-L+1\ge K$ 
2.  第  $K$  大数合法（即区间内至少有  $K$  个 1）： $S\left[R\right]-S\left[L-1\right]\ge K$ 

整理条件 2 得： $S\left[L-1\right]\le S\left[R\right]-K$ 。

#### 4\. 使用树状数组（BIT）加速统计

我们需要遍历所有的右端点  $R$ （从  $K$  到  $N$ ）： 对于固定的  $R$ ，我们需要找到有多少个左端点  $L$ ，满足：

*    $1\le L\le R-K+1$ 
*    $S\left[L-1\right]\le S\left[R\right]-K$ 

令  $j=L-1$ ，则  $0\le j\le R-K$  且  $S\left[j\right]\le S\left[R\right]-K$ 。 这是一个动态统计问题：随着  $R$  的增加，合法的  $j$  的范围也在扩大（每次增加一个新的下标  $R-K$ ）。我们可以用**树状数组**来维护  $S$  值的频率。

**算法流程：**

1.  遍历  $R$  从 1 到  $N$ 。
2.  当  $R\ge K$  时，合法的左端点下标  $j=R-K$  刚刚进入窗口。我们将  $S\left[R-K\right]$  的值加入树状数组（执行 `add(S[R-K], 1)`）。
3.  我们需要查询树状数组中  $\le S\left[R\right]-K$  的数的个数（执行 `query(S[R] - K)`）。
4.  累加结果即为大于等于  $X$  的元素总数。

### 复杂度分析

*   **二分次数**： $A_{i}$  范围是  $10^{9}$ ，大约需要  $\log \left(10^{9}\right)\approx 30$  次。
*   **Check 函数**：遍历  $N$  次，每次树状数组操作  $O\left(\log N\right)$ 。总计  $O\left(N\log N\right)$ 。
*   **总复杂度**： $O\left(N\log N\log \left(\max A\right)\right)$ 。对于  $N=10^{5}$ ，运算量在  $10^{7}$  级别，完全可以在 1 秒内通过。

* * *

### C++ 代码实现

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 树状数组 (Binary Indexed Tree)
// 用于快速统计频率前缀和
class FenwickTree {
public:
    int size;
    vector<int> tree;

    FenwickTree(int n) {
        size = n;
        tree.assign(n + 1, 0);
    }

    // 在 index 位置 +val (注意 index 是基于值的，这里处理为 1-based)
    void add(int index, int val) {
        // 因为前缀和可能为0，而BIT通常从1开始，所以传入时通常+1
        index++; 
        while (index <= size) {
            tree[index] += val;
            index += index & (-index);
        }
    }

    // 查询 <= index 的数量
    int query(int index) {
        index++; // 对应 add 的偏移
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & (-index);
        }
        return sum;
    }
};

int N, K;
long long M;
vector<int> A;

// 检查是否存在至少 M 个子区间，其第 K 大元素 >= X
bool check(int X) {
    // 1. 构建前缀和数组
    // S[i] 表示 A[0...i-1] 中 >= X 的个数
    vector<int> S(N + 1, 0);
    for (int i = 0; i < N; i++) {
        S[i + 1] = S[i] + (A[i] >= X ? 1 : 0);
    }

    // 2. 初始化树状数组
    // S[i] 的最大值是 N，所以 BIT 大小设为 N + 2 足够
    FenwickTree bit(N + 2);
    
    long long count = 0;
    
    // 3. 遍历右端点 r (对应前缀和下标 i)
    // 区间 A[l...r] 对应前缀和 S[r+1] - S[l]
    // 长度 r - l + 1 >= K  => l <= r + 1 - K
    // 设 j = l (前缀和下标), current = r + 1 (前缀和下标)
    // 条件: S[current] - S[j] >= K  =>  S[j] <= S[current] - K
    // 且 0 <= j <= current - K
    
    for (int i = 1; i <= N; i++) {
        // i 代表当前子区间的结束位置在 S 中的下标 (对应 A[i-1])
        
        // 我们需要维护合法的 j 的集合。
        // 当 i 增加时，合法的 j 的右边界 (i - K) 也在增加。
        // 我们把新进入范围的 S[i - K] 加入 BIT。
        if (i >= K) {
            int valid_j = i - K;
            bit.add(S[valid_j], 1);
            
            int target = S[i] - K;
            if (target >= 0) {
                count += bit.query(target);
            }
        }
    }

    return count >= M;
}

void solve() {
    if (!(cin >> N >> K >> M)) return;
    A.resize(N);
    int min_val = 1e9, max_val = -1e9;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        min_val = min(min_val, A[i]);
        max_val = max(max_val, A[i]);
    }

    // 二分答案
    int left = min_val, right = max_val;
    int ans = min_val;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;      // mid 可能是答案，尝试更大的
            left = mid + 1;
        } else {
            right = mid - 1; // mid 太大了，达不到 M 个
        }
    }

    cout << ans << endl;
}

int main() {
    // 加速 IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
```

### 代码关键点解析

1.  **BIT 的偏移量**： 树状数组通常是 1-based 索引。在这个问题中，前缀和数组  $S$  的值范围是  $\left[0,N\right]$ 。为了将 0 映射到 BIT 的有效索引，我在 `add` 和 `query` 内部统一对传入的索引进行了 `+1` 操作。
2.  **滑动窗口逻辑**： 在 `check` 函数的循环中：
    *   当前考察的前缀和下标是 `i` (对应原数组的第 `i` 个元素作为结尾)。
    *   合法的起始前缀和下标是 `j`，必须满足区间长度  $\ge K$ 。
    *   每次循环，新的合法 `j` 是 `i - K`。我们先把 `S[i-K]` 加入 BIT，然后再查询有多少个已加入的 `S[j]` 满足条件  $S\left[j\right]\le S\left[i\right]-K$ 。
3.  **数据类型**：
    *    $M$  可以非常大（接近  $N^{2}/2$ ），必须使用 `long long` 存储 `count` 和 `M`。
    *    $A_{i}$  使用 `int` 即可。

这个解法能够完美通过  $N=10^{5}$  的测试用例，并在规定时间内给出正确答案。



---
Powered by [Gemini Exporter](https://www.ai-chat-exporter.com)
