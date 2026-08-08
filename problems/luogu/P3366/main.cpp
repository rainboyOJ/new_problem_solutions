#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int MAXM = 200005;

struct Edge {
    int u;
    int v;
    int w;
};

int n, m;
Edge edges[MAXM];
int fa[MAXN], sz[MAXN];

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}

int find_set(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

bool unite_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx == fy) {
        return false;
    }
    if (sz[fx] < sz[fy]) {
        swap(fx, fy);
    }
    fa[fy] = fx;
    sz[fx] += sz[fy];
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges + 1, edges + m + 1, cmp_edge);
    init_dsu();

    long long ans = 0;
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (unite_set(edges[i].u, edges[i].v)) {
            ans += edges[i].w;
            cnt++;
            if (cnt == n - 1) {
                break;
            }
        }
    }

    if (cnt != n - 1) {
        cout << "orz\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
