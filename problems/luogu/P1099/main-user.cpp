/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-19 09:10
 * update_at: 2026-08-19 09:10
 */
// main-user.cpp：枚举直径上所有长度不超过 s 的核区间，逐个求偏心距取最小。
// 与 main.cpp 的 O(n) 双指针不同，这里是 O(k^2) 的直白枚举（k 为直径上节点数）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

// 链式前向星：head[u] 为 u 的第一条边编号，0 表示无边
struct Edge {
    int v, w, next;
} e[MAXN * 2];
int head[MAXN], edge_cnt;

void add_edge(int u, int v, int w) {
    e[++edge_cnt] = {v, w, head[u]};
    head[u] = edge_cnt;
}

int n, s;
int st, ed;          // 直径的两个端点
int dis[MAXN];       // dis[u]：u 所在子树的高度（向下最长链长度）
int from[MAXN];      // from[u]：u 的最长链从哪个子节点延续，用来还原直径
int diameter[MAXN];  // 直径上的节点，diameter[1]=st ... diameter[dia_cnt]=ed
int dia_cnt;
bool in_diam[MAXN];  // 节点是否在直径上

int pos_st[MAXN];      // pos_st[u]：直径节点 u 到 st 的距离（直径上的坐标）
int branch_depth[MAXN]; // branch_depth[i]：直径节点 diameter[i] 挂载的直径外子树最大深度

// 返回以 u 为根能到达的最远节点，并更新 dis/from
int dfs(int u, int fa) {
    dis[u] = 0;
    int far = u;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (v == fa) continue;
        int child_far = dfs(v, u);
        if (dis[v] + e[i].w > dis[u]) {
            dis[u] = dis[v] + e[i].w;
            far = child_far;
            from[u] = v;
        }
    }
    return far;
}

// 从 u 出发不经过任何直径节点，能到达的最远距离
int dfs_branch(int u, int fa) {
    int ans = 0;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (v == fa || in_diam[v]) continue;
        ans = max(ans, dfs_branch(v, u) + e[i].w);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    // 两次最远点搜索求直径端点 st、ed
    st = dfs(1, 0);
    memset(dis, 0, sizeof(dis));
    memset(from, 0, sizeof(from));
    ed = dfs(st, 0);

    // 从 st 沿 from 一路走到 ed，得到直径上的节点序列
    for (int u = st; u; u = from[u]) {
        diameter[++dia_cnt] = u;
        in_diam[u] = true;
    }

    // 沿直径走一遍，求出每个直径节点到 st 的距离
    int cur = 0;
    for (int i = 1; i <= dia_cnt; i++) {
        pos_st[diameter[i]] = cur;
        if (i < dia_cnt) {
            for (int j = head[diameter[i]]; j; j = e[j].next) {
                if (e[j].v == diameter[i + 1]) {
                    cur += e[j].w;
                    break;
                }
            }
        }
    }
    int diameter_len = cur; // 直径长度 = st 到 ed 的距离

    // 预先把每个直径节点的分支最大深度算好
    for (int i = 1; i <= dia_cnt; i++) {
        branch_depth[i] = dfs_branch(diameter[i], 0);
    }

    int ans = INT_MAX;

    // 枚举直径上的核区间 [i,j]，要求长度不超过 s
    for (int i = 1; i <= dia_cnt; i++) {
        for (int j = i; j <= dia_cnt; j++) {
            // 直径上两点的距离 = 到 st 的距离差
            if (pos_st[diameter[j]] - pos_st[diameter[i]] > s) continue;

            // 偏心距 = max(st 到 i, j 到 ed, 区间内分支最大深度)
            int ecc = max(pos_st[diameter[i]], diameter_len - pos_st[diameter[j]]);
            for (int k = i; k <= j; k++) {
                ecc = max(ecc, branch_depth[k]);
            }
            ans = min(ans, ecc);
        }
    }

    cout << ans << endl;
    return 0;
}