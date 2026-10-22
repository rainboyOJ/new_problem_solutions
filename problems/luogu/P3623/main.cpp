/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 00:00
 * update_at: 2026-10-21 00:00
 */
// P3623 [APIO2008] 免费道路：两遍 Kruskal 构造一棵恰好含 k 条鹅卵石路的生成树。
#include <bits/stdc++.h>
using namespace std;

// 一条无向道路：连接村庄 u、v；c = 0 是鹅卵石路（免费），c = 1 是水泥路。
struct Edge {
    int u;
    int v;
    int c;
};

const int MAXN = 2e4 + 5;  // 村庄数上限
const int MAXM = 1e5 + 5;  // 道路数上限

int n, m, k;
Edge edges[MAXM];  // edges[i]：第 i 条道路，编号与输入一致（1..m）

// 并查集：路径压缩 + 按大小合并，风格对齐 rbook 的 Kruskal 模板。
int dsu_parent[MAXN];  // dsu_parent[x]：x 的父节点，x 是根时等于 x
int dsu_size[MAXN];    // dsu_size[x]：x 当根时所在集合的大小

// 找 x 所在集合的根，顺路把路径上的点直接挂到根上（路径压缩）。
int dsu_find(int x) {
    if (dsu_parent[x] == x) return x;
    dsu_parent[x] = dsu_find(dsu_parent[x]);
    return dsu_parent[x];
}

// 合并 a、b 所在的两个集合；两端本来就连通（这条边成环）时返回 false。
bool dsu_merge(int a, int b) {
    int root_a = dsu_find(a);
    int root_b = dsu_find(b);
    if (root_a == root_b) return false;
    // 小集合接到大集合下面，配合路径压缩，单次操作接近常数。
    if (dsu_size[root_a] < dsu_size[root_b]) swap(root_a, root_b);
    dsu_parent[root_b] = root_a;
    dsu_size[root_a] += dsu_size[root_b];
    return true;
}

void dsu_reset() {
    for (int i = 1; i <= n; i++) {
        dsu_parent[i] = i;
        dsu_size[i] = 1;
    }
}

bool forced[MAXM];  // forced[i]：第一遍里"不得不选"的鹅卵石路（桥接水泥连通块）
int plan[MAXM];     // 最终方案的边编号
int plan_cnt;       // 方案里的边数，一棵生成树正好 n - 1 条

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) cin >> edges[i].u >> edges[i].v >> edges[i].c;

    // ---------- 第一遍 Kruskal：先加全部水泥路，再补鹅卵石路 ----------
    // 目的：求出"任何生成树都至少需要"的鹅卵石路条数 need。
    // 只用水泥路先连通能连通的局部，剩下的连通块之间没有水泥路可走，
    // 只能靠鹅卵石路桥接，所以这一遍补进来的鹅卵石路条数就是下界 need。
    dsu_reset();
    int cement_cnt = 0;  // 第一遍选中的水泥路条数
    for (int i = 1; i <= m; i++)
        if (edges[i].c == 1 && dsu_merge(edges[i].u, edges[i].v)) cement_cnt++;
    int need = 0;  // 任何生成树至少要用的鹅卵石路条数
    for (int i = 1; i <= m; i++)
        if (edges[i].c == 0 && dsu_merge(edges[i].u, edges[i].v)) {
            forced[i] = true;  // 桥接水泥连通块，"不得不选"
            need++;
        }

    // 图本身不连通（拼不成 n-1 条），或者最少的鹅卵石路都超过 k，都无解。
    if (cement_cnt + need != n - 1 || need > k) {
        cout << "no solution" << "\n";
        return 0;
    }

    // ---------- 第二遍 Kruskal：精确凑够 k 条鹅卵石路 ----------
    // 先放回第一遍"不得不选"的鹅卵石路（need 条）；
    // 再从其余鹅卵石路里挑还能扩大森林的边，直到凑满 k 条；
    // 最后用水泥路补满生成树。
    dsu_reset();
    plan_cnt = 0;
    int cobble_cnt = 0;  // 方案里已有的鹅卵石路条数
    for (int i = 1; i <= m; i++)
        if (forced[i]) {
            dsu_merge(edges[i].u, edges[i].v);  // forced 是森林，必定合并成功
            plan[++plan_cnt] = i;
            cobble_cnt++;
        }
    for (int i = 1; i <= m && cobble_cnt < k; i++)
        if (edges[i].c == 0 && !forced[i] && dsu_merge(edges[i].u, edges[i].v)) {
            plan[++plan_cnt] = i;
            cobble_cnt++;
        }
    if (cobble_cnt < k) {  // 凑不满 k 条：k 超过鹅卵石路在生成树里的上限
        cout << "no solution" << "\n";
        return 0;
    }
    // 水泥路补满：forced 集合 + 全部水泥路已经包含第一遍的那棵生成树，
    // 所以这一步结束后一定连通，恰好再补进 n-1-k 条水泥路。
    for (int i = 1; i <= m; i++)
        if (edges[i].c == 1 && dsu_merge(edges[i].u, edges[i].v)) plan[++plan_cnt] = i;

    sort(plan + 1, plan + plan_cnt + 1);  // 按输入顺序输出，便于对照
    for (int j = 1; j <= plan_cnt; j++) {
        Edge &e = edges[plan[j]];
        cout << e.u << " " << e.v << " " << e.c << "\n";
    }
    return 0;
}
