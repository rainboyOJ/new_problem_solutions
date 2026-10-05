/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-05 10:38
 */
#include <iostream>
using namespace std;

typedef long long ll;

const ll INF = 1e9; // 距离上界，n <= 100，实际距离远小于它

ll n; // 结点数
ll p[105]; // p[i]：结点 i 的居民人口
ll d[105][105]; // d[u][v]：u 到 v 的最少边数

// 用 Floyd 求无向无权图的全源最短路，边权为 1
void floyd() {
    for (ll k = 1; k <= n; k++) {
        for (ll i = 1; i <= n; i++) {
            for (ll j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // 初始化全源距离矩阵
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            d[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (ll i = 1; i <= n; i++) {
        ll l, r;
        cin >> p[i] >> l >> r;
        // 左右链接都是无向边
        if (l != 0) d[i][l] = d[l][i] = 1;
        if (r != 0) d[i][r] = d[r][i] = 1;
    }

    floyd();

    ll ans = INF * INF; // 总路程的答案
    for (ll u = 1; u <= n; u++) {
        ll sum = 0;
        for (ll v = 1; v <= n; v++) {
            sum += p[v] * d[u][v];
        }
        if (sum < ans) ans = sum;
    }

    cout << ans << '\n';
    return 0;
}
