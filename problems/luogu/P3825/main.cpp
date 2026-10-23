/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 13:25
 * update_at: 2026-10-23 13:42
 */
// 因规模必须改为迭代：Tarjan 的搜索路径深度可达 2n = 1e5，故用显式栈写法（参考 P3469）。
// 做法：2-SAT + 枚举每张 x 地图「禁用哪辆车」，2^d 次判定，d <= 8。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;          // n 的上界
const int MAXV = 2 * MAXN + 5;   // 2-SAT 节点数上界：每场游戏 2 个点
const int MAXM = 100005;         // m 的上界
const int MAXE = 2 * MAXM + 5;   // 每条规则最多产生 2 条蕴含边

int n, m;
char S[MAXN + 1];   // S[p]：第 p 场的地图类型（小写 a/b/c/x），1 下标
int forb[MAXN];     // forb[p]：第 p 场地图禁用的赛车编号（0=A,1=B,2=C）
int x_id[MAXN];     // x_id[p]：S[p]=='x' 时它是第几张 x 地图，否则 -1
int x_pos[10];      // x_pos[k]：第 k 张 x 地图对应的场次
int x_cnt;          // 扫描 S 得到的 x 地图张数
int enum_x[10];     // enum_x[k]：第 k 个需要枚举的 x 地图在 x_pos 中的下标
int enum_cnt;       // 需要枚举的 x 地图个数，共 2^enum_cnt 次判定
int d_declared;     // 题面第一行声明的 d，仅用于核对；实际张数以扫描 S 为准

// 规则：第 ri 场用赛车 rci，则第 rj 场必须用赛车 rcj
int ri[MAXM], rj[MAXM], rci[MAXM], rcj[MAXM];
int ri_fixed[MAXM];  // 静态规则（两端都不是 x 地图）在 ri 处的 2-SAT 文字，-1 表示该车不可用
int rj_fixed[MAXM];  // 静态规则在 rj 处的 2-SAT 文字，-1 表示该车不可用
int dyn_rule[MAXM];   // dyn_rule[]：涉及 x 地图的规则编号列表，每轮只需遍历这些
int dyn_cnt;          // dyn_rule 中的规则条数

// 链式前向星；节点 2k 表示「第 k+1 场的布尔变量为真」，2k+1 表示「为假」
struct Edge {
    int to;    // 边的终点
    int nxt;   // 同起点的下一条边
};
Edge edge[MAXE];  // 链式前向星的边池，edge[0] 作为空指针
int head[MAXV];   // head[u]：u 的第一条出边编号
int edge_cnt;         // 边池指针：最新加入的边编号
int static_edge_cnt;  // 只由静态规则建成的边数，每轮枚举结束后把 edge_cnt 退回这里

// 每轮枚举新增的动态边需要在下一轮撤销，只还原被改过 head 的节点
int saved_head[MAXV];   // saved_head[u]：本轮第一次给 u 加边之前的 head[u]
int touch_stamp[MAXV];  // touch_stamp[u]：u 最后一次被本轮修改时的轮次标记
int touched[MAXV];      // touched[]：本轮被修改过 head 的节点清单
int touched_cnt;
int run_stamp;          // 当前枚举轮次标记

// Tarjan 每个节点自己的状态：打包成一个 16 字节的 struct，遍历时一个节点只占半条缓存行。
struct Node {
    int low;   // low[u]：u 能回溯到的最小 dfn
    int dfn;   // dfn[u]：dfs 序，0 表示本轮还没访问
    int iter;  // iter[u]：u 的下一条待处理出边
    int scc;   // scc[u]：所属强连通分量编号，-1 表示尚未归属
};
Node node[MAXV];

// pair_tag[k]：第 k 个布尔变量已经弹出的那一半属于哪个强连通分量（全局唯一标签）。
// 弹出节点时顺手登记，就能 O(1) 判断「互补文字是否落在同一个分量」，不必再扫一遍栈。
long long pair_tag[MAXN];
long long cur_tag;
int dfs_clock, scc_cnt;
int tarjan_stk[MAXV], tarjan_top;   // 强连通分量栈（按 dfn 从小到大压栈）
int dfs_path[MAXV], path_top;       // 显式模拟的 DFS 路径栈

// live_node[]：真正可能进入 2-SAT 图的节点 = 所有规则端点的两个文字。
// 完全没被任何规则提到的位置，两个文字都是孤立点，不参与 DFS，也无需每轮重置。
int live_node[MAXV];
int live_cnt;

int answer_car[MAXN];   // answer_car[p]：第 p 场最终选用的赛车编号
bool satisfiable;       // 本轮判定结果

int read_car(char ch) {
    return ch - 'A';
}

void add_edge(int u, int v) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}

// 第 p 场若禁用赛车 f，则两辆可用的车依次是 first/second。
int first_car(int f) {
    return f == 0 ? 1 : 0;
}

