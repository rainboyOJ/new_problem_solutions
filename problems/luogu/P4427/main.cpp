#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300000 + 5;
const int MAXM = 600000 + 5;
const int LOG = 20;
const int MAXK = 50;
const int MOD = 998244353;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

int depth_arr[MAXN];
int up[MAXN][LOG];
int sum_pow[MAXN][MAXK + 1];  // 根到当前点路径上，depth^k 的前缀和

void init_graph(int n) {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        depth_arr[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
        }
        for (int k = 1; k <= MAXK; k++) {
            sum_pow[i][k] = 0;
        }
    }
}

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void build_lca_and_prefix(int root) {
    vector<int> st;
    st.push_back(root);

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;
            }

            up[v][0] = u;
            depth_arr[v] = depth_arr[u] + 1;

            for (int j = 1; j < LOG; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }

            long long pw = 1;
            for (int k = 1; k <= MAXK; k++) {
                pw = pw * depth_arr[v] % MOD;
                sum_pow[v][k] = sum_pow[u][k] + (int)pw;
                if (sum_pow[v][k] >= MOD) {
                    sum_pow[v][k] -= MOD;
                }
            }

            st.push_back(v);
        }
    }
}

int kth_ancestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    return u;
}

int lca(int a, int b) {
    if (depth_arr[a] < depth_arr[b]) {
        swap(a, b);
    }

    a = kth_ancestor(a, depth_arr[a] - depth_arr[b]);
    if (a == b) {
        return a;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    init_graph(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    build_lca_and_prefix(1);

    cin >> m;
    while (m--) {
        int x, y, k;
        cin >> x >> y >> k;

        int p = lca(x, y);

        long long depth_pow = 1;
        for (int i = 1; i <= k; i++) {
            depth_pow = depth_pow * depth_arr[p] % MOD;
        }

        int ans = sum_pow[x][k];
        ans += sum_pow[y][k];
        if (ans >= MOD) {
            ans -= MOD;
        }

        ans -= 2LL * sum_pow[p][k] % MOD;
        if (ans < 0) {
            ans += MOD;
        }
        ans += depth_pow;
        if (ans >= MOD) {
            ans -= MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}
