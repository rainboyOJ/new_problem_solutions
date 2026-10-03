/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 18:25
 */
// P9248 [集训队互测 2018] 完美的集合
//
// 从所有「重量和 <= M 的连通块中点权和最大」的集合（完美集合）里选出 K 个
// （互不相同，无序），使得存在一个点 x 同时是这 K 个集合的合法测试点
// （x 在每个集合里，且对集合内每点 y 有 dist(x,y)*v_y <= Max）。
//
// 【第一步：整体条件拆成单点计数】
//   B_x = { y : dist(x,y)*v_y <= Max }（一定含 x），
//   A_x = #完美集合 S 满足 x ∈ S ⊆ B_x（即 x 是 S 的合法测试点）。
//   一个集合的合法测试点全体 W(S) 恒连通：若 x,z 合法，则 x-z 路径上任一点 u
//   对任意 y 有 dist(u,y) <= max(dist(x,y), dist(z,y))，故 u 也合法。
//   于是 W(S) 是 S 里的连通块，有唯一最浅点（以 0 为根）。按最浅点分类：
//     答案 = sum_x [ C(A_x, K) - C(C_x, K) ]
//   其中 C_x = #同时以 x 与其父亲为合法测试点的完美集合数（根处该项为 0）。
//   因为 K 个集合互不相同，这里的组合数是不放回的 C(·, K)；
//   K > A_x 时 C = 0。
//
// 【第二步：DFS 序背包求 A_x / C_x】
//   背包容量必须记「重量恰好为 c」而不是「<= c」，否则同价值、不同重量的集合
//   会在同一个状态上被合并而漏解。
//   把树按 DFS 序拍平：选 p_i 则转到 i+1；不选 p_i 则整棵子树都不能选，
//   直接跳到 i + size(p_i)。单次 O(N*M)。
//   求 C_x 时先强制选中 x 与父亲：把父亲安排成 x 的第一个孩子，强制点就落在
//   DFS 序的前缀上，可行域取 B_x ∩ B_{fa(x)}。
//
// 【第三步：C(n,K) mod 5^23】
//   模数是素数幂 5^23，n 可达 2^59，用手写的 Granville 型算法：
//     U(m) = prod_{i=1..m} (i 去掉所有因子 5 之后的部分) mod 5^23
//     C(n,K) = 5^(v5(n)-v5(K)-v5(n-K)) * U(n) * U(K)^-1 * U(n-K)^-1
//   指数 >= 23 时答案为 0。U(m) = U(m/5) * G(m)，其中
//     G(m) = prod_{i<=m, 5 不整除 i} i
//   而 prod_{j<t}(5j+r) 展开成以 5 为变量的幂级数，系数是初等对称多项式
//   e_k(0..t-1) = |s(t,t-k)|（第一类 Stirling 数），它关于 t 是 2k 次多项式，
//   用牛顿级数 sum c[k][i] * C(t,i) 求值；C(t,i)（i <= 46）直接剥掉阶乘里的
//   因子 5 再求逆元即可，避免预处理 5^23 规模的阶乘表。
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <algorithm>
using namespace std;

typedef unsigned long long u64;
typedef long long ll;
typedef __int128 i128;

static const u64 MOD = 11920928955078125ULL;   // 5^23
static const int MAXN = 64;
static const int MAXM = 10005;

// ---------------- 组合数 mod 5^23 ----------------
static u64 mulmod(u64 a, u64 b) { return (u64)((i128)a * b % MOD); }

static u64 powmod(u64 a, u64 e) {
    u64 r = 1 % MOD; a %= MOD;
    while (e) { if (e & 1) r = mulmod(r, a); a = mulmod(a, a); e >>= 1; }
    return r;
}

// 模 5^23 下求逆（要求 a 与 5 互素），迭代版扩展欧几里得
static u64 exgcd(u64 a) {
    i128 old_r = (i128)(a % MOD), r = (i128)MOD, old_s = 1, s = 0;
    while (r != 0) {
        i128 q = old_r / r;
        i128 t = old_r - q * r; old_r = r; r = t;
        t = old_s - q * s; old_s = s; s = t;
    }
    i128 x = old_s % (i128)MOD;
    if (x < 0) x += (i128)MOD;
    return (u64)x;
}

