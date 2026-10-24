/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:13
 * update_at: 2026-10-23 23:13
 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 19650827;

static int n;
static vector<int> h; // h[i]：理想队形中第 i 个人的身高（下标从 1 开始）

// dfs：当前已构成目标区间 [l, r]，最后插入的人是 last_idx，返回扩满 [1, n] 的方案数。
// 只适合小数据：同一个 (l, r, last_idx) 会被不同路径反复访问，指数级重复计算。
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
