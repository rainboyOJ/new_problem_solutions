/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:50
 * update_at: 2026-10-05 05:50
 */
// 1517 间谍网络：Tarjan 缩点成 DAG，源点分量必须收买、买齐即全控；
// 无解时从可收买分量出发做可达性标记，取不可控分量的最小编号。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
const int MAXM = 8005;

typedef long long ll;

const ll INF = 1e18;

ll n, p, r;
ll ea[MAXM], eb[MAXM];      // 证据对 (A, B)：逮捕 A 后可继续逮捕 B，即有向边 A -> B
ll bribe_cost[MAXN];        // bribe_cost[i] = 间谍 i 的收买金额，不可收买为 INF

// 原图邻接表（链式前向星）
int head[MAXN], nxt[MAXM], to[MAXM], edge_cnt;

// Tarjan 所需
ll dfn[MAXN], low[MAXN];
bool on_st[MAXN];
int stk[MAXN], top_stk;     // Tarjan 的点栈
int comp[MAXN];             // comp[v] = v 所在强连通分量编号
int comp_cnt;

// 缩点后各分量的统计
ll comp_cost[MAXN];         // 分量内可收买成员的最低金额，INF 表示不可收买
ll comp_min_id[MAXN];       // 分量内最小的间谍编号
ll indeg[MAXN];             // 缩点后 DAG 的入度

// 缩点后的 DAG（也用链式前向星）
int chead[MAXN], cnxt[MAXM], cto[MAXM], cedge_cnt;

// 加一条原图边 u -> v。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 加一条缩点图边 cu -> cv。
void add_cedge(int cu, int cv) {
    cedge_cnt++;
    cto[cedge_cnt] = cv;
    cnxt[cedge_cnt] = chead[cu];
    chead[cu] = cedge_cnt;
}

// Tarjan 求强连通分量：一个点的出边全部走完后，若 low == dfn 则它是分量根。
void tarjan(int u) {
    static int timer = 0;
    top_stk++;
    stk[top_stk] = u;
    on_st[u] = true;
    timer++;
    dfn[u] = low[u] = timer;

    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (dfn[v] == 0) {          // 树边：深入
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (on_st[v]) {      // 回边：u 能经 v 回到更早的点
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }

    if (low[u] == dfn[u]) {         // u 是分量根：弹栈到 u 为止，整段是一个分量
        comp_cnt++;
        while (top_stk > 0) {
            int w = stk[top_stk];
            top_stk--;
            on_st[w] = false;
            comp[w] = comp_cnt;
            if (w == u) break;
        }
    }
}

ll read_input() {
    cin >> n;
    // 不可收买的间谍金额记为 INF，避免全局零初始化被当成 0 元收买
    for (ll i = 1; i <= n; i++) bribe_cost[i] = INF;
    cin >> p;
    for (ll i = 1; i <= p; i++) {
        ll id, money;
        cin >> id >> money;
        bribe_cost[id] = money;
    }
    cin >> r;
    for (ll i = 1; i <= r; i++) {
        cin >> ea[i] >> eb[i];
        add_edge(ea[i], eb[i]);
    }
    return 0;
}

void solve() {
    // 1. 求每个点的强连通分量编号
    for (ll i = 1; i <= n; i++) {
        if (dfn[i] == 0) tarjan(i);
    }

    // 2. 统计每个分量的最低收买金额和最小编号
    for (ll c = 1; c <= comp_cnt; c++) {
        comp_cost[c] = INF;
        comp_min_id[c] = INF;
    }
    for (ll v = 1; v <= n; v++) {
        ll c = comp[v];
        if (v < comp_min_id[c]) comp_min_id[c] = v;
        if (bribe_cost[v] < comp_cost[c]) comp_cost[c] = bribe_cost[v];
    }

    // 3. 建缩点后的 DAG 并统计入度（跨分量的边才计入）
    for (ll i = 1; i <= r; i++) {
        ll ca = comp[ea[i]], cb = comp[eb[i]];
        if (ca != cb) {
            add_cedge(ca, cb);
            indeg[cb]++;
        }
    }

    // 4. 从每个可收买分量出发做可达性标记：
    //    任一收买方案的控制范围都不超过这些分量的可达并集
    static bool ctrl[MAXN];     // ctrl[c] = 分量 c 能否被某个收买方案控制
    static int bfsq[MAXN];
    int qh = 0, qt = 0;
    for (ll c = 1; c <= comp_cnt; c++) {
        if (comp_cost[c] < INF) {
            ctrl[c] = true;
            qt++;
            bfsq[qt] = c;
        }
    }
    while (qh < qt) {
        qh++;
        int c = bfsq[qh];
        for (int i = chead[c]; i != 0; i = cnxt[i]) {
            int v = cto[i];
            if (!ctrl[v]) {
                ctrl[v] = true;
                qt++;
                bfsq[qt] = v;
            }
        }
    }

    // 5. 判定与输出：
    //    无解 <=> 存在不可控分量（此时必有死源点，补集非空，两个条件等价）
    ll lost_min_id = INF;
    for (ll c = 1; c <= comp_cnt; c++) {
        if (!ctrl[c] && comp_min_id[c] < lost_min_id) {
            lost_min_id = comp_min_id[c];
        }
    }
    if (lost_min_id != INF) {
        cout << "NO\n" << lost_min_id << "\n";
        return;
    }

    // 有解：入度 0 的源点分量必须买（没人能到它们），买齐即覆盖全图
    ll ans = 0;
    for (ll c = 1; c <= comp_cnt; c++) {
        if (indeg[c] == 0) ans += comp_cost[c];
    }
    cout << "YES\n" << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
