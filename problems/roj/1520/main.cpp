/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:57
 * update_at: 2026-10-05 05:57
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;   // 草场数上限
const int MAXM = 20005;  // 边数上限（2 * R）

typedef long long ll;

int n, m;
int head[MAXN], nxt[MAXM], to[MAXM], edge_cnt = 1; // 链式前向星，edge_cnt 从 1 开始，2/3、4/5 互为反向边
int dfn[MAXN], low[MAXN], timer_cnt;  // Tarjan 时间戳与 low 值
int dcc[MAXN], dcc_cnt;               // dcc[i] 表示点 i 所属的边双连通分量编号
int stk[MAXN], top_stk;               // Tarjan 栈，保存当前搜索树上的点
int deg[MAXN];                        // 缩点后每个分量的度数

// 加一条无向边（成对存，反向边编号 = 边编号 xor 1）。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// Tarjan 求边双连通分量：in_edge 记录来向边的编号，这样重边不会被当成反向边跳过。
void dfs(int u, int in_edge) {
    timer_cnt++;
    dfn[u] = low[u] = timer_cnt;
    top_stk++;
    stk[top_stk] = u; // 点进栈，出栈时机是该点所属分量被确定

    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (dfn[v] == 0) { // 树边
            dfs(v, i);
            if (low[v] < low[u]) low[u] = low[v];
        }
        else if (i != (in_edge ^ 1)) { // 非树边且不是来向边的反向边（允许重边）
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }

    // low[u] == dfn[u] 说明 u 是该边双连通分量中最早的点，弹出整个分量
    if (low[u] == dfn[u]) {
        dcc_cnt++;
        while (top_stk > 0) {
            int x = stk[top_stk];
            top_stk--;
            dcc[x] = dcc_cnt;
            if (x == u) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 0); // 题目保证原图连通，从 1 号点出发一次即可

    // 枚举每条边，统计缩点后（分量树）各点的度数
    for (int i = 2; i <= edge_cnt; i += 2) {
        int u = to[i ^ 1], v = to[i]; // 第 i 条边的两个端点
        if (dcc[u] != dcc[v]) {
            deg[dcc[u]]++;
            deg[dcc[v]]++;
        }
    }

    // 度数为 1 的分量就是缩点后树上的叶子，设叶子数为 L，答案为 (L + 1) / 2
    int leaf = 0;
    for (int i = 1; i <= dcc_cnt; i++) {
        if (deg[i] == 1) leaf++;
    }
    cout << (leaf + 1) / 2 << endl;

    return 0;
}
