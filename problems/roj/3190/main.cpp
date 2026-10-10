/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 13:48
 * update_at: 2026-10-09 13:48
 */
// ROJ 3190《天天爱跑步》(NOIP2016 提高组)：树上差分 + 倍增 LCA。
// 把玩家路径 S->T 在 L = LCA(S,T) 处拆成上行段 S->L 与下行段 L->T：
//   上行段节点 u 的到达时刻 = depth[S]-depth[u]  ⇒ 命中条件 depth[u]+W[u] == depth[S]
//   下行段节点 u 的到达时刻 = depth[S]+depth[u]-2*depth[L] ⇒ 命中条件 depth[u]-W[u] == 2*depth[L]-depth[S]
// 于是每条路径变成两个桶上的差分事件，按后序遍历一边进出子树一边用全局桶计数。
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 300005;   // n 的上限
const int LOG = 19;        // 倍增层数：2^19 > 3*10^5

vector<int> adj[MAXN];     // adj[u] = 与 u 相邻的点
int n, m;
int W[MAXN];               // W[u] = 节点 u 的观察时刻

int depth[MAXN];           // depth[u] = 根深度（根取 1，深度记 1）
int up[MAXN][LOG];         // up[u][i] = u 的 2^i 级祖先，越界为 0
int q[MAXN];               // BFS 队列

// 上行段的差分事件：值 = depth[S]
vector<int> ev_add1[MAXN]; // ev_add1[u]：以 u 为起点的玩家在 u 处入桶
vector<int> ev_del1[MAXN]; // ev_del1[u]：在 u 处出桶（u = L 的父节点）
// 下行段的差分事件：值 = 2*depth[L]-depth[S]
vector<int> ev_add2[MAXN]; // ev_add2[u]：在 u = T 处入桶
vector<int> ev_del2[MAXN]; // ev_del2[u]：在 u = L 处出桶，避免 L 被上下两段重复统计

int cnt1[MAXN * 2];        // cnt1[v] 表示值 depth[S]=v 正在生效的上行段条数
int cnt2[MAXN * 3];        // cnt2[v+MAXN] 表示值 2*depth[L]-depth[S]=v 正在生效的下行段条数

int ans[MAXN];             // ans[u] = 节点 u 的观察员看到的人数

int stk[MAXN];             // 手工栈：节点编号
int state[MAXN];           // 手工栈：0 = 刚进入 u，1 = u 的子树已处理完
int pre_val1[MAXN];        // pre_val1[u] = 进入 u 之前 cnt1[depth[u]+W[u]] 的值
int pre_val2[MAXN];        // pre_val2[u] = 进入 u 之前 cnt2[depth[u]-W[u]+MAXN] 的值

// 以 1 为根 BFS：同时求深度、倍增表和 BFS 序（避免递归 DFS 在链上爆栈）。
void bfs() {
    int head = 0, tail = 0;
    q[tail++] = 1;
    depth[1] = 1;

    while (head < tail) {
        int u = q[head++];
        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v != up[u][0]) {
                depth[v] = depth[u] + 1;
                up[v][0] = u;
                q[tail++] = v;
            }
        }
    }
}

// 倍增求 LCA(S,T)。
int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void solve() {
    if (!(cin >> n >> m)) return;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> W[i];
    }

    bfs();

    for (int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        int lca = get_lca(s, t);

        // 上行段 S -> L：在 S 入桶，在 L 的父节点出桶（根无父节点时自然终止）。
        int val1 = depth[s];
        ev_add1[s].push_back(val1);
        if (up[lca][0] != 0) {
            ev_del1[up[lca][0]].push_back(val1);
        }

        // 下行段 L -> T：在 T 入桶，在 L 出桶，让 L 只由上行段负责统计。
        int val2 = 2 * depth[lca] - depth[s];
        ev_add2[t].push_back(val2);
        ev_del2[lca].push_back(val2);
    }

    // 手工栈做后序遍历：state 0 = 刚进入（记进入前的桶值），state 1 = 子树已处理完。
    int top = 0;
    stk[top] = 1;
    state[top] = 0;
    top++;

    while (top > 0) {
        int u = stk[--top];
        int st = state[top];

        if (st == 0) {
            stk[top] = u;
            state[top] = 1;
            top++;

            // 进入 u：先记下桶的当前值，子树内的增量才是 u 的答案。
            int req1 = depth[u] + W[u];
            if (0 <= req1 && req1 < MAXN * 2) pre_val1[u] = cnt1[req1];

            int req2 = depth[u] - W[u] + MAXN;
            if (0 <= req2 && req2 < MAXN * 3) pre_val2[u] = cnt2[req2];

            for (int v : adj[u]) {
                if (v != up[u][0]) {
                    stk[top] = v;
                    state[top] = 0;
                    top++;
                }
            }
        } else {
            // 离开 u：把挂在 u 上的差分事件生效，此时整个子树都已处理完。
            for (int val : ev_add1[u]) {
                if (0 <= val && val < MAXN * 2) cnt1[val]++;
            }
            for (int val : ev_del1[u]) {
                if (0 <= val && val < MAXN * 2) cnt1[val]--;
            }
            for (int val : ev_add2[u]) {
                int idx = val + MAXN;
                if (0 <= idx && idx < MAXN * 3) cnt2[idx]++;
            }
            for (int val : ev_del2[u]) {
                int idx = val + MAXN;
                if (0 <= idx && idx < MAXN * 3) cnt2[idx]--;
            }

            int req1 = depth[u] + W[u];
            if (0 <= req1 && req1 < MAXN * 2) ans[u] += cnt1[req1] - pre_val1[u];

            int req2 = depth[u] - W[u] + MAXN;
            if (0 <= req2 && req2 < MAXN * 3) ans[u] += cnt2[req2] - pre_val2[u];
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
