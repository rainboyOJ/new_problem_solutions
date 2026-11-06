/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// brute.cpp：小数据暴力，每天枚举每只股票买几张
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll S, D, M;
ll p[10][10];

ll best_day(ll d, ll i, ll money) {
    if (i > S) return money;
    ll best = -1;
    for (ll c = 0; c * p[i][d] <= money; c++) {
        ll rest = money - c * p[i][d];
        best = max(best, best_day(d, i + 1, rest) + c * p[i][d + 1]);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> S >> D >> M;
    for (ll i = 1; i <= S; i++)
        for (ll d = 1; d <= D; d++) cin >> p[i][d];
    ll money = M;
    for (ll d = 1; d < D; d++) money = best_day(d, 1, money);
    cout << money << '\n';
}
