/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:26
 * update_at: 2026-10-05 04:26
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;   // 基站数上限（N <= 1000）
const int MAXM = 20005;  // 无向边，正向反向各存一条（P <= 10000）
const ll INF = 1e18;

// 题目数据
int n, p, k;
// 链式前向星存无向图
int head[MAXN], nxt[MAXM], to[MAXM], edge_cnt;
ll w[MAXM];        // w[i] 为第 i 条边的升级花费
ll dist[MAXN];     // dist[u]：1 到 u 路径上边权大于阈值的边的最少条数（0-1 BFS 距离）

// 加一条 u <-> v、花费 c 的无向边。
void add_edge(int u, int v, ll c) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = c;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 0-1 BFS：判定阈值 limit，返回 1 到 n 路径上权值大于 limit 的边的最少条数；
// 不可达返回 INF。
ll bfs01(ll limit) {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[1] = 0;
    deque<int> dq;  // 0-1 BFS 的双端队列：0 边进队头，1 边进队尾
    dq.push_back(1);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            // 边权不超过阈值的花 0 个免费名额，超过阈值的花 1 个
            ll cost = (w[i] > limit) ? 1 : 0;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                if (cost == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist[n];
}

void read_input() {
    cin >> n >> p >> k;
    edge_cnt = 0;
    for (int i = 1; i <= p; i++) {
        int a, b;
        ll l;
        cin >> a >> b >> l;
        add_edge(a, b, l);
        add_edge(b, a, l);
    }
}

void solve() {
    // 先判连通性：阈值取极大值时所有边花费都是 0，等价于普通 BFS
    if (bfs01(INF) == INF) {
        cout << -1 << endl;
        return;
    }

    // 找到最大的边权作为二分上界
    ll max_len = 0;
    for (int i = 1; i <= edge_cnt; i++) {
        if (w[i] > max_len) max_len = w[i];
    }

    // 二分答案：最小的阈值 mid，使得路径上大于 mid 的边数不超过 k
    ll low = 0, high = max_len, ans = max_len;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (bfs01(mid) <= k) {
            ans = mid;      // mid 可行，尝试更小的花费
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
