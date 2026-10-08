/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:48
 * update_at: 2026-10-08 22:48
 */
// roj 5035《【例4.19】阶乘之和》（一本通 2033）
//
// 题意：输入 n（1 <= n <= 999999），求 S = 1! + 2! + ... + n! 的末 6 位，
//   输出不含前导 0。n=10 时 S = 4037913，末 6 位是 037913，应输出 37913。
//
// 做法：同余定理边算边取模，fac 存 i! mod 10^6，sum 存前 i 项和 mod 10^6：
//   (a*b) % m = ((a%m) * (b%m)) % m，(a+b) % m = ((a%m) + (b%m)) % m。
//   又因 25! 中因子 5 的个数为 6（5/10/15/20 各 1 个，25 含 2 个），因子 2 更多，
//   所以 10^6 | 25!，进而 i >= 25 时 i! ≡ 0 (mod 10^6)，fac 一旦为 0 后面恒为 0。
// 输出：用普通整数输出（不含前导 0），绝不能用 %06lld 之类的补零格式。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000; // 末 6 位 = 对 10^6 取模

ll n;   // 题面输入，上界 999999
ll sum; // 答案：1! + 2! + ... + n! 的末 6 位

// 递推求阶乘之和的末 6 位。i >= 25 后 fac 恒为 0，此后每项贡献为 0，可提前退出。
void solve() {
    ll fac = 1; // fac：当前 i! 的末 6 位
    for (ll i = 1; i <= n; i++) {
        fac = fac * i % MOD;
        if (fac == 0) {
            break; // i >= 25 起 fac 恒为 0，后续项不会改变答案
        }
        sum = (sum + fac) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> n) {
        solve();
        cout << sum << "\n"; // 普通整数输出，天然不含前导 0
    }

    return 0;
}
