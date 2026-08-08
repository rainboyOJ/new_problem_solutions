#include <bits/stdc++.h>
using namespace std;

int T;
long long h, x, y;

long long ceil_div(long long a, long long b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    while (T--) {
        cin >> h >> x >> y;

        if (y == 0) {
            cout << "No\n";
            continue;
        }

        // 设在最后一次补刀之前，英雄一共已经攻击了 t+1 次，
        // 防御塔已经攻击了 t 次。
        // 那么此时小兵剩余血量为：
        // h - t * x - t * y
        // 只要它仍然大于 0，并且这一次英雄攻击能把它补死即可。
        long long t = 0;
        if (h > y) {
            t = ceil_div(h - y, x + y);
        }

        if ((__int128)t * x < h) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
