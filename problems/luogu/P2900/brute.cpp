#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXN = 5005;

struct Rect {
    long long x, y;
} a[MAXN], b[MAXN];

int n, m;
long long dp[MAXN];

bool cmp_rect(const Rect &lhs, const Rect &rhs) {
    if (lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    }
    return lhs.y > rhs.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力 DP。
    // 去掉被支配矩形后，直接枚举最后一组从哪里开始分段。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    sort(a + 1, a + n + 1, cmp_rect);

    m = 0;
    for (int i = 1; i <= n; i++) {
        while (m > 0 && b[m].y <= a[i].y) {
            m--;
        }
        b[++m] = a[i];
    }

    dp[0] = 0;
    for (int i = 1; i <= m; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + b[i].x * b[j + 1].y);
        }
    }

    cout << dp[m] << '\n';
    return 0;
}
