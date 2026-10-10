/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 00:32
 * update_at: 2026-10-08 00:32
 */
// ROJ 1765《树上斐波那契》
// ---------------------------------------------------------------------------
// 数学依据（Fibonacci 加法公式，对全体整数成立）：
//   Fib(a+b) = Fib(a)*Fib(b+1) + Fib(a-1)*Fib(b)，
//   负数下标按 Fib(-n) = (-1)^(n+1)*Fib(n) 延拓，于是 Fib(0)=0、Fib(-1)=1。
//
// 关键转化：更新 U X k 对 X 子树内的点 v 加上
//   Fib(k + dep[v] - dep[X]) = c1*Fib(dep[v]+1) + c0*Fib(dep[v]),  c1=Fib(K), c0=Fib(K-1),
//   K = k - dep[X]（根的深度取 0，D = dep[v] - dep[X]）。
// 系数 c0,c1 只与操作有关；Fib(dep[v])、Fib(dep[v]+1) 只与节点的静态深度有关。
//
// 做法（Fib 前缀和 + 子树差分树状数组 + 倍增 LCA）：
//   记 val[v] 为点权，T[u] = Σ_{v 在根..u 的路径上} val[v]（根到 u 的链和），
//   则路径和 = T[X] + T[Y] - 2*T[L] + val[L]（L 为 X,Y 的 LCA）。
//   记 pa[w] = Σ_{v 在根..w 上} Fib(dep[v])、pb 同理换成 Fib(dep[v]+1)。
//   一次更新对 T[u] 的贡献只在 u ∈ X 子树时非零，此时根到 u 上的 Fib 前缀和
//   比根到 x 的父亲那段多出的部分恰好是 pa[u]-pa[faX] 与 pb[u]-pb[faX]，于是
//     T[u] = pa[u]*S0[u] + pb[u]*S1[u] - SD[u]
//   其中 S0[u]=Σc0、S1[u]=Σc1、SD[u]=Σ(c0*pa[faX]+c1*pb[faX])，
//   三个求和都只对"子树区间包含 tin[u] 的那些更新"统计。
//   子树在 DFS 先序里是连续区间 [tin[X], tin[X]+sz[X]-1]，所以"覆盖某点的区间权值和"
//   用差分树状数组做：在 tin[X] 处 +v、在 tin[X]+sz[X] 处 -v，单点前缀和即为所求。
//   点值 val[L] = Fib(dep[L])*S0[L] + Fib(dep[L]+1)*S1[L]，与 T[L] 共用同一次查询结果。
//
// 复杂度：预处理 O(n log n)（倍增 LCA 表），单次更新 O(log n + log k)（Fib 用倍增），
//   单次询问 O(log n)。空间 O(n log n)。n,m ≤ 1e5、k ≤ 1e15 时远超需求。
// ---------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 节点数上限
const int LOGN = 17;     // log2(1e5) 向上取整，倍增 LCA 的层数
const ll MOD = 1000000007LL;

// 一个树上节点：把所有"只依赖树形状"的静态属性聚在一起，避免平行数组
struct Node {
    int fa;  // 父亲编号，根的父亲是 0 号哨兵（它的 pa/pb 都是 0）
    int dep; // 深度 = 到根的边数（根为 0）
    int tin; // DFS 先序编号（1..n），子树恰好是 [tin, tin+sz-1]
    int sz;  // 子树大小
    ll pa;   // 根到本节点的 ΣFib(dep[v]) mod MOD
    ll pb;   // 根到本节点的 ΣFib(dep[v]+1) mod MOD
};
Node nd[MAXN];

// 差分树状数组的一个位置：三个分量属于同一个位置，聚成 struct 而不是三个平行数组
struct BitNode {
    ll c0; // 覆盖该位置的更新带来的 ΣFib(K-1)
    ll c1; // 覆盖该位置的更新带来的 ΣFib(K)
    ll d;  // 覆盖该位置的更新带来的 Σ(c0*pa[faX] + c1*pb[faX])
};

int n, m;                          // 节点数、操作数
vector<int> child[MAXN];           // 每个节点的孩子表（树题用 vector 邻接表足够直观）
BitNode bit[MAXN];                 // 差分树状数组，前缀和 = 覆盖当前点的更新累计量
ll fib_small[MAXN];                // fib_small[t] = Fib(t) mod MOD，深度只用 0..n+1
int up[LOGN][MAXN];                // 倍增表：up[j][v] 是 v 的第 2^j 级祖先（0 表示不存在）
int order[MAXN];                   // DFS 先序序列，order[0..n-1]
int stk[MAXN];                     // 迭代 DFS 的手写栈，避免递归爆栈

// 返回 (Fib(t), Fib(t+1)) mod MOD，要求 t >= 0（倍增法，O(log t)）
pair<ll, ll> fib_pair(ll t) {
    if (t == 0) return make_pair(0LL, 1LL);
    pair<ll, ll> half = fib_pair(t >> 1);
    ll a = half.first, b = half.second;
    ll even = a * ((2 * b % MOD - a + MOD) % MOD) % MOD; // Fib(2i)
    ll odd = (a * a + b * b) % MOD;                      // Fib(2i+1)
    if (t & 1) return make_pair(odd, (even + odd) % MOD);
    return make_pair(even, odd);
}

// Fib(t) mod MOD，允许 t 为负：Fib(-t) = (-1)^(t+1) * Fib(t)
ll fib(ll t) {
    if (t >= 0) return fib_pair(t).first;
    ll positive = -t;
    ll value = fib_pair(positive).first;
    if (positive % 2 == 0) value = (MOD - value) % MOD; // t<0 时符号为 (-1)^(positive+1)
    return value;
}