static u64 mi5[32];
static u64 invSmall[64];        // i 去掉 5 因子后的逆元
static u64 newtonC[24][48];     // 牛顿级数系数
static u64 binomT[48];          // 当前 t 下 C(t,i) mod MOD

// C(t,m) mod MOD，m <= 46（t 可以任意大）
static u64 smallC(u64 t, int m) {
    if (m < 0) return 0;
    if (t < (u64)m) return 0;
    if (m == 0) return 1;
    int e = 0;
    u64 res = 1;
    for (int i = 1; i <= m; i++) {
        u64 x = t - m + i;
        while (x % 5 == 0) { x /= 5; e++; }
        res = mulmod(res, x % MOD);
    }
    for (int i = 1; i <= m; i++) {
        u64 x = i;
        while (x % 5 == 0) { x /= 5; e--; }
        res = mulmod(res, invSmall[i]);
    }
    if (e >= 23) return 0;
    return mulmod(res, mi5[e]);
}

static void initCombo() {
    mi5[0] = 1;
    for (int i = 1; i < 32; i++) mi5[i] = mi5[i - 1] * 5 % MOD;
    for (int i = 1; i <= 46; i++) {
        u64 x = i;
        while (x % 5 == 0) x /= 5;
        invSmall[i] = exgcd(x % MOD);
    }
    static u64 S[48][48];
    memset(S, 0, sizeof(S));
    S[0][0] = 1;
    for (int i = 1; i < 48; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (u64)(((i128)S[i - 1][j - 1] + (i128)(i - 1) * S[i - 1][j] % MOD) % MOD);
    for (int k = 0; k <= 22; k++) {
        static u64 f[48];
        for (int t = 0; t < 48; t++) f[t] = (t - k >= 0) ? S[t][t - k] : 0;
        for (int i = 0; i <= 2 * k && i < 48; i++) {
            newtonC[k][i] = f[0];
            for (int t = 0; t + 1 < 48; t++) f[t] = (f[t + 1] + MOD - f[t]) % MOD;
        }
    }
}

static void buildBinomT(u64 t) {
    for (int i = 0; i <= 46; i++) binomT[i] = smallC(t, i);
}

static u64 elemSym(u64 t, int k) {
    u64 r = 0;
    int lim = 2 * k; if (lim > 46) lim = 46;
    for (int i = 0; i <= lim; i++)
        if (newtonC[k][i]) r = (r + mulmod(newtonC[k][i], binomT[i])) % MOD;
    return r;
}

static u64 prodArith(u64 t, int r) {
    u64 rt = powmod((u64)r, t);
    u64 ir = exgcd((u64)r);
    u64 res = 0, acc = 1;
    u64 lim = t < 23 ? t : 22;
    for (u64 k = 0; k <= lim; k++) {
        res = (res + mulmod(acc, mulmod(elemSym(t, (int)k), rt))) % MOD;
        acc = mulmod(acc, mulmod(5, ir));
    }
    return res;
}

static u64 Gfun(u64 m) {
    u64 t = m / 5, s = m % 5;
    buildBinomT(t);
    u64 res = 1;
    for (int r = 1; r <= 4; r++) res = mulmod(res, prodArith(t, r));
    u64 tm = mulmod(t % MOD, 5);
    for (u64 r = 1; r <= s; r++) res = mulmod(res, (tm + r) % MOD);
    return res;
}

static u64 Ufun(u64 m) {
    u64 res = 1;
    static u64 stk[64];
    int top = 0;
    while (m > 0) { stk[top++] = m; m /= 5; }
    while (top > 0) res = mulmod(res, Gfun(stk[--top]));
    return res;
}

static u64 v5fact(u64 n) { u64 s = 0; while (n) { n /= 5; s += n; } return s; }

// 组合数 C(n,K) mod 5^23
static u64 combination(u64 n, u64 K) {
    if (K > n) return 0;
    if (K == 0) return 1;
    u64 e = v5fact(n) - v5fact(K) - v5fact(n - K);
    if (e >= 23) return 0;
    u64 un = Ufun(n), uk = Ufun(K), ur = Ufun(n - K);
    return mulmod(mi5[e], mulmod(mulmod(un, exgcd(uk)), exgcd(ur)));
}

// ---------------- 图 ----------------
static int N, M;
static ll  K, Max;
static ll  w[MAXN], v[MAXN];
static ll  dist_[MAXN][MAXN];
static int head_[MAXN], nxt_[2 * MAXN], to_[2 * MAXN], eCnt;
static ll  ew_[2 * MAXN];
static bool allowed_[MAXN];

static void addEdge(int a, int b, ll c) {
    to_[eCnt] = b; ew_[eCnt] = c; nxt_[eCnt] = head_[a]; head_[a] = eCnt++;
}

// ---------------- DFS 序 ----------------
static int order_[MAXN], tin_[MAXN], jump_[MAXN], parent_[MAXN];
static int fa_[MAXN];           // 以 0 为根的父亲数组（不会被 buildOrder 覆盖）

// 以 root 为根拍 DFS 序（递归深度 <= N = 60，安全）。
// firstChild >= 0 时，强制它成为 root 的第一个孩子，
// 这样 forced 里的点就落在 DFS 序的前缀 order_[0..flen-1] 上。
static int childL_[MAXN][MAXN], childN_[MAXN];

static void buildOrder(int root, int firstChild) {
    // 先按无向图重新求每个点在 root 下的孩子列表
    static int stk[MAXN];
    static bool vis[MAXN];
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < N; i++) childN_[i] = 0;
    int top = 0; stk[top++] = root; vis[root] = true; parent_[root] = -1;
    while (top > 0) {
        int u = stk[--top];
        for (int e = head_[u]; e != -1; e = nxt_[e]) {
            int to = to_[e];
            if (vis[to]) continue;
            vis[to] = true;
            parent_[to] = u;
            childL_[u][childN_[u]++] = to;
            stk[top++] = to;
        }
    }
    // 把 firstChild 换到 root 孩子列表的第一位
    if (firstChild >= 0 && childN_[root] > 0) {
        int pos = -1;
        for (int i = 0; i < childN_[root]; i++) if (childL_[root][i] == firstChild) { pos = i; break; }
        if (pos > 0) { int t = childL_[root][0]; childL_[root][0] = childL_[root][pos]; childL_[root][pos] = t; }
    }
    // 迭代式 DFS（显式栈），保持孩子顺序
    static int sNode[MAXN], sIdx[MAXN];
    int cnt = 0;
    sNode[0] = root; sIdx[0] = 0; top = 0;
    tin_[root] = cnt; order_[cnt++] = root;
    while (top >= 0) {
        int u = sNode[top];
        if (sIdx[top] < childN_[u]) {
            int c = childL_[u][sIdx[top]++];
            tin_[c] = cnt; order_[cnt++] = c;
            top++; sNode[top] = c; sIdx[top] = 0;
        } else {
            jump_[u] = cnt;
            top--;
        }
    }
}

