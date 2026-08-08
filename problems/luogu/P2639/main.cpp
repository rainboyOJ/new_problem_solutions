#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXH = 45005;

int h, n;
int weight[MAXN];
int dp[MAXH]; // dp[j] 表示总重量不超过 j 时，最多能吃到多少干草

void read_input() {
    cin >> h >> n;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        // 每捆干草只能吃一次，所以容量必须倒序枚举。
        for (int j = h; j >= weight[i]; j--) {
            dp[j] = max(dp[j], dp[j - weight[i]] + weight[i]);
        }
    }

    cout << dp[h] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
