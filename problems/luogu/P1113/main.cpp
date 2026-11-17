#include <bits/stdc++.h>
using namespace std;

const int maxn = 10000 + 5; // 定长数组上限，按题目数据范围调整

int n;
vector<int> g[maxn]; // g[u] 保存从 u 出发的边的终点
int in_deg[maxn];    // 运行中表示剩余入度，会被 topsort 修改
vector<int> ta;      // 拓扑排序输出的顶点序列
int len[maxn];       // 每个任务的耗时
int finish[maxn];    // 最早完成时间

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

    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        int id, cost, pre;
        cin >> id >> cost;
        len[id] = cost;
        while (cin >> pre && pre != 0) {
            g[pre].push_back(id);
            ++in_deg[id];
        }
    }

    // 执行 top sort
    topsort();

    int ans = 0;
    // 按照拓扑序进行 DAG DP
    for (int u : ta) {
        finish[u] += len[u];
        ans = max(ans, finish[u]);
        for (int v : g[u]) {
            finish[v] = max(finish[v], finish[u]);
        }
    }

    cout << ans << '\n';
    return 0;
}
