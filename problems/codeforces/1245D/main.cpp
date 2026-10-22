/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 20:00
 * update_at: 2026-10-21 20:00
 */
// CF1245D Shichikuji and Power Grid
// 建模：加虚拟源点 0，0->i 边权 c_i（建电站），i->j 边权 (k_i+k_j)*曼哈顿距离（拉线），
// 答案 = n+1 个点的最小生成树。
// n <= 2000 时完全图约有 2*10^6 条边，对它们排序的 Kruskal 在时限边缘；
// 这里用 O(n^2) 的 Prim：每轮 O(n) 现场扫描选最近点，不落地保存任何边。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
ll n;
ll x[maxn], y[maxn];   // 城市坐标
ll c[maxn];            // c[i]：在城市 i 建电站的花费
ll k[maxn];            // k[i]：拉线时每公里付出的系数

ll dist[maxn];         // dist[i]：城市 i 到"当前已通电集合"的最小边权（初始为建电站代价 c_i）
int from[maxn];        // from[i]：dist[i] 对应的边的另一端，0 表示"建电站"这条虚拟边
bool used[maxn];       // used[i]：城市 i 是否已并入生成树

// 城市 i 与 j 之间拉线的代价：(k_i + k_j) * 曼哈顿距离
ll wire_cost(ll i, ll j) {
    return (k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
}

vector<ll> stations;              // 建电站的城市编号（对应树里 0->i 的边）
vector<pair<ll, ll>> connections; // 拉线的城市对（对应树里 i->j 的边）

void prim() {
    // 初始所有点都未加入，到集合的最近距离就是"建电站"这条虚拟边的权
    for (ll i = 1; i <= n; i++) {
        dist[i] = c[i];
        from[i] = 0; // 0 是虚拟源点：先默认每个城市自己建电站
    }
    for (ll round = 1; round <= n; round++) { // 一共要把 n 个城市全部并入
        // 找到未加入城市中 dist 最小的一个
        ll best = 0;
        for (ll i = 1; i <= n; i++)
            if (!used[i] && (best == 0 || dist[i] < dist[best]))
                best = i;
        used[best] = true;
        if (from[best] == 0)
            stations.push_back(best);               // 与虚拟源点相连：建电站
        else
            connections.push_back({from[best], best}); // 与已有城市相连：拉线
        // 新点并入后，用它的出边更新其余城市的最近距离
        for (ll i = 1; i <= n; i++)
            if (!used[i] && wire_cost(best, i) < dist[i]) {
                dist[i] = wire_cost(best, i);
                from[i] = best;
            }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (ll i = 1; i <= n; i++) cin >> c[i];
    for (ll i = 1; i <= n; i++) cin >> k[i];

    prim();

    ll total = 0;
    for (ll s : stations) total += c[s];
    for (auto e : connections)
        total += wire_cost(e.first, e.second);

    cout << total << "\n";
    cout << stations.size() << "\n";
    for (ll i = 0; i < (ll)stations.size(); i++)
        cout << stations[i] << " \n"[i + 1 == (ll)stations.size()];
    cout << connections.size() << "\n";
    for (ll i = 0; i < (ll)connections.size(); i++)
        cout << connections[i].first << " " << connections[i].second << "\n";
    return 0;
}
