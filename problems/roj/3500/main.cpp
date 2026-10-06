/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:08
 * update_at: 2026-10-06 12:08
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const char DIGITS[] = "0123456789ABCDEFGHIJ"; // 数码 0..19，超过 9 用 A..J

// 把十进制 v 转成以 base（base < 0）为基数的数码串，高位在前
string to_negative_base(ll v, ll base) {
    if (v == 0) return "0";
    string s;
    while (v != 0) {
        ll q = v / base;   // C++ 向零截断
        ll r = v % base;   // 余数符号跟随被除数，可能为负
        if (r < 0) {       // 借一位：商 +1，余数加上 |base|
            r -= base;     // base 为负，减 base 等价于加 |base|
            q += 1;
        }
        s.push_back(DIGITS[r]);
        v = q;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, negR;
    while (cin >> n >> negR) {
        string digits = to_negative_base(n, negR);
        cout << n << "=" << digits << "(base" << negR << ")\n";
    }
    return 0;
}
