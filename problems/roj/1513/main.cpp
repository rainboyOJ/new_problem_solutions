/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:37
 * update_at: 2026-10-05 05:37
 */

// 受欢迎的牛：Kosaraju 两遍 DFS 求 SCC 缩点，
// 被除自己外所有牛认可 <=> 缩点 DAG 中唯一出度为 0 的汇点，答案为该分量大小。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 50005;

typedef long long ll;

// 链式前向星：正图 g，反图 rg
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int rhead[MAXN], rto[MAXM], rnxt[MAXM], redge_cnt;

int n, m;
int comp[MAXN];     // comp[v] = 点 v 所属强连通分量编号
int out_comp[MAXN]; // out_comp[c] = 分量 c 在缩点图上是否有指向别的分量的出边
bool vis[MAXN];
int order_[MAXN];   // 第一遍 DFS 的后序序列
int order_cnt;
int stk[MAXN];      // 迭代 DFS 的显式栈：stk 存点，edge_ptr 存已走到第几条边
int edge_ptr[MAXN];
ll ans;

// 正图加边 u -> v。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 反图加边（方向取反）。
void add_redge(int u, int v) {
    redge_cnt++;
    rto[redge_cnt] = v;
    rnxt[redge_cnt] = rhead[u];
    rhead[u] = redge_cnt;
}

// 第一遍 DFS：原图上求后序序列，走完一个点的全部出边才入序。
// N 达 1e4，递归可能爆栈，用显式栈迭代实现。
void dfs_order(int s) {
    int top = 0;
    stk[top++] = s;
    edge_ptr[s] = head[s];
    vis[s] = true;
    while (top > 0) {
        int u = stk[top - 1];
        int e = edge_ptr[u];
        if (e != 0) {
            edge_ptr[u] = nxt[e]; // 记录回溯后从下一条出边继续
            int v = to[e];
            if (!vis[v]) {
                vis[v] = true;
                stk[top++] = v;
                edge_ptr[v] = head[v];
            }
        } else {
            // 出边全部走完，记入后序
            top--;
            order_cnt++;
            order_[order_cnt] = u;
        }
    }
}

// 第二遍 DFS：反图上从 s 能走到的点都属于同一个 SCC。
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
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
        add_redge(b, a);
    }

    // Kosaraju 第一遍：对每个未访问点求后序
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs_order(i);
        }
    }

    // 第二遍：按逆后序在反图上染色
    int cid = 0; // 分量编号从 1 开始，comp[v] == 0 表示未染色
    for (int i = n; i >= 1; i--) {
        int u = order_[i];
        if (comp[u] == 0) {
            cid++;
            dfs_assign(u, cid);
        }
    }

    // 扫一遍边：comp[u] != comp[v] 即缩点图上有出边，标记该分量不是汇点
    for (int u = 1; u <= n; u++) {
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (comp[u] != comp[v]) {
                out_comp[comp[u]] = 1;
            }
        }
    }

    // 汇点唯一时答案为该分量大小；有多个汇点则答案为 0
    int sink = 0;
    bool unique_sink = true;
    for (int c = 1; c <= cid; c++) {
        if (out_comp[c] == 0) {
            if (sink != 0) {
                unique_sink = false; // 出现第二个汇点
            }
            sink = c;
        }
    }

    if (!unique_sink) {
        ans = 0;
    } else {
        for (int v = 1; v <= n; v++) {
            if (comp[v] == sink) ans++;
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
