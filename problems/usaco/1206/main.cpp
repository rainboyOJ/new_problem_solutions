/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:23
 * update_at: 2026-07-11 19:25
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n;
int pref[MAXN][MAXN]; // pref[i][k] 表示奶牛 i 第 k 喜欢的礼物
bitset<MAXN> reachable[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        bool before_self = true;
        for (int j = 1; j <= n; j++) {
            cin >> pref[i][j];
            if (before_self) {
                reachable[i][pref[i][j]] = true;
            }
            if (pref[i][j] == i) {
                before_self = false;
            }
        }
    }

    // bitset 版 Floyd：如果 i 能到 k，就合并 k 能到的所有点。
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (reachable[i][k]) {
                reachable[i] |= reachable[k];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int gift = pref[i][j];
            if (reachable[gift][i]) {
                cout << gift << '\n';
                break;
            }
            if (gift == i) {
                break;
            }
        }
    }

    return 0;
}
