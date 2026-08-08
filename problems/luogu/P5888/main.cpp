#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int n, m, k;
vector<int> ids;
vector<pair<int, int> > edges;
vector<vector<int> > in_from; // in_from[v]：哪些特殊点不能把球传给 v
vector<long long> cur_sp, nxt_sp;
int ordinary_cnt;
int start_idx;
long long cur_ordinary, nxt_ordinary;

int get_id(int x) {
    return lower_bound(ids.begin(), ids.end(), x) - ids.begin();
}

int norm(long long x) {
    x %= MOD;
    if (x < 0) {
        x += MOD;
    }
    return (int)x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    ids.push_back(1);

    for (int i = 1; i <= k; i++) {
        int a, b;
        cin >> a >> b;
        if (a == b) {
            // 自己传给自己本来就不允许，这种限制没有额外影响。
            continue;
        }
        edges.push_back(make_pair(a, b));
        ids.push_back(a);
        ids.push_back(b);
    }

    sort(ids.begin(), ids.end());
    ids.erase(unique(ids.begin(), ids.end()), ids.end());

    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    int sp_cnt = (int)ids.size();
    ordinary_cnt = n - sp_cnt;
    start_idx = get_id(1);

    in_from.assign(sp_cnt, vector<int>());
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = get_id(edges[i].first);
        int v = get_id(edges[i].second);
        in_from[v].push_back(u);
    }

    cur_sp.assign(sp_cnt, 0);
    nxt_sp.assign(sp_cnt, 0);
    cur_sp[start_idx] = 1;
    cur_ordinary = 0;

    for (int step = 1; step <= m; step++) {
        long long total = 1LL * ordinary_cnt * cur_ordinary % MOD;
        for (int i = 0; i < sp_cnt; i++) {
            total += cur_sp[i];
            if (total >= MOD) {
                total -= MOD;
            }
        }

        for (int v = 0; v < sp_cnt; v++) {
            long long val = total - cur_sp[v];
            for (int i = 0; i < (int)in_from[v].size(); i++) {
                int u = in_from[v][i];
                val -= cur_sp[u];
            }
            nxt_sp[v] = norm(val);
        }

        nxt_ordinary = norm(total - cur_ordinary);

        cur_sp.swap(nxt_sp);
        cur_ordinary = nxt_ordinary;
    }

    cout << cur_sp[start_idx] % MOD << '\n';
    return 0;
}
