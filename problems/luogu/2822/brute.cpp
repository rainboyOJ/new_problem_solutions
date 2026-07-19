/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：用 Pascal 递推直接算小范围组合数取模，再枚举询问范围。

const int MAXN = 105;

int t, k;
int comb_mod[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t >> k;

    comb_mod[0][0] = 1 % k;
    for (int i = 1; i < MAXN; i++) {
        comb_mod[i][0] = comb_mod[i][i] = 1 % k;
        for (int j = 1; j < i; j++) {
            comb_mod[i][j] = (comb_mod[i - 1][j - 1] + comb_mod[i - 1][j]) % k;
        }
    }

    while (t--) {
        int n, m;
        cin >> n >> m;
        int answer = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= min(i, m); j++) {
                if (comb_mod[i][j] == 0) {
                    answer++;
                }
            }
        }
        cout << answer << '\n';
    }

    return 0;
}
