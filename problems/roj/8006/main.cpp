/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:42
 * update_at: 2026-10-06 16:42
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 数符表，下标即位值

// 将十进制数 v 转为 base 进制字符串（base 在 2~36 之间）
string to_base(ll v, int base) {
    if (v == 0) return "0";
    string out;
    while (v > 0) {
        out.push_back(DIGITS[v % base]);
        v /= base;
    }
    reverse(out.begin(), out.end());
    return out;
}

// 将 a 进制字符串 s 解析为十进制 ll
ll from_base(const string &s, int a) {
    ll v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        int digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else digit = c - 'A' + 10; // 大写字母 A-Z 对应 10-35
        v = v * a + digit;
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        string s;
        int a, b;
        cin >> s >> a >> b;
        ll v = from_base(s, a); // a 进制转十进制
        cout << to_base(v, b);  // 十进制转 b 进制
        if (n) cout << '\n';
    }
    return 0;
}