// ---------------- 背包 ----------------
// 注意：方案数不能取模！C(A_x, K) 依赖 A_x 的精确值（其 5 进制展开），
// 而连通块个数最多 2^59 + 59，用 unsigned long long 精确保存。
static ll  dpVal[MAXN][MAXM];
static u64 dpCnt[MAXN][MAXM];
static int Vstar;

// 「必选 forced[0..flen-1]、只能选 allowed_ 内的点、连通」时价值恰为 Vstar 的方案数
static u64 countWays(int root, const int *forced, int flen) {
    buildOrder(root, flen > 1 ? forced[1] : -1);
    int n = N;
    for (int c = 0; c <= M; c++) { dpVal[n][c] = -1; dpCnt[n][c] = 0; }
    dpVal[n][0] = 0; dpCnt[n][0] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int u = order_[i];
        for (int c = 0; c <= M; c++) {
            ll bv = dpVal[jump_[u]][c];
            u64 bc = dpCnt[jump_[u]][c];
            if (allowed_[u] && w[u] <= c && dpVal[i + 1][c - (int)w[u]] >= 0) {
                ll cv = dpVal[i + 1][c - (int)w[u]] + v[u];
                u64 cc = dpCnt[i + 1][c - (int)w[u]];
                if (cv > bv) { bv = cv; bc = cc; }
                else if (cv == bv) { bc = bc + cc; }          // 精确计数，不取模
            }
            dpVal[i][c] = bv; dpCnt[i][c] = bc;
        }
    }
    int cap = M; ll addv = 0;
    for (int i = 0; i < flen; i++) {
        int u = forced[i];
        if (!allowed_[u] || w[u] > cap) return 0;
        cap -= (int)w[u]; addv += v[u];
    }
    ll best = -1; u64 tot = 0;
    for (int c = 0; c <= cap; c++) {
        if (dpVal[flen][c] < 0) continue;
        ll tv = dpVal[flen][c] + addv;
        if (tv > best) { best = tv; tot = dpCnt[flen][c]; }
        else if (tv == best) { tot = tot + dpCnt[flen][c]; }   // 精确计数
    }
    return (best == Vstar) ? tot : 0;
}

