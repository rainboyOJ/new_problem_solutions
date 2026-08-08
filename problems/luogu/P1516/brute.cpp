#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;

    // brute.cpp：小数据直接模拟跳跃过程。
    i64 cur_x = x;
    i64 cur_y = y;

    for (i64 step = 0; step <= L; step++) {
        if (cur_x == cur_y) {
            cout << step << '\n';
            return 0;
        }
        cur_x = (cur_x + m) % L;
        cur_y = (cur_y + n) % L;
    }

    cout << "Impossible\n";
    return 0;
}
