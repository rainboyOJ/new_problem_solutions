/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// brute.cpp：小数据暴力，枚举两段区间的四个端点
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, a[60], pre[60];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (ll i = 1; i <= n; i++) { cin >> a[i]; pre[i] = pre[i - 1] + a[i]; }
    ll ans = LLONG_MAX;
    for (ll l1 = 1; l1 <= n; l1++)
        for (ll r1 = l1; r1 <= n; r1++)
            for (ll l2 = r1 + 1; l2 <= n; l2++)
                for (ll r2 = l2; r2 <= n; r2++) {
                    ll s1 = pre[r1] - pre[l1 - 1];
                    ll s2 = pre[r2] - pre[l2 - 1];
                    ans = min(ans, llabs(s1 - s2));
                }
    cout << ans << '\n';
}
