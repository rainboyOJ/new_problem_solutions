#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;

int n, q;
int fa[MAXN];
vector<int> children[MAXN];
int sz[MAXN];
int dep[MAXN];

void dfs_sz(int u, int d) {
    dep[u] = d;
    sz[u] = 1;
    for (int v : children[u]) {
        dfs_sz(v, d + 1);
        sz[u] += sz[v];
    }
}

void get_nodes(int u, vector<int>& nodes) {
    nodes.push_back(u);
    for (int v : children[u]) {
        get_nodes(v, nodes);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> q)) return 0;

    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
        children[fa[i]].push_back(i);
    }

    dfs_sz(1, 1);

    while (q--) {
        int u;
        cin >> u;
        int total = sz[u];
        vector<int> nodes;
        get_nodes(u, nodes);

        int best = -1;
        int best_dep = -1;

        for (int x : nodes) {
            int max_part = total - sz[x];
            for (int v : children[x]) {
                max_part = max(max_part, sz[v]);
            }
            if (max_part <= total / 2) {
                // 深度更深的优先（与 main.cpp 一致：在两个重心时停在子节点处）
                if (dep[x] > best_dep) {
                    best_dep = dep[x];
                    best = x;
                }
            }
        }
        cout << best << "\n";
    }

    return 0;
}
