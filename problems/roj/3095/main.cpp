/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:35
 * update_at: 2026-10-06 18:35
 */

// main.cpp：绿豆蛙的归宿。
// 设 f[u] = 从 u 出发走到 N 的期望路径长度。青蛙在 u 时等概率挑一条出边，
// 由全期望公式：f[u] = (Σ出边长 + Σf[后继]) / 出度。
// 右边只依赖后继，图又是 DAG，所以按逆拓扑序倒推一遍即可，终点 f[N] = 0。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

typedef long long ll;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt; // 链式前向星存图
ll edge_len[MAXM]; // 每条边的长度
ll len_sum[MAXN];  // len_sum[u] = u 所有出边的长度和
int outdeg[MAXN];  // outdeg[u] = u 的出边数
int indeg[MAXN];   // Kahn 拓扑排序用的入度
double f[MAXN];    // f[u] = 从 u 走到 N 的期望路径长度

// 加一条 u -> v、长度 c 的有向边。
void add_edge(int u, int v, ll c) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_len[edge_cnt] = c;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    len_sum[u] += c; // 读入时顺手累加每个点的出边长度和
    outdeg[u]++;
    indeg[v]++;
}

void solve() {
    // Kahn 拓扑排序：入度为 0 的点入队，出队时把后继入度减 1。
    // 队列的正序就是拓扑序，倒过来即逆拓扑序。
    static int order[MAXN]; // 保存拓扑序
    int cnt = 0;
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (indeg[u] == 0) q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        order[cnt] = u;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }

    // 逆拓扑序倒推：算 f[u] 时所有后继的 f 都已经算好。
    // 终点 N 到达即停止，f[N] 保持 0，不参与递推。
    for (int j = cnt; j >= 1; j--) {
        int u = order[j];
        if (u == n || outdeg[u] == 0) continue;
        ll sum_f = 0;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            sum_f += f[v];
        }
        f[u] = (double)(len_sum[u] + sum_f) / outdeg[u];
    }

    printf("%.2f\n", f[1]);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        add_edge(a, b, c);
    }
    solve();
    return 0;
}
