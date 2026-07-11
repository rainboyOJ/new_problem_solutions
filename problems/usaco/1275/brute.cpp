/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:55
 * update_at: 2026-07-11 17:03
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
char breed[MAXN];
int e[MAXN];

bool list_has(int from, int to) {
    return from <= to && to <= e[from];
}

bool covers_all_same_breed(int leader, char c) {
    for (int i = 1; i <= n; i++) {
        if (breed[i] == c && !list_has(leader, i)) {
            return false;
        }
    }
    return true;
}

bool can_be_leader(int leader, char c, int other_leader) {
    if (covers_all_same_breed(leader, c)) {
        return true;
    }
    return list_has(leader, other_leader);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> n;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        breed[i] = s[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> e[i];
    }

    int ans = 0;

    // 直接枚举 G leader 和 H leader，按题意逐一检查。
    for (int g = 1; g <= n; g++) {
        if (breed[g] != 'G') {
            continue;
        }
        for (int h = 1; h <= n; h++) {
            if (breed[h] != 'H') {
                continue;
            }
            if (can_be_leader(g, 'G', h) && can_be_leader(h, 'H', g)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
