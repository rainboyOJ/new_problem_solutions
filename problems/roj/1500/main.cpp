/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:41
 * update_at: 2026-10-05 04:41
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
typedef long long ll;

using namespace std;

const ll MAXN = 50005;   // 车站数上限
const ll MAXM = 100005;  // 公路数上限
const ll INF = 1e18;

// 链式前向星存图（无向图，双向加边）
ll head[MAXN];  // head[u] = u 点的第一条边编号
ll nxt[MAXM * 2];  // 同一起点下一条边
ll to_v[MAXM * 2];  // 边的终点
ll weight[MAXM * 2];  // 边权（时间）
ll cnt_edge = 0;

ll n, m;
ll key_node[6];  // key_node[0] = 家(车站1)，key_node[1..5] = 五个亲戚的车站
ll dist[6][MAXN];  // dist[k][u] = 从第 k 个关键点出发到 u 的最短路
ll d[6][6];  // d[i][j] = 关键点 i 到关键点 j 的最短路距离（6x6 距离矩阵）

// 加一条有向边
void add_edge(ll u, ll v, ll w) {
    cnt_edge++;
    to_v[cnt_edge] = v;
    weight[cnt_edge] = w;
    nxt[cnt_edge] = head[u];
    head[u] = cnt_edge;
}

// 堆优化 Dijkstra：以 key_node[k] 为源点求单源最短路
void dijkstra(ll k) {
    for (ll i = 1; i <= n; i++) dist[k][i] = INF;
    ll s = key_node[k];
    dist[k][s] = 0;
    // 小根堆：pair(当前距离, 点编号)
    priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > pq;
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
        pair<ll, ll> top = pq.top();
        pq.pop();
        ll d = top.first;
        ll u = top.second;
        if (d > dist[k][u]) continue;  // 过期状态，跳过
        for (ll e = head[u]; e; e = nxt[e]) {
            ll v = to_v[e];
            ll nd = d + weight[e];
            if (nd < dist[k][v]) {
                dist[k][v] = nd;
                pq.push(make_pair(nd, v));
            }
        }
    }
}

// 全排列枚举 5 个亲戚（关键点 1..5）的拜访顺序
// perm[p] = 第 p 站拜访的关键点编号
ll perm[6];
bool used[6];
ll ans = INF;

// 当前已确定前 pos 站，sum 为从家出发走到上一站的总距离
void dfs_choose(ll pos, ll last, ll sum) {
    if (pos == 6) {  // 5 个亲戚全部拜访完
        if (sum < ans) ans = sum;
        return;
    }
    // 这一层在选择：第 pos 站拜访哪个还没去过的亲戚
    for (ll k = 1; k <= 5; k++) {
        if (used[k]) continue;
        used[k] = true;
        perm[pos] = k;
        dfs_choose(pos + 1, k, sum + d[last][k]);
        used[k] = false;
    }
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (ll i = 1; i <= 5; i++) scanf("%lld", &key_node[i]);
    key_node[0] = 1;  // 佳佳家在车站 1

    memset(head, 0, sizeof(head));
    for (ll i = 1; i <= m; i++) {
        ll x, y, t;
        scanf("%lld %lld %lld", &x, &y, &t);
        add_edge(x, y, t);
        add_edge(y, x, t);
    }

    // 6 个关键点各跑一次堆优化 Dijkstra，提取两两最短路得到距离矩阵
    for (ll k = 0; k <= 5; k++) dijkstra(k);
    for (ll i = 0; i <= 5; i++)
        for (ll j = 0; j <= 5; j++)
            d[i][j] = dist[i][key_node[j]];

    dfs_choose(1, 0, 0);
    printf("%lld\n", ans);
    return 0;
}
