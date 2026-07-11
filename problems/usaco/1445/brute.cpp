/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:38
 * update_at: 2026-07-11 15:41
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int C = 26;

int n, f;
string s;
bool possible[C][C]; // possible[a][b] 表示 abb 可以达到频次要求。

bool is_moo_string(const string &t, int pos) {
    if (pos < 0 || pos + 2 >= (int)t.size()) return false;
    return t[pos] != t[pos + 1] && t[pos + 1] == t[pos + 2];
}

void check_string(const string &t) {
    int cnt[C][C];
    memset(cnt, 0, sizeof(cnt));

    for (int i = 0; i + 2 < (int)t.size(); i++) {
        if (!is_moo_string(t, i)) continue;

        int a = t[i] - 'a';
        int b = t[i + 1] - 'a';
        cnt[a][b]++;
        if (cnt[a][b] >= f) {
            possible[a][b] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> f;
    cin >> s;

    // 小数据暴力：枚举改哪一个位置、改成哪个字符，再完整重新统计所有 moo。
    for (int pos = 0; pos < n; pos++) {
        string t = s;
        for (char c = 'a'; c <= 'z'; c++) {
            t[pos] = c;
            check_string(t);
        }
    }

    int total = 0;
    for (int a = 0; a < C; a++) {
        for (int b = 0; b < C; b++) {
            if (a != b && possible[a][b]) total++;
        }
    }

    cout << total << '\n';
    for (int a = 0; a < C; a++) {
        for (int b = 0; b < C; b++) {
            if (a == b || !possible[a][b]) continue;
            cout << char('a' + a) << char('a' + b) << char('a' + b) << '\n';
        }
    }

    return 0;
}
