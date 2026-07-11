/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:45
 * update_at: 2026-07-11 18:49
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n, q, c_limit;
int original_c[MAXN], cur_c[MAXN];
int memory_a[MAXN], memory_h[MAXN];
bool found_answer;

bool check_all_memories() {
    for (int idx = 1; idx <= q; idx++) {
        int a = memory_a[idx];
        int h = memory_h[idx];

        int max_first_a = 0;
        for (int i = 1; i <= a; i++) {
            max_first_a = max(max_first_a, cur_c[i]);
        }

        for (int i = a + 1; i < h; i++) {
            if (cur_c[i] > max_first_a) {
                return false;
            }
        }

        if (cur_c[h] <= max_first_a) {
            return false;
        }
    }
    return true;
}

void dfs_fill(int pos) {
    if (found_answer) {
        return;
    }
    if (pos == n + 1) {
        if (check_all_memories()) {
            found_answer = true;
            for (int i = 1; i <= n; i++) {
                if (i > 1) {
                    cout << ' ';
                }
                cout << cur_c[i];
            }
            cout << '\n';
        }
        return;
    }

    if (original_c[pos] != 0) {
        cur_c[pos] = original_c[pos];
        dfs_fill(pos + 1);
        return;
    }

    for (int value = 1; value <= c_limit; value++) {
        cur_c[pos] = value;
        dfs_fill(pos + 1);
        if (found_answer) {
            return;
        }
    }
}

void solve_one_case() {
    cin >> n >> q >> c_limit;
    for (int i = 1; i <= n; i++) {
        cin >> original_c[i];
    }
    for (int i = 1; i <= q; i++) {
        cin >> memory_a[i] >> memory_h[i];
    }

    found_answer = false;
    dfs_fill(1);
    if (!found_answer) {
        cout << -1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
