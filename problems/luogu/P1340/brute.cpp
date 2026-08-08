// brute.cpp：每一周都把前缀边重新跑一遍 Kruskal。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 105;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} edges[MAXM];

int n, weeks;
int fa[MAXN];

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

long long solve_prefix(int cnt) {
    vector<Edge> a;
    for (int i = 1; i <= cnt; i++) {
        a.push_back(edges[i]);
    }
    sort(a.begin(), a.end());

    init_dsu();
    int used = 0;
    long long sum = 0;

    for (int i = 0; i < (int)a.size(); i++) {
        if (!unite(a[i].u, a[i].v)) {
            continue;
        }
        used++;
        sum += a[i].w;
        if (used == n - 1) {
            break;
        }
    }

    if (used != n - 1) {
        return -1;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> weeks;
    for (int i = 1; i <= weeks; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    for (int i = 1; i <= weeks; i++) {
        cout << solve_prefix(i) << '\n';
    }

    return 0;
}
