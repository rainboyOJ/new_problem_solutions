/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:26
 * update_at: 2026-10-23 23:26
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll maxn = 1505;

ll n;
vector<ll> e[maxn];
ll dp[maxn][2];
bool vis[maxn];

// 树形 DP
// u: 当前节点，fa: 父节点
void dfs(ll u, ll fa) {
    dp[u][0] = 0; // u 不放士兵
    dp[u][1] = 1; // u 放士兵，花费为 1

    for (ll v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        // 如果 u 不放士兵，则其子节点 v 必须放士兵，否则边 (u, v) 无法被瞭望
        dp[u][0] += dp[v][1];
        // 如果 u 放士兵，则子节点 v 可放可不放，取二者最小值
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
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
            e[u].push_back(v);
            e[v].push_back(u);
        }
    }

    // 任选 0 作为根节点进行树形 DP
    dfs(0, -1);

    cout << min(dp[0][0], dp[0][1]) << "\n";

    return 0;
}
