#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int row_cnt, col_cnt;
int k;
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

bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {
        return false;
    }
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    fa[y] = x;
    sz[x] += sz[y];
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> row_cnt >> col_cnt;
    int tot = row_cnt * col_cnt;
    init_dsu(tot);

    cin >> k;

    int blocks = tot;
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        if (unite(x, y)) {
            blocks--;
        }
    }

    cout << blocks << '\n';
    return 0;
}
