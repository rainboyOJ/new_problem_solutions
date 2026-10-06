/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:01
 * update_at: 2026-10-06 10:01
 */
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

typedef long long ll;

const int MAXN = 40 * 26 + 5;  // 棋盘最多 40 行 26 列，格子总数上界
const ll INF = 1e9;            // 不可达哨兵：只参与取最小值

// 骑士的 8 种走法：(行偏移, 列偏移)，即"日"字形的八个方向
const int DR[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int DC[8] = {2, 1, -1, -2, -2, -1, 1, 2};

ll R, C, n;           // 行数、列数、格子总数
ll kingCol, kingRow;  // 国王的列（0 起）、行（0 起）
ll knightCnt;         // 骑士数量
ll knightId[MAXN];    // knightId[i] = 第 i 枚骑士起点的一维编号

std::vector<ll> adj[MAXN];  // 骑士图邻接表：建表时就把越界方向剔除
ll walk[MAXN];              // walk[u] = 国王从起点走到 u 的步数（切比雪夫距离），只算一次
ll dist[MAXN];              // 骑士 BFS 距离数组，-1 表示不可达
ll best[MAXN];              // 携带距离场 E_k 的当前最优值
ll base[MAXN];              // base[t] = 所有骑士各自直奔 t 的步数和
ll gain[MAXN];              // gain[t] = min_k (E_k(t) - D_k(t))，派骑士接国王的增量
ll reach[MAXN];             // reach[t] = 能走到 t 的骑士数，等于总数才可作集合点
std::vector<ll> bucket[MAXN * 2];  // Dial 桶：bucket[d] 存当前最优值为 d 的格子

// 计算国王走到每个格子的步数：八邻域每步一格，即两个方向偏移量的较大者
void calc_walk() {
    for (ll r = 0; r < R; ++r)
        for (ll c = 0; c < C; ++c) {
            ll dr = r > kingRow ? r - kingRow : kingRow - r;
            ll dc = c > kingCol ? c - kingCol : kingCol - c;
            walk[r * C + c] = dr > dc ? dr : dc;
        }
}

// 骑士从 src 出发到每个格子的最少步数，到不了记 -1。
// 骑士图边权全为 1，普通 BFS 第一次到达就是最短路。
void bfs_knight(ll src) {
    memset(dist, -1, sizeof(ll) * n);
    std::queue<ll> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (ll i = 0; i < (ll)adj[u].size(); ++i) {
            ll v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

// E[t] = min_u (D_k(u) + walk(u) + D(u,t))：这枚骑士绕到 u 接上国王、再赶到 t 的代价。
// 种子取 E[u] = D_k(u) + walk(u)（u 即接人点），再沿骑士图做多源 BFS。
// 种子值就是距离上界（量级 O(n)），用桶按距离值分层扫描，省掉堆。
// 注意：本次调用的前提是 dist[] 里已经是这枚骑士的单源距离场。
void bfs_carry() {
    ll limit = 0;  // 桶的层数上界 = 种子最大值
    for (ll u = 0; u < n; ++u)
        if (dist[u] != -1 && dist[u] + walk[u] > limit)
            limit = dist[u] + walk[u];

    for (ll d = 0; d <= limit; ++d) bucket[d].clear();
    for (ll u = 0; u < n; ++u) {
        if (dist[u] == -1) continue;   // 骑士到不了 u，接人方案不成立
        best[u] = dist[u] + walk[u];   // 种子：骑士先到 u，国王自己走到 u
        bucket[best[u]].push_back(u);
    }

    // 从桶 0 到桶 limit 逐层向外松弛，等价于边权为 1 的多源最短路
    for (ll d = 0; d <= limit; ++d)
        for (ll i = 0; i < (ll)bucket[d].size(); ++i) {
            ll u = bucket[d][i];
            if (best[u] < d) continue;  // 该格已被更小的种子值刷新，桶里副本作废
            for (ll j = 0; j < (ll)adj[u].size(); ++j) {
                ll v = adj[u][j];
                if (d + 1 < best[v]) {
                    best[v] = d + 1;
                    bucket[d + 1].push_back(v);
                }
            }
        }
}

int main() {
    // 输入：第一行 R C；之后每两个 token 是"列字母 行号"，第一个是国王，其余是骑士
    if (scanf("%lld %lld", &R, &C) != 2) return 0;
    char colCh;
    ll row;
    scanf(" %c %lld", &colCh, &row);
    kingCol = colCh - 'A';
    kingRow = row - 1;
    knightCnt = 0;
    while (scanf(" %c %lld", &colCh, &row) == 2)
        knightId[knightCnt++] = (row - 1) * C + (colCh - 'A');

    n = R * C;

    // 骑士图邻接表：把棋盘外的走法在建表时剔除，BFS 时不用再判边界
    for (ll r = 0; r < R; ++r)
        for (ll c = 0; c < C; ++c) {
            ll u = r * C + c;
            for (ll d = 0; d < 8; ++d) {
                ll nr = r + DR[d], nc = c + DC[d];
                if (nr >= 0 && nr < R && nc >= 0 && nc < C)
                    adj[u].push_back(nr * C + nc);
            }
        }

    calc_walk();

    for (ll t = 0; t < n; ++t) {
        base[t] = 0;
        gain[t] = INF;   // 还没有任何携带方案时，增量记为不可达
        reach[t] = 0;
    }

    // 每枚骑士：一趟单源 BFS 求 D_k(·)，一趟桶式多源 BFS 求携带场 E_k(·)
    for (ll k = 0; k < knightCnt; ++k) {
        bfs_knight(knightId[k]);
        bfs_carry();
        for (ll t = 0; t < n; ++t) {
            if (dist[t] == -1) continue;  // 这枚骑士到不了 t
            base[t] += dist[t];
            reach[t]++;
            if (best[t] - dist[t] < gain[t])
                gain[t] = best[t] - dist[t];
        }
    }

    // 集合点 t 的代价 = cost(t) + min(国王自己走 walk[t], 携带增量 gain[t])
    // 两个分支都要取 min：国王自己走过去可能更便宜
    ll ans = INF;
    for (ll t = 0; t < n; ++t) {
        if (reach[t] != knightCnt) continue;  // 必须所有骑士都能到
        ll extra = walk[t] < gain[t] ? walk[t] : gain[t];
        if (base[t] + extra < ans)
            ans = base[t] + extra;
    }
    printf("%lld\n", ans);
    return 0;
}
