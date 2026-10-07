/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:26
 * update_at: 2026-10-08 02:26
 */

// 一本通 1784《山谷》
// 多组数据（读到 EOF）：每组给 n,m 与 '.'/'X' 网格，求“山谷集合恰好等于 X”的
// 1..nm 排列数 mod 998244353。1<=n<=4，1<=m<=7，组数<=5。
//
// 核心不变量：容斥 ans = Σ_{T ⊇ X，T 为八连通独立集} (-1)^{|T|-|X|} * g(T)，
// 其中 g(T) 只要求“T 中每一格都是山谷”，用 |T| 个格子内部排列顺序的子集 DP 求出。
// 复杂度：O(#独立超集 * 2^{|T|} * |T|)，N<=28、|T|<=8、组数<=5，毫秒级。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const int MAXN = 32;      // 格子数上限 4*7 = 28
const int MAXK = 9;       // 八连通独立集规模上限 8（4x7 国王图最大独立集）
const int MAXS = 1 << MAXK;

ll fact[MAXN + 1];        // fact[i] = i! mod MOD
ll invfact[MAXN + 1];     // invfact[i] = (i!)^{-1} mod MOD

int n, m;                 // 当前数据组的网格尺寸
int N;                    // 格子数 n*m
int adjMask[MAXN];        // adjMask[v] = 与格子 v 八连通的格子集合（编号 v = i*m+j）
int Xmask;                // 输入中字符 'X' 的格子集合

int candList[MAXN];       // 可加入山谷集合的候选格：不在 X 上、也不与 X 相邻
int candCnt;
int candBits;             // 候选格的集合掩码

ll dp[MAXS];              // dp[Y]：山谷内部顺序的前缀恰为 Y 时，已填格子顺序的方案系数和
int celCnt[MAXS];         // celCnt[Y] = #{u ∉ T : N(u) ∩ T ⊆ Y}，T 为当前枚举的独立超集
int posInT[MAXN];         // posInT[v] = 格子 v 在 T 里的压缩下标，v ∉ T 时为 -1

ll answer;                // 当前数据组的容斥累加结果

// 快速幂，用来求阶乘的逆元
ll pw(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    while (e) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

// 预处理阶乘与阶乘逆元：g(T) 的转移里要算 a!/b!
void init_fact() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN] = pw(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
}

// g(T)：只要求集合 T 中每一格都是山谷（T 必须是八连通独立集）的填数方案数。
//
// 把 T 的内部顺序固定为 (t_1..t_k)，再把 T 之外的格子插进这个序列：格子 u 必须排在
// 它在 T 里的最后一个邻居之后。按“最后一个邻居的位置 h(u)”从大到小插入时，插第 j 个
// 的可选位置数是 k-h(u)+j，于是对全部顺序求和可写成子集 DP：dp[Y] = 已排好前缀 Y
// 的系数和；剩下的无约束格子（在 T 中没有任何邻居）另有 N!/(N-F)! 种插法。
ll gval(int T) {
    int k = 0;
    for (int v = 0; v < N; v++) posInT[v] = -1;
    for (int v = 0; v < N; v++) if (T >> v & 1) posInT[v] = k++;
    int sz = 1 << k;
    for (int Y = 0; Y < sz; Y++) celCnt[Y] = 0;
    for (int u = 0; u < N; u++) {
        if (T >> u & 1) continue;
        int nb = adjMask[u] & T;
        int sub = 0;                                  // u 在 T 中的邻居（压缩下标）
        while (nb) {
            int v = __builtin_ctz(nb);
            nb &= nb - 1;
            sub |= 1 << posInT[v];
        }
        celCnt[sub]++;
    }
    // 子集和（zeta）变换：celCnt[Y] 变成“T 中邻居全都落在 Y 内”的格子数
    for (int b = 0; b < k; b++)
        for (int Y = 0; Y < sz; Y++)
            if (Y >> b & 1) celCnt[Y] += celCnt[Y ^ (1 << b)];
    int freeCnt = celCnt[0];                          // 在 T 中没有任何邻居的格子数
    for (int Y = 0; Y < sz; Y++) dp[Y] = 0;
    dp[0] = 1;
    for (int Y = 0; Y < sz; Y++) {
        if (!dp[Y]) continue;
        int h = __builtin_popcount(Y);
        for (int s = 0; s < k; s++) {
            if (Y >> s & 1) continue;
            int nxtY = Y | 1 << s;
            int a = N - h - 1 - celCnt[Y];             // 加入 t_{h+1} 之前：a!/b! 的 a
            int b = N - h - 1 - celCnt[nxtY];          // 加入之后：a!/b! 的 b
            dp[nxtY] = (dp[nxtY] + dp[Y] * fact[a] % MOD * invfact[b]) % MOD;
        }
    }
    return dp[sz - 1] * fact[N] % MOD * invfact[N - freeCnt] % MOD;
}

// 枚举所有包含 X 的八连通独立集 T：逐个候选格决定选或不选，选了就封掉它的邻居。
void dfs_superset(int pos, int T, int forbidden) {
    if (pos == candCnt) {
        ll g = gval(T);
        int extra = __builtin_popcount(T & candBits);   // |T| - |X|
        if (extra & 1) answer = (answer - g + MOD) % MOD;
        else answer = (answer + g) % MOD;
        return;
    }
    dfs_superset(pos + 1, T, forbidden);              // 不选这个候选格
    int c = candList[pos];
    if (!(forbidden >> c & 1))                        // 没被已选格封掉才允许选
        dfs_superset(pos + 1, T | 1 << c, forbidden | (adjMask[c] & candBits));
}

int main() {
    init_fact();
    char row[16];
    while (scanf("%d %d", &n, &m) == 2) {             // 多组数据，读到 EOF
        N = n * m;
        Xmask = 0;
        for (int i = 0; i < n; i++) {
            if (scanf("%s", row) != 1) return 0;
            for (int j = 0; j < m; j++)
                if (row[j] == 'X') Xmask |= 1 << (i * m + j);
        }
        // 八连通邻接关系：格子编号 v = i*m+j，邻居掩码含斜向的 4 个方向
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                int v = i * m + j, mask = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++) {
                        if (!di && !dj) continue;
                        int x = i + di, y = j + dj;
                        if (x < 0 || x >= n || y < 0 || y >= m) continue;
                        mask |= 1 << (x * m + y);
                    }
                adjMask[v] = mask;
            }
        // 山谷集合不可能为空：全局最小值所在格必是山谷（无邻居时也恒为山谷，N=1 得 1）
        bool valid = (Xmask != 0);
        for (int v = 0; v < N && valid; v++)
            if ((Xmask >> v & 1) && (adjMask[v] & Xmask))
                valid = false;                        // X 内部八连通相邻，两个约束矛盾
        if (!valid) { printf("0\n"); continue; }
        candCnt = 0;
        candBits = 0;
        for (int v = 0; v < N; v++)
            if (!(Xmask >> v & 1) && !(adjMask[v] & Xmask)) {
                candList[candCnt++] = v;
                candBits |= 1 << v;
            }
        answer = 0;
        dfs_superset(0, Xmask, 0);
        printf("%lld\n", answer % MOD);
    }
    return 0;
}
