#include <bits/stdc++.h>
using namespace std;

long long n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 设用了 b 个 5，那么剩下的部分必须全部由 4 组成。
    // 条件是 n - 5 * b >= 0 且能被 4 整除。
    long long max_five = n / 5;

    // 因为 5 ≡ 1 (mod 4)，所以 5 * b ≡ b (mod 4)。
    // 要让 n - 5 * b 被 4 整除，就等价于 b ≡ n (mod 4)。
    long long first_five = n % 4;

    long long ans = 0;
    if (first_five <= max_five) {
        // 合法的 b 形成一个公差为 4 的等差数列：
        // first_five, first_five + 4, first_five + 8, ...
        ans = (max_five - first_five) / 4 + 1;
    }

    cout << ans << '\n';
    return 0;
}
