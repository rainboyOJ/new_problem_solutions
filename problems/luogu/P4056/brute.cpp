#include <bits/stdc++.h>
using namespace std;

const long long NEG_INF = -(1LL << 60);
const int MAXN = 200005;

struct Node {
    int x, y;
    long long v;
} a[MAXN];

long long best_value[1005][1005];
long long dp[MAXN];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解。
    // 先把同一格子的价值合并，然后直接在偏序 DAG 上做 O(K^2) DP。
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            best_value[i][j] = -1;
        }
    }

    for (int i = 1; i <= n; i++) {
        int x, y;
        long long v;
        cin >> x >> y >> v;
        best_value[x][y] = max(best_value[x][y], v);
    }

    int cnt = 0;
    for (int x = 1; x <= m; x++) {
        for (int y = 1; y <= m; y++) {
            if (best_value[x][y] >= 0) {
                cnt++;
                a[cnt].x = x;
                a[cnt].y = y;
                a[cnt].v = best_value[x][y];
            }
        }
    }

    for (int i = 1; i <= cnt; i++) {
        dp[i] = NEG_INF;
    }

    for (int i = 1; i <= cnt; i++) {
        if (a[i].x == 1 && a[i].y == 1) {
            dp[i] = a[i].v;
        }
        for (int j = 1; j < i; j++) {
            if (dp[j] <= NEG_INF / 2) {
                continue;
            }
            if (a[j].x <= a[i].x && a[j].y <= a[i].y) {
                long long dx = a[i].x - a[j].x;
                long long dy = a[i].y - a[j].y;
                dp[i] = max(dp[i], dp[j] + a[i].v - dx * dx - dy * dy);
            }
        }
    }

    long long answer = NEG_INF;
    for (int i = 1; i <= cnt; i++) {
        if (a[i].x == m && a[i].y == m) {
            answer = dp[i];
        }
    }

    cout << answer << '\n';
    return 0;
}
