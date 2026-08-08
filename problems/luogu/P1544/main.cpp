#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long NEG_INF = -(1LL << 60);

int n, k;
long long a[MAXN][MAXN];
long long pre[MAXN][MAXN], cur[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    // 一条路径一共只会经过 n 个点，所以真正有意义的三倍次数不会超过 n。
    k = min(k, n);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            pre[i][j] = NEG_INF;
            cur[i][j] = NEG_INF;
        }
    }

    pre[1][0] = a[1][1];
    if (k >= 1) {
        pre[1][1] = a[1][1] * 3;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int c = 0; c <= k; c++) {
                cur[j][c] = NEG_INF;
            }
        }

        for (int j = 1; j <= i; j++) {
            for (int c = 0; c <= k; c++) {
                long long best = NEG_INF;

                // 当前点不使用三倍经验。
                if (j <= i - 1) {
                    best = max(best, pre[j][c]);
                }
                if (j - 1 >= 1) {
                    best = max(best, pre[j - 1][c]);
                }
                if (best != NEG_INF) {
                    cur[j][c] = max(cur[j][c], best + a[i][j]);
                }

                // 当前点使用一次三倍经验。
                if (c > 0) {
                    long long best2 = NEG_INF;
                    if (j <= i - 1) {
                        best2 = max(best2, pre[j][c - 1]);
                    }
                    if (j - 1 >= 1) {
                        best2 = max(best2, pre[j - 1][c - 1]);
                    }
                    if (best2 != NEG_INF) {
                        cur[j][c] = max(cur[j][c], best2 + a[i][j] * 3);
                    }
                }
            }
        }

        for (int j = 0; j <= i; j++) {
            for (int c = 0; c <= k; c++) {
                pre[j][c] = cur[j][c];
            }
        }
    }

    long long ans = NEG_INF;
    for (int j = 1; j <= n; j++) {
        for (int c = 0; c <= k; c++) {
            ans = max(ans, pre[j][c]);
        }
    }

    cout << ans << '\n';
    return 0;
}
