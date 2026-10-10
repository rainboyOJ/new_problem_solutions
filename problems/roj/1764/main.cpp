/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 23:31
 * update_at: 2026-10-07 23:31
 */
/*
 * 1764. 社会送温暖
 *
 * 题意：给一棵 n 个点的树，每个点有金币数 A_i。每次操作选定 u,v，
 *       把 u 到 v 路径上的点按「从 u 走到 v 的顺序」编号为 1,2,3,...：
 *         op=1 第 i 个点加 a+(i-1)d      op=2 第 i 个点加 a*2^(i-1)
 *         op=3 第 i 个点改为 a+(i-1)d    op=4 第 i 个点改为 a*2^(i-1)
 *         op=5 询问路径上金币和 mod P
 *       1<=n,q<=1e5，1<=P<=1e7（不必是质数），0<=A_i,a,d<=2^31。
 *
 * 做法：树链剖分把路径拆成 O(log n) 段连续 dfn 区间，每段内「路径编号」
 *       是关于 dfn 的一次函数（沿重链 dfn 单调，编号随之单调），于是每段
 *       加/改的值可写成 f(p)=A*2^(p-l)+B*2^(r-p)+c0+c1*p 的形式。
 *       线段树维护该函数族的懒标记：
 *         - 等差部分就是 c0+c1*p（线性，直接合并）；
 *         - 等比部分把系数锚定在区间两端，指数只用非负的 2^k，
 *           从而 P 为偶数（2 不可逆）时也成立。
 *       求和时用 sum_{k=0}^{len-1}2^k = 2^len-1 与位置前缀和（避免除以 2）。
 *       复杂度 O((n+q) log^2 n)。
 *
 * 编译：/opt/homebrew/bin/g++-16 -O2 -std=c++17 main.cpp -o main
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;

int n, q;
ll P;

/* ---------------- 邻接表 ---------------- */
int eHead[MAXN], eNext[2 * MAXN], eTo[2 * MAXN], eCnt;

inline void addEdge(int u, int v) {
    eTo[eCnt] = v;
    eNext[eCnt] = eHead[u];
    eHead[u] = eCnt++;
}

/* ---------------- 树链剖分 ---------------- */
int dep[MAXN], fa[MAXN], sz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], rnk[MAXN];
ll initVal[MAXN], flatVal[MAXN];   // 点上的初值 / 按 dfn 展平后的初值
int bfsOrder[MAXN];

/* ---------------- 预处理 ---------------- */
ll pow2[MAXN + 2];      // pow2[k] = 2^k mod P
ll preSum[MAXN + 2];    // preSum[i] = (1+2+...+i) mod P

inline ll norm(ll x) { x %= P; if (x < 0) x += P; return x; }

/* ---------------- 线段树 ---------------- */
/*
 * 懒标记描述一个函数 f，对区间 [l,r] 内的位置 p：
 *     f(p) = tagA * 2^(p-l) + tagB * 2^(r-p) + tagC + tagD * p   (mod P)
 * hasSet=false：把 f 加到子区间上；hasSet=true：把子区间整体赋值为 f。
 */
ll segSum[4 * MAXN];
ll tagA[4 * MAXN], tagB[4 * MAXN], tagC[4 * MAXN], tagD[4 * MAXN];
bool hasSet[4 * MAXN];

// 函数 f 在 [l,r] 上的和
inline ll funcSum(ll A, ll B, ll C, ll D, int l, int r) {
    int len = r - l + 1;
    ll g = norm(pow2[len] - 1);                 // sum_{k=0}^{len-1} 2^k
    ll res = (norm(A) * g + norm(B) * g) % P;
    res = (res + norm(C) * (len % P)) % P;
    ll spos = norm(preSum[r] - preSum[l - 1]);  // sum_{p=l}^{r} p
    res = (res + norm(D) * spos) % P;
    return res;
}

inline void applyAdd(int o, int l, int r, ll A, ll B, ll C, ll D) {
    A = norm(A); B = norm(B); C = norm(C); D = norm(D);
    segSum[o] = (segSum[o] + funcSum(A, B, C, D, l, r)) % P;
    tagA[o] = (tagA[o] + A) % P;
    tagB[o] = (tagB[o] + B) % P;
    tagC[o] = (tagC[o] + C) % P;
    tagD[o] = (tagD[o] + D) % P;
    // 若原本是「赋值 f」，再「加 g」等价于「赋值 f+g」，hasSet 保持 true
}

inline void applySet(int o, int l, int r, ll A, ll B, ll C, ll D) {
    A = norm(A); B = norm(B); C = norm(C); D = norm(D);
    segSum[o] = funcSum(A, B, C, D, l, r);
    tagA[o] = A; tagB[o] = B; tagC[o] = C; tagD[o] = D;
    hasSet[o] = true;
}

