/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 22:41
 * update_at: 2026-10-29 22:41
 */
// main-descent.cpp：只跑一遍 DFS 的解法（P1395 会议）。
// 一次 DFS 求出子树大小与 dist_sum[1]（所有点深度之和），
// 然后从根沿"重子树"往下走：每走一步用 dist_sum 的增量判断值是否变小，
// 走到不能再变好时停下的点就是重心，走到哪算到哪，不需要第二遍遍历。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
vector<int> g[MAXN];      // 树的邻接表
int fa[MAXN];             // 以 1 为根时的父亲
int subtree_size[MAXN];   // subtree_size[u]：以 1 为根时 u 子树内的节点数
long long dist_sum_root;  // 所有点到根 1 的距离和，等于所有点的深度之和

// 一次 DFS：记录父亲、求子树大小，顺带把深度累加成 dist_sum[1]。
void dfs(int u, int f, int dep) {
    fa[u] = f;
    subtree_size[u] = 1;
    dist_sum_root += dep;

    for (int v : g[u]) {
        if (v == f) continue;
        dfs(v, u, dep + 1);
        subtree_size[u] += subtree_size[v];
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

    dfs(1, 0, 0);

    // 从根往下走：从 u 移到儿子 v 时，距离和变化量为 n - 2 * subtree_size[v]。
    // 增量为负才变好；为 0 时距离和不变，但题目要输出编号最小的重心，
    // 这时只有 v 的编号比 u 小才值得移过去。
    int cur = 1;
    long long best_sum = dist_sum_root;
    while (true) {
        // 找出子树最大的儿子：只有它可能满足 2 * sz > n
        int heavy = 0;
        for (int v : g[cur]) {
            if (v == fa[cur]) continue;
            if (heavy == 0 || subtree_size[v] > subtree_size[heavy]) heavy = v;
        }
        if (heavy == 0) break;  // 叶子，没有儿子可走

        long long delta = (long long)n - 2LL * subtree_size[heavy];
        if (delta > 0) break;                    // 再往下走距离和会变大
        if (delta == 0 && heavy > cur) break;    // 不变大但编号更大，保留当前点
        best_sum += delta;
        cur = heavy;
    }

    cout << cur << " " << best_sum << "\n";

    return 0;
}
