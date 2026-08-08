#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long MOD = 1000000007LL;

struct Edge {
    int to;
    int id;
};

int case_id, T;
int n, k;
int degree_cnt[MAXN];
bool is_key[MAXN];
long long fact[MAXN], inv_num[MAXN];
long long weight_node[MAXN];
long long f[MAXN], g[MAXN];
int parent_node[MAXN], parent_edge[MAXN];
vector<Edge> tree[MAXN];
vector<int> order_list;

long long power_mod(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1LL) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

void prepare_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    for (int i = 1; i < MAXN; i++) {
        inv_num[i] = power_mod(i, MOD - 2);
    }
}

void clear_case() {
    for (int i = 1; i <= n; i++) {
        tree[i].clear();
        degree_cnt[i] = 0;
        f[i] = g[i] = 0;
        parent_node[i] = parent_edge[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        is_key[i] = false;
    }
    order_list.clear();
}

void build_rooted_tree() {
    order_list.clear();
    order_list.push_back(1);
    parent_node[1] = 0;
    parent_edge[1] = 0;

    for (int i = 0; i < (int)order_list.size(); i++) {
        int u = order_list[i];
        for (int j = 0; j < (int)tree[u].size(); j++) {
            int v = tree[u][j].to;
            int id = tree[u][j].id;
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            parent_edge[v] = id;
            order_list.push_back(v);
        }
    }
}

long long solve_one() {
    long long base = 1;
    for (int i = 1; i <= n; i++) {
        base = base * fact[degree_cnt[i] - 1] % MOD;
        if (degree_cnt[i] <= 1) {
            weight_node[i] = 1;
        } else {
            weight_node[i] = inv_num[degree_cnt[i] - 1];
        }
    }

    build_rooted_tree();

    for (int idx = (int)order_list.size() - 1; idx >= 0; idx--) {
        int u = order_list[idx];
        long long sum_g = 0;
        long long sum_square = 0;
        f[u] = 0;

        for (int j = 0; j < (int)tree[u].size(); j++) {
            int v = tree[u][j].to;
            if (parent_node[v] != u) {
                continue;
            }
            f[u] += f[v];
            if (f[u] >= MOD) {
                f[u] -= MOD;
            }
            sum_g += g[v];
            if (sum_g >= MOD) {
                sum_g -= MOD;
            }
            sum_square = (sum_square + g[v] * g[v]) % MOD;
        }

        long long pair_sum = (sum_g * sum_g % MOD - sum_square + MOD) % MOD;
        pair_sum = pair_sum * inv_num[2] % MOD * weight_node[u] % MOD;
        f[u] = (f[u] + pair_sum) % MOD;

        if (is_key[parent_edge[u]]) {
            f[u] = (f[u] + sum_g * weight_node[u]) % MOD;
            g[u] = 1;
        } else {
            g[u] = sum_g * weight_node[u] % MOD;
        }
    }

    long long choose_one = k % MOD;
    long long multiplier = (choose_one - f[1] + MOD) % MOD;
    return base * multiplier % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    prepare_factorials();

    cin >> case_id >> T;
    while (T--) {
        cin >> n >> k;
        clear_case();

        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back((Edge){v, i});
            tree[v].push_back((Edge){u, i});
            degree_cnt[u]++;
            degree_cnt[v]++;
        }

        for (int i = 1; i <= k; i++) {
            int id;
            cin >> id;
            is_key[id] = true;
        }

        cout << solve_one() << '\n';
    }

    return 0;
}
