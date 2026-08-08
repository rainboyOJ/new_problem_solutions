#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        if (n == 0) {
            break;
        }
        cin >> m;
        init_dsu(n);

        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            unite(x, y);
        }

        int blocks = 0;
        for (int i = 1; i <= n; i++) {
            if (find_root(i) == i) {
                blocks++;
            }
        }

        cout << blocks - 1 << '\n';
    }

    return 0;
}
