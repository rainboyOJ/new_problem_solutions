#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据 DFS 枚举每辆车上几个人，作为教学版和对拍基准。

const int INF = 1000000000;

int n, k, d, s;
int t[105], z[105];
int ans = INF;

void dfs(int idx, int sent, int cost) {
    if (cost >= ans) {
        return;
    }
    if (idx > k) {
        if (sent == n) {
            ans = min(ans, cost);
        }
        return;
    }

    // 这辆车不上人。
    dfs(idx + 1, sent, cost);

    // 这辆车上 x 个人。
    for (int x = 1; x <= z[idx] && sent + x <= n; x++) {
        dfs(idx + 1, sent + x, cost + d + x * t[idx]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> d >> s;
    for (int i = 1; i <= k; i++) {
        cin >> t[i] >> z[i];
    }

    dfs(1, 0, 0);
    cout << ans << '\n';
    return 0;
}
