#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b;
    cin >> a >> b;

    i64 best_d = a + 1;
    i64 best_x = -1;
    i64 best_y = -1;

    // 直接枚举“桶 -> B 杯”做多少次。
    // 每做一次，等价于当前 A 杯里的酒量加上 b，再按 a 处理溢出。
    for (i64 y = 1; y <= a; y++) {
        i64 total = y * b;
        i64 d = total % a;
        if (d == 0) {
            d = a;
        }
        i64 x = (total - d) / a;

        if (d < best_d) {
            best_d = d;
            best_x = x;
            best_y = y;
        }
    }

    cout << best_d << '\n';
    cout << best_x << ' ' << best_y << '\n';

    return 0;
}
