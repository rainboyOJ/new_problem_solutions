/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:15
 * update_at: 2026-10-05 11:15
 */
// main.cpp：Kruskal 求最小生成树，输出选中的 n-1 条边（端点小端在前）。
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXN = 105;
const int MAXM = 10005;

// father[i] 表示城市 i 所在并查集的根；0 号位空置。
int father[MAXN];

struct Edge {
    int u, v;   // 两个端点（读入时归一化 u <= v）
    int w;      // 造价
};

Edge edges[MAXM]; // 1..e 存边
int n, e;

// 并查集 find：沿父指针找根，路径压缩让后续查询近似 O(1)。
int find_set(int x) {
    if (father[x] == x) return x;
    father[x] = find_set(father[x]);
    return father[x];
}

void read_input() {
    scanf("%d %d", &n, &e);
    for (int i = 1; i <= e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u > v) {
            int t = u; u = v; v = t;
        }
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }
}

// 按造价从小到大排序（升序）；造价相同则按 u 升序，再按 v 升序，保证输出去重。
bool cmp_edge(const Edge &a, const Edge &b) {
    if (a.w != b.w) return a.w < b.w;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

// 已选边集合，最后按 (u, v) 字典序输出
Edge mst[MAXN];
int mst_cnt;

// 按 (u, v) 字典序比较，用于最后输出排序
bool cmp_uv(const Edge &a, const Edge &b) {
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

void solve() {
    sort(edges + 1, edges + e + 1, cmp_edge);

    // 初始化并查集：每个城市各自为根
    for (int i = 1; i <= n; i++) father[i] = i;

    mst_cnt = 0;
    // 按造价从小到大扫描每条边：两端不在同一集合则选它并合并
    for (int i = 1; i <= e && mst_cnt < n - 1; i++) {
        int u = edges[i].u, v = edges[i].v;
        int ru = find_set(u), rv = find_set(v);
        if (ru != rv) {
            father[ru] = rv;
            mst[++mst_cnt] = edges[i];
        }
    }

    // 输出按 (u, v) 字典序排序，与官方输出一致
    sort(mst + 1, mst + mst_cnt + 1, cmp_uv);
    for (int i = 1; i <= mst_cnt; i++) {
        printf("%d %d\n", mst[i].u, mst[i].v);
    }
}

int main() {
    read_input();
    solve();
    return 0;
}
