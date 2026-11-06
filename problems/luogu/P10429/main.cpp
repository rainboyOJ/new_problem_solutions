/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// P10429 拔河：两段不相交的连续区间，力量和的差最小
// 枚举右段的左端点 l，此时左段一定整体落在 [1, l-1] 里。
// 用 multiset 维护「[1, l-1] 内全部子段和」，右段每向右延伸一次就在里面二分找最接近的值。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll n;
ll a[MAXN];    // 每名同学的力量值
ll pre[MAXN];  // 前缀和，pre[i] = a[1] + ... + a[i]

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
}

void solve() {
    multiset<ll> left_sum; // 落在 [1, l-1] 内的所有子段和
    ll ans = LLONG_MAX;

    for (ll l = 2; l <= n; l++) {
        // 补进所有「以 l-1 结尾」的子段，此时 left_sum 覆盖 [1, l-1] 的全部子段
        for (ll i = 1; i <= l - 1; i++) {
            left_sum.insert(pre[l - 1] - pre[i - 1]);
        }
        // 右段从 l 开始，逐次向右延伸，取最接近的左段和
        for (ll r = l; r <= n; r++) {
            ll right = pre[r] - pre[l - 1];
            set<ll>::iterator it = left_sum.lower_bound(right);
            if (it != left_sum.end()) {
                ans = min(ans, *it - right);
            }
            if (it != left_sum.begin()) {
                --it;
                ans = min(ans, right - *it);
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
