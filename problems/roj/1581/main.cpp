/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:02
 * update_at: 2026-10-05 10:02
 */
// main.cpp：两遍树形 DP 求树的直径，并输出所有位于最长路径上的节点。
// 做法：以 0 为根，自底向上求每个点子树内最长链 d1、次长链 d2（不同子树分支），
// 自顶向下求每个点向上的最长链 up；经过 u 的最长路径为 d1[u] + max(up[u], d2[u])，
// 等于直径 D 的点即为答案。
#include <bits/stdc++.h>
using namespace std;

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-03-19 10:51
 * update_at: 2026-03-19 10:51
 */

typedef long long ll;

const int MAXN = 2e5 + 5;

int n;
vector<int> g[MAXN]; // g[u] = 节点 u 的相邻节点列表（无向树）
int parent[MAXN];    // BFS 后每个点的父节点，根的父节点为 -1
int order[MAXN];     // BFS 得到的拓扑分层序列，用于两遍扫描
ll d1[MAXN];         // d1[u]：u 在自己子树内向下延伸的最长链长度
ll d2[MAXN];         // d2[u]：u 子树内与最长链不同分支的次长链长度
int c1[MAXN];        // c1[u]：取得 d1[u] 的那个子节点
ll up[MAXN];         // up[u]：从 u 出发先向上走向父节点方向的最长链长度

// BFS 建立以 0 为根的父指针关系与遍历顺序，避免递归爆栈
void bfs_order() {
    for (int i = 0; i < n; i++) parent[i] = -1;
    int head = 0, tail = 0;
    order[tail++] = 0;
    parent[0] = -1;
    while (head < tail) {
        int u = order[head++];
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent[u]) continue;
            parent[v] = u;
            order[tail++] = v;
        }
    }
}

// 第一遍：逆序 BFS 序自底向上，计算 d1、d2、c1
void dp_bottom_up() {
    for (int i = 0; i < n; i++) {
        d1[i] = 0;
        d2[i] = 0;
        c1[i] = -1;
    }
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) continue;
            ll w = d1[v] + 1; // 从 u 经子节点 v 向下走一步能达到的链长
            if (w > d1[u]) {  // 比最长链更长：原最长链降级为次长链
                d2[u] = d1[u];
                d1[u] = w;
                c1[u] = v;
            } else if (w > d2[u]) { // 只比次长链更长：更新次长链
                d2[u] = w;
            }
        }
    }
}

// 第二遍：正序 BFS 序自顶向下，计算每个点向上的最长链 up
void dp_top_down() {
    up[0] = 0;
    for (int i = 0; i < n; i++) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) continue;
            // v 往上看：要么父节点继续向上，要么父节点拐进其它子树方向
            ll best_down = (c1[u] == v) ? d2[u] : d1[u];
            up[v] = max(up[u] + 1, best_down + 1);
        }
    }
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs_order();
    dp_bottom_up();
    dp_top_down();

    // 直径 D = 所有点的 d1 + up 的最大值
    ll diameter = 0;
    for (int i = 0; i < n; i++) diameter = max(diameter, d1[i] + up[i]);

    // 经过 u 的最长路径：向下最长链 + max(向上链, 子树内次长链)，等于 D 即在最长路径上
    for (int i = 0; i < n; i++) {
        ll longest_through = d1[i] + max(up[i], d2[i]);
        if (longest_through == diameter) printf("%d\n", i);
    }
    return 0;
}
