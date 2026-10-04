/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:12
 * update_at: 2026-10-05 07:28
 */
// main.cpp：最长公共子序列 LCS，经典二维 DP + 滚动数组，把空间压到 O(m)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 1005; // m ≤ 1000，开 m+1 的滚动数组

char x[MAXM]; // 输入字符串 X（1..n）
char y[MAXM]; // 输入字符串 Y（1..m）

int prev_row[MAXM]; // 上一行的 dp 值
int cur_row[MAXM];  // 当前行的 dp 值

int n, m;

void read_input() {
    // 两行大写字母字符串，行长均不超过 1000
    string sx, sy;
    if (!(cin >> sx)) return;
    cin >> sy;
    n = (int)sx.size();
    m = (int)sy.size();
    for (int i = 1; i <= n; i++) x[i] = sx[i - 1];
    for (int i = 1; i <= m; i++) y[i] = sy[i - 1];
}

void solve() {
    // 边界：与空串的 LCS 长度都是 0，数组初值就是 0
    for (int i = 1; i <= n; i++) {
        char xi = x[i];
        // j 必须从小到大遍历：cur_row[j] 会用到本行左侧的 cur_row[j-1]
        for (int j = 1; j <= m; j++) {
            if (xi == y[j]) {
                // 末字符相等：拼到 dp[i-1][j-1] 后面，长度 +1
                cur_row[j] = prev_row[j - 1] + 1;
            }
            else {
                // 末字符不等：去掉 X 末尾或 Y 末尾的较大者
                if (prev_row[j] > cur_row[j - 1])
                    cur_row[j] = prev_row[j];
                else
                    cur_row[j] = cur_row[j - 1];
            }
        }
        // 滚动：当前行变上一行，旧上一行复用为草稿
        for (int j = 0; j <= m; j++) prev_row[j] = cur_row[j];
    }

    cout << prev_row[m] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}