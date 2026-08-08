#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护每次乘法操作当前是否还“有效”，
// 每次输出时重新扫描所有有效乘数并求乘积。

const int MAXQ = 100000 + 5;

long long value_arr[MAXQ];
int alive[MAXQ];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int q;
        long long mod_value;
        cin >> q >> mod_value;

        for (int i = 1; i <= q; i++) {
            value_arr[i] = 1;
            alive[i] = 0;
        }

        for (int i = 1; i <= q; i++) {
            int op;
            long long x;
            cin >> op >> x;

            if (op == 1) {
                value_arr[i] = x % mod_value;
                alive[i] = 1;
            } else {
                alive[(int)x] = 0;
            }

            long long ans = 1 % mod_value;
            for (int j = 1; j <= q; j++) {
                if (alive[j]) {
                    ans = ans * value_arr[j] % mod_value;
                }
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
