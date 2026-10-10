// 1707 敲键盘
// ---------------------------------------------------------------------------
// 题意：给 n 个仅含小写字母的模式串 S_1..S_n。A 君每次在 26 个字母中等概率随机敲一个，
//       一旦某个 S_i 成为已敲出的串 T 的子串就停止。求停止时 |T| 的期望，模 1e9+7 输出。
//
// 做法：AC 自动机 + 模意义高斯消元（在自动机上做「吸收态马尔可夫链」的首次命中期望）。
//   1) 把 S_1..S_n 插进 trie，BFS 求 fail 并把转移补全成 DFA：δ(u,c)。
//      若 u 的 fail 链上（含自身）有模式串结尾，则把 u 标记为终止态（终态及其后代都不可再走）。
//   2) 状态 u 记「当前已敲出的串，其最长「是某模式串前缀」的后缀对应的 trie 结点」。
//      只要没进终止态就说明还没有任何 S_i 出现。设 E[u] = 从状态 u 出发（尚未命中）还需敲的字符数期望。
//      每敲一个字符必然多敲 1 个，再按等概率 1/26 走到 δ(u,c)：
//          E[u] = 1 + (1/26) * Σ_c ( δ(u,c) 为终止态 ? 0 : E[δ(u,c)] )
//      其中「到终止态」表示这一步就命中并停止，此后不再敲字符，故贡献 0。
//   3) 只给非终止态设未知量（终止态的期望恒为 0，不入方程），把上式两边乘 26 整理成线性方程组：
//          26 * E[u] - Σ_{c: δ(u,c) 非终止} E[δ(u,c)] = 26
//      状态数 ≤ 1 + Σ|S_i| ≤ 1 + 15*10 = 151，模 1e9+7 高斯消元即可。
//   4) 答案 = E[根结点 0]（初始一个字符都没敲）。
//
// 复杂度：O(T * 151^3) 时间，O(151^2) 空间；T ≤ 50 时远低于 2s。
//
// 数据规模（题面【提示】）：1 ≤ T ≤ 50，1 ≤ n ≤ 15，|S_i| ≤ 10，字符集 = 26 个小写字母。
// ---------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;  // 模数，质数
const int ALPHA = 26;         // 字符集大小
const int MAXNODE = 160;      // 1 + 15 * 10 = 151 个状态，留裕量

int ch[MAXNODE][ALPHA];   // trie 的原始儿子
int go_[MAXNODE][ALPHA];  // 补全后的 DFA 转移 δ(u, c)
int fail_[MAXNODE];       // 失配指针
bool terminal[MAXNODE];   // u 的 fail 链上（含自身）是否有模式串结尾
int nodes;                // trie 结点数（结点 0 为根）

ll A[MAXNODE][MAXNODE + 1];  // 增广矩阵（模意义）
ll x_[MAXNODE];              // 方程组的解
int id_[MAXNODE];            // 自动机状态 -> 未知量下标，-1 表示终止态（不设未知量）
int nVar;                    // 未知量个数 = 非终止状态数

// 快速幂：求 a^e mod MOD
ll qpow(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// 清空单个结点的信息
void clearNode(int u) {
    for (int c = 0; c < ALPHA; ++c) ch[u][c] = 0;
    fail_[u] = 0;
    terminal[u] = false;
}

// 读入 n 个模式串建 trie，再 BFS 求 fail 并把转移补全成 DFA
void buildAC(int n) {
    nodes = 1;
    clearNode(0);
    for (int i = 0; i < n; ++i) {
        static char s[32];
        scanf("%s", s);
        int u = 0;
        for (int j = 0; s[j]; ++j) {
            int c = s[j] - 'a';
            if (ch[u][c] == 0) {
                ch[u][c] = nodes;
                clearNode(nodes);
                ++nodes;
            }
            u = ch[u][c];
        }
        terminal[u] = true;  // 模式串结尾
    }
    // 根结点：没有儿子的字母转移回根
    queue<int> q;
    for (int c = 0; c < ALPHA; ++c) {
        if (ch[0][c] != 0) {
            int v = ch[0][c];
            fail_[v] = 0;
            go_[0][c] = v;
            q.push(v);
        } else {
            go_[0][c] = 0;
        }
    }
    // BFS 逐层处理
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (terminal[fail_[u]]) terminal[u] = true;  // 沿 fail 链传播终止标记
        for (int c = 0; c < ALPHA; ++c) {
            if (ch[u][c] != 0) {
                int v = ch[u][c];
                fail_[v] = go_[fail_[u]][c];
                go_[u][c] = v;
                q.push(v);
            } else {
                go_[u][c] = go_[fail_[u]][c];
            }
        }
    }
}

// 对当前 AC 自动机建方程并解出 E[0]
ll solve() {
    // 给非终止态分配未知量下标
    nVar = 0;
    for (int u = 0; u < nodes; ++u) id_[u] = terminal[u] ? -1 : nVar++;
    // 初始化增广矩阵：26 * E[u] - Σ ... = 26
    for (int i = 0; i < nVar; ++i) {
        for (int j = 0; j <= nVar; ++j) A[i][j] = 0;
        A[i][i] = ALPHA;     // 左边 26 * E[u] 的对角项
        A[i][nVar] = ALPHA;  // 右端常数 26
    }
    // 填系数：转移到的非终止态系数 -1
    for (int u = 0; u < nodes; ++u) {
        if (id_[u] < 0) continue;
        int i = id_[u];
        for (int c = 0; c < ALPHA; ++c) {
            int v = go_[u][c];
            if (id_[v] >= 0) A[i][id_[v]] = (A[i][id_[v]] - 1 + MOD) % MOD;
        }
    }
    // 高斯消元：前向消元
    for (int col = 0; col < nVar; ++col) {
        int piv = -1;
        for (int r = col; r < nVar; ++r)
            if (A[r][col] != 0) { piv = r; break; }
        if (piv < 0) continue;  // 理论上不会发生
        if (piv != col)
            for (int j = col; j <= nVar; ++j) swap(A[col][j], A[piv][j]);
        ll inv = qpow(A[col][col], MOD - 2);
        for (int r = col + 1; r < nVar; ++r) {
            if (A[r][col] == 0) continue;
            ll f = A[r][col] * inv % MOD;
            for (int j = col; j <= nVar; ++j) {
                A[r][j] = (A[r][j] - f * A[col][j]) % MOD;
                if (A[r][j] < 0) A[r][j] += MOD;
            }
        }
    }
    // 回代
    for (int i = nVar - 1; i >= 0; --i) {
        ll s = A[i][nVar];
        for (int j = i + 1; j < nVar; ++j)
            if (A[i][j] != 0) s = (s - A[i][j] * x_[j]) % MOD;
        s %= MOD;
        if (s < 0) s += MOD;
        x_[i] = s * qpow(A[i][i], MOD - 2) % MOD;
    }
    return x_[id_[0]];
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        buildAC(n);
        printf("%lld\n", solve());
    }
    return 0;
}
