/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:52
 * update_at: 2026-10-06 13:52
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

ll p1, p2, p3; // 展开方式 / 重复个数 / 是否逆序
string s;

// 生成 left 与 right 之间的展开段（不包括两端）
string expand(char left, char right) {
    if (p1 == 3) {
        // 星号填充，个数 = 中间字符数 × p2
        return string(p2 * (right - left - 1), '*');
    }
    string seg;
    for (char c = left + 1; c < right; ++c) {
        char out = c;
        if (p1 == 2 && left >= 'a' && left <= 'z') {
            out = c - 'a' + 'A'; // 字母子串转大写
        }
        seg.append(p2, out); // 每个字符重复 p2 次
    }
    if (p3 == 2) {
        reverse(seg.begin(), seg.end()); // 逆序
    }
    return seg;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> p1 >> p2 >> p3;
    cin >> s;
    string res;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '-' && i > 0 && i + 1 < s.size()) {
            char l = s[i - 1];
            char r = s[i + 1];
            bool same_alpha = (l >= 'a' && l <= 'z' && r >= 'a' && r <= 'z');
            bool same_digit = (l >= '0' && l <= '9' && r >= '0' && r <= '9');
            if ((same_alpha || same_digit) && l < r) {
                res += expand(l, r);
                continue;
            }
        }
        res += s[i];
    }
    cout << res << '\n';
    return 0;
}
