#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 5;

int n, m;
bool can_beat[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        can_beat[u][v] = true;
    }

    // Warshall 传递闭包：
    // 如果 i 能赢 k，k 又能赢 j，那么 i 也能赢 j。
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (!can_beat[i][k]) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (can_beat[k][j]) {
                    can_beat[i][j] = true;
                }
            }
        }
    }

    int answer = 0;

    for (int i = 1; i <= n; i++) {
        int known = 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            if (can_beat[i][j] || can_beat[j][i]) {
                known++;
            }
        }

        if (known == n - 1) {
            answer++;
        }
    }

    cout << answer << '\n';

    return 0;
}