// 求最大点权和 V*
static void computeVstar() {
    int best = -1;
    for (int r = 0; r < N; r++) {
        for (int y = 0; y < N; y++) allowed_[y] = true;
        if (w[r] > M) continue;
        buildOrder(r, -1);
        int n = N;
        for (int c = 0; c <= M; c++) dpVal[n][c] = -1;
        dpVal[n][0] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int u = order_[i];
            for (int c = 0; c <= M; c++) {
                ll bv = dpVal[jump_[u]][c];
                if (w[u] <= c && dpVal[i + 1][c - (int)w[u]] >= 0)
                    bv = max(bv, dpVal[i + 1][c - (int)w[u]] + v[u]);
                dpVal[i][c] = bv;
            }
        }
        int cap = M - (int)w[r]; ll addv = v[r];
        for (int c = 0; c <= cap; c++)
            if (dpVal[1][c] >= 0) best = max(best, (int)(dpVal[1][c] + addv));
    }
    Vstar = best;
}

int main() {
    initCombo();

    if (scanf("%d %d %lld %lld", &N, &M, &K, &Max) != 4) return 0;
    for (int i = 0; i < N; i++) scanf("%lld", &w[i]);
    for (int i = 0; i < N; i++) scanf("%lld", &v[i]);
    eCnt = 0;
    for (int i = 0; i < N; i++) head_[i] = -1;
    for (int i = 0; i < N - 1; i++) {
        int a, b; ll c;
        scanf("%d %d %lld", &a, &b, &c);
        a--; b--;
        addEdge(a, b, c); addEdge(b, a, c);
    }

    const ll INF = (ll)4e18;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) dist_[i][j] = (i == j ? 0 : INF);
    for (int u = 0; u < N; u++)
        for (int e = head_[u]; e != -1; e = nxt_[e]) {
            int to = to_[e];
            if (ew_[e] < dist_[u][to]) dist_[u][to] = ew_[e];
        }
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++) {
            if (dist_[i][k] == INF) continue;
            for (int j = 0; j < N; j++)
                if (dist_[i][k] + dist_[k][j] < dist_[i][j])
                    dist_[i][j] = dist_[i][k] + dist_[k][j];
        }

    computeVstar();
    if (Vstar < 0) { puts("0"); return 0; }

    // 以 0 为根的父亲数组（单独算一次，存进 fa_，不要被后面的 buildOrder 覆盖）
    for (int r = 0; r < N; r++) allowed_[r] = true;
    buildOrder(0, -1);
    for (int i = 0; i < N; i++) fa_[i] = parent_[i];

    u64 ans = 0;
    for (int x = 0; x < N; x++) {
        // A_x：x ∈ S ⊆ B_x
        for (int y = 0; y < N; y++)
            allowed_[y] = !(v[y] > 0 && dist_[x][y] > Max / v[y]) &&
                          (v[y] == 0 || dist_[x][y] * v[y] <= Max);
        if (!allowed_[x]) continue;      // 不可能，dist(x,x)=0 使得 x 一定合法
        int forced[2] = { x, -1 };
        u64 Ax = countWays(x, forced, 1);
        ans = (ans + combination(Ax, (u64)K)) % MOD;

        // C_x：x 与父亲同时合法
        int p = fa_[x];
        if (p == -1) continue;
        for (int y = 0; y < N; y++) {
            bool ok1 = (v[y] == 0 || dist_[x][y] * v[y] <= Max);
            bool ok2 = (v[y] == 0 || dist_[p][y] * v[y] <= Max);
            allowed_[y] = ok1 && ok2;
        }
        if (!allowed_[x] || !allowed_[p]) { /* 交集为空则 C=0 */ }
        else {
            forced[0] = x; forced[1] = p;
            u64 Cx = countWays(x, forced, 2);
            ans = (ans + MOD - combination(Cx, (u64)K)) % MOD;
        }
    }
    printf("%llu\n", ans);
    return 0;
}
