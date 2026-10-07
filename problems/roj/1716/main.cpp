// 1716 次短路计数
// ---------------------------------------------------------------------------
// 题意：给定有向带权图与源点 s、汇点 t，求「长度 = 最短路长度」的 s->t 路线条数，
//       再加上「长度 = 最短路长度 + 1」的 s->t 路线条数（不存在则不加）。
//       两条路线不同 <=> 存在至少一条边属于其中一条而不属于另一条（边集不同），
//       因此重边各自独立计一次。
//
// 做法：把每个点拆成两个状态 (u,k)，k=0 表示「到 u 的最短路」，k=1 表示
//       「到 u 的严格次短路」。在 (u,k) 上跑 Dijkstra：
//         - 堆按距离升序弹出，每个状态只被确定一次，确定性后再暴力松弛出边；
//         - 设边 u->v 权 w，松弛值 nd = dist[u][k] + w，分四类处理：
//             nd <  dist[v][0]  -> 原 dist[v][0] 退位成 dist[v][1]（计数一并搬过去），
//                                  nd 顶替成新的 dist[v][0]，计数置为 cnt[u][k]；
//             nd == dist[v][0]  -> cnt[v][0] += cnt[u][k]（同长度路径累加）；
//             nd <  dist[v][1]  -> 更新 dist[v][1] 并置计数为 cnt[u][k]；
//             nd == dist[v][1]  -> cnt[v][1] += cnt[u][k]。
//       退位时「计数一并搬走」是正确的：此后所有长度等于旧 dist[v][0] 的路径
//       都会落进 nd == dist[v][1] 这一支，被继续累加到 cnt[v][1] 上。
//
//       关于计数何时定型：边权 >= 1，所以长度等于 dist[v][k] 的路径，其前驱状态
//       的距离严格小于 dist[v][k]，一定先于 (v,k) 被弹出；于是 (v,k) 出堆时
//       cnt[v][k] 已收齐。同理，状态出堆后再被累加是不可能的（那将要求 w <= 0）。
//
//       答案 = cnt[t][0] + (dist[t][1] == dist[t][0] + 1 ? cnt[t][1] : 0)。
//
// 复杂度：O(T * (n + m) log n) 时间（每个点两个状态、每条边被松弛至多两次），
//         堆内元素 O(n)，其余数组 O(n)，空间 O(n + m)。
// 数据规模：2 <= n <= 1000，1 <= m <= 10000，1 <= w <= 1000，答案 <= 1e9。
// ---------------------------------------------------------------------------
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1005;      // 点数上界
const int MAXM = 10005;     // 边数上界
const int INF = 0x3f3f3f3f; // 无穷大（两条最短路相加不会溢出）

// 链式前向星存边：重边各自占一条边，天然满足「边集不同即路线不同」
int head[MAXN], nxt[MAXM], to[MAXM], wt[MAXM], ecnt;

int n, m, s, t;
int dist[MAXN][2];   // dist[u][0] 最短路；dist[u][1] 严格次短路
ll cnt[MAXN][2];     // 对应条数
bool done[MAXN][2];  // 该状态是否已被最终确定

// 堆中元素：状态 (u, k) 及其距离 d
struct State {
    int d, u, k;
    bool operator<(const State &o) const { return d > o.d; } // 小根堆
};

// 加一条有向边 x -> y，权 w
void addEdge(int x, int y, int w) {
    ++ecnt;
    to[ecnt] = y;
    wt[ecnt] = w;
    nxt[ecnt] = head[x];
    head[x] = ecnt;
}

// 初始化一组数据
void init() {
    ecnt = 0;
    for (int i = 1; i <= n; ++i) {
        head[i] = 0;
        dist[i][0] = dist[i][1] = INF;
        cnt[i][0] = cnt[i][1] = 0;
        done[i][0] = done[i][1] = false;
    }
}

// 用状态 (u, k) 的确定值去松弛 v，nd 为候选距离
void relax(int v, int nd, int u, int k, priority_queue<State> &pq) {
    if (nd < dist[v][0]) {
        // 老的最短路被顶下去，成为次短路（计数一起搬走）
        if (dist[v][0] < dist[v][1]) {
            dist[v][1] = dist[v][0];
            cnt[v][1] = cnt[v][0];
            pq.push(State{dist[v][1], v, 1});
        }
        dist[v][0] = nd;
        cnt[v][0] = cnt[u][k];
        pq.push(State{nd, v, 0});
    } else if (nd == dist[v][0]) {
        cnt[v][0] += cnt[u][k];
    } else if (nd < dist[v][1]) {
        dist[v][1] = nd;
        cnt[v][1] = cnt[u][k];
        pq.push(State{nd, v, 1});
    } else if (nd == dist[v][1]) {
        cnt[v][1] += cnt[u][k];
    }
}

// 单组数据的求解（调用前需已 init() 并读入全部边）
ll solve() {
    priority_queue<State> pq;
    dist[s][0] = 0;
    cnt[s][0] = 1;
    pq.push(State{0, s, 0});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int u = cur.u, d = cur.d, k = cur.k;
        if (done[u][k] || d != dist[u][k]) continue; // 已经确定过 / 陈旧状态
        done[u][k] = true;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            relax(v, d + wt[e], u, k, pq);
        }
    }

    ll ans = cnt[t][0];
    // 只额外统计「恰好比最短路多 1 个单位」的那一层
    if (dist[t][1] == dist[t][0] + 1) ans += cnt[t][1];
    return ans;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        if (scanf("%d %d", &n, &m) != 2) break;
        init(); // 先清空上一组数据的边表与距离，再向其中加边
        for (int i = 0; i < m; ++i) {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            addEdge(x, y, w);
        }
        scanf("%d %d", &s, &t);
        printf("%lld\n", solve());
    }
    return 0;
}
