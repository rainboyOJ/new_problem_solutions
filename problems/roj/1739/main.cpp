/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:29
 * update_at: 2026-10-07 20:33
 */
// 一本通 1739《观光巴士》。
// 「每条线路恰好坐一次并回到 1 号站」= 在每个车站把两条入边与两条出边配成接续，
// 使接续关系构成一个大环。每站先取当地更省的配对（得到若干小环），
// 再把「翻转某个车站的配对」看成合并两个环的边，用最小生成树把环并成一个。
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005;                // 车站数上限 n <= 1000
const int MAXM = 2 * MAXN;            // 线路数上限 2n
const ll INF = 1000000000000000000LL; // 「该配对下连不成单环」的哨兵

int n;                  // 车站数
int m;                  // 线路数，恒为 2n
ll dep[MAXM];           // 线路 i 的每日发车时刻 l_i
ll dur[MAXM];           // 线路 i 的行驶时长 d_i
int arrive_in[MAXN][2]; // arrive_in[v] = 终点是车站 v 的两条线路编号，车站从 0 号开始编号
int arrive_cnt[MAXN];   // 车站 v 已登记的入边条数
ll sum_dur;             // 所有线路的行驶时长之和（与行程方案无关，整块计入答案）
int succ[MAXM];         // 当前接续方案：succ[r] = 到达后接着乘坐的线路编号
int ring[MAXM];         // 初始配对下线路 r 所在环的编号
int par[MAXM];          // Kruskal 并查集，规模是环数
ll delta[MAXN];         // 车站 v 改用另一种配对要多花的等待小时数

struct Edge {
    ll w; // 翻转这个车站的配对要多花的等待
    int u; // 翻转后合并进来的一个环
    int v; // 翻转后合并进来的另一个环
};
Edge edge[MAXN];        // 每个非 1 号车站至多贡献一条合并边

// 在 e 号线路到站后接续 f 号线路所需的等待小时数；
// 只依赖这两条线路（(l_e + d_e) 与 l_f 之差对 24 取模），与已经过了几天无关。
ll wait_cost(int e, int f) {
    ll w = dep[f] % 24 - (dep[e] + dur[e]) % 24;
    if (w < 0) w += 24;
    return w;
}

// 合并边按代价升序排序，供 Kruskal 使用。
bool cmp_edge(const Edge &x, const Edge &y) {
    return x.w < y.w;
}

// 并查集找根，带路径减半。
int find_root(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

// 固定 1 号车站的配对方式 p0（两条入边分别接向哪条出边），
// 返回坐遍所有线路并回到 1 号站的最短用时；该配对下连不成单环时返回 INF。
ll shortest_tour(int p0) {
    // 1 号车站的两条出边固定是线路 0 与线路 1
    succ[arrive_in[0][0]] = p0 ? 1 : 0;
    succ[arrive_in[0][1]] = p0 ? 0 : 1;

    ll base = 0; // 2..n 号车站都取当地更省的配对时的总等待
    for (int v = 1; v < n; ++v) {
        int a = arrive_in[v][0], b = arrive_in[v][1];
        int outA = 2 * v, outB = 2 * v + 1; // 车站 v 的两条出边
        ll costA = wait_cost(a, outA) + wait_cost(b, outB);
        ll costB = wait_cost(a, outB) + wait_cost(b, outA);
        if (costA <= costB) {
            succ[a] = outA;
            succ[b] = outB;
            base += costA;
            delta[v] = costB - costA; // 翻转该车站要多花的等待
        } else {
            succ[a] = outB;
            succ[b] = outA;
            base += costB;
            delta[v] = costA - costB;
        }
    }

    // 初始配对把所有线路分拆成若干环，先给每个环编号
    for (int r = 0; r < m; ++r) ring[r] = -1;
    int ring_cnt = 0;
    for (int r = 0; r < m; ++r) {
        if (ring[r] != -1) continue;
        int cur = r;
        while (ring[cur] == -1) {
            ring[cur] = ring_cnt;
            cur = succ[cur];
        }
        ++ring_cnt;
    }

    // 翻转车站 v 的配对会把 ring[in_a] 与 ring[in_b] 两个环并成一个，代价 delta[v]；
    // 要在环图上连通所有环，取最小生成树。（同一环内的车站翻转只会把环拆开，不建边）
    int ecnt = 0;
    for (int v = 1; v < n; ++v) {
        int x = ring[arrive_in[v][0]], y = ring[arrive_in[v][1]];
        if (x == y) continue;
        edge[ecnt].w = delta[v];
        edge[ecnt].u = x;
        edge[ecnt].v = y;
        ++ecnt;
    }
    sort(edge, edge + ecnt, cmp_edge);

    for (int i = 0; i < ring_cnt; ++i) par[i] = i;
    int merges = 0;  // 已完成的合并次数
    ll extra = 0;    // 合并带来的额外等待
    for (int i = 0; i < ecnt; ++i) {
        int x = find_root(edge[i].u);
        int y = find_root(edge[i].v);
        if (x == y) continue;
        par[x] = y;
        ++merges;
        extra += edge[i].w;
    }
    if (merges != ring_cnt - 1) return INF; // 环图不连通，这个配对拿不到单环

    // 首班线路 s 的那次「接续等待」被第 1 天 0 时起的候车时间 dep[s] 取代：
    // 另一条入边 pin 照常接向 other，而原本接向 s 的那次接续不再发生。
    ll best = INF;
    for (int s = 0; s < 2; ++s) {
        int other = 1 - s;
        int pin = -1;
        for (int k = 0; k < 2; ++k) {
            int r = arrive_in[0][k];
            if (succ[r] == other) pin = r;
        }
        if (pin < 0) continue;
        ll total = sum_dur + dep[s] + wait_cost(pin, other) + base + extra;
        if (total < best) best = total;
    }
    return best;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    m = 2 * n;
    for (int i = 0; i < m; ++i) {
        ll e, l, d;
        if (scanf("%lld %lld %lld", &e, &l, &d) != 3) return 0;
        dep[i] = l;
        dur[i] = d;
        sum_dur += d;
        arrive_in[e - 1][arrive_cnt[e - 1]] = i;
        ++arrive_cnt[e - 1];
    }

    ll ans = INF;
    for (int p0 = 0; p0 < 2; ++p0) {
        ll cur = shortest_tour(p0);
        if (cur < ans) ans = cur;
    }
    printf("%lld\n", ans);
    return 0;
}
