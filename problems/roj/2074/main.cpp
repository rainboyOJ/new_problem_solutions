/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:33
 * update_at: 2026-10-06 11:33
 *
 * main.cpp：追查坏牛奶。
 * 把停运若干卡车使 1 号仓库到不了 n 号仓库建模成带权有向图的最小割，
 * 用容量变换 w_e = c_e * K + 1（K = m + 1）把“损失最小、其次卡车数最少”
 * 两个目标合并成一次最小割，再用 Dinic 求最大流；最后按输入顺序逐条删边
 * 重测流，恰好让最大流下降 w_e 的边就属于该最小割。
 */
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 35;          // 仓库数 n <= 32
const int MAXM = 1005;        // 卡车数 m <= 1000
const int MAXE = 2 * MAXM;    // 每条边带一条反向边
const ll INF = 1000000000000000000LL;

int n;                        // 仓库数（题面第一行的第一个数）
int m;                        // 卡车数（题面第一行的第二个数）
int head[MAXN];               // head[u]：节点 u 的第一条出边编号
int nxt_edge[MAXE];           // 链式前向星的下一条边
int to[MAXE];                 // 边的终点
ll cap[MAXE];                 // 当前残量网络的容量（成对出现：2i 正向，2i+1 反向）
int edge_cnt;                 // 已加入的边数

ll base_w[MAXM];              // base_w[i]：第 i 条卡车线路的修改容量 c*K+1，下标从 0 开始
bool removed[MAXM];           // removed[i]：第 i 条线路是否已被确认属于最小割

int level[MAXN];              // Dinic：BFS 得到的层次
int cur[MAXN];                // Dinic：当前弧指针

// 加入一条有向边以及它的反向边，两者编号为 2i 与 2i+1。
void add_edge(int u, int v, ll c) {
    to[edge_cnt] = v;
    cap[edge_cnt] = c;
    nxt_edge[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// 按 removed 标记重建残量网络：被删掉的线路容量为 0，其余取修改容量。
void reset_cap() {
    for (int i = 0; i < 2 * m; i++) {
        cap[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        if (!removed[i]) {
            cap[2 * i] = base_w[i];
        }
    }
}

// Dinic 的 BFS 分层，返回汇点 t 是否可达。
bool bfs(int s, int t) {
    for (int i = 1; i <= n; i++) {
        level[i] = -1;
    }
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = head[u]; e != -1; e = nxt_edge[e]) {
            int v = to[e];
            if (cap[e] > 0 && level[v] < 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] >= 0;
}

// Dinic 的一次增广：沿层次递增的路径把 f 的流量尽量送到汇点，返回实际送出量。
ll dfs(int u, int t, ll f) {
    if (u == t) {
        return f;
    }
    while (cur[u] != -1) {
        int e = cur[u];
        int v = to[e];
        if (cap[e] > 0 && level[v] == level[u] + 1) {
            ll d = dfs(v, t, min(f, cap[e]));
            if (d > 0) {
                cap[e] -= d;
                cap[e ^ 1] += d;
                return d;
            }
        }
        cur[u] = nxt_edge[e];
    }
    return 0;
}

// 在当前残量网络上求 1 号仓库到 n 号仓库的最大流。
ll max_flow() {
    ll flow = 0;
    int s = 1;
    int t = n;
    while (bfs(s, t)) {
        for (int i = 1; i <= n; i++) {
            cur[i] = head[i];
        }
        while (true) {
            ll d = dfs(s, t, INF);
            if (d == 0) {
                break;
            }
            flow += d;
        }
    }
    return flow;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    edge_cnt = 0;

    ll K = m + 1; // 放大系数：任何割的边数都不超过 m，必小于 K
    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        scanf("%d %d %lld", &u, &v, &c);
        base_w[i] = c * K + 1; // 损失 c 的线路容量变成 c*K+1
        add_edge(u, v, 0);     // 容量稍后由 reset_cap 填入，这里先建好边结构
        add_edge(v, u, 0);
        removed[i] = false;
    }

    reset_cap();
    ll total_flow = max_flow(); // 变换后图的最大流 = 最小割值
    ll cur_flow = total_flow;

    int ans[MAXM]; // 属于最小割的线路行号（按输入顺序）
    int ans_cnt = 0;

    // 贪心提取割边：逐条删除并重跑最大流，若最大流恰好下降该边的修改容量，
    // 说明任何最大流都绕不开它，它属于某个最小割。
    for (int i = 0; i < m; i++) {
        removed[i] = true;
        reset_cap();
        ll next_flow = max_flow();
        if (cur_flow - next_flow == base_w[i]) {
            ans[ans_cnt] = i + 1; // 线路行号从 1 开始
            ans_cnt++;
            cur_flow = next_flow;
        } else {
            removed[i] = false;
        }
    }

    ll cost = total_flow / K; // 商是最小总损失
    printf("%lld %d\n", cost, ans_cnt);
    for (int i = 0; i < ans_cnt; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