inline void pushDown(int o, int l, int r) {
    if (!hasSet[o] && tagA[o] == 0 && tagB[o] == 0 && tagC[o] == 0 && tagD[o] == 0)
        return;
    int mid = (l + r) >> 1;
    int lenL = mid - l + 1, lenR = r - mid;
    ll A = tagA[o], B = tagB[o], C = tagC[o], D = tagD[o];
    // 左子 [l,mid]：左端仍是 l，右端由 r 变成 mid，指数少 lenR
    ll Al = A, Bl = B * pow2[lenR] % P;
    // 右子 [mid+1,r]：右端仍是 r，左端由 l 变成 mid+1，指数少 lenL
    ll Ar = A * pow2[lenL] % P, Br = B;
    if (hasSet[o]) {
        applySet(o << 1, l, mid, Al, Bl, C, D);
        applySet(o << 1 | 1, mid + 1, r, Ar, Br, C, D);
        hasSet[o] = false;
    } else {
        applyAdd(o << 1, l, mid, Al, Bl, C, D);
        applyAdd(o << 1 | 1, mid + 1, r, Ar, Br, C, D);
    }
    tagA[o] = tagB[o] = tagC[o] = tagD[o] = 0;
}

void build(int o, int l, int r) {
    if (l == r) { segSum[o] = flatVal[l] % P; return; }
    int mid = (l + r) >> 1;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    segSum[o] = (segSum[o << 1] + segSum[o << 1 | 1]) % P;
}

// (A,B) 以查询区间两端为锚：A 锚在 p=ql，B 锚在 p=qr
void updateAdd(int o, int l, int r, int ql, int qr, ll A, ll B, ll C, ll D) {
    if (ql <= l && r <= qr) {
        applyAdd(o, l, r, A * pow2[l - ql] % P, B * pow2[qr - r] % P, C, D);
        return;
    }
    pushDown(o, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) updateAdd(o << 1, l, mid, ql, qr, A, B, C, D);
    if (qr > mid) updateAdd(o << 1 | 1, mid + 1, r, ql, qr, A, B, C, D);
    segSum[o] = (segSum[o << 1] + segSum[o << 1 | 1]) % P;
}

void updateSet(int o, int l, int r, int ql, int qr, ll A, ll B, ll C, ll D) {
    if (ql <= l && r <= qr) {
        applySet(o, l, r, A * pow2[l - ql] % P, B * pow2[qr - r] % P, C, D);
        return;
    }
    pushDown(o, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) updateSet(o << 1, l, mid, ql, qr, A, B, C, D);
    if (qr > mid) updateSet(o << 1 | 1, mid + 1, r, ql, qr, A, B, C, D);
    segSum[o] = (segSum[o << 1] + segSum[o << 1 | 1]) % P;
}

ll querySum(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return segSum[o];
    pushDown(o, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) res += querySum(o << 1, l, mid, ql, qr);
    if (qr > mid) res += querySum(o << 1 | 1, mid + 1, r, ql, qr);
    return res % P;
}

/* ---------------- 单段操作 ---------------- */
/*
 * 段 [l,r]（dfn 连续）。anchorIdx = 锚点位置的「路径编号」：
 *   leftAnchored=true ：锚点在最左端 p=l，编号随 p 递增（i = anchorIdx + p - l），u=... 的 v 侧；
 *   leftAnchored=false：锚点在最右端 p=r，编号随 p 递减（i = anchorIdx + r - p），u 侧。
 */
inline void applySeg(int l, int r, int anchorIdx, bool leftAnchored, int op, ll a, ll d) {
    a = norm(a); d = norm(d);
    ll A = 0, B = 0, C = 0, D = 0;
    if (op == 1 || op == 3) {
        // 值为 a + (i-1)d，是 p 的一次函数
        if (leftAnchored) {
            // i-1 = anchorIdx-1 + (p-l)  =>  f(p) = [a + (anchorIdx-l-1)d] + d*p
            ll k = norm((ll)anchorIdx - l - 1);
            C = (a + k * d) % P;
            D = d;
        } else {
            // i-1 = anchorIdx-1 + (r-p)  =>  f(p) = [a + (anchorIdx+r-1)d] - d*p
            ll k = norm((ll)anchorIdx + r - 1);
            C = (a + k * d) % P;
            D = norm(P - d);
        }
    } else {
        // 值为 a*2^(i-1)，锚定在区间端点，指数恒非负
        ll base = a * pow2[anchorIdx - 1] % P;
        if (leftAnchored) A = base;
        else              B = base;
    }
    if (op == 1 || op == 2) updateAdd(1, 1, n, l, r, A, B, C, D);
    else                    updateSet(1, 1, n, l, r, A, B, C, D);
}

inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

