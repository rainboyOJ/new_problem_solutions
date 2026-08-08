#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const long long INF = (1LL << 60);

int n, L;
int d[MAXN];
int t[MAXN];
long long pre_w[MAXN];
long long pre_dw[MAXN];
long long dp[5][MAXN];

long long seg_cost(int l, int r) {
    if (l > r) {
        return 0;
    }
    long long sum_w = pre_w[r] - pre_w[l - 1];
    long long sum_dw = pre_dw[r] - pre_dw[l - 1];
    return 1LL * d[r] * sum_w - sum_dw;
}

long long last_cost(int l) {
    if (l > n) {
        return 0;
    }
    long long sum_w = pre_w[n] - pre_w[l - 1];
    long long sum_dw = pre_dw[n] - pre_dw[l - 1];
    return 1LL * L * sum_w - sum_dw;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：按“前 i 户用了 k 个中间会场”的朴素 DP。
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> d[i] >> t[i];
        pre_w[i] = pre_w[i - 1] + t[i];
        pre_dw[i] = pre_dw[i - 1] + 1LL * d[i] * t[i];
    }

    for (int k = 0; k <= 3; k++) {
        for (int i = 0; i <= n; i++) {
            dp[k][i] = INF;
        }
    }
    dp[0][0] = 0;

    long long ans = last_cost(1);
    for (int k = 1; k <= 3; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[k - 1][j] >= INF / 2) {
                    continue;
                }
                dp[k][i] = min(dp[k][i], dp[k - 1][j] + seg_cost(j + 1, i));
            }
            ans = min(ans, dp[k][i] + last_cost(i + 1));
        }
    }

    cout << ans << '\n';
    return 0;
}
