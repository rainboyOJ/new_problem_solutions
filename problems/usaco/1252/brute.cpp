/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:15
 * update_at: 2026-07-11 17:16
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int INF = 1e9;

int n, k;
char cow[MAXN];
char choose_plan[MAXN]; // 每个位置选择 '.', 'G', 'H'
char best_plan[MAXN];
int best_count;

bool current_plan_valid() {
    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int j = 1; j <= n; j++) {
            if (choose_plan[j] == cow[i] && abs(i - j) <= k) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            return false;
        }
    }
    return true;
}

int current_patch_count() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_plan[i] != '.') {
            cnt++;
        }
    }
    return cnt;
}

void save_best_plan(int cnt) {
    best_count = cnt;
    for (int i = 1; i <= n; i++) {
        best_plan[i] = choose_plan[i];
    }
}

// 第 dep 层决定第 dep 个位置不种、种 G 草或种 H 草。
void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (current_plan_valid()) {
            int cnt = current_patch_count();
            if (cnt < best_count) {
                save_best_plan(cnt);
            }
        }
        return;
    }

    choose_plan[dep] = '.';
    dfs_choose(dep + 1);

    choose_plan[dep] = 'G';
    dfs_choose(dep + 1);

    choose_plan[dep] = 'H';
    dfs_choose(dep + 1);
}

void solve_case() {
    string s;
    cin >> n >> k;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        cow[i] = s[i - 1];
        choose_plan[i] = '.';
        best_plan[i] = '.';
    }

    best_count = INF;
    dfs_choose(1);

    cout << best_count << '\n';
    for (int i = 1; i <= n; i++) {
        cout << best_plan[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
