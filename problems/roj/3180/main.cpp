/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:58
 * update_at: 2026-10-06 11:58
 */
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

// cnt(n, d)：统计 1~n 的十进制写法中数字 d 出现的总次数（逐位算贡献）。
ll cnt(ll n, ll d) {
    ll res = 0;
    for (ll p = 1; p <= n; p *= 10) {
        ll high = n / (p * 10); // 高位部分：第 p 位左边的数
        ll cur = n / p % 10;    // 当前第 p 位上的数字
        ll low = n % p;         // 低位部分：第 p 位右边的数
        if (d == 0) {
            // 0 不能作前导零，高位部分必须至少为 1
            if (high >= 1) {
                res += (high - 1) * p; // 高位取 1~high-1，低位任取
                if (cur == 0) {
                    res += low + 1; // 高位恰好等于 high，低位只能取 0~low
                } else {
                    res += p; // 当前位本来就是 0，低位任取
                }
            }
        } else {
            res += high * p; // 高位取 0~high-1，低位任取
            if (cur > d) {
                res += p;
            } else if (cur == d) {
                res += low + 1;
            }
        }
    }
    return res;
}

int main() {
    ll a, b;
    while (cin >> a >> b && (a != 0 || b != 0)) {
        if (a > b) {
            swap(a, b); // 题面中 a 可能大于 b
        }
        for (ll d = 0; d <= 9; d++) {
            if (d > 0) {
                cout << ' ';
            }
            cout << cnt(b, d) - cnt(a - 1, d); // 前缀差求区间内出现次数
        }
        cout << '\n';
    }
    return 0;
}
