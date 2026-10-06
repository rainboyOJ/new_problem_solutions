/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:40
 * update_at: 2026-10-06 12:40
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;                       // 电脑数上限
const int MAXV = 2 * MAXN + 5;              // 拆点后的点数上限
const int MAXM = 605;                       // 连接数上限
const int MAXE = 4 * MAXM + 2 * MAXN + 10;  // 每次建网的弧数上界（含反向弧）
const ll INF = 1e9;

ll n, m, c1, c2;
ll ea[MAXM], eb[MAXM];      // 每条无向连接的两端电脑
ll cut_id[MAXN], cut_cnt;   // 最小点割：已选中的坏电脑编号与个数

// 拆点网络：点 v 的入点是 2v，出点是 2v+1；链式前向星存弧
int head[MAXV], nxt[MAXE], to[MAXE];
ll cap[MAXE];
int e_cnt = 1;              // 弧计数从 1 开始、成对预增：弧对是 (2,3),(4,5)...，i^1 恰好是 i 的反向弧

ll level[MAXV], cur[MAXV];  // Dinic 的分层图与当前弧
ll s, t;                    // 源 = c1 的入点，汇 = c2 的入点
bool safe[MAXN];            // safe[v]=1：v 不许坏（起止点或已排除点）
bool broken[MAXN];          // broken[v]=1：v 当作已坏（点弧容量 0）

// 加一对正反弧：反向弧初始容量 0，供增广路回退流量
void add_arc(int u, int v, ll c) {
    ++e_cnt; // 正弧取偶数编号，i^1 才是反向弧
    to[e_cnt] = v; cap[e_cnt] = c; nxt[e_cnt] = head[u]; head[u] = e_cnt;
    e_cnt++;
    to[e_cnt] = u; cap[e_cnt] = 0; nxt[e_cnt] = head[v]; head[v] = e_cnt;
}

// 建网：坏点容量 0，不许坏点容量 INF，其余点容量 1；连接是双向 INF 线路
void build_net() {
    memset(head, 0, sizeof(head));
    e_cnt = 1; // 弧对从 (2,3) 开始，保证 i^1 配对成立
    for (ll v = 1; v <= n; v++) {
        ll c = 1;                       // 点内部弧 v入->v出：坏掉 v 的代价
        if (broken[v]) c = 0;
        else if (safe[v]) c = INF;      // c1、c2 的点弧是 INF，永远不会被切
        add_arc(2 * v, 2 * v + 1, c);
    }
    for (ll i = 1; i <= m; i++) {
        // 坏的是电脑不是线：每条连接拆成两个方向，容量 INF
        add_arc(2 * ea[i] + 1, 2 * eb[i], INF);
        add_arc(2 * eb[i] + 1, 2 * ea[i], INF);
    }
}

// BFS 分层：残量网络里从 s 出发能否层层推进到 t
bool bfs() {
    memset(level, -1, sizeof(level));
    queue<ll> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            ll v = to[i];
            if (cap[i] > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

// 在分层图上从 u 尽量往 t 推流，返回这条路径推出的流量
ll dfs(ll u, ll pushed) {
    if (u == t) return pushed;
    for (ll &i = cur[u]; i; i = nxt[i]) {
        ll v = to[i];
        if (cap[i] > 0 && level[v] == level[u] + 1) {
            ll got = dfs(v, min(pushed, cap[i]));
            if (got > 0) {
                cap[i] -= got;
                cap[i ^ 1] += got;
                return got;
            }
        }
    }
    return 0;
}

// Dinic 最大流：按最大流最小割定理，它等于拆点网络的最小点割容量
ll dinic() {
    ll flow = 0;
    while (bfs()) {
        for (ll v = 0; v < 2 * n + 2; v++) cur[v] = head[v];
        while (ll got = dfs(s, INF)) flow += got;
    }
    return flow;
}

int main() {
    cin >> n >> m >> c1 >> c2;
    for (ll i = 1; i <= m; i++) cin >> ea[i] >> eb[i];

    s = 2 * c1;
    t = 2 * c2;
    safe[c1] = safe[c2] = true; // 起止电脑永远不许坏

    build_net();
    ll k = dinic(); // 先求最小点割的大小 k

    // 按编号从小到大逐点判定，保证答案字典序最小
    for (ll v = 1; v <= n; v++) {
        if (safe[v]) continue; // 起止点与已排除点不再试探
        ll rest = k - cut_cnt - 1; // 若选 v，最小割里还差的点数
        broken[v] = true;          // 把 v 当作已坏重跑最大流
        build_net();
        // 恒有 flow >= rest；取等 <=> 存在含 v 的最小割
        if (dinic() == rest) {
            cut_cnt++;
            cut_id[cut_cnt] = v; // 收下 v，让答案这一位尽可能小
        } else {
            broken[v] = false;
            safe[v] = true; // 任何最小割都不含 v，标记为不许坏
        }
    }

    cout << cut_cnt << "\n";
    for (ll i = 1; i <= cut_cnt; i++) {
        cout << cut_id[i] << (i < cut_cnt ? " " : "");
    }
    cout << "\n";
    return 0;
}
