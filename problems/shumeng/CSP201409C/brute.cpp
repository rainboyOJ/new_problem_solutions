/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:30
 */
// brute.cpp：小数据暴力解，枚举文本中的每个起点并逐字符比较。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pattern;
    int sensitive;
    int n;
    cin >> pattern >> sensitive >> n;

    for (int i = 0; i < n; i++) {
        string text;
        cin >> text;
        bool found = false;
        for (int start = 0; start + (int)pattern.size() <= (int)text.size(); start++) {
            bool same = true;
            for (int j = 0; j < (int)pattern.size(); j++) {
                char left = text[start + j];
                char right = pattern[j];
                if (!sensitive) {
                    if ('A' <= left && left <= 'Z') {
                        left = char(left - 'A' + 'a');
                    }
                    if ('A' <= right && right <= 'Z') {
                        right = char(right - 'A' + 'a');
                    }
                }
                if (left != right) {
                    same = false;
                    break;
                }
            }
            if (same) {
                found = true;
                break;
            }
        }
        if (found) {
            cout << text << '\n';
        }
    }

    return 0;
}
