/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 09:42
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
const int MAXM = 6005;

int n, m, k;
int eu[MAXM], ev[MAXM];
vector<int> g[MAXN];

int fa[MAXN], fa_edge[MAXN], dep[MAXN];
int visited[MAXN];
int in_cycle[MAXN], in_core[MAXN];
int dist_core[MAXN];
int dir_u[MAXM], dir_v[MAXM]; // 构造后第 i 条无向边的方向 dir_u[i] -> dir_v[i]
int has_answer;
int back_u, back_v, back_edge;

void clear_case() {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        fa[i] = fa_edge[i] = dep[i] = 0;
        visited[i] = 0;
        in_cycle[i] = in_core[i] = 0;
        dist_core[i] = -1;
    }
    for (int i = 1; i <= m; i++) {
        dir_u[i] = dir_v[i] = 0;
    }
    has_answer = 0;
    back_u = back_v = back_edge = 0;
}

int other_point(int id, int x) {
    if (eu[id] == x) return ev[id];
    return eu[id];
}

void set_dir(int id, int u, int v) {
    if (dir_u[id] == 0) {
        dir_u[id] = u;
        dir_v[id] = v;
    }
}

void bfs_find_cycle() {
    queue<int> q;
    visited[k] = 1;
    dep[k] = 0;
    q.push(k);

    while (!q.empty() && !has_answer) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int id = g[u][i];
            int v = other_point(id, u);
            if (!visited[v]) {
                visited[v] = 1;
                fa[v] = u;
                fa_edge[v] = id;
                dep[v] = dep[u] + 1;
                q.push(v);
            }
            else if (id != fa_edge[u]) {
                // 在 k 所在连通分量中找到一条非树边，它和树边组成一个环。
                has_answer = 1;
                back_u = u;
                back_v = v;
                back_edge = id;
                break;
            }
        }
    }
}

int find_lca_on_tree(int u, int v) {
    while (dep[u] > dep[v]) u = fa[u];
    while (dep[v] > dep[u]) v = fa[v];
    while (u != v) {
        u = fa[u];
        v = fa[v];
    }
    return u;
}

void mark_cycle_and_direct() {
    int lca = find_lca_on_tree(back_u, back_v);

    // 环的方向：back_u -> back_v，然后 back_v 沿树边走到 lca，再从 lca 走到 back_u。
    set_dir(back_edge, back_u, back_v);
    int x = back_v;
    while (x != lca) {
        in_cycle[x] = 1;
        set_dir(fa_edge[x], x, fa[x]);
        x = fa[x];
    }
    in_cycle[lca] = 1;
    x = back_u;
    while (x != lca) {
        in_cycle[x] = 1;
        set_dir(fa_edge[x], fa[x], x);
        x = fa[x];
    }
}

void mark_path_to_k_and_direct() {
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (in_cycle[i] && (p == 0 || dep[i] < dep[p])) {
            p = i;
        }
    }

    // p 是环上离 k 最近的点。把 p 到 k 的树路径定向为 p -> ... -> k。
    for (int i = 1; i <= n; i++) {
        if (in_cycle[i]) in_core[i] = 1;
    }
    int x = p;
    while (x != k) {
        in_core[x] = 1;
        set_dir(fa_edge[x], x, fa[x]);
        x = fa[x];
    }
    in_core[k] = 1;
}

void direct_other_edges() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_core[i]) {
            dist_core[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int id = g[u][i];
            int v = other_point(id, u);
            if (dist_core[v] == -1) {
                dist_core[v] = dist_core[u] + 1;
                q.push(v);
            }
        }
    }

    for (int id = 1; id <= m; id++) {
        if (dir_u[id] != 0) continue;
        int u = eu[id], v = ev[id];
        if (dist_core[u] != -1 && dist_core[v] == -1) set_dir(id, u, v);
        else if (dist_core[u] == -1 && dist_core[v] != -1) set_dir(id, v, u);
        else if (dist_core[u] < dist_core[v]) set_dir(id, u, v);
        else if (dist_core[v] < dist_core[u]) set_dir(id, v, u);
        else set_dir(id, u, v);
    }
}

void solve_case() {
    bfs_find_cycle();
    if (!has_answer) {
        cout << "No\n";
        return;
    }

    mark_cycle_and_direct();
    mark_path_to_k_and_direct();
    direct_other_edges();

    cout << "Yes\n";
    for (int i = 1; i <= m; i++) {
        if (dir_u[i] == eu[i] && dir_v[i] == ev[i]) cout << '0';
        else cout << '1';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        clear_case();
        for (int i = 1; i <= m; i++) {
            cin >> eu[i] >> ev[i];
            g[eu[i]].push_back(i);
            g[ev[i]].push_back(i);
        }
        solve_case();
    }
    return 0;
}
