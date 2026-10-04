/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:07
 * update_at: 2026-10-04 23:07
 */

// main.cpp：完全背包。
// m 高达 10^16，不能对整个容量做 DP：
// 1. 同体积去重：体积 <= 100，每个体积只留价值最大的物品，至多 100 个；
// 2. 密度贪心：取价值/体积密度最大的物品 (a1,b1)，
//    先装 cnt = max(0, m/a1 - 100) 件（大数部分用一次乘法承接）；
// 3. 余量 rest = m - cnt*a1 <= 99 + 100*a1 = 10099，
//    对这段小容量做一维完全背包修正零头。
// 答案 = cnt * b1 + f[rest]，全程与 m 无关。

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXV = 100;        // 体积上限 100
const int MAXREST = 10099;   // DP 段容量上界：99 + 100*100
const ll RESERVE = 100;      // 给零头预留的份数（取自体积上限）

ll n, m;
ll best[MAXV + 1];           // best[v] = 体积为 v 的物品中的最大价值（0 表示该体积没出现过）
ll f[MAXREST + 1];           // f[j] = 容量 j 内能拿到的最大价值（一维完全背包）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 流式读入 n 件物品，同体积只留价值最大的，把 n <= 10^6 压到至多 100 个
    for (ll i = 1; i <= n; ++i) {
        ll a, b;
        cin >> a >> b;
        if (b > best[a])
            best[a] = b;
    }

    // 找密度（b/a）最大的物品 (a1, b1)，它是"万能填充物"
    ll a1 = 0, b1 = 0;
    for (int v = 1; v <= MAXV; ++v) {
        if (best[v] == 0) continue;
        // 交叉相乘比较 b/v > b1/a1，避免浮点误差
        if (a1 == 0 || best[v] * a1 > b1 * v) {
            a1 = v;
            b1 = best[v];
        }
    }

    // 贪心段：装 cnt 件最优物品，留出 100 份容量给 DP 修正零头
    ll cnt = m / a1 - RESERVE;
    if (cnt < 0) cnt = 0;
    ll rest = m - cnt * a1;    // 余量 <= 99 + 100*a1 <= 10099

    // DP 段：对容量 rest 做一维完全背包，正序扫描表示每种物品可重复取
    ll limit = rest;
    for (ll j = 0; j <= limit; ++j) f[j] = 0;
    for (int v = 1; v <= MAXV; ++v) {
        if (best[v] == 0) continue;
        for (ll j = v; j <= limit; ++j) {
            if (f[j - v] + best[v] > f[j])
                f[j] = f[j - v] + best[v];
        }
    }

    cout << cnt * b1 + f[rest] << endl;
    return 0;
}
