/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 22:55
 * update_at: 2026-10-29 22:55
 */
// main-reroot.cpp：加权换根 DP，O(n)（P1364 医院设置）。
// 第一次 DFS 求出以 1 为根时每个点的子树居民数 subtree_pop[] 和根上的总路程 dist_sum[1]，
// 第二次 DFS 沿父子边递推：把医院从 u 挪到儿子 v，v 子树内的居民少走一步、
// 其余居民多走一步，于是 dist_sum[v] = dist_sum[u] + total_pop - 2 * subtree_pop[v]。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll n;
vector<int> tree[MAXN];  // 无向邻接表
ll population[MAXN];     // population[u]：节点 u 的居民数
ll subtree_pop[MAXN];    // subtree_pop[u]：以 1 为根时 u 子树内的居民总数
ll dist_sum[MAXN];       // dist_sum[u]：所有居民走到 u 的总路程
ll total_pop;            // 全树居民总数

// 第一次 DFS：算出子树居民数，同时把每个居民到根 1 的路程累进 dist_sum[1]。
void dfs_subtree(ll u, ll parent, ll depth) {
    subtree_pop[u] = population[u];
    dist_sum[1] += population[u] * depth;

    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs_subtree(v, u, depth + 1);
        subtree_pop[u] += subtree_pop[v];
    }
}

// 第二次 DFS：换根递推，把每个点的总路程都推出来。
void dfs_reroot(ll u, ll parent) {
    for (int v : tree[u]) {
        if (v == parent) continue;

        // 挪一步的代价变化：v 子树内的居民各少走 1 步，其余居民各多走 1 步
        dist_sum[v] = dist_sum[u] - subtree_pop[v] + (total_pop - subtree_pop[v]);
        dfs_reroot(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll u = 1; u <= n; u++) {
        ll w, left_child, right_child;
        cin >> w >> left_child >> right_child;
        population[u] = w;
        total_pop += w;

        if (left_child != 0) {
            tree[u].push_back(left_child);
            tree[left_child].push_back(u);
        }
        if (right_child != 0) {
            tree[u].push_back(right_child);
            tree[right_child].push_back(u);
        }
    }

    dfs_subtree(1, 0, 0);
    dfs_reroot(1, 0);

    // 全部点的总路程都算出来了，扫一遍取最小
    ll answer = dist_sum[1];
    for (ll u = 2; u <= n; u++) {
        answer = min(answer, dist_sum[u]);
    }

    cout << answer << "\n";

    return 0;
}
