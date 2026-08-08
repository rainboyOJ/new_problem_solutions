// brute.cpp：小图枚举所有生成树，直接比较总长度。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 30;
const long double INF = 1e100;

struct Edge {
    int u, v;
    long long d2;
} edges[MAXM];

int n;
long long x[MAXN], y[MAXN];
int edge_cnt;
int picked[MAXM];
int fa[MAXN];
long double best_answer = INF;

long long dis2(int i, int j) {
    long long dx = x[i] - x[j];
    long long dy = y[i] - y[j];
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
    long double sum = 0;

    for (int i = 1; i <= picked_cnt; i++) {
        Edge &e = edges[picked[i]];
        if (!unite(e.u, e.v)) {
            return;
        }
        sum += sqrtl((long double)e.d2);
    }

    int root = find_root(1);
    for (int i = 2; i <= n; i++) {
        if (find_root(i) != root) {
            return;
        }
    }

    if (sum < best_answer) {
        best_answer = sum;
    }
}

void dfs(int pos, int picked_cnt) {
    if (picked_cnt > n - 1) {
        return;
    }
    if (pos > edge_cnt) {
        check_tree(picked_cnt);
        return;
    }

    if (picked_cnt + (edge_cnt - pos + 1) < n - 1) {
        return;
    }

    picked[picked_cnt + 1] = pos;
    dfs(pos + 1, picked_cnt + 1);
    dfs(pos + 1, picked_cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            edges[++edge_cnt] = {i, j, dis2(i, j)};
        }
    }

    dfs(1, 0);

    cout << fixed << setprecision(2) << (double)best_answer << '\n';

    return 0;
}
