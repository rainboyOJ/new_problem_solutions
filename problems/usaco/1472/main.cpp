/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:40
 * update_at: 2026-07-11 20:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXV = 2005;

int n;
int a[MAXN][MAXN];
int freq_cnt[MAXV];
int row_value[MAXN]; // row_value[i] 表示第 i 行对应的 p_i 或其互补值
int col_value[MAXN]; // col_value[j] 表示第 j 列对应的 q_j 或其互补值

int value0(int i, int j) {
    return row_value[i] + col_value[j];
}

int value1(int i, int j) {
    return 2 * (n + 1) - value0(i, j);
}

int choose_answer_type() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = value0(i, j);
            int y = value1(i, j);
            if (x < y) return 0;
            if (x > y) return 1;
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            freq_cnt[a[i][j]]++;
        }
    }

    int unique_row = 1;
    int unique_col = 1;
    for (int val = 2; val <= 2 * n; val++) {
        if (freq_cnt[val] == 1) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (a[i][j] == val) {
                        unique_row = i;
                        unique_col = j;
                    }
                }
            }
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        row_value[i] = freq_cnt[a[i][unique_col]];
    }
    for (int j = 1; j <= n; j++) {
        col_value[j] = freq_cnt[a[unique_row][j]];
    }

    int type = choose_answer_type();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            if (type == 0) {
                cout << value0(i, j);
            } else {
                cout << value1(i, j);
            }
        }
        cout << '\n';
    }

    return 0;
}
