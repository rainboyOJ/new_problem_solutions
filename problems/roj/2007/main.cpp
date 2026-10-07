/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:25
 * update_at: 2026-10-06 09:25
 */

#include <cstdio>
#include <string>

typedef long long ll;

const ll MAX_N = 300; // 题面要求的枚举上界：1 <= x <= 300

ll base;      // 输入的进制 B（2~20）
char buf[50]; // 临时存放一条 B 进制串，用于反转比较

// 把十进制非负整数 value 写成 base 进制串（最高位在前）。
// 10~19 的数码依次用 'A'~'J' 表示。
std::string to_base(ll value) {
    std::string digits = "";
    if (value == 0)
        return "0";
    while (value) {
        int r = value % base; // 余数即当前最低位
        char c;
        if (r < 10)
            c = '0' + r;
        else
            c = 'A' + r - 10; // 数码 10~19 记为 A~J
        digits = c + digits;  // 余数从低位到高位产生，故前置拼接保证高位在前
        value /= base;
    }
    return digits;
}

// 判断字符串 s 是否为回文串。
bool is_palindrome(const std::string &s) {
    ll i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    scanf("%lld", &base);
    // 按 x 升序枚举，输出天然有序；回文条件加在平方上而不是 x 上
    for (ll x = 1; x <= MAX_N; x++) {
        std::string sq = to_base(x * x);
        if (is_palindrome(sq))
            printf("%s %s\n", to_base(x).c_str(), sq.c_str());
    }
    return 0;
}
