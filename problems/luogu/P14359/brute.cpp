// 朴素 O(n²) DP 解法（用于验证小数据）
//
// 设 dp[i] 为前 i 个元素中最多能选出的不相交区间数
// 转移：
//   1. 不选以 i 结尾的区间：dp[i] = dp[i-1]
//   2. 选一个区间 [j+1, i]（异或和为 k）：dp[i] = max(dp[i], dp[j] + 1)
// 利用前缀异或 O(1) 判断区间异或和是否等于 k
// 复杂度 O(n²)，n ≤ 2000 时可接受
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5005; // 小数据规模
int n, k;
int a[maxn];
int pre[maxn]; // 前缀异或: pre[i] = a[1] ^ ... ^ a[i]
int dp[maxn];  // dp[i] = 前 i 个元素中的最优解

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i - 1] ^ a[i]; // 计算前缀异或
    }

    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1]; // 不选以 i 结尾的区间
        // 枚举左端点 j+1，区间 [j+1, i] 异或 = pre[i] ^ pre[j]
        for (int j = 0; j < i; ++j) {
            if ((pre[i] ^ pre[j]) == k) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << dp[n] << "\n";
    return 0;
}
