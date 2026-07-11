/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:15
 * update_at: 2026-07-11 12:20
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

int n, q;
char a[MAXN][MAXN];
int cnt[MAXN][MAXN]; // 每个对称四元组里的 '#' 数量
long long ans;

int group_row(int r) {
    // 映射到上下对称后的代表行。
    return min(r, n + 1 - r);
}

int group_col(int c) {
    // 映射到左右对称后的代表列。
    return min(c, n + 1 - c);
}

int cost(int x) {
    // 一个四元组里有 x 个 '#': 要么全部变 '#', 要么全部变 '.'。
    return min(x, 4 - x);
}

void add_cell(int r, int c) {
    if (a[r][c] == '#') {
        int gr = group_row(r);
        int gc = group_col(c);
        cnt[gr][gc]++;
    }
}

void read_input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            a[i][j] = s[j - 1];
            add_cell(i, j);
        }
    }

    int h = n / 2;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= h; j++) {
            ans += cost(cnt[i][j]);
        }
    }
}

void toggle_cell(int r, int c) {
    // 单点翻转只会改变它所在的一个对称四元组。
    int gr = group_row(r);
    int gc = group_col(c);

    ans -= cost(cnt[gr][gc]);
    if (a[r][c] == '#') {
        a[r][c] = '.';
        cnt[gr][gc]--;
    } else {
        a[r][c] = '#';
        cnt[gr][gc]++;
    }
    ans += cost(cnt[gr][gc]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    cout << ans << '\n';
    for (int i = 1; i <= q; i++) {
        int r, c;
        cin >> r >> c;
        toggle_cell(r, c);
        cout << ans << '\n';
    }

    return 0;
}