// 在差分树状数组的位置 pos 处累加一个三元增量
void bit_add(int pos, ll v0, ll v1, ll v2) {
    for (int i = pos; i <= n; i += i & -i) {
        bit[i].c0 = (bit[i].c0 + v0) % MOD;
        bit[i].c1 = (bit[i].c1 + v1) % MOD;
        bit[i].d = (bit[i].d + v2) % MOD;
    }
}

// 位置 pos 的三元前缀和，即"子树区间覆盖了 pos 的那些更新"的累计量
BitNode bit_query(int pos) {
    BitNode res;
    res.c0 = res.c1 = res.d = 0;
    for (int i = pos; i > 0; i -= i & -i) {
        res.c0 += bit[i].c0;
        res.c1 += bit[i].c1;
        res.d += bit[i].d;
    }
    res.c0 %= MOD; res.c1 %= MOD; res.d %= MOD;
    return res;
}

// T[u] = 根到 u 链上的点权和：静态 Fib 前缀和乘累计量，再减掉差分的第三维
ll chain_sum(int u, BitNode s) {
    ll res = (nd[u].pa * s.c0 + nd[u].pb * s.c1 - s.d) % MOD;
    return (res % MOD + MOD) % MOD;
}

// val[u] = 点 u 当前的权值：比 chain_sum 少一个差分的 d 项（那项属于 X 上半段的修正）
ll point_value(int u, BitNode s) {
    ll res = (fib_small[nd[u].dep] * s.c0 + fib_small[nd[u].dep + 1] * s.c1) % MOD;
    return (res % MOD + MOD) % MOD;
}

int lca(int a, int b) {
    if (nd[a].dep < nd[b].dep) swap(a, b);
    int diff = nd[a].dep - nd[b].dep;
    for (int j = 0; j < LOGN; ++j) {
        if ((diff >> j) & 1) a = up[j][a];
    }
    if (a == b) return a;
    for (int j = LOGN - 1; j >= 0; --j) {
        if (up[j][a] != up[j][b]) {
            a = up[j][a];
            b = up[j][b];
        }
    }
    return nd[a].fa;
}

int main() {
    // 读入与建树
    scanf("%d %d", &n, &m);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &nd[i].fa);
        child[nd[i].fa].push_back(i);
    }

    // 迭代式 DFS：求先序编号 tin、深度 dep
    int order_cnt = 0;
    int top = 0;
    stk[top++] = 1;
    while (top > 0) {
        int u = stk[--top];
        nd[u].tin = order_cnt + 1;
        order[order_cnt++] = u;
        for (int i = 0; i < (int)child[u].size(); ++i) {
            int v = child[u][i];
            nd[v].dep = nd[u].dep + 1; // fa 读入时已存好，不必再赋
            stk[top++] = v;
        }
    }
    // 逆先序累加子树大小：儿子的 sz 一定先算好
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        nd[u].sz = 1;
        for (int j = 0; j < (int)child[u].size(); ++j) nd[u].sz += nd[child[u][j]].sz;
    }

    // Fib(0..n+1) 线性递推（深度加一最多用到 n+1）
    fib_small[0] = 0;
    fib_small[1] = 1;
    for (int i = 2; i <= n + 1; ++i) fib_small[i] = (fib_small[i - 1] + fib_small[i - 2]) % MOD;

    // 根到各点的两条 Fib 前缀和（按先序保证父亲已算过）
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        nd[u].pa = (nd[nd[u].fa].pa + fib_small[nd[u].dep]) % MOD;
        nd[u].pb = (nd[nd[u].fa].pb + fib_small[nd[u].dep + 1]) % MOD;
    }

    // 倍增表：up[0][v] = fa[v]，往上逐级翻倍
    for (int v = 1; v <= n; ++v) up[0][v] = nd[v].fa;
    for (int j = 1; j < LOGN; ++j) {
        for (int v = 1; v <= n; ++v) up[j][v] = up[j - 1][up[j - 1][v]];
    }

    // 处理操作
    char op[8];
    for (int i = 0; i < m; ++i) {
        scanf("%s", op);
        if (op[0] == 'U') {
            int x;
            ll k;
            scanf("%d %lld", &x, &k);
            ll big = k - nd[x].dep;   // K，可能为负
            ll c1 = fib(big);         // Fib(K)，配 Fib(dep[v]+1)
            ll c0 = fib(big - 1);     // Fib(K-1)，配 Fib(dep[v])
            int fx = nd[x].fa;        // x 的父亲（根的哨兵 0，pa/pb 均为 0）
            ll d = (c0 * nd[fx].pa + c1 * nd[fx].pb) % MOD;
            int tail = nd[x].tin + nd[x].sz;   // 子树区间 [tin, tail-1]
            bit_add(nd[x].tin, c0, c1, d);
            if (tail <= n) bit_add(tail, (MOD - c0) % MOD, (MOD - c1) % MOD, (MOD - d) % MOD);
        } else {
            int x, y;
            scanf("%d %d", &x, &y);
            int l = lca(x, y);
            BitNode sx = bit_query(nd[x].tin);
            BitNode sy = bit_query(nd[y].tin);
            BitNode sl = bit_query(nd[l].tin);
            // 路径和 = T[X] + T[Y] - 2*T[L] + val[L]：L 在两条根链里各被算了一次
            ll ans = (chain_sum(x, sx) + chain_sum(y, sy) - 2 * chain_sum(l, sl)
                      + point_value(l, sl)) % MOD;
            printf("%lld\n", (ans % MOD + MOD) % MOD);
        }
    }
    return 0;
}
