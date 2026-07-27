/**
 * P4017 最大食物链计数
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int MAXM = 500005;
const int MOD = 80112002;

int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int indeg[MAXN], outdeg[MAXN];
int ways[MAXN]; // 到达该结点的食物链数
int n, m;

void add_edge(int u, int v) {
    ++cnt;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
        ++indeg[b];
        ++outdeg[a];
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
            ways[i] = 1; // 生产者：食物链数为 1
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            ways[v] = (ways[v] + ways[u]) % MOD;
            --indeg[v];
            if (indeg[v] == 0) q.push(v);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (outdeg[i] == 0) // 顶级消费者
            ans = (ans + ways[i]) % MOD;
    printf("%d\n", ans);
    return 0;
}
