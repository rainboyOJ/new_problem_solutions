/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 09:14
 * update_at: 2026-11-01 09:14
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;
ll n, budget;
ll x[MAXN]; // 每种糖果留下一个单颗项的价格，读完后直接排序
ll pair_cost; // 最便宜的两颗组价格

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> budget;
    for (ll i = 1; i <= n; i++) {
        ll y;
        cin >> x[i] >> y;
        if (i == 1) pair_cost = x[i] + y;
        pair_cost = min(pair_cost, x[i] + y);
    }
    sort(x + 1, x + n + 1);

    ll single_cost = 0; // 最便宜的 singles 个单颗项的总价
    ll answer = 0;
    for (ll singles = 0; singles <= n; singles++) {
        if (singles > 0) single_cost += x[singles];
        if (single_cost > budget) break; // 单颗项只会越选越贵，后面也买不起
        ll pairs = (budget - single_cost) / pair_cost;
        answer = max(answer, singles + 2 * pairs);
    }
    cout << answer << '\n';
    return 0;
}
