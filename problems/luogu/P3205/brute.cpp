#include <bits/stdc++.h>
using namespace std;

const int MOD = 19650827;

static int n;
static vector<int> h;

int dfs(int l, int r, int last_idx) {
    if (l == 1 && r == n) {
        return 1;
    }

    long long ways = 0;

    if (l > 1 && h[l - 1] < h[last_idx]) {
        ways += dfs(l - 1, r, l - 1);
    }
    if (r < n && h[r + 1] > h[last_idx]) {
        ways += dfs(l, r + 1, r + 1);
    }

    return ways % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    h.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        // 暴力枚举第一个站出来的人是谁，再直接搜索后续扩展区间的方式。
        ans += dfs(i, i, i);
    }

    cout << ans % MOD << '\n';
    return 0;
}
