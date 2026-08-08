#include <bits/stdc++.h>
using namespace std;

// brute.cpp：暴力枚举所有合法 n 位数，统计其中 digit k 出现次数为偶数的数量。

const int MOD = 998244353;

int t;
int n, k;
int ans;

void dfs(int pos, int parity) {
    if (pos > n) {
        if (parity == 0) {
            ans++;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
        return;
    }

    int start = 0;
    if (n > 1 && pos == 1) {
        start = 1;
    }

    for (int digit = start; digit <= 9; digit++) {
        int next_parity = parity;
        if (digit == k) {
            next_parity ^= 1;
        }
        dfs(pos + 1, next_parity);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n >> k;
        ans = 0;
        dfs(1, 0);
        cout << ans << '\n';
    }

    return 0;
}
