/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-10-29 22:55
 */
// main.cpp：枚举医院所在节点 + 从该点 BFS 求加权距离和（P1364 医院设置）。
// 题面 n <= 100，O(n^2) 直接可过；需要更大规模时的 O(n) 换根 DP 见 main-reroot.cpp。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll n;
vector<int> tree[MAXN];  // tree[u]：与 u 相邻的节点（题面给的是两条链接，按无向树存）
ll population[MAXN];     // population[u]：节点 u 的居民数
ll dist[MAXN];           // dist[u]：本轮 BFS 中 u 到医院的边数
ll answer = LLONG_MAX;   // 最小总路程

// 从 hospital 出发 BFS，返回所有居民走到 hospital 的路程和。
ll bfs_sum(ll hospital) {
    for (ll i = 1; i <= n; i++) dist[i] = -1;
    dist[hospital] = 0;

    queue<int> q;
    q.push(hospital);
    ll sum = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        sum += population[u] * dist[u];  // 住在 u 的居民各走 dist[u] 步

        for (int v : tree[u]) {
            if (dist[v] != -1) continue;  // 树中路径唯一，访问过就不再走
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll u = 1; u <= n; u++) {
        ll w, left_child, right_child;
        cin >> w >> left_child >> right_child;
        population[u] = w;

        // 0 表示没有这条链接；链接是双向的，两端都要记
        if (left_child != 0) {
            tree[u].push_back(left_child);
            tree[left_child].push_back(u);
        }
        if (right_child != 0) {
            tree[u].push_back(right_child);
            tree[right_child].push_back(u);
        }
    }

    for (ll hospital = 1; hospital <= n; hospital++) {
        answer = min(answer, bfs_sum(hospital));
    }

    cout << answer << "\n";

    return 0;
}
