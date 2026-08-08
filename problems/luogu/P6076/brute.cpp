#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 1000000007LL;

int n, m, c;
int row_cnt[10], col_cnt[10], color_cnt[10];
i64 ans;

// 小数据暴力：
// 枚举每个格子是“不染色”还是染成哪一种颜色。
void dfs(int pos) {
    if (pos == n * m) {
        for (int i = 0; i < n; i++) {
            if (row_cnt[i] == 0) {
                return;
            }
        }
        for (int j = 0; j < m; j++) {
            if (col_cnt[j] == 0) {
                return;
            }
        }
        for (int k = 1; k <= c; k++) {
            if (color_cnt[k] == 0) {
                return;
            }
        }
        ans++;
        if (ans >= MOD) {
            ans -= MOD;
        }
        return;
    }

    int x = pos / m;
    int y = pos % m;

    // 不染色
    dfs(pos + 1);

    // 染成某一种颜色
    for (int color = 1; color <= c; color++) {
        row_cnt[x]++;
        col_cnt[y]++;
        color_cnt[color]++;

        dfs(pos + 1);

        row_cnt[x]--;
        col_cnt[y]--;
        color_cnt[color]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c;
    dfs(0);
    cout << ans << '\n';

    return 0;
}
