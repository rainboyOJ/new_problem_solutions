/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:40
 * update_at: 2026-07-11 14:41
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

bool valid_len(int len) {
    // 朴素检查：枚举两段长度为 len 的子串，看是否相同。
    for (int i = 0; i + len <= n; i++) {
        for (int j = i + 1; j + len <= n; j++) {
            if (s.substr(i, len) == s.substr(j, len)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    for (int len = 1; len <= n; len++) {
        if (valid_len(len)) {
            cout << len << '\n';
            return 0;
        }
    }

    return 0;
}