int second_car(int f) {
    return f == 2 ? 1 : 2;
}

// 第 p 场选赛车 car 对应的 2-SAT 文字：真文字 2(p-1)，假文字 2(p-1)+1。
// 约定布尔变量为真 == 选「第二辆可用车」，为假 == 选「第一辆可用车」。
int literal_with_forbid(int p, int f, int car) {
    return 2 * (p - 1) + (car == second_car(f) ? 0 : 1);
}

void read_data() {
    cin >> n >> d_declared;
    cin >> (S + 1);
    cin >> m;

    x_cnt = 0;
    for (int p = 1; p <= n; p++) {
        x_id[p] = -1;
        forb[p] = -1;
        if (S[p] == 'x') {
            x_id[p] = x_cnt;
            x_pos[x_cnt] = p;
            x_cnt++;
        } else {
            forb[p] = S[p] - 'a';
        }
    }

    for (int e = 1; e <= m; e++) {
        char hi, hj;
        cin >> ri[e] >> hi >> rj[e] >> hj;
        rci[e] = read_car(hi);
        rcj[e] = read_car(hj);
    }
}

// 先把不涉及 x 地图的规则建成固定的边。它们每轮枚举都不变，只需建一次。
void build_static_graph() {
    // 没出现在任何规则里的 x 地图，选哪辆车都不影响可行性，固定成「禁用 A」即可，
    // 不必为它多枚举一倍。只有出现在规则里的 x 地图才需要枚举。
    bool in_rule[10] = {false};
    for (int e = 1; e <= m; e++) {
        if (x_id[ri[e]] >= 0) {
            in_rule[x_id[ri[e]]] = true;
        }
        if (x_id[rj[e]] >= 0) {
            in_rule[x_id[rj[e]]] = true;
        }
    }
    enum_cnt = 0;
    for (int k = 0; k < x_cnt; k++) {
        if (in_rule[k]) {
            enum_x[enum_cnt++] = k;
        } else {
            forb[x_pos[k]] = 0;  // 自由变量：随便禁用一辆，剩两辆足以满足任何规则
        }
    }

    edge_cnt = 0;
    for (int e = 1; e <= m; e++) {
        bool xi = x_id[ri[e]] >= 0;
        bool xj = x_id[rj[e]] >= 0;

        // 非 x 端点上的文字每轮都一样，先算好；x 端点留到枚举时按当前禁用车辆再算。
        ri_fixed[e] = xi ? 0
                         : (rci[e] == forb[ri[e]] ? -1
                                                 : literal_with_forbid(ri[e], forb[ri[e]], rci[e]));
        rj_fixed[e] = xj ? 0
                         : (rcj[e] == forb[rj[e]] ? -1
                                                 : literal_with_forbid(rj[e], forb[rj[e]], rcj[e]));

        if (xi || xj) {
            dyn_rule[dyn_cnt++] = e;
            continue;
        }

        int li = ri_fixed[e];
        int lj = rj_fixed[e];
        if (li < 0) {
            continue;  // 前提在这张地图上本来就不可能，规则恒成立
        }
        if (lj < 0) {
            add_edge(li, li ^ 1);  // 结论不可能成立，只能强制前提为假
        } else {
            add_edge(li, lj);
            add_edge(lj ^ 1, li ^ 1);
        }
    }
    static_edge_cnt = edge_cnt;  // 静态图到此为止，之后的边都是每轮临时追加的

    // 动态边的端点只可能是规则两端的位置；静态边的端点也都在规则两端之内。
    // 因此「规则两端位置的两个文字」就是全部可能参与图的节点。
    bool seen_node[MAXV] = {false};
    live_cnt = 0;
    for (int e = 1; e <= m; e++) {
        for (int side = 0; side < 2; side++) {
            int p = (side == 0) ? ri[e] : rj[e];
            for (int half = 0; half < 2; half++) {
                int u = 2 * (p - 1) + half;
                if (!seen_node[u]) {
                    seen_node[u] = true;
                    live_node[live_cnt++] = u;
                }
            }
        }
    }
}

// 给节点 u 临时加一条边；第一次改 u 时先记下原来的 head，便于本轮结束后撤销。
void add_dynamic_edge(int u, int v) {
    if (touch_stamp[u] != run_stamp) {
        touch_stamp[u] = run_stamp;
        saved_head[u] = head[u];
        touched[touched_cnt++] = u;
    }
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}

