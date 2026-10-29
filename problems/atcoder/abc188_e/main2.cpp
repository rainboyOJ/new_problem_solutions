/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 20:28
 * update_at: 2026-10-29 20:32
 */
// main2.cpp：同一个 DP 的反向记忆化写法。它只要求图是有向无环图，
// 不依赖 X_i < Y_i 带来的「编号即拓扑序」；代价是递归深度等于最长链的长度。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;
const ll INF = LLONG_MAX / 4;

int n, m;
ll price[MAXN];         // price[v]：城镇 v 的金价
ll low[MAXN];           // low[v]：能走到 v 的城镇（含 v）里的最低金价；等于 INF 表示还没算过
vector<int> from[MAXN]; // from[v]：所有有一条边直接指向 v 的城镇

// 求 low[v]：先算完所有入边的对端，再取它们和 price[v] 的最小值。
ll get_low(int v) {
    if (low[v] != INF) {
        return low[v]; // 记住结果，每个城镇只算一次
    }
    ll buy = INF;
    for (auto u : from[v]) {
        buy = min(buy, get_low(u));
    }
    low[v] = min(price[v], buy);
    return low[v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
        low[i] = INF;
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        from[y].push_back(x);
    }

    // 从编号大的城镇开始问，递归会沿入边一路往回走，深度等于最长链的长度。
    for (int v = n; v >= 1; v--) {
        get_low(v);
    }

    ll ans = -INF; // 答案可能是负数
    for (int v = 1; v <= n; v++) {
        if (from[v].empty()) {
            continue; // 没有入边，无法「先走一条边再来这里卖」
        }
        ll buy = INF;
        for (auto u : from[v]) {
            buy = min(buy, low[u]);
        }
        ans = max(ans, price[v] - buy);
    }

    cout << ans << '\n';
    return 0;
}
