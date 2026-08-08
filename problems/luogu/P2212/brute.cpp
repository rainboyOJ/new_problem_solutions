// brute.cpp：小图枚举所有允许边的生成树。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 50;
const int INF = 1e9;

struct Edge {
    int u, v, w;
} edges[MAXM];

int n, limit_c;
int x[MAXN], y[MAXN];
int edge_cnt;
int picked[MAXM];
int fa[MAXN];
int best_answer = INF;

int dis2(int i, int j) {
    int dx = x[i] - x[j];
    int dy = y[i] - y[j];
    return dx * dx + dy * dy;
}

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

bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {
        return false;
    }
    fa[x] = y;
    return true;
}

void check_tree(int picked_cnt) {
    if (picked_cnt != n - 1) {
        return;
    }

    init_dsu();
    int sum = 0;

    for (int i = 1; i <= picked_cnt; i++) {
        Edge &e = edges[picked[i]];
        if (!unite(e.u, e.v)) {
            return;
        }
        sum += e.w;
    }

    int root = find_root(1);
    for (int i = 2; i <= n; i++) {
        if (find_root(i) != root) {
            return;
        }
    }

    best_answer = min(best_answer, sum);
}

void dfs(int pos, int picked_cnt) {
    if (picked_cnt > n - 1) {
        return;
    }
    if (pos > edge_cnt) {
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

    cin >> n >> limit_c;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int w = dis2(i, j);
            if (w < limit_c) {
                continue;
            }
            edges[++edge_cnt] = {i, j, w};
        }
    }

    dfs(1, 0);

    if (best_answer == INF) {
        cout << -1 << '\n';
    } else {
        cout << best_answer << '\n';
    }

    return 0;
}
