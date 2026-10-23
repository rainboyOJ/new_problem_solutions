/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:20
 * update_at: 2026-10-23 23:20
 */
// brute.cpp：小数据暴力解法
// 针对小规模图，利用带剪枝的深度优先搜索在图上模拟采蘑菇过程。
// 只适用于点数极小（N <= 5）且边数极少的情况，步数上限设为 25。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10;
const int MAXM = 30;

int n, m, s;

struct Edge {
    int u, v;
    ll w;
    int k;
};

Edge edges[MAXM];
vector<int> g[MAXN];

ll ans = 0;

void dfs(int u, ll sum, int step, int zero_gain_steps) {
    if (sum > ans) {
        ans = sum;
    }
    if (step >= 25) return;
    if (zero_gain_steps >= 4) return;

    for (int e_idx : g[u]) {
        int v = edges[e_idx].v;
        ll old_w = edges[e_idx].w;
        ll gain = old_w;
        edges[e_idx].w = (old_w * edges[e_idx].k) / 10;

        dfs(v, sum + gain, step + 1, (gain == 0 ? zero_gain_steps + 1 : 0));

        edges[e_idx].w = old_w;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        ll w;
        double coef;
        cin >> u >> v >> w >> coef;
        edges[i] = {u, v, w, (int)round(coef * 10)};
        g[u].push_back(i);
    }
    cin >> s;

    dfs(s, 0, 0, 0);

    cout << ans << "\n";
    return 0;
}
