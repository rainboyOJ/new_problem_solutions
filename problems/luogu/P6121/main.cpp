#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
vector<int> graph[MAXN];
int close_order[MAXN];
bool open_[MAXN];
bool ans[MAXN];

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

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
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
} dsu;

void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        open_[i] = false;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        cin >> close_order[i];
    }
}

void solve() {
    dsu.init(n);

    int components = 0; // 当前开着的谷仓形成了多少个连通块
    for (int i = n; i >= 1; i--) {
        int u = close_order[i];
        open_[u] = true;
        components++;

        for (int v : graph[u]) {
            if (!open_[v]) {
                continue;
            }
            if (dsu.unite(u, v)) {
                components--;
            }
        }

        ans[i] = (components == 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    for (int i = 1; i <= n; i++) {
        cout << (ans[i] ? "YES" : "NO") << '\n';
    }

    return 0;
}
