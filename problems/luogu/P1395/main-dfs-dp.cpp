/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-16 00:40
 * update_at: 2026-08-16 00:40
 */
// main-dfs-dp.cpp：换根 DP 的两次 DFS 实现（P1395 会议）。
// 第一次 DFS 求子树大小与 dist_sum[1]（所有点深度之和），
// 第二次 DFS 沿父子边用换根公式递推全部点的距离和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
vector<int> g[MAXN];      // 树的邻接表
int subtree_size[MAXN];   // subtree_size[u]：以 1 为根时 u 子树内的节点数
long long dist_sum[MAXN]; // dist_sum[u]：所有节点到 u 的距离和

// 第一次 DFS：求子树大小，并累加深度得到 dist_sum[1]。
// dep 表示 u 的深度，根 1 的深度为 0。
void dfs_subtree(int u, int fa, int dep) {
    subtree_size[u] = 1;
    dist_sum[1] += dep;

    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs_subtree(v, u, dep + 1);
        subtree_size[u] += subtree_size[v];
    }
}

// 第二次 DFS：换根递推，从 u 移到儿子 v 时用公式推 dist_sum[v]。
void dfs_reroot(int u, int fa) {
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;

        // 换根公式：v 子树内 subtree_size[v] 个点距离各 -1，
        // 其余 n - subtree_size[v] 个点距离各 +1。
        dist_sum[v] = dist_sum[u] + (long long)n - 2LL * subtree_size[v];
        dfs_reroot(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_subtree(1, 0, 0);
    dfs_reroot(1, 0);

    // 距离和取最小；距离和相等时保留编号最小的点（只严格小于才更新）。
    int best_node = 1;
    long long best_sum = dist_sum[1];
    for (int i = 2; i <= n; i++) {
        if (dist_sum[i] < best_sum) {
            best_sum = dist_sum[i];
            best_node = i;
        }
    }

    cout << best_node << " " << best_sum << "\n";

    return 0;
}
