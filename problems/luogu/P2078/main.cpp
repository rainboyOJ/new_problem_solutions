#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

struct DSU {
    int fa[MAXN], sz[MAXN];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (fa[x] == x) {
            return x;
        }
        fa[x] = find(fa[x]);
        return fa[x];
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (sz[x] < sz[y]) {
            swap(x, y);
        }
        fa[y] = x;
        sz[x] += sz[y];
    }

    int size(int x) {
        return sz[find(x)];
    }
};

int n, m, p, q;
DSU dsu_a, dsu_b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p >> q;
    dsu_a.init(n);
    dsu_b.init(m);

    for (int i = 1; i <= p; i++) {
        int x, y;
        cin >> x >> y;
        dsu_a.unite(x, y);
    }

    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        x = -x;
        y = -y;
        dsu_b.unite(x, y);
    }

    cout << min(dsu_a.size(1), dsu_b.size(1)) << '\n';
    return 0;
}
