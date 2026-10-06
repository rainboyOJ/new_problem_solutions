/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:46
 * update_at: 2026-10-06 09:46
 */
#include <iostream>
using namespace std;

typedef long long ll;

// 各数位 0~9 对应的罗马片段：digit[0] 千位，digit[1] 百位，digit[2] 十位，digit[3] 个位
const char *digit[4][10] = {
    {"", "M", "MM", "MMM", "", "", "", "", "", ""},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
};

// 按数字表中从小到大的顺序输出：I V X L C D M
const char ROMAN_CHAR[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

ll cnt[26]; // cnt[c - 'A'] 记录字符 c 在页码 1..N 的罗马表示中出现次数

// 把一页页码 n 的罗马表示逐字符计入计数器
void count_page(ll n) {
    int d[4]; // d[0] 千位，d[1] 百位，d[2] 十位，d[3] 个位
    d[0] = n / 1000;
    d[1] = n / 100 % 10;
    d[2] = n / 10 % 10;
    d[3] = n % 10;
    for (int p = 0; p < 4; p++) {
        const char *s = digit[p][d[p]];
        for (int k = 0; s[k] != '\0'; k++) {
            cnt[s[k] - 'A']++;
        }
    }
}

int main() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        count_page(i);
    }
    // 按 I V X L C D M 顺序输出出现过的字符
    for (int k = 0; k < 7; k++) {
        int idx = ROMAN_CHAR[k] - 'A';
        if (cnt[idx] > 0) {
            cout << ROMAN_CHAR[k] << " " << cnt[idx] << "\n";
        }
    }
    return 0;
}
