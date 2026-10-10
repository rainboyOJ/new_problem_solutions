/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 快餐店 / 服务员调度：D[b][a] 表示一名服务员站在当前请求位、另两人在 {a, b} 的最小花费。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll INF = 1LL << 50; // 该站位不可达的哨兵

int main() {
    ll l, n;
    if (scanf("%lld %lld", &l, &n) != 2) return 0; // 空输入安全返回

    std::vector<std::vector<ll> > cost(l, std::vector<ll>(l));
    for (ll i = 0; i < l; i++) {
        for (ll j = 0; j < l; j++) {
            scanf("%lld", &cost[i][j]);
        }
    }
    std::vector<ll> req(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &req[i]);
    }

    ll p = 3; // 初始视为第 0 个请求发生在 3
    ll big = INF * 2;
    std::vector<std::vector<ll> > D(l, std::vector<ll>(l, big));
    D[0][1] = D[1][0] = 0;

    std::vector<std::vector<ll> > nD(l, std::vector<ll>(l));
    std::vector<ll> ca(l);

    for (ll t = 0; t < n; t++) {
        ll q = req[t];
        ll q1 = q - 1;
        if (q == p) continue; // 唯一合法动作是 p 处服务员原地接单，状态不变
        ll p1 = p - 1;
        ll cp = cost[p1][q1];
        for (ll i = 0; i < l; i++) ca[i] = cost[i][q1];

        // 转移一：p 处服务员去 q，另两人不动 → 新的「另两人」还是 {a, b}
        for (ll b = 0; b < l; b++) {
            for (ll a = 0; a < l; a++) {
                nD[b][a] = D[b][a] + cp;
            }
        }
        for (ll a = 0; a < l; a++) nD[q1][a] = big; // 新请求位上恰有一人
        for (ll b = 0; b < l; b++) nD[b][q1] = big;

        // 转移二：a 去接 q，b 与 p 处服务员留下 → 新的「另两人」是 {b, p}
        for (ll b = 0; b < l; b++) {
            if (b == q1) continue; // b == q 时该动作非法
            ll best = big;
            for (ll a = 0; a < l; a++) {
                ll cand = D[b][a] + ca[a];
                if (cand < best) best = cand;
            }
            if (best < nD[b][p1]) {
                nD[b][p1] = best;
                nD[p1][b] = best;
            }
        }

        // 转移三：q 恰是另两人之一时，只有他原地接单（代价 0）→ 新的「另两人」是 {x, p}
        for (ll x = 0; x < l; x++) {
            ll val = D[x][q1];
            if (val < nD[x][p1]) {
                nD[x][p1] = val;
                nD[p1][x] = val;
            }
        }

        D.swap(nD);
        p = q;
    }

    ll ans = big;
    for (ll b = 0; b < l; b++) {
        for (ll a = 0; a < l; a++) {
            if (D[b][a] < ans) ans = D[b][a];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
