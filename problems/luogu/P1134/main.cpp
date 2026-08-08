#include <bits/stdc++.h>
using namespace std;

int n;
int tail_digit[5] = {1, 1, 2, 6, 4}; // 0! 到 4! 的最右非零位

// 快速幂：计算 base^exp mod 10。
int quick_pow(int base, int exp) {
    int ans = 1;
    base %= 10;

    while (exp > 0) {
        if (exp & 1) {
            ans = ans * base % 10;
        }
        base = base * base % 10;
        exp >>= 1;
    }

    return ans;
}

// solve(x) 表示 x! 的最右非零位。
int solve(int x) {
    if (x < 5) {
        return tail_digit[x];
    }

    int q = x / 5;
    int r = x % 5;

    // 经典递推：
    // D(x) = D(x / 5) * D(x % 5) * 2^(x / 5) mod 10
    return solve(q) * tail_digit[r] % 10 * quick_pow(2, q) % 10;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cout << solve(n) << '\n';

    return 0;
}
