/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:55
 * update_at: 2026-10-06 14:55
 */

// main.cpp：把 62 进制数位串在任意两种进制之间转换。
// 数值最大约 62^62，装不进 long long，所以把整数存成数位数组，
// 只需要一种原子操作：数位的长除法（除以目标进制 c，同时得到商和余数）。

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

typedef long long ll;

const ll MAXL = 200;  // 输入串最长约 109 位，开 200 足够

// 62 个数位字符：'0'-'9' 权值 0-9，'A'-'Z' 权值 10-35，'a'-'z' 权值 36-61
const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

ll T;
ll base;                 // 源进制 b
ll target;               // 目标进制 c
ll digits[MAXL + 5];     // 当前数位数组（高位在前），每次长除法后变成商
ll q[MAXL + 5];          // 长除法的临时商数组
ll len;                  // digits 当前的位数
std::string out;         // 收集到的余数，即目标进制的数位（从低到高）

// 按字符查它在 62 个数位里的权值，不在集合里返回 -1
ll char_value(char ch) {
    for (ll i = 0; i < 62; i++)
        if (DIGITS[i] == ch) return i;
    return -1;
}

// 把数位 digits（共 len 位，基数为 base）除以 div，就地更新为商，
// 返回余数；除完跳过商的前导零，len 变成商的实际位数。
ll divide_small(ll div) {
    ll rem = 0;  // 从高位往低位下落的进位，始终小于 div <= 62
    for (ll i = 1; i <= len; i++) {
        ll x = rem * base + digits[i];  // x 最大 61*62+61 = 3843，int 都够
        q[i] = x / div;
        rem = x % div;
    }
    // 找商的第一个非零位；商可能全零（此时余数就是原数本身取模）
    ll first = 1;
    while (first <= len && q[first] == 0) first++;
    ll new_len = len - (first - 1);  // 商的位数（可能为 0）
    for (ll i = 1; i <= new_len; i++)
        digits[i] = q[first + i - 1];
    len = new_len;
    return rem;
}

// 反复长除法：每轮余数是目标进制的最低一位，逆序拼出答案
std::string convert() {
    out.clear();
    while (len > 0) {
        ll rem = divide_small(target);
        out += DIGITS[rem];
    }
    std::string res;
    for (ll i = (ll)out.size() - 1; i >= 0; i--)  // 余数从低到高，翻转
        res += out[i];
    if (res.empty()) res = "0";  // 原数就是 0
    return res;
}

void solve() {
    scanf("%lld", &T);
    while (T--) {
        char str[MAXL + 5];
        scanf("%lld %lld %s", &base, &target, str);
        len = strlen(str);
        for (ll i = 0; i < len; i++)  // 高位在前，直接查表得到数位
            digits[i + 1] = char_value(str[i]);

        std::string ans = convert();
        printf("%lld %s\n", base, str);        // 第一行：源进制与原数
        printf("%lld %s\n\n", target, ans.c_str());  // 第二行：目标进制与新数，第三行为空行
    }
}

int main() {
    solve();
    return 0;
}
