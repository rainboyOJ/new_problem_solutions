/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:52
 * update_at: 2026-10-05 07:52
 */
#include <cstdio>
#include <set>
#include <utility>
using namespace std;

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 12:41
 * update_at: 2026-10-04 12:41
 */

// 异象石：动态度维护点集在树上的斯坦纳树边权和。
// 核心：把点集按 DFS 序(tin)排成环，环上相邻距离之和 = 2 * 斯坦纳树长度。
// 插入/删除一个点只改环上 O(1) 条相邻边，用有序表 + 倍增 LCA 增量维护。

typedef long long ll;

const int MAXN = 100005;   // n, m <= 1e5
const int LOG = 17;        // 2^17 > 1e5，倍增层数

// 链式前向星存树
int head[MAXN];   // head[u]：u 的第一条边编号
int nxt[2 * MAXN]; // nxt[e]：与边 e 同起点的下一条边
int to_[2 * MAXN]; // to_[e]：边 e 的终点
ll wt[2 * MAXN];   // wt[e]：边 e 的长度（z 可达 1e9，用 ll）
int edge_cnt;

int n, m;
int tin[MAXN];    // tin[u]：DFS 进入时刻，即 DFS 序排名
int dep[MAXN];    // dep[u]：深度
int up[MAXN];     // up[u]：父亲节点（0 为根的哨兵父亲）
ll dis[MAXN];     // dis[u]：根到 u 的距离（边长和可达 1e14，用 ll）
int node_of_tin[MAXN]; // node_of_tin[t]：DFS 序第 t 个位置的节点编号
int jump[LOG][MAXN];   // jump[k][v]：v 的第 2^k 级祖先

// 有序表：当前异象石按 tin 升序
set<int> order;   // 存每个异象石的 tin
// total：环上相邻距离之和 = 2 * 当前答案（环游每条斯坦纳树边恰走两次）
ll total;

// 加一条双向边
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to_[edge_cnt] = v;
    wt[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 迭代 DFS 求 tin / dep / up / dis。
// 树可能退化成链，深度 1e5，递归会爆栈，必须用显式栈。
// 栈元素 (u, e)：u 尚未扫完的邻边从 e 开始；e == 0 表示 u 的边已扫完。
void dfs_tin() {
    pair<int, int> stk[MAXN];
    int top = 0;
    int timer = 0;

    up[1] = 0;
    dep[1] = 0;
    dis[1] = 0;
    stk[top++] = make_pair(1, head[1]);
    while (top > 0) {
        int u = stk[top - 1].first;
        int e = stk[top - 1].second;
        if (e == 0) { // u 的邻边扫完，弹出
            top--;
            continue;
        }
        if (e == head[u]) { // 第一次处理 u：登记进入时刻
            timer++;
            tin[u] = timer;
            node_of_tin[timer] = u;
        }
        stk[top - 1].second = nxt[e]; // 接着扫 u 的下一条邻边
        int v = to_[e];
        if (v != up[u]) { // 不沿来路边走回父亲
            up[v] = u;
            dep[v] = dep[u] + 1;
            dis[v] = dis[u] + wt[e]; // 父亲的距离此刻已经算好
            stk[top++] = make_pair(v, head[v]);
        }
    }
}

// 倍增表预处理
void build_jump() {
    for (int v = 1; v <= n; v++) jump[0][v] = up[v];
    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++)
            jump[k][v] = jump[k - 1][jump[k - 1][v]];
}

// 倍增求最近公共祖先
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int t = u; u = v; v = t;
    }
    int diff = dep[u] - dep[v];
    for (int k = 0; k < LOG; k++)
        if (diff >> k & 1) u = jump[k][u];
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--)
        if (jump[k][u] != jump[k][v]) {
            u = jump[k][u];
            v = jump[k][v];
        }
    return up[u];
}

// 树上两点距离 = 根距离之和 - 2 * 根到 LCA 的距离
ll dist(int u, int v) {
    int w = lca(u, v);
    return dis[u] + dis[v] - 2 * dis[w];
}

// 插入或删除点 x：环上 (前驱, 后继) 与 (前驱, x) + (x, 后继) 的差值大小相同。
// 插入加、删除减，共用同一段表达式。
void update_delta(int x, bool is_add) {
    set<int>::iterator it = order.find(tin[x]);
    // 环上找前驱、后继：首尾相接，只有一个元素时前驱后继都是自己
    int p, s;
    if (it == order.begin()) p = node_of_tin[*order.rbegin()];
    else p = node_of_tin[*(--it)]; // --it 之后 it 不再指向 tin[x]，下面重新 find
    it = order.find(tin[x]);
    it++;
    if (it == order.end()) s = node_of_tin[*order.begin()];
    else s = node_of_tin[*it];

    ll delta = dist(p, x) + dist(x, s) - dist(p, s);
    if (is_add) total += delta;
    else total -= delta;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) head[i] = 0;
    edge_cnt = 0;
    for (int i = 1; i < n; i++) {
        int x, y;
        ll z;
        scanf("%d %d %lld", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }

    dfs_tin();
    build_jump();

    scanf("%d", &m);
    total = 0;
    for (int i = 1; i <= m; i++) {
        char op[5];
        scanf("%s", op);
        if (op[0] == '?') {
            // 环长是答案的两倍，且必为偶数，整除无舍入；空集时 total = 0
            printf("%lld\n", total / 2);
        } else {
            int x;
            scanf("%d", &x);
            if (op[0] == '+') {
                order.insert(tin[x]);
                update_delta(x, true);
            } else { // '-'
                update_delta(x, false);
                order.erase(tin[x]);
            }
        }
    }
    return 0;
}
