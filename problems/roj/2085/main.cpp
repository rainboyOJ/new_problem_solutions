/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:43
 * update_at: 2026-10-06 10:44
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // N <= 1000，多留一点

int dp[MAXN][MAXN];   // dp[r][c] 表示以 (r,c) 为右下角的全空正方形最大边长
bool tree[MAXN][MAXN]; // tree[r][c] 为 true 表示该格有树

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    // 读入有树的坐标
    for (int i = 1; i <= t; i++) {
        int r, c;
        cin >> r >> c;
        tree[r][c] = true;
    }

    int ans = 0;
    // 按行递推每个格子的最大正方形边长
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (tree[r][c]) {
                dp[r][c] = 0; // 有树则不能作为正方形右下角
            } else {
                // 上方、左方、左上三者的最小值加一
                int up = dp[r - 1][c];
                int left = dp[r][c - 1];
                int ul = dp[r - 1][c - 1];
                dp[r][c] = min(up, min(left, ul)) + 1;
                if (dp[r][c] > ans) {
                    ans = dp[r][c];
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
