/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:50
 * update_at: 2026-07-11 17:52
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int dice_a[4], dice_b[4], dice_c[4];
bool found_answer;

bool beats(int x[], int y[]) {
    int win = 0;
    int lose = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (x[i] > y[j]) {
                win++;
            }
            if (x[i] < y[j]) {
                lose++;
            }
        }
    }

    return win > lose;
}

bool check_non_transitive() {
    if (beats(dice_a, dice_b) && beats(dice_b, dice_c) && beats(dice_c, dice_a)) {
        return true;
    }
    if (beats(dice_b, dice_a) && beats(dice_a, dice_c) && beats(dice_c, dice_b)) {
        return true;
    }
    return false;
}

// 第 pos 层选择第三个骰子的第 pos 个面。
void dfs_choose_face(int pos) {
    if (found_answer) {
        return;
    }
    if (pos == 4) {
        if (check_non_transitive()) {
            found_answer = true;
        }
        return;
    }

    for (int value = 1; value <= 10; value++) {
        dice_c[pos] = value;
        dfs_choose_face(pos + 1);
    }
}

bool solve_case() {
    for (int i = 0; i < 4; i++) {
        cin >> dice_a[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> dice_b[i];
    }

    found_answer = false;
    dfs_choose_face(0);
    return found_answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        if (solve_case()) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }

    return 0;
}
