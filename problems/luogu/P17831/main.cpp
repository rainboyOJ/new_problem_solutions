/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:08
 * update_at: 2026-10-31 21:08
 */
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 500005;
ll a[MAXN]; // 排序后的原始数值，窗口移动时不修改它们

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    if (!(cin >> n >> m)) return 0;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    ll ans = 1;
    ll l = 1;
    ll sum = 0; // 当前区间 [l, r] 的元素和

    for (ll r = 1; r <= n; r++) {
        sum += a[r];
        // 都变成 a[r]，需要补的量 = 目标总和 - 现在的总和。
        while (a[r] * (r - l + 1) - sum > m) {
            sum -= a[l]; // 预算不够，先放弃最小、补起来最贵的数
            l++;
        }
        ans = max(ans, r - l + 1);
    }

    cout << ans << "\n";
    return 0;
}
