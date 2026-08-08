// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
int a[MAXN];
int ans;

void dfs(int idx, int cnt, int sum) {
    if (cnt == 3) {
        if (sum <= m) {
            ans = max(ans, sum);
        }
        return;
    }
    if (idx > n) {
        return;
    }

    // 选当前这个数。
    dfs(idx + 1, cnt + 1, sum + a[idx]);
    // 不选当前这个数。
    dfs(idx + 1, cnt, sum);
}

void solve() {
    ans = 0;
    dfs(1, 0, 0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
