/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:33
 * update_at: 2026-10-07 18:33
 */
// main.cpp：最小边权和。把边按 w 升序排序，逐边做 DP 松弛：
// f[a][v][k] = 从点 a 出发、恰好走 k 条边、边权非降序到达点 v 的最小边权和。
// 排序后的处理顺序就是"边权非降序"时边的使用顺序，所以每条边只需松弛一次。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 150;       // 点数上界
const int MAXM = 5000;      // 边数上界
const int INF = 0x3f3f3f3f; // 不可达标记；真实答案 <= 149 * 5000 = 745000，远小于它
const int JUNK = 100000000; // 超过它说明该格被 INF 污染过，判无解输出 -1

struct Edge {
    int u; // 起点
    int v; // 终点
    int w; // 边权（题面保证两两不同，单个不超过 5000，int 够用）
};
Edge e[MAXM]; // 读入后按 w 升序重排

// f[a][v][k] 用 int 存：真实答案上界 745000 与 INF = 0x3f3f3f3f 不会混淆，
// 用 int 把 150^3 个状态压到约 14 MB（换成 ll 会翻倍）。
// 语义随状态推进变化：松弛阶段是"恰好 k 条边"，做完前缀 min 后变成"不超过 k 条边"。
int f[MAXN + 1][MAXN + 1][MAXN + 1];

// 按边权升序排序：题面保证 w 两两不同，所以这个顺序唯一，就是行走时边的使用顺序
bool cmp_edge(const Edge &x, const Edge &y) {
    return x.w < y.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, q;
    cin >> n >> m >> q;

    for (ll i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    sort(e, e + m, cmp_edge);

    memset(f, 0x3f, sizeof(f)); // 全部先标成不可达
    for (ll a = 1; a <= n; a++) {
        f[a][a][0] = 0; // 走 0 条边：自己到自己，代价 0
    }

    // 逐边松弛。k 从大到小枚举，保证读到的是"这条边松弛之前"的 f[a][u][k-1]，
    // 于是一条边在一次松弛里不会被重复使用，k 与走路实际用掉的边数严格对应。
    for (ll t = 0; t < m; t++) {
        ll u = e[t].u;
        ll v = e[t].v;
        ll w = e[t].w;
        for (ll a = 1; a <= n; a++) {
            for (ll k = n; k >= 1; k--) {
                int cand = f[a][u][k - 1] + w;
                if (cand < f[a][v][k]) {
                    f[a][v][k] = cand;
                }
            }
        }
    }

    // 前缀 min：把"恰好 k 条边"改成"不超过 k 条边"，因为询问允许少走几条边
    for (ll a = 1; a <= n; a++) {
        for (ll b = 1; b <= n; b++) {
            for (ll k = 1; k <= n; k++) {
                if (f[a][b][k - 1] < f[a][b][k]) {
                    f[a][b][k] = f[a][b][k - 1];
                }
            }
        }
    }

    for (ll t = 0; t < q; t++) {
        ll a, b, c;
        cin >> a >> b >> c;
        // 最优解一定是简单路径（去掉环代价严格变小），长度不超过 n-1，
        // 所以 c 超过 n 时截断不影响答案；c 没有给上界，数据里出现过 1e9，用 ll 读入。
        if (c > n) c = n;
        if (c < 0) c = 0;
        ll ans = f[a][b][c]; // 此处 c 已夹在 [0, n]
        if (ans > JUNK) {
            cout << -1 << "\n";
        } else {
            cout << ans << "\n";
        }
    }

    return 0;
}
