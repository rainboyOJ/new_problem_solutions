/**
 * P1347 排序
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int n, m;
int graph[26][26];   // 邻接矩阵
int indeg[26];       // 入度

// 返回状态：0=不确定 1=确定 2=矛盾
int topo(char order[]) {
    int deg[26], idx = 0;
    memcpy(deg, indeg, sizeof(deg));
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (deg[i] == 0) q.push(i);
    bool unique = true;
    while (!q.empty()) {
        if (q.size() > 1) unique = false;
        int u = q.front(); q.pop();
        order[idx++] = u + 'A';
        for (int v = 0; v < n; ++v)
            if (graph[u][v] && --deg[v] == 0) q.push(v);
    }
    order[idx] = '\0';
    if (idx < n) return 2; // 有环 → 矛盾
    return unique ? 1 : 0; // 唯一确定 or 尚不确定
}

int main() {
    scanf("%d%d", &n, &m);
    char rel[5];
    for (int i = 1; i <= m; ++i) {
        scanf("%s", rel);
        int a = rel[0] - 'A', b = rel[2] - 'A';
        if (!graph[a][b]) {
            graph[a][b] = 1;
            ++indeg[b];
        }
        char ord[26];
        int st = topo(ord);
        if (st == 2) {
            printf("Inconsistency found after %d relations.\n", i);
            return 0;
        }
        if (st == 1 && i < m) {
            // 确定后还需要验证后续关系不矛盾
            // 但不能提前退出，因为后续可能矛盾
            // 但是题目说：确定后可直接结束
            printf("Sorted sequence determined after %d relations: %s.\n", i, ord);
            return 0;
        }
    }
    puts("Sorted sequence cannot be determined.");
    return 0;
}
