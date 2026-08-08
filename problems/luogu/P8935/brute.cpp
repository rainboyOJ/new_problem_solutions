#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const long long MOD = 1000000007LL;

int n, k, x;
vector<int> g[25];
vector<int> child[25];
int parent_node[25];
int tin[25], tout[25], timer_cnt;

unordered_map<unsigned long long, long long> memo;

void dfs_build(int u, int fa) {
    parent_node[u] = fa;
    tin[u] = ++timer_cnt;
    for (int v : g[u]) {
        if (v == fa) {
            continue;
        }
        child[u].push_back(v);
        dfs_build(v, u);
    }
    tout[u] = timer_cnt;
}

bool in_subtree(int u, int v) {
    return tin[u] <= tin[v] && tin[v] <= tout[u];
}

// mask 表示当前还活着的点集合，step 表示当前是第几次操作。
long long dfs(long long mask, int step) {
    if (((mask >> 0) & 1LL) == 0) {
        return step - 1 >= k ? 1 : 0;
    }

    unsigned long long key = (unsigned long long) mask * 32ULL + (unsigned long long) step;
    unordered_map<unsigned long long, long long>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    long long ans = 0;
    for (int u = 1; u <= n; u++) {
        if (((mask >> (u - 1)) & 1LL) == 0) {
            continue;
        }

        // x 只能在第 k 次被主动选择。
        if ((u == x) != (step == k)) {
            continue;
        }

        // 在第 k 次及以前，不能删掉 x 的祖先来连带剪掉 x。
        if (step <= k && u != x && in_subtree(u, x)) {
            continue;
        }

        long long new_mask = mask;
        for (int v = 1; v <= n; v++) {
            if (((mask >> (v - 1)) & 1LL) == 0) {
                continue;
            }
            if (in_subtree(u, v)) {
                new_mask &= ~(1LL << (v - 1));
            }
        }
        ans += dfs(new_mask, step + 1);
        if (ans >= MOD) {
            ans %= MOD;
        }
    }

    ans %= MOD;
    memo[key] = ans;
    return ans;
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

    dfs_build(1, 0);
    memo.clear();

    long long full_mask = (1LL << n) - 1;
    cout << dfs(full_mask, 1) % MOD << '\n';
    return 0;
}
