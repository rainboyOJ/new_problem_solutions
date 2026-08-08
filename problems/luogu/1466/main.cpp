#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXS = 400;

int n;
// dp[j] 表示从 1..n 中选若干不同的数，和为 j 的子集个数。
ll dp[MAXS * MAXS];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int total = n * (n + 1) / 2;
    if (total % 2 != 0) {                // 总和为奇数无法平分为两个相等子集
        cout << 0 << '\n';
        return 0;
    }

    int target = total / 2;

    // 0/1 背包计数：dp[0]=1，每个数 i 只能用一次，倒序枚举。
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = target; j >= i; j--) {
            dp[j] += dp[j - i];
        }
    }

    // 每种集合划分算了两次（左右交换），除以 2。
    cout << dp[target] / 2 << '\n';
    return 0;
}
