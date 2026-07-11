/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:27
 * update_at: 2026-07-11 21:28
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n;
int g[MAXN][MAXN];
int all_good[MAXN]; // 当前上下边界内，第 col 列是否全部满足阈值。

long long count_at_least(int limit) {
    long long ans = 0;

    for (int top = 1; top <= n; top++) {
        for (int col = 1; col <= n; col++) {
            all_good[col] = 1;
        }

        for (int bottom = top; bottom <= n; bottom++) {
            int run = 0;
            for (int col = 1; col <= n; col++) {
                if (g[bottom][col] < limit) {
                    all_good[col] = 0;
                }

                if (all_good[col]) {
                    run++;
                    ans += run;
                } else {
                    run = 0;
                }
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    cout << count_at_least(100) - count_at_least(101) << '\n';

    return 0;
}
