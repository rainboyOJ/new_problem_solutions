/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:05
 * update_at: 2026-10-08 04:05
 */
// main.cpp：一本通 1801《异或》。求 [1,n] 内满足 gcd(a,b) = a xor b 的无序数对个数。
// 与 main.py 同一算法：由等号链 gcd(a,b) = a-b = a xor b = c 把问题化为
// "枚举公约数 c 与其倍数 a，判断 (a-c) & c == 0"，O(n log n)。
//
// 题意与规模：30% n<=1000，60% n<=10^5，100% n<=10^7；时限 1000ms / 128MB。
//
// 关键观察（等号链）：
//   取 a > b（a = b 时 gcd = a 而 a xor a = 0，无解，故无序对与 a > b 一一对应）。
//   一方面 gcd(a,b) | (a-b) 故 gcd(a,b) <= a-b；
//   另一方面任意整数有 a xor b >= a-b（当且仅当 a & b == 0 且 b <= a 时取等）。
//   两式夹逼使 gcd(a,b) = a xor b 时三者相等：gcd(a,b) = a-b = a xor b =: c。
//   反过来，c 是 a 的约数且 (a-c) & c == 0 时 a = b + c 做加法不进位，
//   于是 a xor b = c，且 gcd(a,b) = gcd(a, a-c) = gcd(a, c) = c（因 c | a），条件成立。
//   每个合法无序对唯一对应 (c = gcd, a)，枚举不会重复计数。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll n;                                  // 题目给定的上界，规模到 1e7，故用 ll
    if (scanf("%lld", &n) != 1) return 0;  // 空输入直接结束
    ll ans = 0;                            // 满足条件的无序对个数
    // 枚举公约数 c 与其倍数 a（a >= 2c，保证 b = a - c >= 1 且 b < a）
    for (ll c = 1; c + c <= n; ++c) {
        for (ll a = c + c; a <= n; a += c) {
            // (a-c) & c == 0 等价于 b + c 相加无进位，即 b xor a == c
            if (((a - c) & c) == 0) ++ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
