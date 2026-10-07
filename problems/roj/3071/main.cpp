/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:16
 * update_at: 2026-10-06 17:16
 */
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
using namespace std;

typedef long long ll;

const int MAXN = 1005;                 // 点数上界（N <= 1000）
const ll INF = 1000000000000000000LL;  // 最短路无穷大标记

struct Edge {
    int to; // 边的另一端点
    ll w;   // 边权
};

vector<Edge> g[MAXN];   // 正图：g[u] 保存 u 的全部出边
vector<Edge> rg[MAXN];  // 反图：rg[v] 保存指向 v 的边，用于从终点倒推 h

ll h[MAXN]; // h[v] = v 到终点 T 的最短路长度（A* 启发函数），INF 表示到不了终点

// A* 堆中的一条部分路径：f = g + h[u]
struct Node {
    ll f;  // 估价 f = g + h[u]
    ll g;  // 从起点走到 u 已经花费的边权和
    int u; // 当前所在点
};

// 小根堆比较：f 小的先弹出；f 相同时 g 小的先弹出
struct CmpNode {
    bool operator()(const Node &a, const Node &b) const {
        if (a.f != b.f) return a.f > b.f;
        return a.g > b.g;
    }
};

int n, m;    // 点数、边数
int s, t, k; // 起点、终点、第 K 短路

// 在反图上从终点 T 跑 Dijkstra，求出每个点到 T 的最短路，作为启发函数 h
void dijkstra_reverse() {
    for (int i = 1; i <= n; i++) h[i] = INF;
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    h[t] = 0;
    pq.push(make_pair(0, t));
    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll d = top.first;
        int u = top.second;
        if (d != h[u]) continue; // 过期的堆条目
        int deg = rg[u].size();
        for (int i = 0; i < deg; i++) {
            int v = rg[u][i].to;
            ll w = rg[u][i].w;
            if (h[u] + w < h[v]) { // u 到 T 的这段最短路可以更新 v
                h[v] = h[u] + w;
                pq.push(make_pair(h[v], v));
            }
        }
    }
}

// A* 依次弹出终点：第 cnt 次弹出终点时 g 恰为第 cnt 短路长度；不足 K 条返回 -1
ll kth_shortest() {
    priority_queue<Node, vector<Node>, CmpNode> pq;
    Node start;
    start.f = h[s];
    start.g = 0;
    start.u = s;
    pq.push(start);
    int cnt = 0; // 已经弹出终点的次数
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        if (cur.u == t && cur.g > 0) { // g = 0 是 S = T 时的零边空路径，题目要求至少一条边
            cnt++;
            if (cnt == k) return cur.g;
        }
        int deg = g[cur.u].size();
        for (int i = 0; i < deg; i++) {
            int v = g[cur.u][i].to;
            ll w = g[cur.u][i].w;
            if (h[v] == INF) continue; // v 到不了终点，扩展它永远得不到答案
            Node nxt;
            nxt.g = cur.g + w;
            nxt.f = nxt.g + h[v];
            nxt.u = v;
            pq.push(nxt);
        }
    }
    return -1; // 堆空说明不足 K 条路
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll l;
        scanf("%d%d%lld", &a, &b, &l);
        Edge e;
        e.to = b;
        e.w = l;
        g[a].push_back(e);
        e.to = a; // 反图上边由 b 指向 a
        rg[b].push_back(e);
    }
    scanf("%d%d%d", &s, &t, &k);

    dijkstra_reverse();
    if (h[s] == INF) { // 起点连一条到终点的路都没有
        printf("-1\n");
        return 0;
    }
    printf("%lld\n", kth_shortest());
    return 0;
}
