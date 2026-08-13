/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-12 22:29
 */
// brute.cpp：小数据暴力解，对每条路径直接枚举所有（买入城市，卖出城市）点对，辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, q;
long long price[MAXN];          // price[u] 城市 u 当前的宝石价格
vector<int> g[MAXN];            // 树的邻接表
int prev_node[MAXN];            // BFS 时记录的父链
int path[MAXN];                 // 还原出的 a -> b 路径序列
int path_len;                   // 路径长度（城市个数）

// 用 BFS 在树上求 a -> b 的路径，结果按旅行顺序放在 path[1..path_len]。
void get_path(int a, int b) {
    for (int i = 1; i <= n; i++) prev_node[i] = 0;
    queue<int> qq;
    qq.push(a);
    prev_node[a] = -1;
    while (!qq.empty()) {
        int u = qq.front();
        qq.pop();
        if (u == b) break;
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (prev_node[v] != 0) continue;
            prev_node[v] = u;
            qq.push(v);
        }
    }
    // 从 b 沿父链回溯到 a，再反转得到 a -> b 顺序。
    int cnt = 0;
    for (int u = b; u != -1; u = prev_node[u]) {
        path[++cnt] = u;
    }
    for (int i = 1; i <= cnt / 2; i++) {
        swap(path[i], path[cnt + 1 - i]);
    }
    path_len = cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> q;
    while (q--) {
        int a, b;
        long long v;
        cin >> a >> b >> v;
        get_path(a, b);

        // 枚举路径上的所有买卖点对：先经过的为买入城市，后经过的为卖出城市。
        long long best = 0; // 最大利润，至少为 0（不交易）
        for (int i = 1; i <= path_len; i++) {
            for (int j = i + 1; j <= path_len; j++) {
                long long profit = price[path[j]] - price[path[i]];
                if (profit > best) best = profit;
            }
        }
        cout << best << '\n';

        // ZJY 路过路径上每个城市，价格整体上涨 v。
        for (int i = 1; i <= path_len; i++) {
            price[path[i]] += v;
        }
    }

    return 0;
}
