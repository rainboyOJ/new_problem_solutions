/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:05
 * update_at: 2026-07-11 21:06
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 25;
const long long INF = (1LL << 60);

long long n;
int m, k;
long long change_val[MAXM][2];
int choose_seq[MAXM];
int answer_seq[MAXM];
bool found;

bool check_sequence() {
    long long cur = n;
    for (int i = 0; i < m; i++) {
        cur += change_val[i][choose_seq[i]];
        if (cur <= 0) return false;
    }
    return true;
}

// 按字典序生成完整的 Even/Odd 选择序列，再在叶子节点检查。
void dfs_choose(int dep) {
    if (found) return;

    if (dep == m) {
        if (check_sequence()) {
            found = true;
            for (int i = 0; i < m; i++) {
                answer_seq[i] = choose_seq[i];
            }
        }
        return;
    }

    for (int p = 0; p <= 1; p++) {
        choose_seq[dep] = p;
        dfs_choose(dep + 1);
        if (found) return;
    }
}

void solve_one() {
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        change_val[i][0] = INF;
        change_val[i][1] = INF;

        for (int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            int parity = x & 1;
            if (change_val[i][parity] > x) change_val[i][parity] = x;
            if (change_val[i][parity ^ 1] > -x) change_val[i][parity ^ 1] = -x;
        }
    }

    found = false;
    dfs_choose(0);

    if (!found) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 0; i < m; i++) {
        if (i) cout << ' ';
        if (answer_seq[i] == 0) {
            cout << "Even";
        } else {
            cout << "Odd";
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
