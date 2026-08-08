#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
const int MAXM = 100005;

struct Edge {
    int u, v, w;
};

int n, m;
Edge edge[MAXM];
int father[MAXN * 2];

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

int find_root(int x) {
    if (father[x] == x) {
        return x;
    }
    father[x] = find_root(father[x]);
    return father[x];
}

void merge_set(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx != ry) {
        father[rx] = ry;
    }
}

int opposite(int x) {
    return x + n;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
}

void solve() {
    sort(edge + 1, edge + m + 1, cmp_edge);

    for (int i = 1; i <= 2 * n; i++) {
        father[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int u = edge[i].u;
        int v = edge[i].v;

        // u 和 v 必须关在不同监狱；如果已经被迫同组，就无法避开这条冲突。
        if (find_root(u) == find_root(v)) {
            cout << edge[i].w << '\n';
            return;
        }

        merge_set(u, opposite(v));
        merge_set(v, opposite(u));
    }

    cout << 0 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
