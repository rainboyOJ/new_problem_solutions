/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:36
 * update_at: 2026-10-08 07:36
 */
#include <cstdio>
#include <queue>

typedef long long ll;

const int MAXN = 100005;
const int MAXM = 100005;

int head[MAXN]; // head[u] 是反图中从 u 出发的第一条边的编号，0 表示无出边
int to[MAXM];   // to[i] 是第 i 条边的终点
int nxt[MAXM];  // nxt[i] 是同一起点的下一条边的编号
int edge_cnt;   // 已加入的边数（链式前向星的分配指针）

ll n, m;
ll ans[MAXN]; // ans[v] 表示原图中 v 能到达的最大编号点，0 表示还没被更大的编号覆盖

// 在反图中加入一条 u -> v 的边。
void add_edge(ll u, ll v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 在反图上从 start 出发做 BFS：沿途首次走到的点，在反图中都能走到 start，
// 也就是在原图中能到达 start，于是把它们的答案一次性定为 start。
void bfs(ll start) {
    std::queue<ll> q;
    q.push(start);
    ans[start] = start; // 每个点至少能到达自己

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll e = head[u]; e != 0; e = nxt[e]) {
            ll v = to[e];
            if (ans[v] == 0) { // 只在这里染色，保证每个点只入队一次
                ans[v] = start;
                q.push(v);
            }
        }
    }
}

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0;

    for (ll i = 1; i <= m; i++) {
        ll u, v;
        scanf("%lld %lld", &u, &v);
        add_edge(v, u); // 反向建边：原图的 u -> v 换成反图的 v -> u
    }

    // 从大到小枚举起点：编号更大的起点先遍历，它第一次到达的点就该取它当答案
    for (ll v = n; v >= 1; v--) {
        if (ans[v] == 0) {
            bfs(v);
        }
    }

    for (ll i = 1; i <= n; i++) {
        printf("%lld%c", ans[i], i == n ? '\n' : ' ');
    }
    return 0;
}
