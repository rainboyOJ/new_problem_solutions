/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:22
 */
// brute.cpp：小轮数直接展开整个字符串，再逐位置比较模式串。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string pattern, text = "1";
    cin >> n >> pattern;
    while (n--) {
        string next;
        for (int i = 0; i < (int)text.size(); i++) {
            if (text[i] == '1') next += '2';
            else if (text[i] == '2') next += '4';
            else if (text[i] == '4') next += "16";
            else next += "64";
        }
        text.swap(next);
    }
    int answer = 0;
    for (int i = 0; i + (int)pattern.size() <= (int)text.size(); i++) {
        if (text.compare(i, pattern.size(), pattern) == 0) answer++;
    }
    cout << answer << '\n';

    return 0;
}
