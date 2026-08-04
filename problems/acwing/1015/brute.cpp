/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 12:40
 * update_at: 2026-08-04 12:40
 */

// brute.cpp：小数据暴力解，使用选择序列递归枚举所有路径。
// 每一层递归在选择"下一步向右还是向下走"，走到底（到达 (r,c)）时结算并更新最优。
// 只能处理小数据：路径数是组合数 C(r+c-2, r-1)，指数级。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int r, c;                 // 行数、列数
int a[MAXN][MAXN];        // 花生数量
int ans;                  // 最优花生总数

// 当前在 (x, y)，已摘 sum 颗花生
void dfs(int x, int y, int sum) {
    if (x == r && y == c) {          // 到达东南角，结算
        ans = max(ans, sum);
        return;
    }
    if (x < r) dfs(x + 1, y, sum + a[x + 1][y]); // 向下走
    if (y < c) dfs(x, y + 1, sum + a[x][y + 1]); // 向右走
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> r >> c;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> a[i][j];
            }
        }
        ans = 0;
        dfs(1, 1, a[1][1]);
        cout << ans << '\n';
    }
    return 0;
}
