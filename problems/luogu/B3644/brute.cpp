#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
int n;
vector<int> g[maxn];
int vis[maxn]; // 0: 未访问, 1: 访问中, 2: 已完成
vector<int> topo;

bool dfs(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (vis[v] == 1) return false; // 有环
        if (vis[v] == 0 && !dfs(v)) return false;
    }
    vis[u] = 2;
    topo.push_back(u);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int u = 1; u <= n; ++u) {
        int v;
        while (cin >> v && v != 0) {
            g[u].push_back(v);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 0) {
            if (!dfs(i)) {
                cout << "Cycle\n";
                return 0;
            }
        }
    }

    reverse(topo.begin(), topo.end());
    for (int i = 0; i < (int)topo.size(); ++i) {
        cout << topo[i] << (i + 1 == (int)topo.size() ? "" : " ");
    }
    cout << '\n';
    return 0;
}
