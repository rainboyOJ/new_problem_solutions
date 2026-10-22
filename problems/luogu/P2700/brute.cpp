/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 21:40
 * update_at: 2026-10-21 21:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：直接枚举「每条公路破坏还是保留」（共 2^(n-1) 种方案），
// 对每个完整方案把保留的边连起来，检查 K 个敌城是否两两不连通，合法就更新最小代价。
// 复杂度 2^(n-1) * n，n = 10 时约 500 次叶子检查，只适合很小的数据；
// 它完全没有用到「按边权降序 + 并查集」的正解思路，因此可以和 main.cpp 独立对拍。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 15;  // 城市数上限，只服务小数据（n <= 10）

int n;               // 城市数
int k;               // 被敌军占领的城市数
bool is_enemy[MAXN]; // is_enemy[x]：城市 x 是否被敌军占领

int edge_u[MAXN];    // edge_u[e]：第 e 条公路的一端
int edge_v[MAXN];    // edge_v[e]：第 e 条公路的另一端
ll edge_w[MAXN];     // edge_w[e]：破坏第 e 条公路的代价

int choose[MAXN];    // 01 序列：choose[e] = 1 表示破坏第 e 条公路，0 表示保留

ll best_cost;        // 当前搜到的最小破坏代价

int dsu_parent[MAXN];  // 并查集父节点，只在 check() 里临时用

int dsu_find(int x) {
    while (dsu_parent[x] != x) {
        dsu_parent[x] = dsu_parent[dsu_parent[x]];
        x = dsu_parent[x];
    }
    return x;
}

// 检查当前方案是否合法：把保留的公路连起来，K 个敌城必须落在 K 个不同的连通块里。
bool check() {
    for (int i = 0; i < n; i++) dsu_parent[i] = i;
    for (int e = 1; e <= n - 1; e++) {
        if (choose[e]) continue;  // 这条公路被破坏了，不参与连通
        int root_a = dsu_find(edge_u[e]);
        int root_b = dsu_find(edge_v[e]);
        if (root_a != root_b) dsu_parent[root_b] = root_a;
    }

    // 把每个敌城所在连通块的根记下来，出现重复根就说明两队敌军还连着
    bool used_root[MAXN] = {false};
    for (int i = 0; i < n; i++) {
        if (!is_enemy[i]) continue;
        int root = dsu_find(i);
        if (used_root[root]) return false;
        used_root[root] = true;
    }
    return true;
}

// 一层在做一件事：决定第 dep 条公路破坏还是保留。
void dfs_choose(int dep) {
    if (dep > n - 1) {
        // 完整方案已生成，先检查合法性，再算代价并更新答案
        if (!check()) return;
        ll cost = 0;
        for (int e = 1; e <= n - 1; e++) {
            if (choose[e]) cost += edge_w[e];
        }
        if (cost < best_cost) best_cost = cost;
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs_choose(dep + 1);
    }
    choose[dep] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        int city;
        cin >> city;
        is_enemy[city] = true;
    }
    for (int e = 1; e <= n - 1; e++) {
        cin >> edge_u[e] >> edge_v[e] >> edge_w[e];
    }

    best_cost = 1LL << 60;  // 全破坏一定合法，所以答案有上界
    dfs_choose(1);
    cout << best_cost << '\n';
    return 0;
}
