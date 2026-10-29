/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 22:55
 * update_at: 2026-10-29 22:55
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 枚举每个节点当医院，从这个点出发做一次带深度的 DFS，把 Σ 居民 × 深度 全部算出来取最小。
// 复杂度 O(n^2)，只有 n <= 100 这种规模才跑得动。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll n;
vector<int> tree[MAXN];  // 无向邻接表
ll population[MAXN];     // population[u]：节点 u 的居民数
bool visited[MAXN];      // visited[u]：本轮 DFS 是否已经走过 u
ll answer = LLONG_MAX;   // 最小总路程

// 从 u 出发往下 DFS，depth 是 u 到医院的步数；返回这棵子树的居民总路程。
ll dfs_sum(ll u, ll depth) {
    visited[u] = true;
    ll sum = population[u] * depth;

    for (int v : tree[u]) {
        if (visited[v]) continue;
        sum += dfs_sum(v, depth + 1);
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
        for (ll i = 1; i <= n; i++) visited[i] = false;
        answer = min(answer, dfs_sum(hospital, 0));
    }

    cout << answer << "\n";

    return 0;
}
