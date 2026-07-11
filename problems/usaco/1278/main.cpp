/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:05
 * update_at: 2026-07-11 19:08
 */
#include <bits/stdc++.h>
using namespace std;

const int SIGMA = 52;

int T;

int char_id(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a';
    }
    return 26 + (c - 'A');
}

void solve_one() {
    string s, t;
    cin >> s >> t;

    int to[SIGMA];
    int indeg[SIGMA];
    int seen[SIGMA];
    bool in_target[SIGMA];
    memset(indeg, 0, sizeof(indeg));
    memset(seen, 0, sizeof(seen));
    memset(in_target, 0, sizeof(in_target));

    for (int i = 0; i < SIGMA; i++) {
        to[i] = -1;
    }

    bool possible = true;
    for (int i = 0; i < (int)s.size(); i++) {
        int x = char_id(s[i]);
        int y = char_id(t[i]);
        in_target[y] = true;

        if (to[x] != -1 && to[x] != y) {
            possible = false;
        }
        to[x] = y;
    }

    int target_cnt = 0;
    for (int i = 0; i < SIGMA; i++) {
        if (in_target[i]) target_cnt++;
    }

    if (s != t && target_cnt == SIGMA) {
        possible = false;
    }

    if (!possible) {
        cout << -1 << '\n';
        return;
    }

    int ans = 0;
    for (int i = 0; i < SIGMA; i++) {
        if (to[i] != -1 && to[i] != i) {
            ans++;
            indeg[to[i]]++;
        }
    }

    // 函数图中，纯环需要额外借一个临时字符打破。
    for (int start = 0; start < SIGMA; start++) {
        if (seen[start] != 0) continue;

        int x = start;
        while (x != -1 && seen[x] == 0) {
            seen[x] = start + 1;
            x = to[x];
        }

        if (x != -1 && to[x] != x && seen[x] == start + 1) {
            int y = x;
            bool has_extra_in = false;
            do {
                if (indeg[y] > 1) {
                    has_extra_in = true;
                }
                y = to[y];
            } while (y != x);

            if (!has_extra_in) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
