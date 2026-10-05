/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:14
 * update_at: 2026-10-05 23:14
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string p, q, r;

// 把数字串 s 当作 base 进制转成十进制；出现非法数字则返回 -1
ll to_base(const string &s, int base) {
    ll value = 0;
    for (char ch : s) {
        int digit = ch - '0';
        if (digit >= base) return -1; // 某一位数字超出进制允许范围，非法
        value = value * base + digit;
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> p >> q >> r;
    for (int base = 2; base <= 40; ++base) {
        ll pv = to_base(p, base);
        ll qv = to_base(q, base);
        ll rv = to_base(r, base);
        if (pv >= 0 && qv >= 0 && rv >= 0 && pv * qv == rv) {
            cout << base << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
    return 0;
}
