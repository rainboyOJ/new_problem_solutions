/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:57
 * update_at: 2026-10-06 18:57
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

typedef long long ll;

ll T;
ll n;
ll pos[MAXN]; // pos[i]：第 i 个棋子所在的网格编号，排序后从左到右

void solve() {
    cin >> T;
    while (T--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) {
            cin >> pos[i];
        }
        sort(pos + 1, pos + n + 1);

        // 把棋子间的空格看成沿阶梯从右往左流动的石子：
        // gap[i] = 第 i 个棋子左边可自由移动的空格数，最左棋子以 1 号格左侧为界。
        // 从右往左数第 1、3、5……段参与 Nim 异或，这里直接从最右棋子隔一个取一个。
        ll nim_sum = 0;
        for (ll i = n; i >= 1; i -= 2) {
            if (i == 1) {
                nim_sum ^= pos[i] - 1;
            } else {
                nim_sum ^= pos[i] - pos[i - 1] - 1;
            }
        }

        if (nim_sum != 0) {
            cout << "Georgia will win\n";
        } else {
            cout << "Bob will win\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
