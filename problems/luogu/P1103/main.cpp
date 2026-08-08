#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 1000000000;

struct Book {
    int h, w;
};

int n, k;
Book a[MAXN];
int dp[MAXN][MAXN];

bool cmp_book(const Book &lhs, const Book &rhs) {
    return lhs.h < rhs.h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].h >> a[i].w;
    }

    sort(a + 1, a + n + 1, cmp_book);

    int keep = n - k;

    for (int i = 0; i <= keep; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }

    // 只保留一本书时，不整齐度为 0。
    for (int j = 1; j <= n; j++) {
        dp[1][j] = 0;
    }

    for (int cnt = 2; cnt <= keep; cnt++) {
        for (int j = cnt; j <= n; j++) {
            for (int p = cnt - 1; p < j; p++) {
                dp[cnt][j] = min(dp[cnt][j], dp[cnt - 1][p] + abs(a[j].w - a[p].w));
            }
        }
    }

    int ans = INF;
    for (int j = keep; j <= n; j++) {
        ans = min(ans, dp[keep][j]);
    }

    cout << ans << '\n';
    return 0;
}
