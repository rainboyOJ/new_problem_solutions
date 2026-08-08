#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int q;
int fa[MAXN], sz[MAXN], dist_to_head[MAXN];

void init_dsu() {
    for (int i = 1; i <= 30000; i++) {
        fa[i] = i;
        sz[i] = 1;
        dist_to_head[i] = 0;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    int old_fa = fa[x];
    fa[x] = find_root(fa[x]);
    dist_to_head[x] += dist_to_head[old_fa];
    return fa[x];
}

// 把 x 所在整列接到 y 所在整列的尾部。
void merge_queue(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);

    if (rx == ry) {
        return;
    }

    // 并查集的根表示这一列的队头。
    // x 这一列整体接到 y 这一列后面，所以 x 这一列的队头
    // 前面会多出 sz[ry] 艘战舰。
    fa[rx] = ry;
    dist_to_head[rx] = sz[ry];
    sz[ry] += sz[rx];
}

int query_between(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);

    if (rx != ry) {
        return -1;
    }
    if (x == y) {
        return 0;
    }

    return abs(dist_to_head[x] - dist_to_head[y]) - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> q;
    init_dsu();

    while (q--) {
        char op;
        int x, y;
        cin >> op >> x >> y;

        if (op == 'M') {
            merge_queue(x, y);
        } else {
            cout << query_between(x, y) << '\n';
        }
    }

    return 0;
}
