/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:42
 * update_at: 2026-10-05 05:42
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;   // 点数上限
const int MAXM = 1000005;  // 边数上限

// 原图，链式前向星存边
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

// Tarjan 缩点所需数组
int dfn[MAXN], low[MAXN], scc_id[MAXN], scc_size[MAXN];
int scc_cnt, timer;
int stk[MAXN], stk_top;   // Tarjan 的已访问栈
bool in_stk[MAXN];
int dfs_node[MAXN], dfs_edge[MAXN], dfs_top; // 非递归 DFS 的调用栈：当前点、下一条待走的边

// 缩点后的 DAG：先用 ll 编码所有跨分量边，排序去重后再建邻接表
ll dag_key[MAXM];         // dag_key[j] = a * (scc_cnt + 1) + b，表示分量 a -> 分量 b
int dag_head[MAXN], dag_nxt[MAXM];
int dag_indeg[MAXN];

// DAG 上拓扑 DP：dp_len 为以该分量结尾的最长链点权和，dp_cnt 为该长度的链方案数
ll dp_len[MAXN], dp_cnt[MAXN];
int que[MAXN];

ll n, m, mod_value;

// 加一条原图边 u -> v。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    scanf("%lld %lld %lld", &n, &m, &mod_value);
    for (ll i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
}

// 非递归 Tarjan 求强连通分量：把点的 DFS 调用栈显式写成数组，避免 N=10^5 时递归爆栈。
void tarjan() {
    for (int root = 1; root <= n; root++) {
        if (dfn[root] != 0) {
            continue;
        }

        timer++;
        dfn[root] = low[root] = timer;
        stk_top++;
        stk[stk_top] = root;
        in_stk[root] = true;

        dfs_top = 0;
        dfs_top++;
        dfs_node[dfs_top] = root;
        dfs_edge[dfs_top] = head[root];

        while (dfs_top > 0) {
            int u = dfs_node[dfs_top];
            int e = dfs_edge[dfs_top];

            if (e != 0) {
                // 先把当前点的边指针后移，再处理这条边
                dfs_edge[dfs_top] = nxt[e];
                int v = to[e];
                if (dfn[v] == 0) {
                    timer++;
                    dfn[v] = low[v] = timer;
                    stk_top++;
                    stk[stk_top] = v;
                    in_stk[v] = true;
                    dfs_top++;
                    dfs_node[dfs_top] = v;
                    dfs_edge[dfs_top] = head[v];
                } else if (in_stk[v] && dfn[v] < low[u]) {
                    low[u] = dfn[v];
                }
            } else {
                // u 的所有出边走完，回溯时用儿子的 low 更新父亲
                dfs_top--;
                if (dfs_top > 0) {
                    int p = dfs_node[dfs_top];
                    if (low[u] < low[p]) {
                        low[p] = low[u];
                    }
                }
                if (dfn[u] == low[u]) {
                    scc_cnt++;
                    int sz = 0;
                    while (true) {
                        int x = stk[stk_top];
                        stk_top--;
                        in_stk[x] = false;
                        scc_id[x] = scc_cnt;
                        sz++;
                        if (x == u) {
                            break;
                        }
                    }
                    scc_size[scc_cnt] = sz;
                }
            }
        }
    }
}

// 建缩点后的无重边无自环 DAG，并统计入度。重边会让方案数被重复累加，必须去重。
void build_dag() {
    ll base = scc_cnt + 1;
    int key_cnt = 0;
    for (int u = 1; u <= n; u++) {
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            int a = scc_id[u];
            int b = scc_id[v];
            if (a != b) {
                key_cnt++;
                dag_key[key_cnt] = (ll)a * base + b;
            }
        }
    }

    sort(dag_key + 1, dag_key + key_cnt + 1);

    int unique_cnt = 0;
    for (int i = 1; i <= key_cnt; i++) {
        if (i == 1 || dag_key[i] != dag_key[i - 1]) {
            unique_cnt++;
            dag_key[unique_cnt] = dag_key[i];
        }
    }

    for (int j = 1; j <= unique_cnt; j++) {
        int a = dag_key[j] / base;
        int b = dag_key[j] % base;
        dag_nxt[j] = dag_head[a];
        dag_head[a] = j;
        dag_indeg[b]++;
    }
}

// 在 DAG 上拓扑排序，求最大点权链 K 与方案数 C mod X。
void solve_dag() {
    int qhead = 0, qtail = 0;
    for (int u = 1; u <= scc_cnt; u++) {
        if (dag_indeg[u] == 0) {
            dp_len[u] = scc_size[u];
            dp_cnt[u] = 1;
            qtail++;
            que[qtail] = u;
        }
    }

    ll base = scc_cnt + 1;
    while (qhead < qtail) {
        qhead++;
        int u = que[qhead];
        for (int j = dag_head[u]; j != 0; j = dag_nxt[j]) {
            int v = dag_key[j] % base;
            ll cand = dp_len[u] + scc_size[v];
            if (cand > dp_len[v]) {
                dp_len[v] = cand;
                dp_cnt[v] = dp_cnt[u];
            } else if (cand == dp_len[v]) {
                dp_cnt[v] = (dp_cnt[v] + dp_cnt[u]) % mod_value;
            }
            dag_indeg[v]--;
            if (dag_indeg[v] == 0) {
                qtail++;
                que[qtail] = v;
            }
        }
    }

    ll best_len = 0;
    ll best_cnt = 0;
    for (int u = 1; u <= scc_cnt; u++) {
        if (dp_len[u] > best_len) {
            best_len = dp_len[u];
        }
    }
    for (int u = 1; u <= scc_cnt; u++) {
        if (dp_len[u] == best_len) {
            best_cnt = (best_cnt + dp_cnt[u]) % mod_value;
        }
    }

    printf("%lld\n%lld\n", best_len, best_cnt);
}

int main() {
    read_input();
    tarjan();
    build_dag();
    solve_dag();
    return 0;
}
