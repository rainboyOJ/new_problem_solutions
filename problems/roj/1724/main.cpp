/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:40
 * update_at: 2026-10-07 18:40
 */
// 1724《小K的农场》：差分约束系统判可行解。
// 三种记忆分别化成 x_v <= x_u + w 的边，加超级源点后用 SPFA 判负环：
// 有负环 <=> 约束互相矛盾（无解）；无负环 <=> 存在一种赋值吻合所有记忆。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10005;  // n <= 1e4，再留 1 个编号给超级源点 0
const int MAXE = 40005;  // 3 型约束双向共 2m 条边 + 源点 n 条边 <= 3e4

// 链式前向星：to/w/nxt 是同一条边的三个字段（边编号即下标）
int head[MAXN], to[MAXE], nxt[MAXE];
ll w[MAXE]; // 边权，约束里的 c 可达 1e4，松弛路径累加用 ll 更稳妥
int edge_cnt;

// 加一条 u -> v、边权为 weight 的有向边
void add_edge(int u, int v, ll weight) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = weight;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

ll dist[MAXN];   // dist[u] 表示超级源点到 u 的最短路估计（松弛上界）
int enq_cnt[MAXN]; // 某点入队累计次数，超过点数即判定负环
bool in_queue[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; i++) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            // 农场 a 至少比 b 多 c：x_a - x_b >= c  <=>  x_b <= x_a - c
            ll c;
            cin >> c;
            add_edge(a, b, -c);
        } else if (op == 2) {
            // 农场 a 至多比 b 多 c：x_a - x_b <= c  <=>  x_a <= x_b + c
            ll c;
            cin >> c;
            add_edge(b, a, c);
        } else {
            // 农场 a 与 b 一样多：双向各一条 0 权边
            add_edge(a, b, 0);
            add_edge(b, a, 0);
        }
    }

    // 超级源点 0 连向所有农场（权 0）：图不连通也能一次判完整
    for (int i = 1; i <= n; i++) add_edge(0, i, 0);

    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    in_queue[0] = true;
    enq_cnt[0] = 1;

    int total_nodes = n + 1; // 含超级源点
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (dist[u] + w[e] < dist[v]) {
                dist[v] = dist[u] + w[e];
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    enq_cnt[v]++;
                    // Bellman-Ford 队列法标准判据：某点入队次数超过点数 => 负环
                    if (enq_cnt[v] > total_nodes) {
                        cout << "No\n";
                        return 0;
                    }
                    q.push(v);
                }
            }
        }
    }

    cout << "Yes\n";
    return 0;
}
