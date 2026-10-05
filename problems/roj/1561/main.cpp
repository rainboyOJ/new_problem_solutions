/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:25
 * update_at: 2026-10-05 08:25
 */
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

// 题目数据规模：N, M <= 1e5
const int MAXN = 100005;

int n, m;

vector<int> g[MAXN]; // 邻接表，g[u] 存与 u 相邻的点（树题用 vector 写法更直观）

ll weight[MAXN]; // weight[u]：节点 u 的初始权值

int tin[MAXN];   // tin[u]：DFS 进入 u 的时刻（欧拉序编号，1 起）
int tout[MAXN];  // tout[u]：u 子树内最后一个点的进入时刻，子树对应 [tin[u], tout[u]]
int depth[MAXN]; // depth[u]：根为 0 的深度，最大不超过 n，用 int 即可
int par[MAXN];   // par[u]：u 的父亲，根的父亲记 0

ll bit1[MAXN]; // 树状数组 1：维护 A[y] 中 depth[y] 的一次项系数
ll bit2[MAXN]; // 树状数组 2：维护 A[y] 中的常数项

int stk[MAXN * 2]; // 迭代 DFS 的显式栈：正数为进入事件，负数为对应节点的退出事件

// 迭代 DFS 求欧拉序与深度：用显式栈代替递归，避免链状树上的爆栈。
// 栈中正数表示进入节点，负数表示该节点子树已全部进入（退出事件）。
void build_tour() {
    int top = 0;
    int timer = 0;
    stk[++top] = 1;
    par[1] = 0;
    depth[1] = 0;
    while (top > 0) {
        int u = stk[top--];
        if (u < 0) {
            tout[-u] = timer; // 退出时，子树内所有点都已编号
            continue;
        }
        tin[u] = ++timer;
        stk[++top] = -u; // 先压退出事件，保证它排在所有孩子之后
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == par[u]) continue;
            par[v] = u;
            depth[v] = depth[u] + 1;
            stk[++top] = v;
        }
    }
}

// 树状数组单点加：下标 i 处加 v。
void bit_add(ll bit[], int i, ll v) {
    for (; i <= n + 1; i += i & -i) {
        bit[i] += v;
    }
}

// 树状数组前缀和 Σ(1..i)：在差分写法下就是单点查询。
ll bit_sum(ll bit[], int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) {
        s += bit[i];
    }
    return s;
}

// 区间 [l, r] 统一加 v：差分树状数组，左端 +v、右端后一位 -v。
void range_add(ll bit[], int l, int r, ll v) {
    bit_add(bit, l, v);
    bit_add(bit, r + 1, -v);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int u = 1; u <= n; u++) {
        scanf("%lld", &weight[u]);
    }
    for (int i = 1; i < n; i++) {
        int fr, to;
        scanf("%d %d", &fr, &to);
        g[fr].push_back(to);
        g[to].push_back(fr);
    }
    build_tour();

    // 设 A[y] = 根到 y 的路径点权和。所有修改对 A[y] 的贡献要么是常数，
    // 要么是 depth[y] 的一次函数，因此写成 A[y] = depth[y] * bit1 点查 + bit2 点查。
    // 初始权值：u 的权值让子树内每个 y 的 A[y] 都 +weight[u]，属于常数项。
    for (int u = 1; u <= n; u++) {
        range_add(bit2, tin[u], tout[u], weight[u]);
    }

    for (int i = 1; i <= m; i++) {
        int op, x;
        scanf("%d %d", &op, &x);
        int l = tin[x], r = tout[x];
        if (op == 1) {
            // 单点加 a：只影响子树内每个 y，统一 +a
            ll a;
            scanf("%lld", &a);
            range_add(bit2, l, r, a);
        } else if (op == 2) {
            // 子树加 a：y 在子树内时 A[y] 增加 a*(depth[y]-depth[x]+1)，
            // 拆成 depth[y] 的系数 a 与常数项 a*(1-depth[x]) 两段区间加。
            ll a;
            scanf("%lld", &a);
            range_add(bit1, l, r, a);
            range_add(bit2, l, r, a * (1 - depth[x]));
        } else {
            // 询问根到 x 的路径点权和
            ll ans = depth[x] * bit_sum(bit1, tin[x]) + bit_sum(bit2, tin[x]);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
