/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:41
 * update_at: 2026-10-05 04:41
 */
// main.cpp：「一本通 3.2 练习 3」最短路计数
// 无向无权图（允许重边）：BFS 按层推进求最短距离，同时递推统计到每个点的最短路条数。
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 顶点数上限 N <= 100000
const int MOD = 100003;  // 题面要求的取模值

// adj[u]：与顶点 u 相邻的所有顶点（一条无向边在两个邻接表里各存一次，重边原样保留）
vector<int> adj[MAXN];

// dist[u]：从顶点 1 到 u 的最短边数，-1 表示尚未访问（同时充当"层号"）
int dist[MAXN];

// cnt[u]：从顶点 1 到 u 的最短路条数，边算边对 MOD 取模
ll cnt[MAXN];

// 从顶点 1 出发做 BFS，并同步递推最短路条数。
// 关键不变式：dist 相同的点按 BFS 出队顺序处理，第 dist[u]-1 层的点全部先于 u 出队，
// 所以出队 u 时 cnt[u] 已经收齐全部前驱的贡献，可以安全地传给下一层。
void bfs_count(ll n) {
    for (ll i = 1; i <= n; i++) {
        dist[i] = -1;
        cnt[i] = 0;
    }

    dist[1] = 0;
    cnt[1] = 1; // 顶点 1 到自己算 1 条最短路，输出第 1 行为 1

    queue<ll> q; // BFS 队列，出队顺序按 dist 非降
    q.push(1);

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        ll du = dist[u];
        ll cu = cnt[u];
        ll deg = adj[u].size();

        for (ll i = 0; i < deg; i++) {
            ll v = adj[u][i];

            if (dist[v] == -1) {
                // 第一次到达 v：最短路长度由 u 确定为 du + 1，先把 cnt[u] 作为初值
                dist[v] = du + 1;
                cnt[v] = cu;
                q.push(v);
            } else if (dist[v] == du + 1) {
                // v 正好是 u 的下一层：多出一条经过 (u, v) 的最短路
                // 重边会让同一对 (u, v) 再次落到这里，语义正是两条不同的路径
                cnt[v] = (cnt[v] + cu) % MOD;
            }
            // 其余情形（v 更浅或与 u 同层）都不构成最短路，直接忽略
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v); // 无向图，两个方向都要存
        adj[v].push_back(u);
    }

    bfs_count(n);

    for (ll i = 1; i <= n; i++) {
        cout << cnt[i] << '\n'; // 不可达点的 cnt 保持 0，输出自然为 0
    }

    return 0;
}