// 显式栈版 Tarjan（迭代写法的原因见文件头）。返回值：是否存在变量与其取反在同一强连通分量。
// 一旦某个强连通分量里同时出现 $2k$ 与 $2k+1$，立即返回 false，避免整张图跑完。
bool tarjan() {
    dfs_clock = 0;
    scc_cnt = 0;
    tarjan_top = 0;
    path_top = 0;

    // 每轮把「可能参与图的节点」的 dfn 清 0。出度为 0 的节点仍可能被别的点指向，
    // 所以 live_node 必须包含所有规则端点；只有完全没被规则提到的位置可以排除在外。
    for (int idx = 0; idx < live_cnt; idx++) {
        int u = live_node[idx];
        node[u].dfn = 0;
        node[u].scc = -1;
    }

    for (int idx = 0; idx < live_cnt; idx++) {
        int start = live_node[idx];
        // 出度为 0 的节点自成一个单点强连通分量，不可能与互补文字同分量，
        // 无需作为 DFS 起点（它若被别的点指向，会在那个 DFS 里被正常访问到）。
        if (head[start] == 0 || node[start].dfn != 0) {
            continue;
        }
        node[start].dfn = node[start].low = ++dfs_clock;
        node[start].iter = head[start];
        tarjan_stk[tarjan_top++] = start;
        dfs_path[path_top++] = start;

        while (path_top > 0) {
            int u = dfs_path[path_top - 1];
            int e = node[u].iter;

            if (e != 0) {
                node[u].iter = edge[e].nxt;
                int v = edge[e].to;
                if (node[v].dfn == 0) {
                    node[v].dfn = node[v].low = ++dfs_clock;
                    node[v].scc = -1;  // 新入栈的节点必须清掉上一轮遗留的分量编号
                    node[v].iter = head[v];
                    tarjan_stk[tarjan_top++] = v;
                    dfs_path[path_top++] = v;
                } else if (node[v].scc < 0 && node[v].dfn < node[u].low) {
                    node[u].low = node[v].dfn;  // 回边：v 还在栈上
                }
                continue;
            }

            // u 的出边处理完，结算 u
            path_top--;
            if (node[u].low == node[u].dfn) {
                cur_tag++;
                bool conflict = false;
                int w;
                do {
                    w = tarjan_stk[--tarjan_top];
                    int k = w >> 1;
                    if (pair_tag[k] == cur_tag) {
                        conflict = true;  // 互补的两半落在同一个强连通分量
                    }
                    pair_tag[k] = cur_tag;
                    node[w].scc = scc_cnt;
                } while (w != u);
                scc_cnt++;
                if (conflict) {
                    return false;
                }
            }
            if (path_top > 0) {
                int parent = dfs_path[path_top - 1];
                if (node[u].low < node[parent].low) {
                    node[parent].low = node[u].low;
                }
            }
        }
    }
    return true;
}

// 在 mask 指定的「每张 x 地图禁用哪辆车」方案下判定；有解时把安排写入 answer_car[]。
bool check_mask(int mask) {
    run_stamp++;
    touched_cnt = 0;

    // 每张 x 地图：mask 的第 k 位为 0 表示禁用 A，为 1 表示禁用 B。
    // 「禁用 A / 禁用 B」两种情形合起来已覆盖 A、B、C 三种真实取值。
    for (int k = 0; k < enum_cnt; k++) {
        forb[x_pos[enum_x[k]]] = ((mask >> k) & 1) ? 1 : 0;
    }

    for (int idx = 0; idx < dyn_cnt; idx++) {
        int e = dyn_rule[idx];
        int i = ri[e];
        int j = rj[e];
        int li, lj;
        if (x_id[i] >= 0) {
            li = (rci[e] == forb[i]) ? -1 : literal_with_forbid(i, forb[i], rci[e]);
        } else {
            li = ri_fixed[e];
        }
        if (x_id[j] >= 0) {
            lj = (rcj[e] == forb[j]) ? -1 : literal_with_forbid(j, forb[j], rcj[e]);
        } else {
            lj = rj_fixed[e];
        }

        if (li < 0) {
            continue;
        }
        if (lj < 0) {
            add_dynamic_edge(li, li ^ 1);
        } else {
            add_dynamic_edge(li, lj);
            add_dynamic_edge(lj ^ 1, li ^ 1);
        }
    }

    satisfiable = tarjan();

    // 撤销本轮加的动态边，恢复静态图：head 只需还原被改过的节点，边池指针退回静态边数
    for (int idx = 0; idx < touched_cnt; idx++) {
        int u = touched[idx];
        head[u] = saved_head[u];
    }
    edge_cnt = static_edge_cnt;

    if (!satisfiable) {
        return false;
    }

    for (int p = 1; p <= n; p++) {
        bool takes_second = node[2 * (p - 1)].scc < node[2 * (p - 1) + 1].scc;
        answer_car[p] = takes_second ? second_car(forb[p]) : first_car(forb[p]);
    }
    return true;
}

void solve() {
    int mask_cnt = 1 << enum_cnt;
    for (int mask = 0; mask < mask_cnt; mask++) {
        if (check_mask(mask)) {
            for (int p = 1; p <= n; p++) {
                cout << char('A' + answer_car[p]);
            }
            cout << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_data();
    build_static_graph();
    solve();

    return 0;
}
