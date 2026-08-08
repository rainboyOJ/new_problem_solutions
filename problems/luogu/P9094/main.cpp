#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;

int n, m;
int diff_color[4][MAXN];

void add_color(int color, int left_pos, int right_pos) {
    diff_color[color][left_pos] += 1;
    diff_color[color][right_pos + 1] -= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        add_color(k, l, r);
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        diff_color[1][i] += diff_color[1][i - 1];
        diff_color[2][i] += diff_color[2][i - 1];
        diff_color[3][i] += diff_color[3][i - 1];

        // 绿色 = 有黄色 + 有蓝色 + 没有红色。
        if (diff_color[1][i] > 0 && diff_color[2][i] > 0 && diff_color[3][i] == 0) {
            ++ans;
        }
    }

    cout << ans << '\n';
    return 0;
}
