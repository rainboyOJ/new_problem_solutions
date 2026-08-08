// brute.cpp：枚举所有 n-1 条边的方案，直接检查哪棵生成树的最大边最小。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 30;
const int INF = 1e9;

struct Edge {
    int u, v, w;
} edges[MAXM];

int n, m;
int picked[MAXM];
int fa[MAXN];
int best_answer = INF;

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

void unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y) {
        fa[x] = y;
    }
}

void check_tree(int picked_cnt) {
    if (picked_cnt != n - 1) {
        return;
    }

    init_dsu();
    int max_w = 0;

    for (int i = 1; i <= picked_cnt; i++) {
        Edge &e = edges[picked[i]];
        unite(e.u, e.v);
        max_w = max(max_w, e.w);
    }

    int root = find_root(1);
    for (int i = 2; i <= n; i++) {
        if (find_root(i) != root) {
            return;
        }
    }

    best_answer = min(best_answer, max_w);
}

void dfs(int pos, int picked_cnt) {
    if (picked_cnt > n - 1) {
        return;
    }
    if (pos > m) {
        check_tree(picked_cnt);
        return;
    }

    picked[picked_cnt + 1] = pos;
    dfs(pos + 1, picked_cnt + 1);
    dfs(pos + 1, picked_cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    dfs(1, 0);
    cout << n - 1 << ' ' << best_answer << '\n';

    return 0;
}
