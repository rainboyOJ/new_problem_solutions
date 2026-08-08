#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXK = 105;

struct Point {
    int x, y;
};

int n, k;
Point p[MAXN];
int dp[MAXN][MAXK]; // dp[i][t]：以第 i 个给定点结尾，恰好用了 t 个新增点时，最多能选多少个给定点

bool cmp_point(const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p + 1, p + n + 1, cmp_point);

    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
    }

    int best = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (p[j].x < p[i].x || p[j].y < p[i].y) {
                continue;
            }

            int need = (p[j].x - p[i].x) + (p[j].y - p[i].y) - 1;
            if (need > k) {
                continue;
            }

            for (int t = 0; t + need <= k; t++) {
                if (dp[i][t] == 0) {
                    continue;
                }
                dp[j][t + need] = max(dp[j][t + need], dp[i][t] + 1);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int t = 0; t <= k; t++) {
            best = max(best, dp[i][t]);
        }
    }

    // 若一条路径中选了 best 个给定点，剩余新增点总能放到路径两端继续延长。
    cout << best + k << '\n';
    return 0;
}
