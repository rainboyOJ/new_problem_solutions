/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:41
 * update_at: 2026-10-03 10:48
 */
// main.cpp：洛谷 P2169 正则表达式
//
// 关键建模：题目说的“A 和 B 处于同一局域网”，正确理解是「A、B 互相可达」
// （A 能走到 B，B 也能走到 A），也就是图论里的强连通。局域网内传输耗时 0。
//
// 为什么不是“只有直接互相有边才免费”？
//   对于 A->B->C->A 这样的三元环，任意两点间都没有直接的反向边，
//   但任意两点确实互相可达。题目样例 2 正是这种图：
//       1->2(1), 2->3(6), 3->4(1), 4->2(1), 3->5(2)
//   全图没有任何一对点存在双向边；若按“直接反向边才免费”算，答案是 9，
//   而官方答案是 3（1->2 花 1，2 到 3 免费，3->5 花 2）。
//   可见“同一局域网”必须按互相可达（强连通分量）来理解。
//
// 于是算法分三步：
//   1. Tarjan 求出所有强连通分量（SCC），每个分量就是一个“局域网”；
//   2. 把每个分量缩成一个点，分量内部的边权视为 0，跨分量的边保留原权；
//   3. 在缩点后的 DAG 上用堆优化 Dijkstra 求 belong[1] 到 belong[n] 的最短路。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 5;
const int maxm = 1e6 + 5;
const ll INF = 1e18;

int n, m;

/* ---------- 原图：链式前向星存边 ---------- */
int head[maxn], nxt[maxm], to[maxm], w[maxm], ecnt;

/* ---------- Tarjan 求强连通分量 ---------- */
int dfn[maxn];             // 时间戳，0 表示还没访问过
int low[maxn];             // 能回溯到的最小时间戳
int belong[maxn];          // belong[u]：点 u 属于哪个强连通分量
int stk[maxn], top;        // 手写栈，保存当前还没定分量的点
bool in_stack[maxn];       // 点是否在栈中
int dfs_clock, scc_cnt;

/* 手写 DFS 用的两个栈（Tarjan 迭代版）。
   n 最大 2e5，递归 Tarjan 在链状图上会压到 2e5 层，直接爆栈，
   所以这里用显式栈把递归改成循环：
   dfs_stk_u[i]：第 i 层正在访问的结点；dfs_stk_e[i]：它下一条要处理的边 */
int dfs_stk_u[maxn], dfs_stk_e[maxn], dfs_stk_top;

/* ---------- 缩点后的新图 ---------- */
int nhead[maxn], nnxt[maxm], nto[maxm], nw[maxm], ne_cnt;

/* ---------- Dijkstra ---------- */
ll dist[maxn];             // 从 belong[1] 出发的最短路
bool done[maxn];           // 该点是否已经确定最短路

priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > pq;

void add_edge(int u, int v, int c) {
    ecnt++;
    to[ecnt] = v;
    w[ecnt] = c;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void add_new_edge(int u, int v, int c) {
    ne_cnt++;
    nto[ne_cnt] = v;
    nw[ne_cnt] = c;
    nnxt[ne_cnt] = nhead[u];
    nhead[u] = ne_cnt;
}

// 迭代版 Tarjan：dfn/low 打时间戳，栈里同一个 low 值的点构成一个强连通分量
void tarjan(int root) {
    dfs_stk_top = 0;
    dfs_clock++;
    dfn[root] = dfs_clock;
    low[root] = dfs_clock;
    top++; stk[top] = root; in_stack[root] = true;
    dfs_stk_top++;
    dfs_stk_u[dfs_stk_top] = root;
    dfs_stk_e[dfs_stk_top] = head[root];

    while (dfs_stk_top > 0) {
        int u = dfs_stk_u[dfs_stk_top];
        int e = dfs_stk_e[dfs_stk_top];

        if (e != 0) {
            // 先记下一条边，下次循环继续；这一句等价于递归版 for 循环的 e = nxt[e]
            dfs_stk_e[dfs_stk_top] = nxt[e];
            int v = to[e];
            if (dfn[v] == 0) {
                // v 没访问过：手动“递归”进入 v
                dfs_clock++;
                dfn[v] = dfs_clock;
                low[v] = dfs_clock;
                top++; stk[top] = v; in_stack[v] = true;
                dfs_stk_top++;
                dfs_stk_u[dfs_stk_top] = v;
                dfs_stk_e[dfs_stk_top] = head[v];
            } else if (in_stack[v]) {
                // v 在栈中说明它和 u 还在同一个分量里，可以用 dfn[v] 更新 low
                if (dfn[v] < low[u]) low[u] = dfn[v];
            }
        } else {
            // u 的边全部处理完，模拟递归返回
            dfs_stk_top--;
            if (dfs_stk_top > 0) {
                int p = dfs_stk_u[dfs_stk_top];   // 父结点
                if (low[u] < low[p]) low[p] = low[u];
            }
            // low[u] == dfn[u]：u 是这个分量的“根”，把栈里的点弹出来
            if (low[u] == dfn[u]) {
                scc_cnt++;
                while (true) {
                    int v = stk[top];
                    top--;
                    in_stack[v] = false;
                    belong[v] = scc_cnt;
                    if (v == u) break;
                }
            }
        }
    }
}

void dijkstra() {
    for (int i = 1; i <= scc_cnt; i++) {
        dist[i] = INF;
        done[i] = false;
    }
    int s = belong[1];
    dist[s] = 0;
    pq.push(make_pair(0LL, s));

    while (!pq.empty()) {
        pair<ll, int> cur = pq.top();
        pq.pop();
        int u = cur.second;
        if (done[u]) continue;      // 懒删除：过期的堆元素直接跳过
        done[u] = true;

        for (int e = nhead[u]; e != 0; e = nnxt[e]) {
            int v = nto[e];
            if (dist[u] + nw[e] < dist[v]) {
                dist[v] = dist[u] + nw[e];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        add_edge(u, v, c);
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) tarjan(i);
    }

    // 缩点：分量内部的边不用加（耗时 0），只保留跨分量的边
    for (int u = 1; u <= n; u++) {
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (belong[u] != belong[v]) {
                add_new_edge(belong[u], belong[v], w[e]);
            }
        }
    }

    dijkstra();
    printf("%lld\n", dist[belong[n]]);
    return 0;
}
