/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 08:30
 * update_at: 2026-10-09 08:48
 */
// main.cpp：2-SAT。每党恰选 1 人 + 互相厌恶者不能同选。
// 用迭代版 Tarjan 求 SCC，避免 n=8000 的长链上递归爆栈（数据里最深链 16000 层）。
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXV = 16005; // 2 * 8000 + 余量：每个代表是 2-SAT 图上的一个结点
const int MAXE = 40005; // 2 * 20000 + 余量：每个厌恶对贡献两条蕴含边

int head[MAXV];    // 链式前向星：结点 u 的第一条出边编号
int to_edge[MAXE]; // 第 i 条边指向的结点编号
int nxt[MAXE];     // 第 i 条边的下一条兄弟边编号
int edge_cnt;      // 已加入的边数

int dfn[MAXV]; // Tarjan 时间戳，0 表示结点还没被访问过
int low[MAXV]; // Tarjan 追溯值：所在 SCC 能回溯到的最小 dfn
int scc[MAXV]; // 结点所属强连通分量编号（按完成序编号，天然是缩点 DAG 拓扑序的逆序）
int timer;     // dfn / low 的计数器
int scc_cnt;   // 已经求出的 SCC 个数

int st[MAXV];      // Tarjan 的 SCC 栈
int top;           // SCC 栈顶下标
bool in_st[MAXV];  // 结点当前是否还在 SCC 栈里

int call_st[MAXV]; // 迭代版 Tarjan 的手工调用栈，模拟递归的调用链
int call_top;      // 手工调用栈顶下标
int edge_ptr[MAXV]; // 每个结点正在扫描的出边游标，模拟递归里 for 循环的位置

// 加一条 u -> v 的蕴含边。
void add_edge(int u, int v) {
    to_edge[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 代表 x 的同党伙伴：奇数 2i-1 配偶数 2i，异或 1 即可互换。
int get_other(int x) {
    return (x % 2 == 1) ? (x + 1) : (x - 1);
}

// 迭代版 Tarjan：从 root 出发求强连通分量，写成显式栈是为了不受递归深度限制。
void tarjan(int root) {
    call_st[++call_top] = root;
    dfn[root] = low[root] = ++timer;
    st[++top] = root;
    in_st[root] = true;
    edge_ptr[root] = head[root];

    while (call_top > 0) {
        int u = call_st[call_top];
        int e = edge_ptr[u];

        if (e) { // 还有出边没扫完，继续往下走
            edge_ptr[u] = nxt[e];
            int v = to_edge[e];
            if (!dfn[v]) {
                dfn[v] = low[v] = ++timer;
                st[++top] = v;
                in_st[v] = true;
                edge_ptr[v] = head[v];
                call_st[++call_top] = v;
            } else if (in_st[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        } else { // 出边扫完，回溯
            if (low[u] == dfn[u]) {
                ++scc_cnt;
                while (true) {
                    int v = st[top--];
                    in_st[v] = false;
                    scc[v] = scc_cnt;
                    if (u == v) break;
                }
            }
            --call_top;
            if (call_top > 0) {
                int p = call_st[call_top];
                low[p] = min(low[p], low[u]);
            }
        }
    }
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // 厌恶对 (u,v)：不能同时入选。由于每党恰选 1 人，
    // 「不选 v」等价于「选 v 的同党伙伴 get_other(v)」，于是
    //   u -> get_other(v)   且   v -> get_other(u)
    // 当 u == v 时连边 u -> get_other(u)，正好表达「u 不能入选」，无需特判。
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, get_other(v));
        add_edge(v, get_other(u));
    }

    for (int i = 1; i <= 2 * n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    // 同党两名代表落在同一个 SCC ⇒ 选一个就必然推出另一个，与「每党恰 1 人」矛盾。
    for (int i = 1; i <= n; ++i) {
        if (scc[2 * i - 1] == scc[2 * i]) {
            cout << "NIE\n";
            return;
        }
    }

    // Tarjan 的 SCC 编号是拓扑序的逆序：编号小的在拓扑序上更靠后（更靠近汇点），
    // 选它不会推出矛盾。按 i 从小到大输出，天然就是升序。
    for (int i = 1; i <= n; ++i) {
        if (scc[2 * i - 1] < scc[2 * i]) {
            cout << 2 * i - 1 << "\n";
        } else {
            cout << 2 * i << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
