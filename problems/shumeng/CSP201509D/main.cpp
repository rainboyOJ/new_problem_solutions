/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:57
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
vector<int> graph[MAXN]; // 邻接表存有向图
int dfn[MAXN], low[MAXN]; // 首次访问时间戳与可达的最早时间戳
int in_stack[MAXN];       // 节点是否在 Tarjan 的栈中
int stack_nodes[MAXN];    // Tarjan 栈
int clock_time, stack_size;
long long answer; // 便利城市对总数，用 long long 防溢出

// Tarjan 求强连通分量：栈中同一分量会连续弹出。
void tarjan(int u) {
    dfn[u] = low[u] = ++clock_time;
    stack_nodes[++stack_size] = u;
    in_stack[u] = 1;
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i];
        if (dfn[v] == 0) {
            // 树边：递归后尝试用子树的可达时间更新 low[u]。
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            // 回边或横叉边指向栈中节点：说明它们处于同一分量。
            low[u] = min(low[u], dfn[v]);
        }
    }
    // low[u] == dfn[u] 时，u 是所在分量的根，栈顶到 u 之间是完整分量。
    if (low[u] != dfn[u]) return;
    int size = 0;
    while (true) {
        int v = stack_nodes[stack_size--];
        in_stack[v] = 0;
        size++;
        if (v == u) break;
    }
    // 分量内任意两点两两互通，贡献 C(size, 2) 对。
    answer += 1LL * size * (size - 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) if (dfn[i] == 0) tarjan(i);
    cout << answer << '\n';
    return 0;
}
