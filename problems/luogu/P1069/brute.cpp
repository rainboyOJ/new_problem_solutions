#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 对每种细胞直接模拟 S_i^t mod M 的变化，
// 找最早什么时候余数变成 0；如果余数开始循环还没变成 0，就说明无解。

int n;
long long m1, m2;
long long s[25];

long long power_small(long long a, long long b) {
    long long ans = 1;
    while (b--) {
        ans *= a;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> m1 >> m2;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    long long M = power_small(m1, m2);

    if (M == 1) {
        cout << 0 << '\n';
        return 0;
    }

    long long ans = (long long)4e18;

    for (int i = 1; i <= n; i++) {
        vector<int> vis((int)M, 0);
        long long rem = 1 % M;
        long long t = 0;

        while (!vis[(int)rem]) {
            vis[(int)rem] = 1;
            if (rem == 0) {
                ans = min(ans, t);
                break;
            }
            rem = rem * (s[i] % M) % M;
            t++;
        }
    }

    if (ans == (long long)4e18) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
