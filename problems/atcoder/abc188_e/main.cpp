/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 20:24
 * update_at: 2026-10-29 20:32
 */
// main.cpp：按编号从小到大扫一遍。题目保证 X_i < Y_i，编号顺序就是拓扑序，
// 于是只要维护「能走到 v 的城镇里的最低金价」，答案在 O(N + M) 内就能求出来。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;
const ll INF = LLONG_MAX / 4;

int n, m;
ll price[MAXN];         // price[v]：城镇 v 的金价，买入与卖出同价
ll low[MAXN];           // low[v]：能走到 v 的城镇（含 v 自己）里的最低金价
vector<int> from[MAXN]; // from[v]：所有有一条边直接指向 v 的城镇，即边 u -> v 里的 u

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        from[y].push_back(x);
    }

    ll ans = -INF; // 答案可能是负数：买入价高于卖出价时，要输出真实的亏损
    for (int v = 1; v <= n; v++) {
        // from[v] 里的城镇编号都比 v 小，它们的 low 在更早的轮次已经算完，可以直接用。
        ll buy = INF; // buy：能走到 v 的城镇里的最低买入价
        for (auto u : from[v]) {
            buy = min(buy, low[u]);
        }
        // 在 v 卖出的前提是至少走过一条边，所以没有入边的城镇不产生答案。
        if (!from[v].empty()) {
            ans = max(ans, price[v] - buy);
        }
        // low[v] 允许「在 v 买入」，把这个值留给 v 的后继城镇使用。
        low[v] = min(price[v], buy);
    }

    cout << ans << '\n';
    return 0;
}
