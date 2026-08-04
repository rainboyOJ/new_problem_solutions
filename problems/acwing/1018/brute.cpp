/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 12:50
 * update_at: 2026-08-04 12:50
 */

// brute.cpp：小数据暴力解，使用选择序列递归枚举所有路径。
// 每一层递归在选择"下一步向右还是向下走"，走到底（到达 (n,n)）时结算并更新最优。
// 只能处理小数据：路径数是组合数 C(2n-2, n-1)，指数级。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int INF = 0x3f3f3f3f;

int n;                 // 网格边长
int a[MAXN][MAXN];     // 费用
int ans;               // 最小费用

// 当前在 (x, y)，已花费 sum
void dfs(int x, int y, int sum) {
    if (x == n && y == n) {          // 到达右下角，结算
        ans = min(ans, sum);
        return;
    }
    if (x < n) dfs(x + 1, y, sum + a[x + 1][y]); // 向下走
    if (y < n) dfs(x, y + 1, sum + a[x][y + 1]); // 向右走
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    ans = INF;
    dfs(1, 1, a[1][1]);
    cout << ans << '\n';
    return 0;
}
