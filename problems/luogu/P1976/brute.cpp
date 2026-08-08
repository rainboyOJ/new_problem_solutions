#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
i64 memo[35][35];
bool vis[35][35];

// dfs(l, r) 表示只考虑区间 [l, r] 里的点，
// 这些点按圆上的顺序排成一段时，不相交配对的方案数。
i64 dfs(int l, int r) {
    if (l > r) {
        return 1;
    }

    if (vis[l][r]) {
        return memo[l][r];
    }
    vis[l][r] = true;

    i64 ans = 0;

    // 固定最左端点 l，枚举它和哪个点配对。
    // 配对后，区间会被拆成 [l+1, k-1] 和 [k+1, r] 两段。
    for (int k = l + 1; k <= r; k += 2) {
        ans += dfs(l + 1, k - 1) * dfs(k + 1, r);
    }

    memo[l][r] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cout << dfs(1, 2 * n) << '\n';

    return 0;
}
