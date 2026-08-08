/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 17:48
 * update_at: 2026-07-22 21:04
 */
// brute.cpp：小数据暴力解，枚举所有横切位置，再枚举每条横带内部的竖切位置。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int R, C, A, B;
int a[MAXN][MAXN];
int row_cut[MAXN]; // row_cut[k] 表示第 k 条横带的结束行
int ans;

int rect_sum(int r1, int r2, int c1, int c2) {
    int sum = 0;
    for (int i = r1; i <= r2; i++) {
        for (int j = c1; j <= c2; j++) {
            sum += a[i][j];
        }
    }
    return sum;
}

// 对固定的一条横带，枚举 B-1 个竖切位置，求这条横带最优的最小块权值。
int best_strip_value(int r1, int r2) {
    vector<int> cuts;
    int best = 0;

    int limit = 1 << (C - 1);
    for (int mask = 0; mask < limit; mask++) {
        cuts.clear();
        for (int j = 1; j < C; j++) {
            if ((mask & (1 << (j - 1))) != 0) {
                cuts.push_back(j);
            }
        }
        if ((int)cuts.size() != B - 1) {
            continue;
        }

        int last = 1;
        int worst = 1000000000;
        for (int i = 0; i < (int)cuts.size(); i++) {
            int now = cuts[i];
            worst = min(worst, rect_sum(r1, r2, last, now));
            last = now + 1;
        }
        worst = min(worst, rect_sum(r1, r2, last, C));
        best = max(best, worst);
    }

    return best;
}

void evaluate_current_rows() {
    int last_row = 1;
    int worst = 1000000000;
    for (int i = 1; i <= A; i++) {
        int now_row = row_cut[i];
        worst = min(worst, best_strip_value(last_row, now_row));
        last_row = now_row + 1;
    }
    ans = max(ans, worst);
}

// 递归枚举每条横带的结束行。
void dfs_rows(int dep, int start_row) {
    if (dep == A) {
        row_cut[dep] = R;
        evaluate_current_rows();
        return;
    }

    int max_end = R - (A - dep);
    for (int end_row = start_row; end_row <= max_end; end_row++) {
        row_cut[dep] = end_row;
        dfs_rows(dep + 1, end_row + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C >> A >> B;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> a[i][j];
        }
    }

    ans = 0;
    dfs_rows(1, 1);
    cout << ans << '\n';

    return 0;
}
