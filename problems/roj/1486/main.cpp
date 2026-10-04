/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:57
 * update_at: 2026-10-05 03:57
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;
const int MAXM = 500005; // N(N-1)/2 上界，双向边所以存边数翻倍后仍够用
const ll MOD = (1LL << 31) - 1;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

// 边权 l <= 200，距离最大约 1000*200 = 2e5，用 ll 稳妥
int n, m;
int head[MAXN], nxt[MAXM * 2], to[MAXM * 2], w[MAXM * 2], edge_cnt; // 链式前向星存无向图
ll dist_[MAXN]; // dist_[i] 表示 1 号房间到 i 号房间的最短距离 D_i
bool vis[MAXN]; // Dijkstra 中该点最短路是否已确定
ll ans;         // 方案数，对 2^31 - 1 取模

struct HeapNode {
    ll d; // 当前距离
    int u; // 节点编号
    // 小根堆按距离比较
    bool operator<(const HeapNode &b) const {
        return d > b.d;
    }
};

// 加一条无向边 u <-> v，长度 len
void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 堆优化 Dijkstra，求 1 到所有点的最短距离
void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist_[i] = INF;
        vis[i] = false;
    }
    dist_[1] = 0;
    priority_queue<HeapNode> q; // 小根堆，堆顶是当前距离最小的点
    q.push({0, 1});

    while (!q.empty()) {
        HeapNode top = q.top();
        q.pop();
        int u = top.u;
        if (vis[u]) continue; // 已确定最短路的点直接跳过
        vis[u] = true;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (dist_[u] + w[i] < dist_[v]) {
                dist_[v] = dist_[u] + w[i];
                q.push({dist_[v], v});
            }
        }
    }
}

// 统计节点 u 可选的合法前驱父节点数量 c_u
ll count_choice(int u) {
    ll cnt = 0;
    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        // v 能作为 u 的父节点当且仅当 D_v + w(v,u) = D_u
        if (dist_[v] + w[i] == dist_[u]) cnt++;
    }
    return cnt;
}

void solve() {
    dijkstra();
    // 乘法原理：每个非根节点独立选父节点，方案数连乘
    ans = 1;
    for (int u = 2; u <= n; u++) {
        ans = ans * count_choice(u) % MOD;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        add_edge(x, y, l);
        add_edge(y, x, l);
    }
    solve();

    return 0;
}
