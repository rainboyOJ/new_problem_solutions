/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:12
 * update_at: 2026-07-11 19:14
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 35;

int n, q;
char dirc[MAXN][MAXN];
int cost[MAXN][MAXN];

ll calc_answer() {
    ll ans = 0;
    for (int sx = 1; sx <= n; sx++) {
        for (int sy = 1; sy <= n; sy++) {
            int x = sx;
            int y = sy;
            while (x <= n && y <= n) {
                if (dirc[x][y] == 'R') {
                    y++;
                } else {
                    x++;
                }
            }
            ans += cost[x][y];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s >> cost[i][n + 1];
        for (int j = 1; j <= n; j++) {
            dirc[i][j] = s[j - 1];
        }
    }
    for (int j = 1; j <= n; j++) {
        cin >> cost[n + 1][j];
    }

    cout << calc_answer() << '\n';

    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (dirc[x][y] == 'R') {
            dirc[x][y] = 'D';
        } else {
            dirc[x][y] = 'R';
        }
        cout << calc_answer() << '\n';
    }

    return 0;
}
