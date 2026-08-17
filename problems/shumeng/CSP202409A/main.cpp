/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

// 判断单个字符属于哪类：字母 / 数字 / 特殊字符
void classify(char ch, bool &has_letter, bool &has_digit, bool &has_special) {
    if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
        has_letter = true;
    } else if ('0' <= ch && ch <= '9') {
        has_digit = true;
    } else {
        has_special = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string password;
        cin >> password;

        // 统计三类字符是否出现，以及每个字符的出现次数
        bool has_letter = false;
        bool has_digit = false;
        bool has_special = false;
        int count[128] = {};
        for (int i = 0; i < (int)password.size(); i++) {
            unsigned char ch = password[i];
            count[ch]++;
            classify((char)ch, has_letter, has_digit, has_special);
        }

        // 是否存在出现次数超过 2 的字符
        bool has_three_same = false;
        for (int i = 0; i < 128; i++) {
            if (count[i] > 2) {
                has_three_same = true;
                break;
            }
        }

        // 高安全度：三类字符齐全且每个字符至多出现 2 次
        if (has_letter && has_digit && has_special && !has_three_same) {
            cout << 2 << '\n';
        } else if (has_letter && has_digit && has_special) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

    return 0;
}