/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:33
 * update_at: 2026-10-05 04:33
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;      // 结点数上限
const int MAXM = 400005;    // 边数上限（无向边存两条，2 * 10^5 * 2）
const ll INF = 1e18;

ll n, m;                    // 结点数 N、边数 R
ll best[MAXN][2];           // best[v][0] 最短距离，best[v][1] 次短距离（严格大于最短）

// 链式前向星存图（边权需要保存，单独开 w 数组）
int head[MAXN], nxt[MAXM], to[MAXM], edge_cnt;
ll w[MAXM];

// 加一条无向边。
void add_edge(int u, int v, ll d) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = d;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 双标签 Dijkstra：小根堆按长度弹出，对每个结点同时维护最短与次短两个槽位。
void solve() {
    // 初始化两个槽位都是无穷大
    for (int i = 1; i <= n; i++) {
        best[i][0] = INF;
        best[i][1] = INF;
    }
    best[1][0] = 0;

    // 小根堆存 (长度, 结点)
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair(0LL, 1));

    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll length = top.first;
        int u = top.second;

        // 过期项跳过：这条长度入堆后已被更小的次短淘汰
        if (length > best[u][1]) continue;

        // 松弛 u 的每条出边
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            ll cand = length + w[i];
            if (cand < best[v][0]) {
                // 原最短降级为次短，cand 成为新最短
                best[v][1] = best[v][0];
                best[v][0] = cand;
                pq.push(make_pair(cand, v));
            } else if (cand > best[v][0] && cand < best[v][1]) {
                // 严格落在开区间 (最短, 次短) 内，才登记为次短
                best[v][1] = cand;
                pq.push(make_pair(cand, v));
            }
            // 其余情况丢弃：等于最短不算（要求严格大于），超过已知次短无意义
        }
    }

    cout << best[n][1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        ll d;
        cin >> a >> b >> d;
        add_edge(a, b, d);
        add_edge(b, a, d);
    }

    solve();

    return 0;
}
