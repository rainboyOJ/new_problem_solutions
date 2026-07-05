#include <bits/stdc++.h>
using namespace std;

int cnt[10]; // cnt[d] 表示数字 d 在字符串中出现的次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    for (int i = 0; i < (int)s.size(); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            cnt[s[i] - '0']++;
        }
    }

    // 为了得到最大的正整数，应使用所有数字，并按从大到小排列。
    for (int d = 9; d >= 0; d--) {
        for (int i = 1; i <= cnt[d]; i++) {
            cout << d;
        }
    }
    cout << '\n';

    return 0;
}
