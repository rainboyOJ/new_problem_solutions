/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:36
 * update_at: 2026-10-08 01:36
 *
 * 一本通 1772《动漫排序》
 *
 * 题意：给出以 1 为根的树，每个点的孩子已按「喜爱度从大到小」列出。
 *   求满足 ① 祖先排在子孙前面；② 同一父亲的孩子们按给定顺序出现的
 *   排列个数，答案 mod 10007（10007 是质数，且 > n）。
 *
 * 算法：树形 DP + 组合数，每组数据 O(n)。
 *   设 f[u] = 子树 u 内部合法的排列数（u 必在子树最前），sz[u] = 子树大小。
 *   u 的孩子依次是 c1..ck（输入顺序即必须满足的先后顺序）。
 *   把「u 在最前，后面接 k 个子树各自合法序列的洗牌」拆开看：
 *   洗牌只额外要求各子树首元素（即 c_i）出现顺序为 c1 < c2 < ... < ck，
 *   与子树内部内容无关，只与各子树长度有关。
 *   记 Cnt(n1..nk) = 长度 n_i 的 k 段序列洗牌、且首元素先后为 1..k 的方案数。
 *   倒着合并：c_i 必定占 T(c_i) 与其后兄弟子树并集的第一个位置，
 *   余下 sz[c_i]-1 个元素与后面已合并的 |U| 个元素自由插空，
 *   于是 Cnt = prod_i C(N_i - 1, sz[c_i] - 1)，N_i = sum_{j>=i} sz[c_j]，
 *   所以 f[u] = prod_i [ f[c_i] * C(N_i - 1, sz[c_i] - 1) ]，答案即 f[1]。
 *
 * 边界：n = 1 时无孩子，f[1] = 1，DP 自然兼容。
 * 数据来源说明：本题 data/ 由随题的 data.py 自造，题面来自网络重建。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 10007;
const int MAXN = 1005; // 题面 n <= 1000，留安全余量

ll fact[MAXN];     // 阶乘 mod 10007
ll inv_fact[MAXN]; // 阶乘逆元 mod 10007

vector<int> ch[MAXN]; // 孩子的原始顺序（下标 1..n）
ll f[MAXN];           // f[u]：子树 u 内部的合法排列数 mod 10007
ll sz[MAXN];          // sz[u]：子树 u 的节点数

// 快速幂：模 10007 下的 a^e，用于费马小定理求逆元。
ll mod_pow(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// 组合数 C(a, b) mod 10007；a < 10007 故无需求 Lucas。
ll comb(ll a, ll b) {
    if (b < 0 || b > a || a < 0) {
        return 0;
    }
    return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD;
}

// 以 1 为根的树做迭代后序遍历，order 中孩子一定排在父亲前面。
void post_order(ll n, vector<int> &order) {
    order.clear();
    vector<int> stk;
    int iter[MAXN]; // 每个点已经枚举过的孩子个数
    bool vis[MAXN];
    for (int i = 1; i <= n; i++) {
        iter[i] = 0;
        vis[i] = false;
    }
    vis[1] = true;
    stk.push_back(1);
    while (!stk.empty()) {
        int u = stk.back();
        if (iter[u] < (int)ch[u].size()) {
            int c = ch[u][iter[u]];
            iter[u]++;
            if (!vis[c]) {
                vis[c] = true;
                stk.push_back(c);
            }
        } else {
            order.push_back(u);
            stk.pop_back();
        }
    }
}

void solve() {
    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            ch[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            int tot;
            cin >> tot;
            for (int j = 0; j < tot; j++) {
                int x;
                cin >> x;
                ch[i].push_back(x);
            }
        }

        vector<int> order;
        post_order(n, order);

        // order 里孩子先于父亲，顺序处理即为自底向上。
        for (int idx = 0; idx < (int)order.size(); idx++) {
            int u = order[idx];
            ll total = 0; // 所有孩子子树大小之和
            for (int j = 0; j < (int)ch[u].size(); j++) {
                total += sz[ch[u][j]];
            }
            ll res = 1;
            ll rem = total; // N_i：第 i 个孩子及其右侧兄弟的子树大小之和
            for (int j = 0; j < (int)ch[u].size(); j++) {
                int c = ch[u][j];
                res = res * f[c] % MOD;
                res = res * comb(rem - 1, sz[c] - 1) % MOD;
                rem -= sz[c];
            }
            sz[u] = total + 1;
            f[u] = res;
        }
        cout << f[1] % MOD << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理阶乘与逆元：n <= 1000 < MOD，分母不会为 0。
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[MAXN - 1] = mod_pow(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i >= 1; i--) {
        inv_fact[i - 1] = inv_fact[i] * i % MOD;
    }

    solve();
    return 0;
}
