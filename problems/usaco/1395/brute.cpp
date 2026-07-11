/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:45
 * update_at: 2026-07-11 12:46
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 100000;

int t;
int query_value[20];
bool is_pal[MAXS + 5];
bool win_pos[MAXS + 5]; // win_pos[i] 表示还剩 i 个石子时先手是否必胜

bool check_pal(int x) {
    string s = to_string(x);
    int l = 0;
    int r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

void build_dp(int max_s) {
    for (int i = 1; i <= max_s; i++) {
        is_pal[i] = check_pal(i);
    }

    win_pos[0] = false;
    for (int i = 1; i <= max_s; i++) {
        win_pos[i] = false;
        for (int take = 1; take <= i; take++) {
            if (is_pal[take] && !win_pos[i - take]) {
                win_pos[i] = true;
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    int max_s = 0;
    for (int i = 1; i <= t; i++) {
        string s;
        cin >> s;
        query_value[i] = stoi(s);
        if (max_s < query_value[i]) {
            max_s = query_value[i];
        }
    }

    build_dp(max_s);

    for (int i = 1; i <= t; i++) {
        cout << (win_pos[query_value[i]] ? 'B' : 'E') << '\n';
    }

    return 0;
}
