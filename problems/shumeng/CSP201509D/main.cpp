/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:36
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
vector<int> graph[MAXN];
int dfn[MAXN], low[MAXN], in_stack[MAXN], stack_nodes[MAXN];
int clock_time, stack_size;
long long answer;

void tarjan(int u) {
    dfn[u] = low[u] = ++clock_time;
    stack_nodes[++stack_size] = u;
    in_stack[u] = 1;
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i];
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] != dfn[u]) return;
    int size = 0;
    while (true) {
        int v = stack_nodes[stack_size--];
        in_stack[v] = 0;
        size++;
        if (v == u) break;
    }
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
