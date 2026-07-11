/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:13
 * update_at: 2026-07-11 18:17
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 35;

int m, k;
int path[MAXM], path_len;
int answer[MAXM], answer_len;
bool found_answer;

int popcount_int(int x) {
    int cnt = 0;
    while (x > 0) {
        if ((x & 1) != 0) {
            cnt++;
        }
        x >>= 1;
    }
    return cnt;
}

// 枚举非降的正整数拆分；0 不影响和与异或，可以不用枚举。
void dfs_partition(int min_value, int rest, int xor_value) {
    if (found_answer) {
        return;
    }
    if (rest == 0) {
        if (xor_value == k) {
            found_answer = true;
            answer_len = path_len;
            for (int i = 1; i <= path_len; i++) {
                answer[i] = path[i];
            }
        }
        return;
    }

    for (int x = min_value; x <= rest; x++) {
        path_len++;
        path[path_len] = x;
        dfs_partition(x, rest - x, xor_value ^ popcount_int(x));
        path_len--;
        if (found_answer) {
            return;
        }
    }
}

void solve_one_case() {
    cin >> m >> k;

    path_len = 0;
    answer_len = 0;
    found_answer = false;
    dfs_partition(1, m, 0);

    if (!found_answer) {
        cout << -1 << '\n';
        return;
    }

    cout << answer_len << '\n';
    for (int i = 1; i <= answer_len; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
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
