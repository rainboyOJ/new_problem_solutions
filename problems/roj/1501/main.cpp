/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:48
 * update_at: 2026-10-05 04:49
 */
#include <bits/stdc++.h>
using namespace std;

// 一本通 3.2 练习 5 最优贸易：正反向 SPFA 预处理前缀最低买入价与后缀最高卖出价
// 数据范围 n <= 1e5，m <= 5e5，价格在 1..100 之间，队列松弛可快速收敛

const int MAXN = 100005;
const int MAXM = 1000005; // m <= 5e5，双向边拆成两条，最多 1e6 条有向边
const int INF = 1e9;

typedef long long ll;

ll n;
ll m;
int price[MAXN]; // price[i] 表示第 i 号城市的水晶球价格，值域只有 1..100，用 int

// 正向图存所有有向边，反向图把每条边方向翻转，用链式前向星避免大 vector 开销
int head[MAXN];
int to[MAXM];
int nxt[MAXM];
int edge_cnt;
int rhead[MAXN];
int rto[MAXM];
int rnxt[MAXM];
int redge_cnt;

int min_buy[MAXN];  // min_buy[i] 表示从 1 号城市走到 i 的路径上出现过的最低价格
int max_sell[MAXN]; // max_sell[i] 表示从 i 号城市走到 n 的路径上出现过的最高价格

// 加入一条有向边 u -> v，正向图和反向图同时登记，省去二次读入
// 城市编号不超过 n <= 1e5，用 int 作端点类型即可
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;

    redge_cnt++;
    rto[redge_cnt] = u;
    rnxt[redge_cnt] = rhead[v];
    rhead[v] = redge_cnt;
}

// 正向松弛：沿 1 号城市能走到的边不断更新各点路径上的最低买入价
void spfa_min_buy() {
    for (ll i = 1; i <= n; i++) {
        min_buy[i] = INF;
    }
    min_buy[1] = price[1];

    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            // 走到 v 时能买到的最低价：之前的最低价与 v 的售价取较小值
            int cand = min_buy[u];
            if (price[v] < cand) {
                cand = price[v];
            }
            if (cand < min_buy[v]) {
                min_buy[v] = cand;
                q.push(v);
            }
        }
    }
}

// 反向松弛：在反向图上从 n 号城市出发，求各点出发能到达 n 时的最高卖出价
void spfa_max_sell() {
    for (ll i = 1; i <= n; i++) {
        max_sell[i] = -1;
    }
    max_sell[n] = price[n];

    queue<int> q;
    q.push(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = rhead[u]; e != 0; e = rnxt[e]) {
            int v = rto[e];
            // 从 v 出发能卖出的最高价：后续最高价与 v 的售价取较大值
            int cand = max_sell[u];
            if (price[v] > cand) {
                cand = price[v];
            }
            if (cand > max_sell[v]) {
                max_sell[v] = cand;
                q.push(v);
            }
        }
    }
}

// 枚举中转城市 i，把收益拆成 max_sell[i] - min_buy[i]
void solve() {
    spfa_min_buy();
    spfa_max_sell();

    int ans = 0; // 赚不到差价时不做贸易，收益为 0
    for (ll i = 1; i <= n; i++) {
        // min_buy[i] <= 100 说明 i 可由 1 到达，max_sell[i] >= 0 说明 i 可到达 n
        if (min_buy[i] <= 100 && max_sell[i] >= 0) {
            int profit = max_sell[i] - min_buy[i];
            if (profit > ans) {
                ans = profit;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> price[i];
    }
    for (ll i = 1; i <= m; i++) {
        int x; // 道路端点，x, y <= n <= 1e5
        int y;
        int z; // z = 1 单向，z = 2 双向
        cin >> x >> y >> z;
        add_edge(x, y);
        if (z == 2) {
            add_edge(y, x); // 双向道路相当于两条方向相反的单向边
        }
    }

    solve();

    return 0;
}
