#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int INF = 0x3f3f3f3f;

int n;
int a[MAXN];
int sumv[MAXN];
int dp_min[MAXN][MAXN];
int dp_max[MAXN][MAXN];

// 计算区间 [l, r] 的石子总数。
int range_sum(int l, int r) {
    return sumv[r] - sumv[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int i = 1; i <= 2 * n; i++) {
        sumv[i] = sumv[i - 1] + a[i];
    }

    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            dp_min[i][j] = INF;
            dp_max[i][j] = -INF;
        }
        dp_min[i][i] = 0;
        dp_max[i][i] = 0;
    }

    // 区间 DP：先枚举长度，再枚举左端点。
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= 2 * n; l++) {
            int r = l + len - 1;
            int seg_sum = range_sum(l, r);
            for (int k = l; k < r; k++) {
                dp_min[l][r] = min(dp_min[l][r], dp_min[l][k] + dp_min[k + 1][r] + seg_sum);
                dp_max[l][r] = max(dp_max[l][r], dp_max[l][k] + dp_max[k + 1][r] + seg_sum);
            }
        }
    }

    int ans_min = INF;
    int ans_max = -INF;
    for (int l = 1; l <= n; l++) {
        int r = l + n - 1;
        ans_min = min(ans_min, dp_min[l][r]);
        ans_max = max(ans_max, dp_max[l][r]);
    }

    cout << ans_min << '\n';
    cout << ans_max << '\n';
    return 0;
}
