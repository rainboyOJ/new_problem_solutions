/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:14
 * update_at: 2026-10-07 15:14
 */
// main.cpp：放苹果。把 M 个相同苹果放进 N 个相同盘子（允许空盘）的分法数，
// 就是「M 拆成不超过 N 个正整数之和」的拆分数，用整数分拆的递推式一次打表，每组询问 O(1)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 10; // 题面 M 的上限
const int MAXN = 10; // 题面 N 的上限

// dp[m][n]：把 m 个相同苹果放进 n 个相同盘子、允许空盘的分法数，
// 即 m 的不超过 n 个部分的拆分数。答案最大是 dp[10][10] = 42。
ll dp[MAXM + 1][MAXN + 1];

// 按 m 从小到大、m 相同时按 n 从小到大打表
void build_table() {
    for (int n = 0; n <= MAXN; n++) dp[0][n] = 1; // 0 个苹果：全是空盘，唯一分法
    for (int m = 1; m <= MAXM; m++) {
        dp[m][0] = 0; // 一个盘子都没有，非零个苹果放不下
        for (int n = 1; n <= MAXN; n++) {
            if (n > m) {
                dp[m][n] = dp[m][m]; // 盘子比苹果多，多出来的盘子必然空着，可以砍掉
            } else {
                // 至少一个空盘：dp[m][n-1]；每盘都非空：先各放 1 个，剩下 m-n 个任意放
                dp[m][n] = dp[m][n - 1] + dp[m - n][n];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_table();

    ll t;
    if (!(cin >> t)) return 0; // 无输入时直接结束
    while (t-- > 0) {
        ll m, n;
        cin >> m >> n;
        cout << dp[m][n] << "\n";
    }
    return 0;
}
