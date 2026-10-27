#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
// dp[c] 表示容量为 c 时的最大价值。
int dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, V;
    cin >> N >> V;
    for (int i = 0; i < N; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        if (s == -1) {                     // 0/1 背包：倒序枚举避免重复使用
            for (int j = V; j >= v; j--)
                dp[j] = max(dp[j], dp[j - v] + w);
        } else {                            // 完全背包：正序枚举，允许多次取用
            for (int j = v; j <= V; j++)
                dp[j] = max(dp[j], dp[j - v] + w);
        }
    }
    cout << dp[V] << '\n';
    return 0;
}
