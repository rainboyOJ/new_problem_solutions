/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:45
 * update_at: 2026-10-06 01:45
 */

#include <iostream>
#include <climits>
using namespace std;

typedef long long ll;

ll mx = LLONG_MIN; // 当前最大值
ll mn = LLONG_MAX; // 当前最小值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m, n;
    cin >> m >> n;

    for (ll i = 0; i < m; ++i) {
        for (ll j = 0; j < n; ++j) {
            ll x;
            cin >> x;
            if (x > mx) mx = x;
            if (x < mn) mn = x;
        }
    }

    cout << mx - mn << "\n";
    return 0;
}
