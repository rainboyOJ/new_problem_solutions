/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:12
 * update_at: 2026-10-05 06:12
 */
// main.cpp：Tarjan 求无向图割边（桥）数量，用边编号处理重边，用显式栈避免递归爆栈。
#include <cstdio>

const int MAXN = 30005; // 星球（节点）数量上限
const int MAXM = 60015; // 无向边拆成两条有向边后的数量上限

typedef long long ll;

int head[MAXN]; // head[u] 是节点 u 的第一条出边编号，链式前向星
int to[MAXM];   // to[e] 是有向边 e 的终点
int nxt[MAXM];  // nxt[e] 是边 e 的下一条兄弟边
int edge_id[MAXM]; // edge_id[e] 是该有向边所属无向边的唯一编号，用来区分反向边与重边
int edge_cnt;

int dfn[MAXN]; // dfn[u] 是节点 u 在 DFS 中的访问时间戳
int low[MAXN]; // low[u] 是 u 子树内经至多一条返祖边能到达的最小时间戳
int timer;

// DFS 显式栈的一帧：节点 u、进入 u 的边编号 in_edge、正在扫描的出边编号 cur_edge
struct Frame {
    int u;
    int in_edge;
    int cur_edge;
};

Frame stk[MAXN]; // 显式栈，链状图上深度可达 30000，递归会爆栈
int top;

ll m; // 星球数（节点数）
ll n; // 航道数（边数）

// 加入一条从 u 到 v 的有向边，两侧由同一个无向边编号绑定。
void add_edge(int u, int v, int id) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_id[edge_cnt] = id;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 用迭代式 Tarjan 算法统计当前图的割边数量。
ll count_bridges() {
    ll bridges = 0; // 割边数量
    timer = 0;
    for (int i = 1; i <= m; i++) {
        dfn[i] = 0;
        low[i] = 0;
    }

    // 图可能不连通，每个未访问节点都作为一棵 DFS 树的根
    for (int s = 1; s <= m; s++) {
        if (dfn[s] != 0) continue;
        timer++;
        dfn[s] = low[s] = timer;
        top = 0;
        stk[top].u = s;
        stk[top].in_edge = 0;
        stk[top].cur_edge = head[s];
        top++;

        while (top > 0) {
            Frame &f = stk[top - 1];
            int u = f.u;
            if (f.cur_edge != 0) {
                int e = f.cur_edge;
                f.cur_edge = nxt[e];
                int v = to[e];
                if (edge_id[e] == f.in_edge) continue; // 同一条无向边的反向边，跳过
                if (dfn[v] != 0) {
                    // 返祖边（含重边）：用 dfn[v] 更新 low[u]
                    if (dfn[v] < low[u]) low[u] = dfn[v];
                } else {
                    // 树边：访问 v，把 v 入栈
                    timer++;
                    dfn[v] = low[v] = timer;
                    stk[top].u = v;
                    stk[top].in_edge = edge_id[e];
                    stk[top].cur_edge = head[v];
                    top++;
                }
            } else {
                top--; // u 的邻边扫描完毕，出栈并回溯
                if (top > 0) {
                    int p = stk[top - 1].u;
                    if (low[u] < low[p]) low[p] = low[u];
                    // v 子树无法回到 p 或更早的祖先，树边 (p, u) 是割边
                    if (low[u] > dfn[p]) bridges++;
                }
            }
        }
    }

    return bridges;
}

void solve() {
    while (scanf("%lld %lld", &m, &n) == 2) {
        if (m == 0) break; // 以一行 0 结束（样例为 0 0）
        edge_cnt = 0;
        for (int i = 1; i <= m; i++) head[i] = 0;
        for (int i = 1; i <= n; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            add_edge(a, b, i);
            add_edge(b, a, i);
        }
        printf("%lld\n", count_bridges());
    }
}

int main() {
    solve();
    return 0;
}
