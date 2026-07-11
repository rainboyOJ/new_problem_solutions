/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:02
 * update_at: 2026-07-11 15:06
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int C = 26;

int n, q;
string s;

int left_pos[MAXN][C]; // left_pos[i][c] 表示 1..i 中字符 c 最靠右的位置。
int next_pos[MAXN][C]; // next_pos[i][c] 表示 i..n 中字符 c 最靠左的位置。
int next_not[MAXN][C]; // next_not[i][c] 表示 i..n 中第一个不是字符 c 的位置。

long long calc_value(int i, int j, int k) {
    return 1LL * (j - i) * (k - j);
}

void build_precalc() {
    for (int c = 0; c < C; c++) {
        left_pos[0][c] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int c = 0; c < C; c++) {
            left_pos[i][c] = left_pos[i - 1][c];
        }
        left_pos[i][s[i] - 'a'] = i;
    }

    for (int c = 0; c < C; c++) {
        next_pos[n + 1][c] = n + 1;
    }

    for (int i = n; i >= 1; i--) {
        for (int c = 0; c < C; c++) {
            next_pos[i][c] = next_pos[i + 1][c];
        }
        next_pos[i][s[i] - 'a'] = i;

        int best = n + 1;
        int second_best = n + 1;
        for (int c = 0; c < C; c++) {
            if (next_pos[i][c] < best) {
                second_best = best;
                best = next_pos[i][c];
            } else if (next_pos[i][c] < second_best) {
                second_best = next_pos[i][c];
            }
        }

        for (int c = 0; c < C; c++) {
            if (next_pos[i][c] == best) next_not[i][c] = second_best;
            else next_not[i][c] = best;
        }
    }
}

long long answer_query(int l, int r) {
    long long ans = -1;

    // 枚举 moo 的后两个相同字符。
    for (int rc = 0; rc < C; rc++) {
        int k = left_pos[r][rc];  // rc 在 [l,r] 中尽量靠右，作为第三个位置。
        int i = next_not[l][rc];  // 第一个不是 rc 的位置，作为第一个位置。

        if (i >= k) continue;

        int mid = (i + k) / 2;

        // j 越靠近 i 和 k 的中点，(j-i)(k-j) 越大。
        int j1 = left_pos[mid][rc];
        if (i < j1 && j1 < k) {
            long long value = calc_value(i, j1, k);
            if (ans < value) ans = value;
        }

        int j2 = next_pos[mid][rc];
        if (i < j2 && j2 < k) {
            long long value = calc_value(i, j2, k);
            if (ans < value) ans = value;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    cin >> s;
    s = " " + s;

    build_precalc();

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << answer_query(l, r) << '\n';
    }

    return 0;
}
