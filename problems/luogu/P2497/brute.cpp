#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const long double INF = 1e100L;

struct Node {
    long long x, r, v;
} a[MAXN];

int n;
long long home_x;
long double dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：朴素 DP。
    // 直接枚举前一个被选中的基站，做 O(n^2) 的最短路转移。
    cin >> n >> home_x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].r >> a[i].v;
    }

    sort(a + 1, a + n + 1, [](const Node &lhs, const Node &rhs) {
        if (lhs.x != rhs.x) {
            return lhs.x < rhs.x;
        }
        if (lhs.r != rhs.r) {
            return lhs.r < rhs.r;
        }
        return lhs.v < rhs.v;
    });

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[1] = (long double) a[1].v; // 第一个点就是移动公司。

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (dp[j] >= INF / 2 || a[j].x >= a[i].x) {
                continue;
            }
            long double extra = (long double) (a[i].x - a[j].x)
                              / (2.0L * sqrtl((long double) a[j].r));
            dp[i] = min(dp[i], dp[j] + extra + (long double) a[i].v);
        }
    }

    long double ans = INF;
    for (int i = 1; i <= n; i++) {
        if (llabs(a[i].x - home_x) <= a[i].r) {
            ans = min(ans, dp[i]);
        }
    }

    cout.setf(ios::fixed);
    cout << setprecision(3) << (double) ans << '\n';
    return 0;
}
