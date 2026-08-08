#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
int fa[MAXN], sz[MAXN];

void init_dsu(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        sz[i] = 1;
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
    if (x == y) {
        return;
    }
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    fa[y] = x;
    sz[x] += sz[y];
}

bool same(int x, int y) {
    return find_root(x) == find_root(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_dsu(n);

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            unite(x, y);
        } else {
            cout << (same(x, y) ? 'Y' : 'N') << '\n';
        }
    }

    return 0;
}
