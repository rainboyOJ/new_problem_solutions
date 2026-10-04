/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:01
 * update_at: 2026-10-05 07:01
 */
#include <cstdio>

typedef long long ll;

const int MAXV = 1005; // 节点编号上限 1000，多开几个位置

int parent[MAXV];  // 并查集：parent[x] 为 x 所在弱连通分量的代表元
ll in_deg[MAXV];   // in_deg[u] 表示节点 u 的入度
ll out_deg[MAXV];  // out_deg[u] 表示节点 u 的出度
ll pos_sum[MAXV];  // pos_sum[root] 表示该连通块内所有 out>in 节点的 (out-in) 之和
int used[MAXV];    // used[u]=1 表示节点 u 在输入中出现过

// 并查集查找，带路径压缩
int find_root(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

// 合并两个节点所在的弱连通分量
void union_sets(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx != ry) {
        parent[rx] = ry;
    }
}

int main() {
    int m;
    if (scanf("%d", &m) != 1) {
        return 0;
    }

    for (int i = 1; i < MAXV; i++) {
        parent[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        out_deg[l]++;
        in_deg[r]++;
        used[l] = 1;
        used[r] = 1;
        union_sets(l, r);
    }

    // 把每个节点出度比入度多出的部分累加到所在连通块的代表元上
    for (int u = 1; u < MAXV; u++) {
        if (used[u] == 1 && out_deg[u] > in_deg[u]) {
            pos_sum[find_root(u)] += out_deg[u] - in_deg[u];
        }
    }

    // 每个连通块至少需要 1 条路径覆盖，若正度数差更大则按正度数差算
    ll path_count = 0;
    for (int u = 1; u < MAXV; u++) {
        if (used[u] == 1 && parent[u] == u) {
            ll delta = pos_sum[u];
            if (delta < 1) {
                delta = 1;
            }
            path_count += delta;
        }
    }

    // 每条路径有 e 条边就需要 e+1 个元素，所有路径合计为 m + 路径数
    printf("%lld\n", (ll)m + path_count);
    return 0;
}
