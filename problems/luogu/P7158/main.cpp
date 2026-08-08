#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int MOD = 998244353;

int t;
int ans[MAXN + 5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // n = 1 时，一位数可以是 0~9，共 10 个。
    // 因为 k 在 1~9 中，只有数字 k 本身会出现 1 次，所以合法数有 9 个。
    ans[1] = 9;

    // 下面维护“长度至少为 1，且首位已经确定为非 0”时的奇偶状态。
    // len = 1 时：
    // - 偶数个 k：首位不是 k，有 8 种
    // - 奇数个 k：首位是 k，有 1 种
    long long even = 8;
    long long odd = 1;

    for (int len = 2; len <= MAXN; len++) {
        long long new_even = (even * 9 + odd) % MOD;
        long long new_odd = (even + odd * 9) % MOD;
        even = new_even;
        odd = new_odd;
        ans[len] = (int)even;
    }

    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << ans[n] << '\n';
    }

    return 0;
}
