/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-19 18:07
 * update_at: 2026-09-19 18:07
 */
// main.cpp：最长公共子序列（LCS）长度，O(nm) 的朴素 DP，直接用 string 当作字符序列。
#include <bits/stdc++.h>
using namespace std;

string a, b;  // 读入的两个序列，下标从 0 开始，长度分别是 a.size()、b.size()
int dp[1005][1005];  // dp[i][j] = LCS(a 的前 i 个字符, b 的前 j 个字符)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    int n = a.size();  // 序列 X 的长度
    int m = b.size();  // 序列 Y 的长度

    // 第 0 行、第 0 列表示其中一个串为空，公共子序列只能是空串
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                // 两个字符相同，可以直接把它们接在 LCS(a[0..i-2], b[0..j-2]) 后面
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // 否则 X 的第 i 个字符和 Y 的第 j 个字符不可能同时出现在 LCS 的末尾
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // dp[n][m] 就是两个完整串的 LCS 长度
    cout << dp[n][m] << "\n";

    return 0;
}
