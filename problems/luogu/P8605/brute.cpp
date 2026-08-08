#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> g;
static int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;
    g.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u][v] = g[v][u] = 1;
    }

    long long ans = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            if (!g[a][b]) {
                continue;
            }
            for (int c = 1; c <= n; ++c) {
                if (!g[b][c]) {
                    continue;
                }
                if (c == a || c == b) {
                    continue;
                }
                for (int d = 1; d <= n; ++d) {
                    if (!g[c][d]) {
                        continue;
                    }
                    if (d == b || d == c) {
                        continue;
                    }
                    // 源点和终点可以相同，但两个中间点必须和两端都区分开。
                    if (b == a || b == d || c == a || c == d) {
                        continue;
                    }
                    ++ans;
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
