/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:10
 * update_at: 2026-10-05 04:10
 */

// 最小生成树计数（JSOI 2008）：同权边不超过 10 条，按权值段枚举选边方案。
// 性质 1：所有 MST 中权值为 w 的边数 c_w 固定，等于 Kruskal 求出的数量。
// 性质 2：处理完所有权值 < w 的边后，连通块划分唯一，与具体选法无关。
// 所以各权值段选边方案相互独立，答案 = 各段合法选法数的乘积，对 31011 取模。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;   // 顶点数上限
const int MAXM = 1005;  // 边数上限
const ll MOD = 31011;   // 题目要求的模数

int n, m;

// 边结构：按权值排序后按段处理
struct Edge {
    int u;
    int v;
    ll w;
};
Edge edges[MAXM];

ll fa[MAXN];  // 并查集父节点（第一阶段探测、第二阶段合并时各初始化一次）

ll find_fa(ll x) {
    while (fa[x] != x) x = fa[x];
    return x;
}

// 每个权值段的记录：need[i] = 第 i 段在 MST 中必须选的边数（0 的段不计入）
int seg_start[MAXM];  // 段在排序后边数组中的起始下标
int seg_len[MAXM];    // 段内边数
int seg_need[MAXM];   // 该段必须选的边数
int seg_total = 0;    // need > 0 的段数

// 第二阶段：当前段映射到连通块代表元后的可选边
int cur_u[MAXM];
int cur_v[MAXM];
int cur_cnt;

// 枚举状态
int need;         // 当前段需要选的边数
int way_cnt;      // 当前段的合法方案数
ll tmp_fa[MAXN];  // 验证单个组合时的临时并查集
int sel_u[12];    // 当前已选边的端点（need <= 10）
int sel_v[12];

ll tmp_find(ll x) {
    while (tmp_fa[x] != x) x = tmp_fa[x];
    return x;
}

// 递归枚举：第 dep 层对第 dep 条可选拍边做"选 / 不选"的决定，
// 凑满 need 条后用临时并查集检查是否无环，无环则方案数 +1。
void dfs_choose(int dep, int chosen) {
    // 剪枝：剩下的边不够凑满 need 条
    if (chosen + (cur_cnt - dep) < need) return;
    if (chosen == need) {
        // 完整方案已生成：复制工作并查集后验证无环
        for (int i = 1; i <= n; i++) tmp_fa[i] = fa[i];
        for (int i = 0; i < need; i++) {
            ll ru = tmp_find(sel_u[i]);
            ll rv = tmp_find(sel_v[i]);
            if (ru == rv) return;  // 有环，非法
            tmp_fa[ru] = rv;
        }
        way_cnt++;
        return;
    }
    if (dep >= cur_cnt) return;

    // 不选第 dep 条边
    dfs_choose(dep + 1, chosen);

    // 选第 dep 条边（存端点便于叶子统一验证）
    sel_u[chosen] = cur_u[dep];
    sel_v[chosen] = cur_v[dep];
    dfs_choose(dep + 1, chosen + 1);
}

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    sort(edges, edges + m, cmp_edge);

    // ===== 第一阶段：Kruskal 探测每个权值段必须选的边数 =====
    for (int i = 1; i <= n; i++) fa[i] = i;
    int total_used = 0;  // 加入生成树的总边数
    int idx = 0;
    while (idx < m) {
        int start = idx;
        int cnt_need = 0;
        while (idx < m && edges[idx].w == edges[start].w) {
            ll ru = find_fa(edges[idx].u);
            ll rv = find_fa(edges[idx].v);
            if (ru != rv) {  // 不连通则这条边属于这棵 MST
                fa[ru] = rv;
                cnt_need++;
                total_used++;
            }
            idx++;
        }
        if (cnt_need > 0) {  // 记录 need > 0 的段
            seg_start[seg_total] = start;
            seg_len[seg_total] = idx - start;
            seg_need[seg_total] = cnt_need;
            seg_total++;
        }
    }

    // 图不连通，不存在生成树
    if (total_used < n - 1) {
        printf("0\n");
        return 0;
    }

    // ===== 第二阶段：按段独立枚举选法数并累乘（fa 重新初始化为工作并查集）=====
    for (int i = 1; i <= n; i++) fa[i] = i;
    ll ans = 1;
    for (int s = 0; s < seg_total; s++) {
        // 过滤：端点已在同一连通块的边映射后相同，必不可选
        cur_cnt = 0;
        for (int i = 0; i < seg_len[s]; i++) {
            Edge &e = edges[seg_start[s] + i];
            ll ru = find_fa(e.u);
            ll rv = find_fa(e.v);
            if (ru != rv) {
                cur_u[cur_cnt] = ru;
                cur_v[cur_cnt] = rv;
                cur_cnt++;
            }
        }
        need = seg_need[s];
        way_cnt = 0;
        dfs_choose(0, 0);
        ans = (ans * way_cnt) % MOD;

        // 真实合并这一段：任意一种合法选法产生的连通性一致（性质 2）
        for (int i = 0; i < seg_len[s]; i++) {
            Edge &e = edges[seg_start[s] + i];
            ll ru = find_fa(e.u);
            ll rv = find_fa(e.v);
            if (ru != rv) fa[ru] = rv;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
