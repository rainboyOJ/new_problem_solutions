/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:04
 * update_at: 2026-07-11 14:06
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n;
string s;

int calc_min_distance(const string &str) {
    int last = -1;
    int best = 1000000000;

    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            if (last != -1 && i - last < best) {
                best = i - last;
            }
            last = i;
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    int ans = 0;

    // 枚举两头新牛分别放在哪两个空栏。
    for (int i = 0; i < n; i++) {
        if (s[i] != '0') {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (s[j] != '0') {
                continue;
            }

            string t = s;
            t[i] = '1';
            t[j] = '1';

            int value = calc_min_distance(t);
            if (ans < value) {
                ans = value;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
