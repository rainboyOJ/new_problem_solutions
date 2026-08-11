/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 10:05
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
long long s, now_value;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    now_value = s;
    for (int i = 1; i <= n; i++) {
        string word;
        cin >> word;

        if (word.find("kirai") != string::npos) {
            if (now_value >= 0) now_value = 0;
        }
        else if (word.find("daishuki") != string::npos) {
            now_value += 2;
        }
        else if (word.find("shuki") != string::npos) {
            now_value += 1;
        }
        else {
            now_value -= 1;
        }
    }

    if (now_value > 0) cout << now_value - s << '\n';
    else cout << "shuki\n";
    return 0;
}
