/**
 * P1983 车站分级
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 1000005;

int head[MAXN * 2], to[MAXM], nxt[MAXM], w[MAXM], cnt;
int indeg[MAXN * 2];
int level[MAXN * 2];
int n, train_count;

void add_edge(int u, int v, int weight) {
    ++cnt;
    to[cnt] = v;
    w[cnt] = weight;
    nxt[cnt] = head[u];
    head[u] = cnt;
    ++indeg[v];
}

int main() {
    scanf("%d%d", &n, &train_count);
    int total = n + train_count; // 真实站 + 虚拟站
    for (int t = 0; t < train_count; ++t) {
        int stop_cnt;
        scanf("%d", &stop_cnt);
        int stops[MAXN], stop_set[MAXN] = {0};
        for (int i = 1; i <= stop_cnt; ++i) {
            scanf("%d", &stops[i]);
            stop_set[stops[i]] = 1;
        }
        int virtual_node = n + t + 1;
        // 未停靠的站 → 虚拟站（权 0）
        for (int s = stops[1]; s <= stops[stop_cnt]; ++s) {
            if (!stop_set[s]) add_edge(s, virtual_node, 0);
        }
        // 虚拟站 → 停靠的站（权 1）
        for (int i = 1; i <= stop_cnt; ++i)
            add_edge(virtual_node, stops[i], 1);
    }
    queue<int> q;
    for (int i = 1; i <= total; ++i)
        if (indeg[i] == 0) q.push(i);
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            level[v] = max(level[v], level[u] + w[i]);
            --indeg[v];
            if (indeg[v] == 0) q.push(v);
        }
        if (u <= n) ans = max(ans, level[u]);
    }
    printf("%d\n", ans);
    return 0;
}
