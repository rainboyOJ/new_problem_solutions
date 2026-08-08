#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, k;
vector<int> g[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 枚举所有大小恰好为 k 的点集，检查每个点是否都有相邻点被选中。
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int answer = 0;
    int total_mask = 1 << n;

    for (int mask = 0; mask < total_mask; mask++) {
        if (__builtin_popcount((unsigned) mask) != k) {
            continue;
        }

        bool ok = true;
        for (int u = 1; u <= n; u++) {
            bool covered = false;
            for (size_t i = 0; i < g[u].size(); i++) {
                int v = g[u][i];
                if (mask & (1 << (v - 1))) {
                    covered = true;
                    break;
                }
            }
            if (!covered) {
                ok = false;
                break;
            }
        }

        if (ok) {
            answer++;
        }
    }

    cout << answer << '\n';
    return 0;
}
