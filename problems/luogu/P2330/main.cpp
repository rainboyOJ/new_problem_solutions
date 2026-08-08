#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAXM = 8005;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} edges[MAXM];

int n, m;
int fa[MAXN];

void init_dsu(int n) {
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

int kruskal_answer() {
    sort(edges + 1, edges + m + 1);
    init_dsu(n);

    int used = 0;
    int max_w = 0;

    for (int i = 1; i <= m; i++) {
        if (!unite(edges[i].u, edges[i].v)) {
            continue;
        }
        used++;
        max_w = max(max_w, edges[i].w);
        if (used == n - 1) {
            break;
        }
    }

    return max_w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    cout << n - 1 << ' ' << kruskal_answer() << '\n';

    return 0;
}
