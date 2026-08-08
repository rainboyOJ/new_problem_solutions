#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 205;

int n1, m1, n2, m2, k;
int top_rows;
int total_rows;
int a[MAXN][MAXN];
int miss_x, miss_y;

int row_len(int row) {
    if (row <= top_rows) {
        return m1;
    }
    return m2;
}

int cell_sign(int row, int col) {
    if ((row + col) % 2 == 0) {
        return 1;
    }
    return -1;
}

void read_input() {
    cin >> n1 >> m1 >> n2 >> m2 >> k;

    // 上面的小矩形只在 n1,m1 都大于 0 时才真正存在。
    if (n1 > 0 && m1 > 0) {
        top_rows = n1;
    } else {
        top_rows = 0;
    }
    total_rows = top_rows + n2;

    miss_x = miss_y = 0;
    for (int i = 1; i <= total_rows; i++) {
        int len = row_len(i);
        for (int j = 1; j <= len; j++) {
            cin >> a[i][j];
            if (a[i][j] == 999999) {
                miss_x = i;
                miss_y = j;
            }
        }
    }
}

void solve() {
    ll target = 0;     // 初始棋盘的黑白带符号和
    ll known_sum = 0;  // 除缺失值外，当前棋盘的带符号和

    for (int i = 1; i <= total_rows; i++) {
        int len = row_len(i);
        for (int j = 1; j <= len; j++) {
            int sgn = cell_sign(i, j);
            target += 1LL * sgn * k;
            if (i == miss_x && j == miss_y) {
                continue;
            }
            known_sum += 1LL * sgn * a[i][j];
        }
    }

    int sgn = cell_sign(miss_x, miss_y);
    ll ans = 1LL * sgn * (target - known_sum);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
