/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:50
 * update_at: 2026-10-05 05:50
 */

// main.cpp：roj 1516「一本通 3.5 练习 2」消息的传递
// 互相可达的奸细属于同一个传播单元，先 Kosaraju 求强连通分量并缩点，
// 缩点得到 DAG 后，入度为 0 的分量没有人能传消息进来，必须各选一个起点；
// 其余分量沿入边逆推必定停在某个源点分量，所以答案就是入度为 0 的分量个数。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 1000005; // 边数最多 n^2 = 1e6

typedef long long ll;

// 链式前向星：正图为 head/to/nxt，反图为 rhead/rto/rnxt
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int rhead[MAXN], rto[MAXM], rnxt[MAXM], redge_cnt;

ll n;
int comp[MAXN];     // comp[v] = 点 v 所属的强连通分量编号，0 表示还没染色
int has_in[MAXN];   // has_in[c] = 分量 c 在缩点 DAG 中是否存在入边
bool vis[MAXN];     // 第一遍 DFS 的访问标记
int order_[MAXN];   // 第一遍 DFS 按离开时间记录的后序序列
int order_cnt;
int stk[MAXN];      // 迭代 DFS 的显式栈，保存当前搜索路径上的点
int edge_ptr[MAXN]; // edge_ptr[u] = 点 u 下一条待走的出边编号
ll ans;

// 正图加一条 u -> v 的边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 反图加一条 u -> v 的边，对应正图中的 v -> u。
void add_redge(int u, int v) {
    redge_cnt++;
    rto[redge_cnt] = v;
    rnxt[redge_cnt] = rhead[u];
    rhead[u] = redge_cnt;
}

// Kosaraju 第一遍：在正图上 DFS，一个点的全部出边走完才记入后序序列。
// n 最大 1000，用显式栈迭代实现，避免依赖递归深度。
void dfs_order(int s) {
    int top = 0;
    stk[top++] = s;
    vis[s] = true;
    edge_ptr[s] = head[s];
    while (top > 0) {
        int u = stk[top - 1];
        int e = edge_ptr[u];
        if (e != 0) {
            edge_ptr[u] = nxt[e]; // 回溯到 u 时从下一条出边继续
            int v = to[e];
            if (!vis[v]) {
                vis[v] = true;
                edge_ptr[v] = head[v];
                stk[top++] = v;
            }
        } else {
            // 出边全部走完，点 u 可以确定后序位置
            top--;
            order_cnt++;
            order_[order_cnt] = u;
        }
    }
}

// Kosaraju 第二遍：按后序倒序在反图上 DFS，每棵 DFS 树就是一个强连通分量。
void dfs_assign(int s, int cid) {
    int top = 0;
    stk[top++] = s;
    comp[s] = cid;
    while (top > 0) {
        int u = stk[--top];
        for (int e = rhead[u]; e != 0; e = rnxt[e]) {
            int v = rto[e];
            if (comp[v] == 0) {
                comp[v] = cid;
                stk[top++] = v;
            }
        }
    }
}

void solve() {
    cin >> n;

    // 读入 n x n 的传递矩阵：矩阵里为 1 表示 i 能直接传给 j，同时建正图和反图
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            if (x == 1) {
                add_edge(i, j);
                add_redge(j, i);
            }
        }
    }

    // 第一遍：正图上求每个点的后序
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs_order(i);
        }
    }

    // 第二遍：按后序倒序在反图上染强连通分量编号，编号从 1 开始
    int cid = 0;
    for (int i = order_cnt; i >= 1; i--) {
        int u = order_[i];
        if (comp[u] == 0) {
            cid++;
            dfs_assign(u, cid);
        }
    }

    // 扫跨分量边，给目标分量记入度；分量内部的边（含自环）不算入度
    for (int u = 1; u <= n; u++) {
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (comp[u] != comp[v]) {
                has_in[comp[v]] = 1;
            }
        }
    }

    // 缩点 DAG 中入度为 0 的分量各需要一个起点
    ans = 0;
    for (int c = 1; c <= cid; c++) {
        if (has_in[c] == 0) {
            ans++;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
