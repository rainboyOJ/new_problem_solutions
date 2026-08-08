#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

vector<vector<int> > g;

long long dfs(int u, int fa) {
    long long ret = 1; // 只选当前根
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        ret = ret * (dfs(v, u) + 1) % MOD;
    }
    return ret;
}

long long parse_binary(const string &s) {
    long long x = 0;
    for (size_t i = 0; i < s.size(); i++) {
        x = x * 2 + (s[i] - '0');
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：显式建出小规模完全二叉树，再在真实树上递归统计。
    int T;
    cin >> T;
    while (T--) {
        int dep;
        string s;
        cin >> dep >> s;
        long long last_cnt = parse_binary(s);

        if (dep == 1) {
            cout << 1 << '\n';
            continue;
        }

        vector<long long> exist_pos;
        long long last_begin = 1LL << (dep - 1);
        long long last_end = last_begin + last_cnt - 1;

        long long total_pos = (1LL << dep) - 1;
        vector<int> id(total_pos + 2, 0);
        int tot = 0;

        for (int level = 1; level <= dep - 1; level++) {
            long long l = 1LL << (level - 1);
            long long r = (1LL << level) - 1;
            for (long long pos = l; pos <= r; pos++) {
                id[pos] = ++tot;
            }
        }
        for (long long pos = last_begin; pos <= last_end; pos++) {
            id[pos] = ++tot;
        }

        g.assign(tot + 1, vector<int>());
        for (long long pos = 1; pos <= total_pos; pos++) {
            if (id[pos] == 0) {
                continue;
            }
            long long lc = pos << 1;
            long long rc = lc | 1;
            if (lc <= total_pos && id[lc] != 0) {
                g[id[pos]].push_back(id[lc]);
                g[id[lc]].push_back(id[pos]);
            }
            if (rc <= total_pos && id[rc] != 0) {
                g[id[pos]].push_back(id[rc]);
                g[id[rc]].push_back(id[pos]);
            }
        }

        cout << dfs(1, 0) % MOD << '\n';
    }
    return 0;
}
