/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 22:30
 * update_at: 2026-10-10 01:48
 */
// main.cpp：项链。
// DAG 上先求全图最大权路径（Monster 的项链），再从该路径的终点向后、起点向前
// 在「不含该路径上任何点」的子图里求最大权路径（我的项链），最后对 0 取 max。
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXM = 200005;

// 路径权值可以低到 -1e5 * 1e9 = -1e14，所以极小值要取到 -1e18 级别
const ll NEG = -(ll)1e18;

int n, m;
ll w[MAXN]; // w[i] 第 i 个城市的宝石价值

// 原图链式前向星：head/to/nxt 存 u -> v
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
// 反向图链式前向星：存 v -> u，用来求「前驱方向」的最大权路径
int rhead[MAXN], rto[MAXM], rnxt[MAXM], redge_cnt;
// 两张图的入度，拓扑排序时会被消耗
int indeg[MAXN], rindeg[MAXN];

int topo[MAXN], rtopo[MAXN]; // 原图 / 反向图的拓扑序

// 以某点为终点的最大权路径信息（一个点一条记录，聚合成 struct）
struct PathInfo {
    ll value;  // 该路径的宝石价值之和
    int start; // 该路径的起点
    int from;  // 该路径上这个点的前驱（起点指向自己）
};
PathInfo info[MAXN];

int on_path[MAXN]; // on_path[u] = 1 表示 u 属于 Monster 拿走的那条路径
int usable[MAXN];  // usable[u] = 1 表示 u 在当前这一次 DP 的候选集合内
ll dp[MAXN];       // 当前这一次 DP 的「以 u 结尾的最大权值」

// 加一条原图边 u -> v，同时把反向边 v -> u 加进反向图。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    indeg[v]++;

    redge_cnt++;
    rto[redge_cnt] = u;
    rnxt[redge_cnt] = rhead[v];
    rhead[v] = redge_cnt;
    rindeg[u]++;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
}

// Kahn 算法分别求原图、反向图的拓扑序；入度为 0 的点先入队。
void topo_sort() {
    queue<int> q;
    int len = 0;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo[++len] = u;
        for (int e = head[u]; e; e = nxt[e]) {
            if (--indeg[to[e]] == 0) q.push(to[e]);
        }
    }

    len = 0;
    for (int i = 1; i <= n; i++) {
        if (rindeg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        rtopo[++len] = u;
        for (int e = rhead[u]; e; e = rnxt[e]) {
            if (--rindeg[rto[e]] == 0) q.push(rto[e]);
        }
    }
}

// Monster 的项链：按拓扑序做「以某点为终点的最大权路径」DP。
// Monster 拿走全图价值最大的那条路径，价值可以为负，所以空项链（0）随时可选。
void find_monster_path(ll &ans1, int &l1, int &r1) {
    for (int i = 1; i <= n; i++) {
        info[i].value = NEG;
        info[i].start = i;
        info[i].from = i;
    }
    for (int t = 1; t <= n; t++) {
        int u = topo[t];
        if (w[u] > info[u].value) { // 从 u 自己开始一条新路径
            info[u].value = w[u];
            info[u].start = u;
            info[u].from = u;
        }
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (info[v].value < w[v] + info[u].value) { // 把 u 接到 v 前面
                info[v].value = w[v] + info[u].value;
                info[v].start = info[u].start;
                info[v].from = u;
            }
        }
    }

    ans1 = NEG;
    l1 = r1 = 0;
    for (int i = 1; i <= n; i++) { // 同为最优时取编号小的终点（固定 Monster 的项链）
        if (info[i].value > ans1) {
            ans1 = info[i].value;
            l1 = info[i].start;
            r1 = i;
        }
    }
}

// 我的项链：在「绕开 on_path 上的点」的前提下，从种子集合出发求最大权路径。
// 沿原图走就是接在 Monster 项链后面，沿反向图走就是接在前面。
// 返回在这一片子图里能得到的最优价值（可以与 0 取 max 由调用者负责）。
ll best_avoiding_path(int *h, int *t, int *nx, int *order, int seed_from) {
    int e;
    for (int i = 1; i <= n; i++) {
        usable[i] = 0;
        dp[i] = NEG;
    }
    // 种子集合：Monster 项链终点（或起点）在本方向上的直接相邻点
    for (e = h[seed_from]; e; e = nx[e]) {
        usable[t[e]] = 1;
    }
    for (int k = 1; k <= n; k++) {
        int u = order[k];
        if (!usable[u] || on_path[u]) continue; // 必须绕开 Monster 项链上的点
        if (w[u] > dp[u]) dp[u] = w[u];
        for (e = h[u]; e; e = nx[e]) {
            int v = t[e];
            if (on_path[v]) continue;
            usable[v] = 1;
            if (dp[v] < w[v] + dp[u]) dp[v] = w[v] + dp[u];
        }
    }

    ll res = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > res) res = dp[i];
    }
    return res;
}

void solve() {
    ll ans1;
    int l1, r1;
    find_monster_path(ans1, l1, r1);

    if (ans1 <= 0) { // 最大路径都非正，空项链（0）最优，两条项链都取空
        cout << "0 0\n";
        return;
    }
    cout << ans1 << ' ';

    // 回溯出 Monster 项链占用的点集合
    for (int u = r1;; u = info[u].from) {
        on_path[u] = 1;
        if (u == l1) break;
    }

    // 接在 Monster 项链后面：从 r1 出发向「后继方向」走
    ll ans2 = best_avoiding_path(head, to, nxt, topo, r1);
    // 接在 Monster 项链前面：从 l1 出发向「前驱方向」走（在反向图上做）
    ll before = best_avoiding_path(rhead, rto, rnxt, rtopo, l1);
    if (before > ans2) ans2 = before;

    cout << ans2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    topo_sort();
    solve();

    return 0;
}
