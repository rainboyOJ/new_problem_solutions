#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b;
    cin >> a >> b;

    // brute.cpp：小数据暴力枚举最小正整数解。
    for (i64 x = 1; x <= b; x++) {
        if ((a * x) % b == 1) {
            cout << x << '\n';
            return 0;
        }
    }

    return 0;
}
