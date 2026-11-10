/**
 * Problem: luogu P3951 - [NOIP 2017 提高组] 小凯的疑惑
 * Author: rainboy
 * Date: 2026-11-10 23:55
 * Description: 赛尔维斯特 Frobenius 闭式公式求解
 */
#include <iostream>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    if (cin >> a >> b) {
        // a * b 最大可达 10^18，必须用 long long 防溢出
        ll ans = a * b - a - b;
        cout << ans << "\n";
    }

    return 0;
}
