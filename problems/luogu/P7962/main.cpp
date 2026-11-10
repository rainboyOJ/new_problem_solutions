/**
 * Problem: luogu P7962 - [NOIP2021] 方差
 * Author: rainboy
 * Date: 2026-11-10 23:15
 * Description: 差分置换 + 单谷性质 + 滚动数组 DP
 */
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

const int MAXN = 10005;
const int MAXM = 600005;
const ll INF = 1e18;

int n;
int a[MAXN];
int w[MAXN];
int s[MAXN];
ll f[2][MAXM];

void chkmin(ll &x, ll y) {
    if (y < x) x = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int m = a[n] * n;
    int diff_cnt = n - 1;
    for (int i = 1; i <= diff_cnt; ++i) {
        w[i] = a[i + 1] - a[i];
    }
    sort(w + 1, w + diff_cnt + 1);

    for (int i = 1; i <= diff_cnt; ++i) {
        s[i] = s[i - 1] + w[i];
    }

    int op = 0;
    f[op][0] = 0;
    for (int j = 1; j <= m; ++j) {
        f[op][j] = INF;
    }

    for (int i = 1; i <= diff_cnt; ++i) {
        if (w[i] == 0) continue;
        op ^= 1;
        for (int j = 0; j <= m; ++j) {
            f[op][j] = INF;
        }

        for (int j = 0; j <= m; ++j) {
            if (f[op ^ 1][j] == INF) continue;

            // 放在右边：新增元素 s[i]
            if (j + s[i] <= m) {
                chkmin(f[op][j + s[i]], f[op ^ 1][j] + static_cast<ll>(s[i]) * s[i]);
            }
            // 放在左边：已有 i 个元素全部加上 w[i]
            if (j + w[i] * i <= m) {
                chkmin(f[op][j + w[i] * i], f[op ^ 1][j] + 2LL * j * w[i] + static_cast<ll>(w[i]) * w[i] * i);
            }
        }
    }

    ll res = INF;
    for (int j = 0; j <= m; ++j) {
        if (f[op][j] != INF) {
            chkmin(res, static_cast<ll>(n) * f[op][j] - static_cast<ll>(j) * j);
        }
    }

    cout << res << "\n";

    return 0;
}
