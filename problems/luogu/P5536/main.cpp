/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-08-13 08:02
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, k;
vector<int> g[MAXN]; // 邻接表存树
int degree[MAXN];    // 当前剩余度数（剥叶过程中动态更新）
int layer[MAXN];     // layer[i]：节点 i 在第几轮被剥掉（叶子为第 1 轮）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    // 拓扑剥叶：每一轮把所有当前叶子（剩余度数 <= 1）标记层数并删除。
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (degree[i] <= 1) {
            layer[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (degree[v] > 1) {
                degree[v]--;
                if (degree[v] == 1) {
                    layer[v] = layer[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    // 选 layer 最大的 k 个点作核心（剥叶剩余部分连通），
    // 第 k+1 大的 layer 值就是非核心点到核心的最大距离。
    sort(layer + 1, layer + n + 1, greater<int>());
    cout << layer[k + 1] << '\n';
    return 0;
}
