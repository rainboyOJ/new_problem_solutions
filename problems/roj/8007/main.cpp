/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:42
 * update_at: 2026-10-06 16:42
 */
#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef long long ll;

string binary_text;  // 毛毛写错的二进制表示
string ternary_text; // 毛毛写错的三进制表示
set<ll> binary_candidates; // 把二进制表示逐位改正后能得到的全部数值

// 把 base 进制的字符串转成十进制数值
ll to_value(const string &s, int base) {
    ll len = s.size();
    ll value = 0;
    for (ll i = 0; i < len; i++) {
        value = value * base + (s[i] - '0');
    }
    return value;
}

int main() {
    cin >> binary_text >> ternary_text;

    ll binary_len = binary_text.size();
    ll ternary_len = ternary_text.size();

    // 二进制只可能是某一位写反，逐位翻转得到候选值（含前导 0 的情况）
    for (ll i = 0; i < binary_len; i++) {
        string fixed = binary_text;
        fixed[i] = (fixed[i] == '0' ? '1' : '0');
        binary_candidates.insert(to_value(fixed, 2));
    }

    // 三进制某一位写成了另外的两个数字之一，逐位换成其余数字
    // 答案必须在两个候选集合的交集中，且题目保证解唯一
    for (ll i = 0; i < ternary_len; i++) {
        for (int d = 0; d < 3; d++) {
            if (d == ternary_text[i] - '0') {
                continue;
            }
            string fixed = ternary_text;
            fixed[i] = '0' + d;
            ll value = to_value(fixed, 3);
            if (binary_candidates.count(value)) {
                cout << value << endl;
                return 0;
            }
        }
    }

    return 0;
}
