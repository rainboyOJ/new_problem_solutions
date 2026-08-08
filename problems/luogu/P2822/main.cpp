/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 2000;

int test_count, divisor;
int combination[LIMIT + 1]; // 当前 Pascal 行的 C(i,j) mod k。
int prefix_bad[LIMIT + 1][LIMIT + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> test_count >> divisor;

    combination[0] = 1 % divisor;
    for (int i = 0; i <= LIMIT; i++) {
        if (i > 0) {
            // 从右向左更新，避免覆盖本轮仍要使用的上一行状态。
            for (int j = i; j >= 1; j--) {
                combination[j] = (combination[j] + combination[j - 1]) % divisor;
            }
        }

        for (int j = 0; j <= LIMIT; j++) {
            int divisible = (j <= i && combination[j] == 0 ? 1 : 0);
            int up = (i > 0 ? prefix_bad[i - 1][j] : 0);
            int left = (j > 0 ? prefix_bad[i][j - 1] : 0);
            int diagonal = (i > 0 && j > 0 ? prefix_bad[i - 1][j - 1] : 0);
            prefix_bad[i][j] = up + left - diagonal + divisible;
        }
    }

    while (test_count--) {
        int n, m;
        cin >> n >> m;
        if (m > n) m = n;
        cout << prefix_bad[n][m] << '\n';
    }
    return 0;
}
