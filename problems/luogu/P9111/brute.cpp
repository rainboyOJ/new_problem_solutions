#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const ll NEG_INF = -(1LL << 60);

int n;
ll d[15];
vector<int> g[15];
int permu[15];
int posi[15];
vector<int> out[15];

// 统计固定删点顺序下的总答案。
ll calc_one_order() {
    for (int i = 1; i <= n; i++) {
        posi[permu[i]] = i;
        out[i].clear();
    }

    // 一条边一定从“更早被删的点”指向“更晚被删的点”。
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (u < v) {
                if (posi[u] < posi[v]) {
                    out[u].push_back(v);
                }
                else {
                    out[v].push_back(u);
                }
            }
        }
    }

    ll total = 0;
    for (int s = 1; s <= n; s++) {
        queue<int> q;
        vector<int> vis(n + 1, 0);
        q.push(s);
        vis[s] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            total += d[s];
            for (int v : out[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        permu[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        int c;
        cin >> c;
        g[i].push_back(c);
        g[c].push_back(i);
    }

    ll ans = NEG_INF;
    sort(permu + 1, permu + n + 1);
    do {
        ans = max(ans, calc_one_order());
    } while (next_permutation(permu + 1, permu + n + 1));

    cout << ans << '\n';
    return 0;
}
