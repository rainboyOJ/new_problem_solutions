/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll NEG = -(1LL << 62);
const ll INF = 1LL << 62;

int n, m;
int a[55], b[110];
ll pre[110];
ll dp_min[55][10], dp_max[55][10];

// 链 b[0..n-1]（pre 为其前缀和）分成 m 段的（最小乘积, 最大乘积）
pair<ll, ll> best_products(int n, int m) {
    for (int i = 0; i <= n; i++) {
        dp_min[i][0] = (i == 0) ? 1 : INF;
        dp_max[i][0] = (i == 0) ? 1 : NEG;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, m); j++) {
            ll best_min = INF, best_max = NEG;
            for (int k = j - 1; k < i; k++) {
                ll seg = ((pre[i] - pre[k]) % 10 + 10) % 10;
                if (dp_min[k][j - 1] < INF) {
                    ll v = dp_min[k][j - 1] * seg;
                    if (v < best_min) best_min = v;
                }
                if (dp_max[k][j - 1] > NEG / 2) {
                    ll v = dp_max[k][j - 1] * seg;
                    if (v > best_max) best_max = v;
                }
            }
            dp_min[i][j] = best_min;
            dp_max[i][j] = best_max;
        }
    }
    return make_pair(dp_min[n][m], dp_max[n][m]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    // 环 -> 链：复制一份
    for (int i = 0; i < 2 * n; i++) b[i] = a[i % n];
    pre[0] = 0;
    for (int i = 0; i < 2 * n; i++) pre[i + 1] = pre[i] + b[i];
    ll pre_orig[110];
    for (int i = 0; i <= 2 * n; i++) pre_orig[i] = pre[i];

    ll ans_min = INF, ans_max = NEG;
    for (int st = 0; st < n; st++) {
        // 该起点的前缀和：pre 换成局部窗口
        ll p[110];
        p[0] = 0;
        for (int i = 0; i <= n; i++) p[i] = pre_orig[st + i] - pre_orig[st];
        for (int i = 0; i <= n; i++) pre[i] = p[i];
        pair<ll, ll> r = best_products(n, m);
        ans_min = min(ans_min, r.first);
        ans_max = max(ans_max, r.second);
    }
    cout << ans_min << "\n" << ans_max << "\n";
    return 0;
}
