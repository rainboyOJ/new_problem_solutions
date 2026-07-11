/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:50
 * update_at: 2026-07-11 17:52
 */
#include <bits/stdc++.h>
using namespace std;

int dice_a[4], dice_b[4], dice_c[4];

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

bool solve_case() {
    for (int i = 0; i < 4; i++) {
        cin >> dice_a[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> dice_b[i];
    }

    for (int a = 1; a <= 10; a++) {
        dice_c[0] = a;
        for (int b = 1; b <= 10; b++) {
            dice_c[1] = b;
            for (int c = 1; c <= 10; c++) {
                dice_c[2] = c;
                for (int d = 1; d <= 10; d++) {
                    dice_c[3] = d;
                    if (check_non_transitive()) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
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
