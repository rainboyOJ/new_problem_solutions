/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:14
 * update_at: 2026-07-11 15:17
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXK = 3;

int T;
int n, k;
int a[MAXN];
int memo[MAXN][MAXN][MAXK + 1]; // 0 未计算，1 false，2 true。

bool is_period(int l, int r, int len) {
    int total = r - l + 1;
    if (total % len != 0) return false;

    for (int i = l; i <= r; i++) {
        int base = l + (i - l) % len;
        if (a[i] != a[base]) return false;
    }
    return true;
}

bool can_print(int l, int r, int print_limit) {
    if (l > r) return true;
    if (print_limit == 0) return false;

    if (memo[l][r][print_limit] != 0) {
        return memo[l][r][print_limit] == 2;
    }

    if (l == r) {
        memo[l][r][print_limit] = 2;
        return true;
    }

    int len = r - l + 1;

    // 枚举一个 REP 语句：整个区间是否由某个更短程序重复得到。
    for (int body_len = 1; body_len < len; body_len++) {
        if (!is_period(l, r, body_len)) continue;
        if (can_print(l, l + body_len - 1, print_limit)) {
            memo[l][r][print_limit] = 2;
            return true;
        }
    }

    // 枚举程序中语句序列的分界点：左程序 + 右程序。
    for (int mid = l; mid < r; mid++) {
        for (int left_prints = 1; left_prints < print_limit; left_prints++) {
            int right_prints = print_limit - left_prints;
            if (can_print(l, mid, left_prints) &&
                can_print(mid + 1, r, right_prints)) {
                memo[l][r][print_limit] = 2;
                return true;
            }
        }
    }

    memo[l][r][print_limit] = 1;
    return false;
}

void solve_one() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    memset(memo, 0, sizeof(memo));

    cout << (can_print(1, n, k) ? "YES" : "NO") << '\n';
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
