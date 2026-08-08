// brute.cpp：每次查询直接找出 x 到 y 的唯一路径，然后把路径上所有点的 depth^k 加起来。
// 这个做法复杂度高，只适合小数据理解和对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MOD = 998244353;

int n, m;
vector<int> g[MAXN];
int depth_arr[MAXN];
int parent_arr[MAXN];

void build_depth() {
    vector<int> st;
    st.push_back(1);
    parent_arr[1] = 0;
    depth_arr[1] = 0;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }
            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            st.push_back(v);
        }
    }
}

bool dfs_find(int u, int target, int fa) {
    if (u == target) {
        return true;
    }

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        parent_arr[v] = u;
        if (dfs_find(v, target, u)) {
            return true;
        }
    }
    return false;
}

int power_mod(int a, int k) {
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * a % MOD;
    }
    return (int)res;
}

int query_path_sum(int x, int y, int k) {
    for (int i = 1; i <= n; i++) {
        parent_arr[i] = 0;
    }
    dfs_find(x, y, 0);

    int ans = 0;
    int u = y;
    while (u != x) {
        ans += power_mod(depth_arr[u], k);
        if (ans >= MOD) {
            ans -= MOD;
        }
        u = parent_arr[u];
    }
    ans += power_mod(depth_arr[x], k);
    if (ans >= MOD) {
        ans -= MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        depth_arr[i] = 0;
        parent_arr[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_depth();

    cin >> m;
    while (m--) {
        int x, y, k;
        cin >> x >> y >> k;
        cout << query_path_sum(x, y, k) << '\n';
    }

    return 0;
}
