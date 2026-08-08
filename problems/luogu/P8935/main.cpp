#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MOD = 1000000007;

int n, k, x;
vector<int> g[MAXN];
vector<int> child[MAXN];
vector<int> order_nodes;
vector<int> path_nodes;
vector<int> poly_all[MAXN]; // 普通子树的一元 EGF：系数 = 方案数 / t!

int parent_node[MAXN];
int stem_next[MAXN];
int inv_num[MAXN], fact[MAXN], comb_num[MAXN][MAXN];

int cur_all[MAXN][MAXN];
int open_dp[MAXN][MAXN];
int next_all[MAXN][MAXN];
int next_close[MAXN][MAXN];
int root_close[MAXN][MAXN];

// 模意义下加法。
inline void add_mod(int &x, long long y) {
    x = (x + y) % MOD;
}

// 模意义下减法。
inline void sub_mod(int &x, long long y) {
    x = (x - y) % MOD;
    if (x < 0) {
        x += MOD;
    }
}

// 建树，并把无根树转成以 1 为根的有根树。
void dfs_build(int u, int fa) {
    parent_node[u] = fa;
    order_nodes.push_back(u);
    for (int v : g[u]) {
        if (v == fa) {
            continue;
        }
        child[u].push_back(v);
        dfs_build(v, u);
    }
}

// 朴素多项式卷积。
vector<int> multiply_poly(const vector<int> &a, const vector<int> &b) {
    vector<int> c((int) a.size() + (int) b.size() - 1, 0);
    for (int i = 0; i < (int) a.size(); i++) {
        if (a[i] == 0) {
            continue;
        }
        for (int j = 0; j < (int) b.size(); j++) {
            if (b[j] == 0) {
                continue;
            }
            c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % MOD;
        }
    }
    return c;
}

// 计算普通子树的一元 EGF。
// poly_all[u][t] 表示：
// 在 u 的整棵子树里，做出恰好 t 次操作的方案数 / t!。
void build_plain_subtree_dp() {
    for (int idx = (int) order_nodes.size() - 1; idx >= 0; idx--) {
        int u = order_nodes[idx];
        vector<int> prod(1, 1);
        for (int v : child[u]) {
            prod = multiply_poly(prod, poly_all[v]);
        }

        vector<int> res((int) prod.size() + 1, 0);
        for (int t = 0; t < (int) prod.size(); t++) {
            // 不操作 u，自身保留。
            add_mod(res[t], prod[t]);
            // 最后再操作一次 u。
            add_mod(res[t + 1], 1LL * prod[t] * inv_num[t + 1]);
        }
        poly_all[u] = res;
    }
}

// 计算路径点 u 的所有侧枝（不含通向 x 的那条儿子）的一元 EGF。
vector<int> build_side_poly(int u) {
    vector<int> prod(1, 1);
    for (int v : child[u]) {
        if (v == stem_next[u]) {
            continue;
        }
        prod = multiply_poly(prod, poly_all[v]);
    }
    return prod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> x;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    inv_num[1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        inv_num[i] = MOD - 1LL * (MOD / i) * inv_num[MOD % i] % MOD;
    }
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++) {
        comb_num[i][0] = comb_num[i][i] = 1;
        for (int j = 1; j < i; j++) {
            comb_num[i][j] = comb_num[i - 1][j - 1] + comb_num[i - 1][j];
            if (comb_num[i][j] >= MOD) {
                comb_num[i][j] -= MOD;
            }
        }
    }

    dfs_build(1, 0);
    build_plain_subtree_dp();

    // 找出从 1 到 x 的茎。
    int cur = x;
    while (cur != 0) {
        path_nodes.push_back(cur);
        cur = parent_node[cur];
    }
    reverse(path_nodes.begin(), path_nodes.end());
    for (int i = 0; i + 1 < (int) path_nodes.size(); i++) {
        stem_next[path_nodes[i]] = path_nodes[i + 1];
    }

    memset(cur_all, 0, sizeof(cur_all));
    memset(root_close, 0, sizeof(root_close));

    for (int idx = (int) path_nodes.size() - 1; idx >= 0; idx--) {
        int u = path_nodes[idx];
        vector<int> side_poly = build_side_poly(u);

        if (u == x) {
            memset(cur_all, 0, sizeof(cur_all));
            for (int a = 0; a < (int) side_poly.size(); a++) {
                cur_all[a][0] = side_poly[a];
            }
            if (u == 1) {
                memcpy(root_close, cur_all, sizeof(root_close));
            }
            continue;
        }

        memset(open_dp, 0, sizeof(open_dp));
        for (int a = 0; a <= n; a++) {
            for (int s = 0; s <= n; s++) {
                if (cur_all[a][s] == 0) {
                    continue;
                }
                int lim = min((int) side_poly.size() - 1, n - s);
                for (int r = 0; r <= lim; r++) {
                    if (side_poly[r] == 0) {
                        continue;
                    }
                    add_mod(open_dp[a][s + r], 1LL * cur_all[a][s] * side_poly[r]);
                }
            }
        }

        memset(next_all, 0, sizeof(next_all));
        memset(next_close, 0, sizeof(next_close));
        for (int a = 0; a <= n; a++) {
            for (int s = 0; s <= n; s++) {
                next_all[a][s] = open_dp[a][s];
            }
        }

        // 对 q 积分：
        // ∫ p^a (p+q)^s dq = (p^a (p+q)^(s+1) - p^(a+s+1)) / (s+1)
        for (int a = 0; a <= n; a++) {
            for (int s = 0; s <= n; s++) {
                int val = open_dp[a][s];
                if (val == 0) {
                    continue;
                }
                if (s + 1 <= n) {
                    int add = 1LL * val * inv_num[s + 1] % MOD;
                    add_mod(next_close[a][s + 1], add);
                    add_mod(next_all[a][s + 1], add);
                    if (a + s + 1 <= n) {
                        sub_mod(next_close[a + s + 1][0], add);
                        sub_mod(next_all[a + s + 1][0], add);
                    }
                }
            }
        }

        memcpy(cur_all, next_all, sizeof(cur_all));
        if (u == 1) {
            memcpy(root_close, next_close, sizeof(root_close));
        }
    }

    int need_before = k - 1;
    int answer = 0;
    for (int a = 0; a <= n; a++) {
        for (int s = 0; s <= n; s++) {
            int val = root_close[a][s];
            if (val < 0) {
                val += MOD;
            }
            if (val == 0) {
                continue;
            }
            int choose_before = need_before - a;
            if (choose_before < 0 || choose_before > s) {
                continue;
            }
            int after_cnt = s - choose_before;
            long long ways = 1LL * val * comb_num[s][choose_before] % MOD;
            ways = ways * fact[need_before] % MOD;
            ways = ways * fact[after_cnt] % MOD;
            add_mod(answer, ways);
        }
    }

    cout << answer % MOD << '\n';
    return 0;
}
