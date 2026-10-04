/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:48
 * update_at: 2026-10-05 00:48
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

typedef long long ll;

ll n;
ll a[MAXN]; // 第 i 个小朋友原有的糖果数（下标从 0 开始）
ll c[MAXN]; // c[i] = sum_{k=0}^{i-1}(a[k] - avg)，即前 i 个人的糖果偏差前缀和，c[0] = 0

void read_input() {
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void solve() {
    // 先求平均数：总糖果数一定能被 n 整除。
    ll total = 0;
    for (ll i = 0; i < n; i++) {
        total += a[i];
    }
    ll avg = total / n;

    // 设第 1 个人顺时针传给第 n 个人的数量为自由变量 x，
    // 则与下一个人之间的传递量可表示为 x - c[i]，
    // 总代价 = sum |x - c[i]|，取 x 为 c[] 的中位数时最小。
    c[0] = 0;
    for (ll i = 1; i < n; i++) {
        c[i] = c[i - 1] + (a[i - 1] - avg);
    }

    sort(c, c + n);
    ll mid = c[n / 2];

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (c[i] > mid) {
            ans += c[i] - mid;
        } else {
            ans += mid - c[i];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
