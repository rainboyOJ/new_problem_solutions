/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:30
 * update_at: 2026-10-10 13:30
 */

// 必经边 + 两趟 DP：正/反两张图上各跑一次拓扑 DP 数路径条数，
// 入边前段条数 × 出边后段条数 = 总条数 的边即必经边；
// 沿最短路树取出路径后，前后两趟 DP 各安排一次乘车，滑动窗口枚举断点取最小危险度。
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL; // 路径条数取的模
const ll INF = 1LL << 60;    // 最短路哨兵

struct Arc { // 邻接表里的一条出边
    int to;
    ll w;
    int eid;
};

struct Edge { // 一条边：u -> v，权 w
    int u, v;
    ll w;
};

int n, m, s, t;
ll q;

vector<vector<Arc> > fwd, radj;
vector<Edge> edges;

void topsort(vector<vector<Arc> > &adj, vector<int> &indeg, int src, vector<ll> &cnt, vector<int> &pre) {
    // Kahn 拓扑 DP：环上的点永远不会出队，路径条数保持 0
    cnt.assign(n, 0);
    pre.assign(n, 0);
    vector<ll> dist(n, INF);
    cnt[src] = 1;
    dist[src] = 0;
    vector<int> deg(indeg);
    vector<int> queue;
    for (int v = 0; v < n; ++v) if (deg[v] == 0) queue.push_back(v);
    for (int qi = 0; qi < (int)queue.size(); ++qi) {
        int x = queue[qi];
        ll cx = cnt[x], dx = dist[x]; // 出队时 x 的所有入边都已松弛完
        for (int j = 0; j < (int)adj[x].size(); ++j) {
            int y = adj[x][j].to;
            ll w = adj[x][j].w;
            cnt[y] = (cnt[y] + cx) % MOD;
            if (dx + w < dist[y]) { dist[y] = dx + w; pre[y] = adj[x][j].eid; }
            deg[y] -= 1;
            if (deg[y] == 0) queue.push_back(y);
        }
    }
}

ll solveCase() {
    scanf("%d %d %d %d %lld", &n, &m, &s, &t, &q);

    fwd.assign(n, vector<Arc>());
    radj.assign(n, vector<Arc>());
    edges.assign(m, Edge());
    vector<int> indegF(n, 0), indegB(n, 0);
    for (int e = 0; e < m; ++e) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        edges[e].u = u; edges[e].v = v; edges[e].w = w;
        Arc a;
        a.to = v; a.w = w; a.eid = e;
        fwd[u].push_back(a);
        a.to = u;
        radj[v].push_back(a);
        indegF[v] += 1;
        indegB[u] += 1;
    }
    for (int u = 0; u < n; ++u) reverse(fwd[u].begin(), fwd[u].end()); // 头插法：遍历顺序 = 输入逆序

    vector<ll> cntS, cntT;
    vector<int> pre, preT;
    topsort(fwd, indegF, s, cntS, pre);
    if (cntS[t] == 0) return -1; // 无路径
    topsort(radj, indegB, t, cntT, preT); // 反向那趟的最短路树入边用不上

    vector<char> onBridge(m, 0);
    for (int e = 0; e < m; ++e) {
        int u = edges[e].u, v = edges[e].v;
        onBridge[e] = (cntS[u] * cntT[v] % MOD == cntS[t]);
    }

    // 最短路树上从 t 回溯到 s 的边，反转成行驶顺序
    vector<int> path;
    int x = t;
    while (x != s) {
        int e = pre[x];
        path.push_back(e);
        x = edges[e].u;
    }
    reverse(path.begin(), path.end());
    if (path.empty()) return 1 << 30; // S = T 时无路段可步行

    int p = path.size();
    vector<ll> segW(p), pref(p + 1, 0), danger(p + 1, 0);
    vector<char> segBr(p, 0);
    for (int i = 0; i < p; ++i) {
        segW[i] = edges[path[i]].w;
        segBr[i] = onBridge[path[i]];
        pref[i + 1] = pref[i] + segW[i];
        danger[i + 1] = danger[i] + (segBr[i] ? segW[i] : 0);
    }

    vector<ll> dps(p + 1, 0), dpt(p + 2, 0);
    int j = 0;
    for (int i = 1; i <= p; ++i) {
        while (pref[i] - pref[j] > q) j += 1; // 乘车窗口左端压进第 j 段内部
        ll z = segBr[i - 1] ? segW[i - 1] : 0; // 方案一：第 i 段整段步行
        ll side = 0;
        if (j > 0 && segBr[j - 1]) side = q - (pref[i] - pref[j]); // 窗口左端残留护住第 j 段尾部
        ll a = dps[i - 1] + z, b = danger[j] - side;
        dps[i] = a < b ? a : b;
    }
    j = p;
    for (int i = p; i >= 1; --i) {
        while (pref[j] - pref[i - 1] > q) j -= 1; // 乘车窗口右端压进第 j+1 段内部
        ll z = segBr[i - 1] ? segW[i - 1] : 0; // 方案一：第 i 段整段步行
        ll side = 0;
        if (j < p && segBr[j]) side = q - (pref[j] - pref[i - 1]); // 窗口右端残留护住第 j+1 段头部
        ll a = dpt[i + 1] + z, b = danger[p] - danger[j] - side;
        dpt[i] = a < b ? a : b;
    }

    ll ans = INF;
    for (int i = 1; i <= p; ++i) {
        ll v = dps[i - 1] + dpt[i];
        if (v < ans) ans = v;
    }
    return ans;
}

int main() {
    int L;
    if (scanf("%d", &L) != 1) return 0; // 空输入安全返回
    for (int i = 0; i < L; ++i) printf("%lld\n", solveCase());
    if (L == 0) printf("\n"); // 复刻 py 的 print('') 
    return 0;
}