/* ---------------- 路径操作 ---------------- */
void pathUpdate(int u, int v, int op, ll a, ll d) {
    int U0 = u;
    int L = lca(u, v);
    // u 侧：编号 i(x) = dep[U0]-dep[x]+1，沿 dfn 递增编号递减 => 右端锚定
    int x = u;
    while (top[x] != top[L]) {
        applySeg(dfn[top[x]], dfn[x], dep[U0] - dep[x] + 1, false, op, a, d);
        x = fa[top[x]];
    }
    if (x != L) {
        // 此时 x 与 L 同链，[dfn[L]+1, dfn[x]] 是去掉 L 的剩余部分
        applySeg(dfn[L] + 1, dfn[x], dep[U0] - dep[x] + 1, false, op, a, d);
    }
    // v 侧：编号 i(x) = dep[U0]+dep[x]-2dep[L]+1，沿 dfn 递增编号递增 => 左端锚定
    int y = v;
    while (top[y] != top[L]) {
        applySeg(dfn[top[y]], dfn[y], dep[U0] + dep[top[y]] - 2 * dep[L] + 1, true, op, a, d);
        y = fa[top[y]];
    }
    if (y != L) {
        applySeg(dfn[L] + 1, dfn[y], dep[U0] - dep[L] + 2, true, op, a, d);
    }
    // L 本身
    applySeg(dfn[L], dfn[L], dep[U0] - dep[L] + 1, true, op, a, d);
}

ll pathQuery(int u, int v) {
    int U0 = u;
    int L = lca(u, v);
    ll res = 0;
    int x = u;
    while (top[x] != top[L]) {
        res += querySum(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (x != L) res += querySum(1, 1, n, dfn[L] + 1, dfn[x]);
    int y = v;
    while (top[y] != top[L]) {
        res += querySum(1, 1, n, dfn[top[y]], dfn[y]);
        y = fa[top[y]];
    }
    if (y != L) res += querySum(1, 1, n, dfn[L] + 1, dfn[y]);
    res += querySum(1, 1, n, dfn[L], dfn[L]);
    return res % P;
}

/* ---------------- 快读 ---------------- */
static char inBuf[1 << 25];
static size_t inLen = 0, inPos = 0;

inline ll readLL() {
    if (inPos >= inLen) { inLen = fread(inBuf, 1, sizeof(inBuf), stdin); inPos = 0; }
    while (inPos < inLen && (inBuf[inPos] < '0' || inBuf[inPos] > '9')) inPos++;
    ll x = 0;
    while (inPos < inLen && inBuf[inPos] >= '0' && inBuf[inPos] <= '9')
        x = x * 10 + (inBuf[inPos++] - '0');
    return x;
}
inline int readInt() { return (int)readLL(); }

int main() {
    n = readInt(); q = readInt(); P = readLL();
    memset(eHead, -1, sizeof(int) * (n + 1));
    eCnt = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = readInt(), v = readInt();
        addEdge(u, v); addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) initVal[i] = readLL();

    /* ---- BFS 求 fa / dep / 层次序 ---- */
    int qh = 0, qt = 0;
    bfsOrder[qt++] = 1; fa[1] = 0; dep[1] = 0;
    while (qh < qt) {
        int u = bfsOrder[qh++];
        for (int e = eHead[u]; e != -1; e = eNext[e]) {
            int v = eTo[e];
            if (v == fa[u]) continue;
            fa[v] = u; dep[v] = dep[u] + 1; bfsOrder[qt++] = v;
        }
    }
    /* ---- 逆序求 sz / 重儿子 ---- */
    for (int i = n; i >= 1; i--) {
        int u = bfsOrder[i - 1];
        sz[u] = 1; son[u] = 0;
        for (int e = eHead[u]; e != -1; e = eNext[e]) {
            int v = eTo[e];
            if (v == fa[u]) continue;
            sz[u] += sz[v];
            if (son[u] == 0 || sz[v] > sz[son[u]]) son[u] = v;
        }
    }
    /* ---- 分配 dfn：用栈让每条重链的 dfn 连续 ---- */
    {
        static int stk[MAXN];
        int sp = 0;
        stk[sp++] = 1; top[1] = 1;
        int cur = 0;
        while (sp) {
            int u = stk[--sp];
            dfn[u] = ++cur; rnk[cur] = u;
            for (int e = eHead[u]; e != -1; e = eNext[e]) {
                int v = eTo[e];
                if (v == fa[u] || v == son[u]) continue;
                top[v] = v; stk[sp++] = v;
            }
            if (son[u]) { top[son[u]] = top[u]; stk[sp++] = son[u]; }
        }
    }
    for (int i = 1; i <= n; i++) flatVal[dfn[i]] = initVal[i] % P;

    /* ---- 2 的幂 / 位置前缀和 ---- */
    pow2[0] = 1 % P;
    for (int i = 1; i <= n + 1; i++) pow2[i] = pow2[i - 1] * 2 % P;
    preSum[0] = 0;
    for (int i = 1; i <= n + 1; i++) preSum[i] = (preSum[i - 1] + i) % P;

    build(1, 1, n);

    for (int i = 0; i < q; i++) {
        int op = readInt(), u = readInt(), v = readInt();
        if (op == 5) {
            printf("%lld\n", pathQuery(u, v));
        } else if (op == 1 || op == 3) {
            ll a = readLL(), d = readLL();
            pathUpdate(u, v, op, a, d);
        } else {
            ll a = readLL();
            pathUpdate(u, v, op, a, 0);
        }
    }
    return 0;
}
