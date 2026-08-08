#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // brute.cpp：小数据暴力解。
    // 直接从 1 累乘到 n，每次把末尾的 0 去掉，
    // 再保留一部分低位，避免数字无限增长。
    long long ans = 1;

    for (int i = 1; i <= n; i++) {
        ans *= i;

        while (ans % 10 == 0) {
            ans /= 10;
        }

        // 只保留低 12 位已经足够判断最后一个非零数字。
        ans %= 1000000000000LL;
    }

    cout << ans % 10 << '\n';

    return 0;
}
