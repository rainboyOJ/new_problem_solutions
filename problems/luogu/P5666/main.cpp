/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:34
 * update_at: 2026-10-30 14:12
 */
// main.cpp：对每条边断开，用“沿最大子树方向倍增”求两侧连通块的重心编号和。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300005;
const int LOGN = 20; // 2^19 > 3e5，跳表需要 0..19 共 20 层

int n;
vector<int> g[MAXN];          // 邻接表存树
int sz[MAXN];                 // 当前定向下以 i 为根的子树大小（定向根的大小为 n）
int fa[MAXN];                 // 当前定向下 i 的父节点
int son[MAXN];                // 初始定向下 i 的最大子节点（重儿子）
int jump_table[MAXN][LOGN];   // jump_table[i][k]：沿 heavy 链向下跳 2^k 步到达的点
ll answer;                    // 所有边断开后两侧重心编号和的总和

// 重新构建节点 u 的倍增表。换根只会改变 u 一层的 heavy 方向，其余节点不变。
void rebuild_jump(int u) {
    for (int k = 1; k < LOGN; k++) {
        jump_table[u][k] = jump_table[jump_table[u][k - 1]][k - 1];
    }
}

// 求“以 root 为根、大小为 sz[root] 的连通块”的重心编号和（重心可能有 1 或 2 个）。
// 从 root 出发沿最大子树方向下降，走到最后一个满足“子树不小于一半”的节点；
// 若最大子树恰好为一半，说明它和父节点是两个重心，两个编号都要计入。
void add_centroid_sum(int root) {
    int total = sz[root];
    int u = root;

    // 倍增贪心：大步到小步，能跳就跳（子树大小不小于 half）。
    for (int k = LOGN - 1; k >= 0; k--) {
        int v = jump_table[u][k];
        if (v != 0 && sz[v] * 2 >= total) {
            u = v;
        }
    }

    answer += u;
    if (sz[u] * 2 == total) {
        answer += fa[u];
    }
}

// 求节点 u 在当前定向下最大、次大的相邻组件大小对应的邻居。
// first/second 用于换根时把 v 排除后重选 u 的最大子树方向。
void largest_two(int u, int& first, int& second) {
    first = second = 0;
    for (auto v : g[u]) {
        if (sz[v] >= sz[first]) {
            second = first;
            first = v;
        } else if (sz[v] >= sz[second]) {
            second = v;
        }
    }
}

// 第一遍 DFS：以 1 为根填 fa，回溯时汇总 sz 并选出重儿子。
void dfs_init(int u, int p) {
    fa[u] = p;
    sz[u] = 1;
    son[u] = 0;
    for (auto v : g[u]) {
        if (v == p) {
            continue;
        }
        dfs_init(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}

// 第二遍：换根 DFS 枚举每条边，统计两侧重心。
//
// 进入 v 的子树前把 v 临时当根：u 的 heavy 方向换成“除 v 外最大的邻居”，
// sz[u]、sz[v]、fa 同步改；递归回来后再逆操作恢复。
// 因为切边只影响 u 一个点，其余节点零修改，所以每条边只需一次换根 + 一次恢复。
void dfs_reroot(int u, int p) {
    // 当前定向下 u 的最大、次大相邻组件，用于把某个儿子排除后重选 heavy 方向。
    int first, second;
    largest_two(u, first, second);

    for (auto v : g[u]) {
        if (v == p) {
            continue;
        }

        // 边 (u, v) 断开后，v 一侧就是当前定向下 v 的子树，直接求重心。
        add_centroid_sum(v);

        // 保存现场，准备把 v 临时变成定向根。
        int save_fa_u = fa[u], save_fa_v = fa[v];
        int save_sz_u = sz[u], save_sz_v = sz[v];
        int save_jump0_u = jump_table[u][0];

        // 换根：u 的 heavy 方向变成“除 v 外最大的相邻组件”。
        jump_table[u][0] = (v == first) ? second : first;
        rebuild_jump(u);
        sz[u] -= sz[v];
        sz[v] += sz[u];

        // u 一侧是“补树”（整棵树去掉 v 的子树），求重心。
        add_centroid_sum(u);

        // 更新父指针，进入 v 的子树继续枚举。
        fa[u] = v;
        fa[v] = p;
        dfs_reroot(v, u);

        // 恢复现场，回到“u 是当前定向根”的状态，继续处理 u 的下一个儿子。
        fa[u] = save_fa_u;
        fa[v] = save_fa_v;
        sz[u] = save_sz_u;
        sz[v] = save_sz_v;
        jump_table[u][0] = save_jump0_u;
        rebuild_jump(u);
    }
}

// 处理单组测试数据：读入、预处理、换根枚举每条边并累加重心编号和。
void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        sz[i] = 1;
        fa[i] = 0;
        son[i] = 0;
        for (int k = 0; k < LOGN; k++) {
            jump_table[i][k] = 0;
        }
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 第一遍：以 1 为根求 fa、sz、son。
    dfs_init(1, 0);

    // 构建初始倍增表：jump_table[u][0] 就是 heavy 方向。
    // 必须按层构建：第 k 层只依赖第 k-1 层，保证任意节点的下层都已完成。
    for (int u = 1; u <= n; u++) {
        jump_table[u][0] = son[u];
    }
    for (int k = 1; k < LOGN; k++) {
        for (int u = 1; u <= n; u++) {
            jump_table[u][k] = jump_table[jump_table[u][k - 1]][k - 1];
        }
    }

    // 第二遍：换根 DFS 枚举每条边。
    answer = 0;
    dfs_reroot(1, 0);

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
