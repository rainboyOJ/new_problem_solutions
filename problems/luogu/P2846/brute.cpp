#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接用数组维护每盏灯当前是否打开。
// 区间翻转时逐个异或，区间查询时逐个统计。

const int MAXN = 100000 + 5;

int n, m;
int light_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0) {
            for (int i = l; i <= r; i++) {
                light_arr[i] ^= 1;
            }
        } else {
            int ans = 0;
            for (int i = l; i <= r; i++) {
                ans += light_arr[i];
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
