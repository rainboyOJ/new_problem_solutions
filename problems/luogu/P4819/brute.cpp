/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 12:51
 * update_at: 2026-10-23 13:25
 */
// brute.cpp：小数据暴力/参考解，使用 Kosaraju 求 SCC + 相同概率逻辑
// 用于对拍验证主解 Tarjan 实现
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXM = 300010 * 2;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int rhead[MAXN], rto[MAXM], rnxt[MAXM], redge_cnt;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;

    redge_cnt++;
    rto[redge_cnt] = u;
    rnxt[redge_cnt] = rhead[v];
    rhead[v] = redge_cnt;
}

bool vis[MAXN];
vector<int> order, component;

void dfs1(int u) {
    vis[u] = true;
    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u) {
    vis[u] = true;
    component.push_back(u);
    for (int i = rhead[u]; i != 0; i = rnxt[i]) {
        int v = rto[i];
        if (!vis[v]) dfs2(v);
    }
}

int scc_id[MAXN], scc_cnt, sz[MAXN];
vector<int> dag[MAXN];
int in_deg[MAXN];

void kosaraju() {
    memset(vis, 0, sizeof(bool) * (n + 1));
    order.clear();
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }

    memset(vis, 0, sizeof(bool) * (n + 1));
    scc_cnt = 0;
    memset(scc_id, 0, sizeof(int) * (n + 1));
    memset(sz, 0, sizeof(int) * (n + 1));

    for (int i = order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (!vis[u]) {
            scc_cnt++;
            component.clear();
            dfs2(u);
            sz[scc_cnt] = component.size();
            for (int x : component) {
                scc_id[x] = scc_cnt;
            }
        }
    }
}

void build_dag() {
    vector<set<int>> temp(scc_cnt + 1);
    for (int u = 1; u <= n; u++) {
        int su = scc_id[u];
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            int sv = scc_id[v];
            if (su != sv) {
                temp[su].insert(sv);
            }
        }
    }
    for (int i = 1; i <= scc_cnt; i++) {
        dag[i].clear();
        for (int v : temp[i]) dag[i].push_back(v);
    }
}

void calc_in_deg() {
    memset(in_deg, 0, sizeof(int) * (scc_cnt + 1));
    for (int i = 1; i <= scc_cnt; i++) {
        for (int v : dag[i]) {
            in_deg[v]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    edge_cnt = redge_cnt = 0;
    memset(head, 0, sizeof(int) * (n + 1));
    memset(rhead, 0, sizeof(int) * (n + 1));

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
    }

    kosaraju();
    build_dag();
    calc_in_deg();

    int cnt = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_deg[i] == 0) cnt++;
    }

    bool can_omit = false;
    for (int i = 1; i <= scc_cnt && !can_omit; i++) {
        if (in_deg[i] == 0 && sz[i] == 1) {
            bool ok = true;
            for (int v : dag[i]) {
                if (in_deg[v] <= 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) can_omit = true;
        }
    }

    int must = (n == 1 ? 0 : cnt);
    if (can_omit && must > 0) must--;

    double ans = 1.0 - (double)must / n;
    printf("%.6f\n", ans);

    return 0;
}
