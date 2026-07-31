/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:13
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string password;
        cin >> password;

        bool has_letter = false;
        bool has_digit = false;
        bool has_special = false;
        int count[128] = {};
        for (int i = 0; i < (int)password.size(); i++) {
            unsigned char ch = password[i];
            count[ch]++;
            if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
                has_letter = true;
            } else if ('0' <= ch && ch <= '9') {
                has_digit = true;
            } else if (ch == '*' || ch == '#') {
                has_special = true;
            }
        }

        bool has_three_same = false;
        for (int i = 0; i < 128; i++) {
            if (count[i] > 2) {
                has_three_same = true;
                break;
            }
        }

        if (has_letter && has_digit && has_special && !has_three_same) cout << 2 << '\n';
        else if (has_letter && has_digit && has_special) cout << 1 << '\n';
        else cout << 0 << '\n';
    }

    return 0;
}
