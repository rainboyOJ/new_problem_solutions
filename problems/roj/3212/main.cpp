/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 13:44
 * update_at: 2026-10-09 13:44
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll MAX_P = 505;    // 题面 P <= 500，多开几个留余量
const ll MAX_E = MAX_P * MAX_P / 2; // 完全图边数上界 P(P-1)/2

struct Point {
    ll x; // 前哨站横坐标
    ll y; // 前哨站纵坐标
};
Point pt[MAX_P];         // pt[i] 为第 i 个前哨站（0 基）

struct Edge {
    ll u;      // 边的一端
    ll v;      // 边的另一端
    double w;  // 两点的欧几里得距离
};
Edge edge[MAX_E];        // 完全图的所有边

ll edge_cnt;             // 完全图边数
ll pa[MAX_P];            // 并查集父亲

// 并查集找根（带路径压缩）
ll find_root(ll x) {
    if (pa[x] == x) return x;
    return pa[x] = find_root(pa[x]);
}

// 按边权升序排序用的比较函数
bool cmp_edge(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

// 每组数据：Kruskal 加到第 P-S 条边即为最小通信半径
void solve() {
    ll s, p;
    cin >> s >> p;
    for (ll i = 0; i < p; i++) {
        cin >> pt[i].x >> pt[i].y;
    }

    edge_cnt = 0;
    for (ll i = 0; i < p; i++) {
        for (ll j = i + 1; j < p; j++) {
            ll dx = pt[i].x - pt[j].x;
            ll dy = pt[i].y - pt[j].y;
            ll len2 = dx * dx + dy * dy; // 平方距离，直接用 ll 算避免精度损失
            edge[edge_cnt].u = i;
            edge[edge_cnt].v = j;
            edge[edge_cnt].w = sqrt(len2);
            edge_cnt++;
        }
    }
    sort(edge, edge + edge_cnt, cmp_edge);

    for (ll i = 0; i < p; i++) {
        pa[i] = i;
    }

    ll need = p - s;   // 连通块从 P 个降到 S 个，需要加入 P-S 条边
    double ans = 0.0;  // P <= S 时全部用卫星信道，半径为 0
    if (need > 0) {
        ll added = 0;
        for (ll i = 0; i < edge_cnt; i++) {
            ll ru = find_root(edge[i].u);
            ll rv = find_root(edge[i].v);
            if (ru != rv) {
                pa[ru] = rv;
                ans = edge[i].w; // 最后加入的这条边就是瓶颈
                added++;
                if (added == need) break;
            }
        }
    }
    cout << fixed << setprecision(2) << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
