/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:35
 */
// P2938 Stock Market：每天做一次完全背包
// 第 d 天买、第 d+1 天卖：当天价格是「体积」，次日价格是「价值」。
// f[j] 表示手里有 j 元时按今天的价格买完、明天最多值多少钱；每天跑完 f[money] 就是明天的本金。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXS = 55;
const int MAXD = 15;

ll S, D, M;
ll p[MAXS][MAXD]; // p[i][d]：第 i 只股票第 d 天的价格

void read_input() {
    cin >> S >> D >> M;
    for (ll i = 1; i <= S; i++) {
        for (ll d = 1; d <= D; d++) {
            cin >> p[i][d];
        }
    }
}

void solve() {
    ll money = M;
    for (ll d = 1; d < D; d++) {
        vector<ll> f(money + 1); // f[j]：手里有 j 元时明天的最大市值（容量随本金增长，故用 vector）
        for (ll j = 0; j <= money; j++) {
            f[j] = j; // 今天不买，钱原样留到明天
        }
        for (ll i = 1; i <= S; i++) {
            ll cost = p[i][d];
            ll val = p[i][d + 1];
            if (val <= cost) {
                continue; // 明天不涨，买了不赚
            }
            for (ll j = cost; j <= money; j++) {
                if (f[j - cost] + val > f[j]) {
                    f[j] = f[j - cost] + val;
                }
            }
        }
        money = f[money];
    }
    cout << money << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
