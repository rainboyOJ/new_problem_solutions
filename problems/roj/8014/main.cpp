/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:51
 * update_at: 2026-10-06 16:51
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll divisor_count_sum(ll n) {
    // S(n) = sum_{d=1}^{n} floor(n/d)，整除分块按相同商区间累加
    ll total = 0;
    ll l = 1;
    while (l <= n) {
        ll q = n / l;       // 当前块的商
        ll r = n / q;       // 商仍为 q 的最大右端点
        total += q * (r - l + 1);
        l = r + 1;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t1, t2;
    if (!(cin >> t1 >> t2)) return 0;
    cout << divisor_count_sum(t2) - divisor_count_sum(t1 - 1) << "\n";
    return 0;
}
