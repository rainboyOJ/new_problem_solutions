/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:14
 * update_at: 2026-07-11 15:17
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int T;
int n, k;
int a[MAXN];
int block_value[MAXN], block_len[MAXN];

bool check1(int l, int r) {
    if (l > r) return true;

    for (int i = l + 1; i <= r; i++) {
        if (a[i] != a[l]) return false;
    }
    return true;
}

bool check2(int l, int r) {
    if (l > r) return true;
    if (check1(l, r)) return true;

    int block_cnt = 0;
    for (int i = l; i <= r; i++) {
        if (i == l || a[i] != a[i - 1]) {
            block_cnt++;
            block_value[block_cnt] = a[i];
            block_len[block_cnt] = 1;
        } else {
            block_len[block_cnt]++;
        }
    }

    if (block_cnt <= 2) return true;
    if (block_cnt % 2 == 1) return false;

    for (int i = 1; i + 2 <= block_cnt; i++) {
        if (block_value[i] != block_value[i + 2]) return false;
        if (block_len[i] != block_len[i + 2]) return false;
    }

    return true;
}

bool is_repeated_block(int l, int r, int len) {
    int total = r - l + 1;
    if (total % len != 0) return false;

    for (int i = l; i + len <= r; i++) {
        if (a[i] != a[i + len]) return false;
    }
    return true;
}

bool check3(int l, int r) {
    int total = r - l + 1;

    // 枚举外层 REP 的循环体长度。
    for (int len = 1; len <= total; len++) {
        if (!is_repeated_block(l, r, len)) continue;

        int body_l = l;
        int body_r = l + len - 1;

        // 循环体由 degree 1 + degree 2，或 degree 2 + degree 1 组成。
        for (int cut = 0; cut <= len; cut++) {
            int left_l = body_l;
            int left_r = body_l + cut - 1;
            int right_l = body_l + cut;
            int right_r = body_r;

            if (check1(left_l, left_r) && check2(right_l, right_r)) return true;
            if (check2(left_l, left_r) && check1(right_l, right_r)) return true;
        }
    }

    return false;
}

void solve_one() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    bool ok = false;
    if (k == 1) ok = check1(1, n);
    else if (k == 2) ok = check2(1, n);
    else ok = check3(1, n);

    cout << (ok ? "YES" : "NO") << '\n';
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
