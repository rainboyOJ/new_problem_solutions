#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 100000007LL;

int n;
i64 f[5005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    f[0] = 1;

    // Catalan 递推：
    // 任选与 1 号点配对的点，把圆分成左右两部分。
    // 如果左边有 i 对点，右边就有 n-1-i 对点。
    for (int i = 1; i <= n; i++) {
        f[i] = 0;
        for (int j = 0; j <= i - 1; j++) {
            f[i] = (f[i] + f[j] * f[i - 1 - j]) % MOD;
        }
    }

    cout << f[n] << '\n';

    return 0;
}
