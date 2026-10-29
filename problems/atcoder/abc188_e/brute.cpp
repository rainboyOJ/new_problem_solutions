/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 20:24
 * update_at: 2026-10-29 20:32
 */
// brute.cpp：小数据暴力解，枚举买入城镇，DFS 找出它能到达的所有城镇，再取最大差价。
// 只适合小数据：单次 DFS 是 O(N + M)，对每个起点都做一遍就是 O(N(N + M))。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 205; // 暴力只跑小数据，这个上界够用

int n, m;
ll price[MAXN];      // price[v]：城镇 v 的金价
vector<int> g[MAXN]; // g[u]：城镇 u 能直接前往的城镇
int visited[MAXN];   // visited[v] == u 表示本轮（起点为 u）已经到达城镇 v

// 从 u 出发沿有向边标记所有能到达的城镇。
void dfs_walk(int u, int mark) {
    for (auto v : g[u]) {
        if (visited[v] == mark) {
            continue;
        }
        visited[v] = mark;
        dfs_walk(v, mark);
    }
}

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
        g[x].push_back(y);
    }

    ll ans = LLONG_MIN / 4; // 答案可能是负数
    for (int u = 1; u <= n; u++) {
        dfs_walk(u, u); // 用起点编号当本轮标记，省去每次清空 visited
        for (int v = 1; v <= n; v++) {
            if (visited[v] == u) { // 从 u 出发能走到 v，且至少走了一条边
                ans = max(ans, price[v] - price[u]);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
