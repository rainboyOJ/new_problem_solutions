/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:04
 * update_at: 2026-10-07 18:04
 */
// main.cpp：益智游戏（一本通 1718）。
// 4 次 Dijkstra 求出 dA(A→v)、dB(v→B)、dC(C→v)、dD(v→D)，
// 筛出「同时在 A→B 与 C→D 最短路上的点」以及「同时在两条最短路上的边」，
// 答案就是这张公共最短路 DAG 上的最长节点链（沿边 dA 严格递增，按 dA 排序即可线性 DP）。
// 与 main.py 同一算法；权值可达 5e8、最短路长度可达 1e14，故所有距离一律 64 位。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int MAXN = 50005;   // 点数上界
const int MAXM = 200005;  // 边数上界
const ll INF = (ll)4e18;  // 不可达的哨兵（4e18 远大于任何真实最短路长度）

int n, m;                 // 点数、边数
int ex[MAXM], ey[MAXM], ew[MAXM]; // 第 i 条边：ex[i] -> ey[i]，权 ew[i]

// 前向 / 反向 CSR 邻接表：start[v] .. start[v+1]-1 是 v 的出边在 to/wt 里的下标
int startF[MAXN + 2], startR[MAXN + 2];
int toF[MAXM], wtF[MAXM], toR[MAXM], wtR[MAXM];

ll dA[MAXN], dB[MAXN], dC[MAXN], dD[MAXN]; // 四组最短路
int dp[MAXN];                              // 公共最短路 DAG 上的最长链（节点数）

// 把边表压成 CSR：forward 为真建原图，为假建反图
// 建好后 v 的出边就是下标区间 [start[v], start[v+1])
void build(int *start, int *to, int *wt, bool forward) {
    static int cnt[MAXN + 2], cur[MAXN + 2];
    for (int v = 0; v <= n + 1; v++) cnt[v] = 0;
    for (int i = 0; i < m; i++) cnt[forward ? ex[i] : ey[i]]++; // 先数每个点的出度
    start[0] = start[1] = 0;
    for (int v = 1; v <= n; v++) start[v + 1] = start[v] + cnt[v]; // 前缀和定出各点区间的左端
    for (int v = 0; v <= n + 1; v++) cur[v] = start[v];
    for (int i = 0; i < m; i++) {
        int u = forward ? ex[i] : ey[i], v = forward ? ey[i] : ex[i];
        to[cur[u]] = v;
        wt[cur[u]] = ew[i];
        cur[u]++;
    }
}

// 从 src 出发的单源最短路，图由 CSR (start,to,wt) 给出
void dijkstra(int src, const int *start, const int *to, const int *wt, ll *dist) {
    for (int v = 1; v <= n; v++) dist[v] = INF;
    priority_queue<pli, vector<pli>, greater<pli> > pq;
    dist[src] = 0;
    pq.push(pli(0, src));
    while (!pq.empty()) {
        pli cur = pq.top();
        pq.pop();
        ll du = cur.first;
        int u = cur.second;
        if (du > dist[u]) continue; // 过期堆元素
        for (int e = start[u]; e < start[u + 1]; e++) {
            int v = to[e];
            ll nd = du + wt[e];
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push(pli(nd, v));
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) scanf("%d %d %d", &ex[i], &ey[i], &ew[i]);
    int A, B, C, D;
    scanf("%d %d %d %d", &A, &B, &C, &D);

    build(startF, toF, wtF, true);
    build(startR, toR, wtR, false);
    dijkstra(A, startF, toF, wtF, dA); // dA[v] = dist(A,v)
    dijkstra(B, startR, toR, wtR, dB); // 反图从 B => dB[v] = dist(v,B)
    dijkstra(C, startF, toF, wtF, dC); // dC[v] = dist(C,v)
    dijkstra(D, startR, toR, wtR, dD); // 反图从 D => dD[v] = dist(v,D)

    if (dA[B] >= INF / 2 || dC[D] >= INF / 2) { // 某个人走不到终点
        printf("-1\n");
        return 0;
    }
    const ll dab = dA[B], dcd = dC[D];

    // 公共点：同时在两条最短路上；按 dA 升序就是公共 DAG 的拓扑序
    vector<int> order;
    for (int v = 1; v <= n; v++) {
        if (dA[v] + dB[v] == dab && dC[v] + dD[v] == dcd) {
            dp[v] = 1; // 这个点本身可以贡献一次奖励
            order.push_back(v);
        } else {
            dp[v] = 0;
        }
    }
    sort(order.begin(), order.end(), [](int x, int y) { return dA[x] < dA[y]; });

    // 公共边 (u,v,w)：同时落在 A→B 与 C→D 的某条最短路上，沿它 DP 即可接上链
    for (size_t i = 0; i < order.size(); i++) {
        int u = order[i];
        for (int e = startF[u]; e < startF[u + 1]; e++) {
            int v = toF[e];
            ll w = wtF[e];
            if (dA[u] + w + dB[v] == dab && dC[u] + w + dD[v] == dcd && dp[u] + 1 > dp[v]) {
                dp[v] = dp[u] + 1;
            }
        }
    }

    int ans = 0;
    for (int v = 1; v <= n; v++) ans = max(ans, dp[v]); // 没有公共点时为 0
    printf("%d\n", ans);
    return 0;
}
