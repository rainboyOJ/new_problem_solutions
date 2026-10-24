/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:26
 * update_at: 2026-10-23 23:26
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 复杂度为 O(2^n * m) = O(2^n * n)，通过指数级枚举所有结点的选/不选状态，
// 逐条检查树上的每条边是否至少有一个端点被选（即被士兵瞭望到），
// 只能用于验证极小规模数据（如 n <= 20）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll maxn = 30;

ll n;
struct Edge {
    ll u, v;
};
vector<Edge> edges;
ll b[maxn]; // 记录每个结点是否选士兵：1 选，0 不选
ll ans = 1e9;

// 递归枚举每个结点的选择状态
void dfs(ll dep) {
    if (dep == n) {
        // 检查所有边是否都被覆盖
        bool ok = true;
        for (const auto &e : edges) {
            if (!b[e.u] && !b[e.v]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ll cnt = 0;
            for (ll i = 0; i < n; ++i) {
                if (b[i]) cnt++;
            }
            ans = min(ans, cnt);
        }
        return;
    }

    // 不选当前结点
    b[dep] = 0;
    dfs(dep + 1);

    // 选当前结点
    b[dep] = 1;
    dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;

    for (ll i = 0; i < n; ++i) {
        ll u, k;
        cin >> u >> k;
        for (ll j = 0; j < k; ++j) {
            ll v;
            cin >> v;
            edges.push_back({u, v});
        }
    }

    ans = n;
    dfs(0);

    cout << ans << "\n";

    return 0;
}
