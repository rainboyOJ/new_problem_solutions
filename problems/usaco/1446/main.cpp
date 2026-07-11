/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:32
 * update_at: 2026-07-11 18:35
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;

int n;
ll a[MAXN], prefix_sum[MAXN];

void solve_one_case() {
    cin >> n;
    prefix_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    int len = n / 2 + 1;
    ll bessie = (1LL << 62);

    // Bessie 最终保留一个长度为 n/2+1 的连续窗口，取其中最小的和。
    for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        ll sum = prefix_sum[r] - prefix_sum[l - 1];
        if (sum < bessie) {
            bessie = sum;
        }
    }

    ll total = prefix_sum[n];
    cout << bessie << ' ' << total - bessie << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
