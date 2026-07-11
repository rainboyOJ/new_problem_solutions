/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:45
 * update_at: 2026-07-11 14:46
 */
// brute.cpp：小数据暴力解，使用选择序列递归枚举所有挤奶顺序。
#include <bits/stdc++.h>
using namespace std;

const int COW_CNT = 8;
const int MAXN = 10;

int n;
string cows[COW_CNT] = {
    "Beatrice",
    "Belinda",
    "Bella",
    "Bessie",
    "Betsy",
    "Blue",
    "Buttercup",
    "Sue"
};

string need_a[MAXN], need_b[MAXN]; // need_a[i] 必须和 need_b[i] 相邻
string choose_cow[COW_CNT];        // choose_cow[dep] 表示第 dep 个位置选择的奶牛
bool used[COW_CNT];
bool found;

int find_pos_in_choose(string name) {
    for (int i = 0; i < COW_CNT; i++) {
        if (choose_cow[i] == name) {
            return i;
        }
    }
    return -1;
}

bool check_order() {
    for (int i = 1; i <= n; i++) {
        int pos_a = find_pos_in_choose(need_a[i]);
        int pos_b = find_pos_in_choose(need_b[i]);
        if (abs(pos_a - pos_b) != 1) {
            return false;
        }
    }
    return true;
}

void dfs_build(int dep) {
    if (found) {
        return;
    }

    if (dep == COW_CNT) {
        if (check_order()) {
            for (int i = 0; i < COW_CNT; i++) {
                cout << choose_cow[i] << '\n';
            }
            found = true;
        }
        return;
    }

    // 第 dep 个位置选择一头还没使用过的奶牛。按字典序枚举，保证第一个合法解最小。
    for (int i = 0; i < COW_CNT; i++) {
        if (used[i]) {
            continue;
        }
        used[i] = true;
        choose_cow[dep] = cows[i];
        dfs_build(dep + 1);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string t;
        cin >> need_a[i] >> t >> t >> t >> t >> need_b[i];
    }

    dfs_build(0);

    return 0;
}
