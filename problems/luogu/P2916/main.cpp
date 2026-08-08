#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 100005;

struct Edge {
    int u, v;
    int w;

    bool operator<(const Edge &other) const {
        return w < other.w;
    }
} edges[MAXM];

int n, p;
int cost[MAXN];
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

long long kruskal() {
    sort(edges + 1, edges + p + 1);
    init_dsu(n);

    long long answer = 0;
    int used = 0;

    for (int i = 1; i <= p; i++) {
        if (!unite(edges[i].u, edges[i].v)) {
            continue;
        }
        answer += edges[i].w;
        used++;
        if (used == n - 1) {
            break;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;

    int min_cost = 1e9;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
        min_cost = min(min_cost, cost[i]);
    }

    for (int i = 1; i <= p; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        edges[i] = {u, v, 2 * len + cost[u] + cost[v]};
    }

    cout << kruskal() + min_cost << '\n';

    return 0;
}
