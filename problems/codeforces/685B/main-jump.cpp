/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-30 15:02
 * update_at: 2026-10-30 15:02
 */
// main-jump.cpp：CF685B 的倍增跳表解法。
// 与 main.cpp 的均摊 O(n) 解法方向相反：这里沿 heavy 链「向下」跳，
// 每次查询独立 O(log n)，不依赖任何已算好的答案。
// 好处是查询之间无耦合，正是 P5666 删边后查两侧连通块所需的能力。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOGN = 20; // 2^19 = 524288 > 3e5

int n, q;
vector<int> g[MAXN];        // 邻接表（无向，dfs 时按 fa 定向）
int fa[MAXN];               // fa[u]：父亲，根的 fa 为 0
int sz[MAXN];               // sz[u]：子树大小（含自己）
int son[MAXN];              // son[u]：重儿子，叶子为 0
int up[MAXN][LOGN];         // up[u][k]：沿 heavy 链从 u 向下跳 2^k 步到达的点

// 一遍 DFS：往下填 fa，回溯时汇总 sz、选出重儿子，并顺手定下跳表第 0 层。
void dfs(int u, int p) {
    fa[u] = p;
    sz[u] = 1;
    son[u] = 0;
    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v; // sz[0] 恒为 0，叶子自然没有重儿子
    }
    up[u][0] = son[u];
}

// 求“以 u 为根、大小为 sz[u] 的子树”的一个重心。
// 沿重链向下走：只要某个方向的点还不少于子树的一半，重心必在那一侧；
// 重链上 sz 严格递减，所以“2*sz[x] >= m”沿链单调，可倍增贪心下降。
int centroid_of_subtree(int u) {
    int m = sz[u];
    for (int k = LOGN - 1; k >= 0; --k) {
        int v = up[u][k];
        if (v != 0 && sz[v] * 2 >= m) u = v; // 能跳就跳
    }
    return u; // 子节点方向都不足一半，且上方块 m - sz[u] 也不超过一半
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    dfs(1, 0);

    // 按层搭跳表：up[u][k] = up[ up[u][k-1] ][k-1]。
    // 必须外层枚举 k：第 k 层只依赖第 k-1 层。
    for (int k = 1; k < LOGN; k++) {
        for (int u = 1; u <= n; u++) {
            up[u][k] = up[up[u][k - 1]][k - 1];
        }
    }

    while (q--) {
        int v;
        cin >> v;
        cout << centroid_of_subtree(v) << '\n';
    }

    return 0;
}
