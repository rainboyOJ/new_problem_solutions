#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3405;
const int MAXM = 12885;

int n, m;
int weight[MAXN];
int value[MAXN];
int dp[MAXM]; // dp[j] 表示容量不超过 j 时能获得的最大奖励

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        // 每个物品只能选一次，所以容量必须倒序枚举。
        for (int j = m; j >= weight[i]; j--) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    cout << dp[m] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
