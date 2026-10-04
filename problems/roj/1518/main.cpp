/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:58
 * update_at: 2026-10-05 05:58
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int MAXM = 500005;

typedef long long ll;

const ll NEG = -(1LL << 60); // 不可达哨兵；金额非负，用它区分"没走到过"和"收益为 0"

int n, m;

// 链式前向星：head[v] 是 v 的第一条出边编号，0 表示没有出边。
int head[MAXN];
int to[MAXM];
int nxt[MAXM];
int edge_cnt;

int money[MAXN]; // 每个路口的 ATM 金额，非负且不超过 4000
char bar[MAXN];  // bar[v] = 1 表示路口 v 有酒吧

// Tarjan 需要的全局数组。
int cur[MAXN];       // 每个点下一条待处理出边的游标，是 head 的副本，避免破坏 head
int dfn[MAXN];       // 访问时间戳，0 表示还没访问
int low[MAXN];       // 子树经回边能触到的最小 dfn
int comp[MAXN];      // 每个点所属的强连通分量编号
char on_stack[MAXN]; // 是否还在 Tarjan 的 SCC 栈里
int scc_stack[MAXN]; // 待判定的 SCC 栈
int work_stack[MAXN];// 人工递归栈，模拟 Tarjan 的深搜过程
int comp_cnt;        // 强连通分量个数

// 缩点后的结果。
ll pool[MAXN];    // pool[c] = 分量 c 内所有路口金额之和
char has_bar[MAXN]; // has_bar[c] = 1 表示分量 c 里有酒吧
ll dp[MAXN];      // dp[c] = 从起点走到分量 c 时能抢到的最大金额（含 c 自己的钱）

int node_of[MAXN];      // 按分量编号分桶后的节点序列
int bucket_start[MAXN]; // 分量 c 的节点在 node_of 中的区间 [bucket_start[c], bucket_start[c+1])
int pos[MAXN];          // 分桶写入时的临时游标

// 加一条 u -> v 的边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 迭代式 Tarjan 求强连通分量，结果写入 comp[]，分量个数写入 comp_cnt。
// 分量在"子树全部处理完"后才弹出并编号，所以跨分量的边 u -> v 恒有 comp[u] > comp[v]，
// 也就是 comp 的降序天然就是缩点 DAG 的拓扑序。用人工栈代替递归，避免 50 万点爆栈。
void tarjan_scc() {
    for (int v = 1; v <= n; v++) {
        cur[v] = head[v];
    }

    int timer = 0;
    int scc_top = 0;
    int work_top = 0;

    for (int root = 1; root <= n; root++) {
        if (dfn[root] != 0) continue;

        timer++;
        dfn[root] = low[root] = timer;
        scc_stack[++scc_top] = root;
        on_stack[root] = 1;
        work_stack[++work_top] = root;

        while (work_top > 0) {
            int v = work_stack[work_top];
            int e = cur[v];

            if (e == 0) {
                // v 的出边全部处理完，可以收尾。
                work_top--;
                if (low[v] == dfn[v]) {
                    // v 是所在分量的根，弹出整个分量并编号。
                    while (true) {
                        int u = scc_stack[scc_top--];
                        on_stack[u] = 0;
                        comp[u] = comp_cnt;
                        if (u == v) break;
                    }
                    comp_cnt++;
                }
                if (work_top > 0) {
                    int parent = work_stack[work_top];
                    if (low[v] < low[parent]) low[parent] = low[v]; // 子树 low 回传给父亲
                }
                continue;
            }

            cur[v] = nxt[e]; // 这条边走过了，下次从下一条继续
            int u = to[e];
            if (dfn[u] == 0) {
                // 树边：新节点入栈。
                timer++;
                dfn[u] = low[u] = timer;
                scc_stack[++scc_top] = u;
                on_stack[u] = 1;
                work_stack[++work_top] = u;
            } else if (on_stack[u] && dfn[u] < low[v]) {
                // 回边或横叉边：只有仍在栈里的点才能更新 low。
                low[v] = dfn[u];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
    }
    for (int v = 1; v <= n; v++) {
        cin >> money[v];
    }

    int start, bar_cnt;
    cin >> start >> bar_cnt;
    for (int i = 1; i <= bar_cnt; i++) {
        int v;
        cin >> v;
        bar[v] = 1;
    }

    tarjan_scc();

    // 缩点：分量内任意两点互达，走进一个点就能把整个分量的钱扫空，故按分量求和。
    for (int v = 1; v <= n; v++) {
        int c = comp[v];
        pool[c] += money[v];
        if (bar[v]) has_bar[c] = 1;
    }

    // 计数排序：把节点按分量编号分桶，才能按分量顺序访问分量内的点。
    for (int v = 1; v <= n; v++) {
        bucket_start[comp[v] + 1]++;
    }
    for (int c = 1; c <= comp_cnt; c++) {
        bucket_start[c] += bucket_start[c - 1];
    }
    for (int c = 0; c < comp_cnt; c++) {
        pos[c] = bucket_start[c];
    }
    for (int v = 1; v <= n; v++) {
        int c = comp[v];
        node_of[pos[c]] = v;
        pos[c]++;
    }

    // 在缩点 DAG 上做最长路 DP：dp[c] = pool[c] + max(dp[u])，u 是 c 的入边来源分量。
    for (int c = 0; c < comp_cnt; c++) {
        dp[c] = NEG;
    }
    dp[comp[start]] = pool[comp[start]];

    ll best = NEG;
    for (int c = comp_cnt - 1; c >= 0; c--) { // 分量编号降序 = 缩点 DAG 的拓扑序
        if (dp[c] == NEG) continue;           // 这个分量从起点根本走不到
        if (has_bar[c] && dp[c] > best) {
            best = dp[c]; // 停在任意一个有酒吧的分量都能收尾，随时刷新答案
        }
        for (int i = bucket_start[c]; i < bucket_start[c + 1]; i++) {
            int v = node_of[i];
            for (int e = head[v]; e != 0; e = nxt[e]) {
                int u = comp[to[e]];
                if (u != c && dp[c] + pool[u] > dp[u]) {
                    dp[u] = dp[c] + pool[u]; // 只沿跨分量的边松弛
                }
            }
        }
    }

    cout << best << '\n';
    return 0;
}
