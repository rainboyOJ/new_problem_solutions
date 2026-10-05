/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:24
 * update_at: 2026-10-05 11:24
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10005;      // 员工数 n <= 10000
const int MAXM = 20005;      // 意见条数 m <= 20000

// 反向图：约束 "a 应该比 b 高" 改写成 b -> a，沿这条边方向拓扑，才能先定低薪再定高薪。
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int indeg[MAXN];             // 入度：a 的入度 = 让 a 必须更高的"下级"个数
ll pay[MAXN];               // 每人最终奖金；用 ll 累加并兼容极端值

// 加一条 u -> v 的有向边（u 工资更低 / v 工资更高）。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int n, m;

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) head[i] = 0, indeg[i] = 0;
    edge_cnt = 0;
    for (int i = 1; i <= m; i++) {
        int a, b;             // a 应该比 b 高 => 建边 b -> a
        cin >> a >> b;
        add_edge(b, a);
        indeg[a]++;
    }
}

void solve() {
    for (int i = 1; i <= n; i++) pay[i] = 100;  // 每位员工奖金最少 100 元

    queue<int> q;             // Kahn 队列：所有入度为 0 的点（没有更低的人要超过）
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    int done = 0;             // 已经定薪出队的员工数
    while (!q.empty()) {
        int u = q.front(); q.pop();
        done++;
        // u 已经定薪，把后继端点 v 抬到 max(pay[v], pay[u] + 1)
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (pay[u] + 1 > pay[v]) pay[v] = pay[u] + 1;
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }

    if (done < n) {           // 还有人没轮到：约束成环，互相矛盾，无解
        cout << "Poor Xed";
    }
    else {
        ll total = 0;
        for (int i = 1; i <= n; i++) total += pay[i];
        cout << total;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}