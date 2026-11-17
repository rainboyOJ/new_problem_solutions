#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5; // 定长数组上限，按题目数据范围调整
const int MOD = 80112002;

int n, m;
vector<int> g[maxn]; // g[u] 保存从 u 出发的边的终点
int in_deg[maxn];    // 运行中表示剩余入度，会被 topsort 修改
int out_deg[maxn];   // 出度，用于判断顶级消费者
vector<int> ta;      // 拓扑排序输出的顶点序列
int ways[maxn];      // 到达该节点的食物链路径数

bool topsort() {
    queue<int> q;
    ta.clear();

    for (int u = 1; u <= n; ++u) {
        if (in_deg[u] == 0) q.push(u);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ta.push_back(u);

        for (int v : g[u]) {
            --in_deg[v]; // 删除 u -> v，解除一条依赖
            if (in_deg[v] == 0) q.push(v);
        }
    }

    // 是否无环（DAG）
    return ta.size() == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    // 读取数据
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        ++in_deg[v];
        ++out_deg[u];
    }

    // 初始生产者（入度为 0）的食物链路径数为 1
    for (int u = 1; u <= n; ++u) {
        if (in_deg[u] == 0) {
            ways[u] = 1;
        }
    }

    // 执行 top sort
    topsort();

    // 按照拓扑序递推路径数
    for (int u : ta) {
        for (int v : g[u]) {
            ways[v] = (ways[v] + ways[u]) % MOD;
        }
    }

    // 统计所有顶级消费者（出度为 0）的路径数之和
    int ans = 0;
    for (int u = 1; u <= n; ++u) {
        if (out_deg[u] == 0) {
            ans = (ans + ways[u]) % MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}
