/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:15
 * update_at: 2026-10-05 11:15
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105; // n <= 100，留几个余量
const ll INF = 1e18;  // dist 的初值，大于任何合法费用之和

ll cost[MAXN][MAXN]; // cost[x][y]：直接连接第 x、y 台计算机的费用
ll dist[MAXN];       // dist[v]：已接入点集连到 v 的最便宜一条边的费用
bool used[MAXN];     // used[v]：第 v 台计算机是否已经接入

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; // 计算机台数
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            cin >> cost[i][j];
        }
    }

    // 朴素 Prim：任选 1 号点当起点，接入自己不要钱
    for (ll i = 1; i <= n; i++) {
        dist[i] = INF;
        used[i] = false;
    }
    dist[1] = 0;

    ll ans = 0; // 最小生成树的权值和
    for (ll round = 1; round <= n; round++) {
        // 在未接入点里找 dist 最小的，连它的那条边就是横跨切割的最便宜边
        ll u = 0;
        for (ll v = 1; v <= n; v++) {
            if (!used[v] && (u == 0 || dist[v] < dist[u])) {
                u = v;
            }
        }
        used[u] = true;
        ans += dist[u];
        // 接入 u 后各未接入点可以改走 u 中转；只松弛未接入点，
        // 否则 cost[u][u] = 0 会把自己那行覆盖成 0
        for (ll v = 1; v <= n; v++) {
            if (!used[v] && cost[u][v] < dist[v]) {
                dist[v] = cost[u][v];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
