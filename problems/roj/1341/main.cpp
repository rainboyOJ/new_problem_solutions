/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:46
 * update_at: 2026-10-05 11:05
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 1005;   // 点数上限
const int MAXM = 2005;   // 边数上限

// 无向图：每条边存两个方向的半边，用边编号标记是否走过（正确处理平行边）
struct Edge {
    ll to;   // 这条半边指向的点
    ll id;   // 所属无向边的编号
};

Edge edge[MAXM * 2];     // 邻接表：每条无向边存两条半边
ll head[MAXN];           // head[u]：u 的邻接表链头（-1 表示空）
ll nxt[MAXM * 2];        // 链表 next 指针
ll cnt_edge = 0;         // 半边计数器

bool used[MAXM];         // used[e]：第 e 条无向边是否已经走过
ll sta[MAXM + 10];       // 手写栈：沿途的点
ll top = 0;              // 栈顶指针
ll ans[MAXM + 10];       // 出栈序列（逆序输出后就是欧拉路）
ll len_ans = 0;          // 出栈序列长度
ll deg[MAXN];            // 每个点的度数，用来找奇点

// 加一条无向边，两个方向各存一条半边
void add_edge(ll u, ll v, ll id) {
    edge[cnt_edge].to = v; edge[cnt_edge].id = id;
    nxt[cnt_edge] = head[u];
    head[u] = cnt_edge; cnt_edge++;

    edge[cnt_edge].to = u; edge[cnt_edge].id = id;
    nxt[cnt_edge] = head[v];
    head[v] = cnt_edge; cnt_edge++;
}

// 检查第 e 条半边是否可走：它所属的无向边（含反向半边）还没走过
bool check_ok(ll e) {
    if (used[edge[e].id]) return false;
    if (used[edge[e ^ 1].id]) return false;
    return true;
}

// Hierholzer 迭代版：能走就走并压栈，走不动才把点记进出栈序列
void solve() {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    for (ll i = 0; i < m; ++i) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        add_edge(a, b, i);
        deg[a]++; deg[b]++;
    }

    // 选起点：有奇点就从编号最大的奇点出发，否则取第一个有边的点
    ll start = 0;
    for (ll i = 1; i <= n; ++i)
        if (deg[i] % 2 == 1) start = i;
    if (start == 0)
        for (ll i = 1; i <= n; ++i)
            if (deg[i] > 0) { start = i; break; }
    if (start == 0) start = 1;   // 一条边都没有时兜底输出 1

    sta[top++] = start;
    while (top > 0) {
        ll u = sta[top - 1];     // 只看栈顶，不弹出
        ll e = head[u];
        while (e != -1 && !check_ok(e)) e = nxt[e];   // 找第一条可走的边
        if (e != -1) {
            used[edge[e].id] = true;   // 走掉这条边
            sta[top++] = edge[e].to;
        } else {
            top--;                     // 无路可走，这个点正式落进出栈序列
            ans[len_ans++] = u;
        }
    }

    // 出栈序列逆序输出才是欧拉路（起点在前，终点在后）
    for (ll i = len_ans - 1; i >= 0; --i)
        printf("%lld%c", ans[i], i == 0 ? '\n' : ' ');
}

int main() {
    for (ll i = 0; i < MAXN; ++i) head[i] = -1;
    solve();
    return 0;
}
