/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 20:00
 * update_at: 2026-10-21 20:00
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 真正的暴力：枚举「哪些城市建电站」的所有子集 S（01 枚举），
// 固定 S 后，最优拉线方案 = 以 S 中城市为根、覆盖所有城市的最小生成森林，
// 也就是「T 中城市 = 全部城市」时把 S 看作已免费连通再对其余城市做 Prim。
// 复杂度 O(2^n * n^2)，只适合 n <= 14 左右的小数据，与 main.cpp 不共享实现。
// 注意：输出只有最小花费，用于与主解对拍数值。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 16;
ll n;
ll x[maxn], y[maxn]; // 城市坐标
ll c[maxn];         // c[i]：在城市 i 建电站的花费
ll k[maxn];         // k[i]：拉线时每公里付出的系数

// 城市 i 与 j 之间拉线的代价：(k_i + k_j) * 曼哈顿距离
ll wire_cost(ll i, ll j) {
    return (k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
}

// 固定建电站集合 mask（第 i-1 位为 1 表示城市 i 建电站）后的最优总花费：
// 电站城市视为已通电，其余城市用最小生成森林的方式连进来。
// 朴素 Prim：dist[i] 是未入树城市 i 到「已通电集合」的最小拉线代价。
ll forest_cost(ll mask) {
    ll station_cost = 0;
    for (ll i = 1; i <= n; i++)
        if (mask >> (i - 1) & 1) station_cost += c[i];

    ll dist[maxn];      // dist[i]：城市 i 到已通电集合的最小拉线代价
    bool in_tree[maxn]; // in_tree[i]：城市 i 是否已通电（含建电站的城市）
    for (ll i = 1; i <= n; i++) {
        in_tree[i] = mask >> (i - 1) & 1;
        dist[i] = 0;
    }
    // 非电站城市初始只能直接连到某个电站城市：取到最近电站的拉线代价
    for (ll i = 1; i <= n; i++)
        if (!in_tree[i]) {
            dist[i] = -1; // -1 作为无穷哨兵
            for (ll s = 1; s <= n; s++)
                if (in_tree[s]) {
                    ll cost = wire_cost(s, i);
                    if (dist[i] == -1 || cost < dist[i]) dist[i] = cost;
                }
        }
    ll wire_total = 0;
    ll left = n;
    for (ll i = 1; i <= n; i++)
        if (in_tree[i]) left--;
    while (left > 0) { // 每轮把离已通电集合最近的城市连进来
        ll best_i = 0;
        for (ll i = 1; i <= n; i++)
            if (!in_tree[i] && (best_i == 0 || dist[i] < dist[best_i]))
                best_i = i;
        in_tree[best_i] = true;
        wire_total += dist[best_i];
        left--;
        for (ll i = 1; i <= n; i++)
            if (!in_tree[i]) {
                ll cost = wire_cost(best_i, i); // 新通电城市刷新其余城市的最近距离
                if (cost < dist[i]) dist[i] = cost;
            }
    }
    return station_cost + wire_total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (ll i = 1; i <= n; i++) cin >> c[i];
    for (ll i = 1; i <= n; i++) cin >> k[i];

    // 枚举所有建电站子集：城市 1..n 的建/不建构成 01 序列，mask 的第 i-1 位即城市 i
    ll best = -1; // 最优总花费，-1 表示还没有答案
    for (ll mask = 1; mask < (1LL << n); mask++) { // 至少建一个电站
        ll total = forest_cost(mask);
        if (best == -1 || total < best) best = total;
    }
    if (n == 0) best = 0;
    cout << best << "\n";
    return 0;
}
