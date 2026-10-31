/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:16
 * update_at: 2026-10-31 21:16
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 505;
const int MAXM = 500005;
const ll INF = 1LL << 60;

struct Platform {
    ll line; // 线路编号
    ll walk; // 这个站的站厅到该线路站台的步行时间
};

ll c, n, m, d, q;
ll w[MAXM]; // 地铁口到站厅的时间，只在起点和终点计算
vector<Platform> station_lines[MAXM]; // station_lines[v]：站 v 能上的线路
ll dist[MAXN][MAXN]; // 两条线路之间的最少换乘步行时间

void read_input() {
    cin >> c >> n >> m >> d >> q;
    for (ll v = 1; v <= m; v++) cin >> w[v];
    for (ll line = 1; line <= n; line++) {
        ll k;
        cin >> k;
        for (ll j = 1; j <= k; j++) {
            ll v, walk;
            cin >> v >> walk;
            station_lines[v].push_back({line, walk});
        }
    }
}

// 两条线路在同一站换乘：先走回站厅，再走到另一条线路的站台。
void build_transfer_graph() {
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }
    for (ll v = 1; v <= m; v++) {
        for (const auto &from : station_lines[v]) {
            for (const auto &to : station_lines[v]) {
                ll cost = from.walk + to.walk;
                dist[from.line][to.line] = min(dist[from.line][to.line], cost);
            }
        }
    }
}

// 线路只有 500 条，预先算好任意两条线路之间的最短路。
void floyd() {
    for (ll k = 1; k <= n; k++) {
        for (ll i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;
            for (ll j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

// 枚举第一条和最后一条线路，中间的换乘费用直接查表。
ll query(ll x, ll y) {
    ll answer = INF;
    for (const auto &first : station_lines[x]) {
        for (const auto &last : station_lines[y]) {
            ll cost = first.walk + dist[first.line][last.line] + last.walk;
            answer = min(answer, cost);
        }
    }
    return w[x] + answer + w[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_transfer_graph();
    floyd();
    while (q--) {
        ll x, y;
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }
    return 0;
}
