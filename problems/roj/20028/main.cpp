/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 20:47
 * update_at: 2026-10-09 21:05
 */
// roj 20028《王国旅行》：Tarjan 缩点 + DAG 可达位掩码，枚举跨分量边取交集贡献。
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;

const int MAXN = 2005;
const int MAXM = 40005;

int n, m;

// 原始边表：并行数组会让人脑补下标对应关系，聚合成 struct 后一个下标就是一条边
struct Edge {
    int u;  // 起点
    int v;  // 终点
};
Edge edge[MAXM];

vector<int> adj[MAXN];

int dfn[MAXN], low[MAXN], timer;
int stk[MAXN], top;
bool in_stk[MAXN];

int scc[MAXN], scc_cnt;
int scc_sz[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;
    in_stk[u] = true;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        while (true) {
            int v = stk[top--];
            in_stk[v] = false;
            scc[v] = scc_cnt;
            scc_sz[scc_cnt]++;
            if (u == v) break;
        }
    }
}

vector<int> dag[MAXN], rev_dag[MAXN];

unsigned long long reach[MAXN][35];
unsigned long long reach_rev[MAXN][35];
int in_deg[MAXN];

int q[MAXN];

void solve() {
    if (!(cin >> n >> m)) return;

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        dfn[i] = low[i] = 0;
        in_stk[i] = false;
        scc[i] = 0;
        scc_sz[i] = 0;
    }
    timer = top = scc_cnt = 0;

    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v;
        adj[edge[i].u].push_back(edge[i].v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= scc_cnt; i++) {
        dag[i].clear();
        rev_dag[i].clear();
        in_deg[i] = 0;
        memset(reach[i], 0, sizeof(reach[i]));
        memset(reach_rev[i], 0, sizeof(reach_rev[i]));
    }

    for (int i = 1; i <= m; i++) {
        int u = scc[edge[i].u];
        int v = scc[edge[i].v];
        if (u != v) {
            dag[u].push_back(v);
        }
    }

    for (int i = 1; i <= scc_cnt; i++) {
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        for (int v : dag[i]) {
            rev_dag[v].push_back(i);
            in_deg[v]++;
        }
    }

    int head = 1, tail = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_deg[i] == 0) {
            q[++tail] = i;
        }
    }
    
    vector<int> topo;
    while (head <= tail) {
        int u = q[head++];
        topo.push_back(u);
        for (int v : dag[u]) {
            if (--in_deg[v] == 0) {
                q[++tail] = v;
            }
        }
    }

    for (int i = 1; i <= scc_cnt; i++) {
        reach[i][i >> 6] |= (1ULL << (i & 63));
        reach_rev[i][i >> 6] |= (1ULL << (i & 63));
    }

    for (int i = topo.size() - 1; i >= 0; i--) {
        int u = topo[i];
        for (int v : dag[u]) {
            for (int k = 0; k <= (scc_cnt >> 6); k++) {
                reach[u][k] |= reach[v][k];
            }
        }
    }

    for (size_t i = 0; i < topo.size(); i++) {
        int u = topo[i];
        for (int p : rev_dag[u]) {
            for (int k = 0; k <= (scc_cnt >> 6); k++) {
                reach_rev[u][k] |= reach_rev[p][k];
            }
        }
    }

    int max_ans = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        max_ans = max(max_ans, scc_sz[i]);
    }

    for (int u = 1; u <= scc_cnt; u++) {
        for (int v : dag[u]) {
            int current_ans = 0;
            for (int k = 0; k <= (scc_cnt >> 6); k++) {
                unsigned long long mask = reach[u][k] & reach_rev[v][k];
                while (mask) {
                    int bit = __builtin_ctzll(mask);
                    current_ans += scc_sz[(k << 6) | bit];
                    mask &= mask - 1;
                }
            }
            max_ans = max(max_ans, current_ans);
        }
    }

    cout << max_ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}