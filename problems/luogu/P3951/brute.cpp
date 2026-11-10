/**
 * Problem: luogu P3951 - [NOIP 2017 提高组] 小凯的疑惑 (Brute Force)
 * Author: rainboy
 * Date: 2026-11-10 23:55
 * Description: 暴力标记与可达性搜索
 */
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    if (!(cin >> a >> b)) return 0;

    // 当规模较小时，使用同余系最小表示寻找最大无法表示的数
    ll max_unreachable = 0;
    for (ll y = 0; y < a; ++y) {
        ll val = y * b - a;
        if (val > max_unreachable) {
            max_unreachable = val;
        }
    }

    cout << max_unreachable << "\n";

    return 0;
}
