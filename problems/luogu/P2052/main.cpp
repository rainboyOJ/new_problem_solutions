/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-20 11:28
 * update_at: 2026-10-24 11:09
 */
// P2052 [NOI2011] 道路修建
// 两次 DFS：dfs_build 把无根树根化（记下每个点的父亲），
// dfs_calc 后序回推子树大小，并累加每条父子边的修建费用。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 5; // 国家数上限

typedef long long ll;

struct edge {
    int to; // 另一端点
    ll w;   // 道路长度（边权）
};

ll n;                // 国家数
vector<edge> g[maxn]; // g[u] 存与 u 直接相连的所有道路
int parent_arr[maxn]; // parent_arr[u] 是 u 在根化后的父亲，根的值为 0
int subtree_size[maxn]; // subtree_size[u] 是以 u 为根的子树点数
ll ans;                 // 所有道路的修建费用之和

// 第一次 DFS：以 1 号点为根，先序建出父子关系。
void dfs_build(int u) {
    for (const edge& e : g[u]) {
        if (e.to == parent_arr[u]) continue; // 跳过父亲，避免走回上一步
        parent_arr[e.to] = u;
        dfs_build(e.to);
    }
}

// 第二次 DFS：后序求子树大小。
// 断开父子边 (u, v) 后，v 一侧有 subtree_size[v] 个点，
// u 一侧有 n - subtree_size[v] 个点，
// 这条边的费用 = e.w * |n - 2 * subtree_size[v]|。
void dfs_calc(int u) {
    subtree_size[u] = 1; // 只算自己
    for (const edge& e : g[u]) {
        if (e.to == parent_arr[u]) continue;
        dfs_calc(e.to);
        subtree_size[u] += subtree_size[e.to];
        ans += e.w * llabs(n - 2LL * subtree_size[e.to]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    parent_arr[1] = 0; // 1 号点为根
    dfs_build(1);
    dfs_calc(1);

    cout << ans << '\n';

    return 0;
}
