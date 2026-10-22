/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 10:20
 * update_at: 2026-10-21 10:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：直接枚举"哪些田打了井"（共 2^n 种），再枚举"选了哪些水管"（共 2^m 种，m = n(n-1)/2），
// 对每个完整方案检查"每个只连水管的连通块里都至少有一口井"，合法就更新最小花费。
// 复杂度 2^n * 2^m，n = 5 时约 3.3 万，n = 6 时约 200 万，所以只适合很小的数据；
// 它完全没有用到虚拟源点和最小生成树，因此可以和 main.cpp 独立对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10;   // 田地数上限，只服务小数据（下标 1..n，含 0 号位）
const int MAXM = 60;   // 水管边数上限，n = 10 时 m = 45
const ll INF = 1000000000;  // 足够大的"无穷"，答案最大约 n * max(W_i) = 8e5

int n;                 // 田地数
ll well_cost[MAXN];    // well_cost[i]：在第 i 块田打井的花费 W_i
ll pipe_cost[MAXN][MAXN];  // pipe_cost[i][j]：第 i、j 块田之间铺水管的费用 P_ij

int edge_u[MAXM];      // edge_u[e]：第 e 条水管的一端
int edge_v[MAXM];      // edge_v[e]：第 e 条水管的另一端
ll edge_w[MAXM];       // edge_w[e]：第 e 条水管的费用
int edge_cnt;          // 水管条数 m

int choose_edge[MAXM]; // 01 序列：choose_edge[e] = 1 表示选了第 e 条水管

ll best_cost;          // 当前搜到的最小花费

int dsu_parent[MAXN];  // 并查集父节点，只在 check() 里临时用

int dsu_find(int x) {
    while (dsu_parent[x] != x) {
        dsu_parent[x] = dsu_parent[dsu_parent[x]];
        x = dsu_parent[x];
    }
    return x;
}

// 判断当前方案是否合法：把选了的水管连起来，每个连通块里至少要有一口井。
bool check(int well_mask) {
    for (int i = 1; i <= n; i++) dsu_parent[i] = i;
    for (int e = 1; e <= edge_cnt; e++) {
        if (!choose_edge[e]) continue;
        int root_a = dsu_find(edge_u[e]);
        int root_b = dsu_find(edge_v[e]);
        if (root_a != root_b) dsu_parent[root_b] = root_a;
    }

    // has_well[root] 记录这个连通块里有没有井
    bool has_well[MAXN] = {false};
    for (int i = 1; i <= n; i++) {
        int root = dsu_find(i);
        if ((well_mask >> (i - 1)) & 1) has_well[root] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!has_well[dsu_find(i)]) return false;  // 这一块没水
    }
    return true;
}

// 一层在做一件事：决定第 dep 条水管选还是不选。
void dfs_choose_edge(int dep, int well_mask, ll well_sum, ll pipe_sum) {
    if (dep > edge_cnt) {
        if (check(well_mask) && well_sum + pipe_sum < best_cost) {
            best_cost = well_sum + pipe_sum;
        }
        return;
    }
    choose_edge[dep] = 0;
    dfs_choose_edge(dep + 1, well_mask, well_sum, pipe_sum);
    choose_edge[dep] = 1;
    dfs_choose_edge(dep + 1, well_mask, well_sum, pipe_sum + edge_w[dep]);
    choose_edge[dep] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> well_cost[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> pipe_cost[i][j];
    }

    // 建出全部水管边（只取上三角，跳过自环）
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            edge_cnt++;
            edge_u[edge_cnt] = i;
            edge_v[edge_cnt] = j;
            edge_w[edge_cnt] = pipe_cost[i][j];
        }
    }

    best_cost = INF;  // 全部打井一定可行，所以答案一定有上界
    for (int well_mask = 0; well_mask < (1 << n); well_mask++) {
        ll well_sum = 0;
        for (int i = 1; i <= n; i++) {
            if ((well_mask >> (i - 1)) & 1) well_sum += well_cost[i];
        }
        if (well_sum >= best_cost) continue;  // 光打井就比当前答案贵，没戏
        for (int e = 1; e <= edge_cnt; e++) choose_edge[e] = 0;
        dfs_choose_edge(1, well_mask, well_sum, 0);
    }

    cout << best_cost << '\n';
    return 0;
}
