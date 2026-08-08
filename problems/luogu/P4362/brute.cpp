#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);
const int MAXN = 18;

struct Edge {
    int u, v, w;
};

int n, m, k_need;
Edge edges[MAXN];
int color[MAXN];
int choose_big[MAXN];
long long ans;

void brute_two_heads(int u) {
    if (u == n + 1) {
        int big_cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (color[i] == 1) {
                big_cnt++;
            }
        }
        if (big_cnt != k_need) {
            return;
        }

        long long cost = 0;
        for (int i = 1; i < n; i++) {
            if (color[edges[i].u] == color[edges[i].v]) {
                cost += edges[i].w;
            }
        }
        ans = min(ans, cost);
        return;
    }

    if (u == 1) {
        color[u] = 1;
        brute_two_heads(u + 1);
        return;
    }

    color[u] = 0;
    brute_two_heads(u + 1);
    color[u] = 1;
    brute_two_heads(u + 1);
    color[u] = 0;
}

bool outside_is_bipartite() {
    vector<vector<int> > g2(n + 1);
    for (int i = 1; i < n; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (!choose_big[u] && !choose_big[v]) {
            g2[u].push_back(v);
            g2[v].push_back(u);
        }
    }

    vector<int> col(n + 1, -1);
    for (int s = 1; s <= n; s++) {
        if (choose_big[s] || col[s] != -1) {
            continue;
        }
        queue<int> q;
        q.push(s);
        col[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (size_t i = 0; i < g2[u].size(); i++) {
                int v = g2[u][i];
                if (col[v] == -1) {
                    col[v] = col[u] ^ 1;
                    q.push(v);
                } else if (col[v] == col[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void brute_many_heads(int u) {
    if (u == n + 1) {
        int big_cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (choose_big[i]) {
                big_cnt++;
            }
        }
        if (big_cnt != k_need) {
            return;
        }
        if (n - k_need < m - 1) {
            return;
        }
        if (!outside_is_bipartite()) {
            return;
        }

        long long cost = 0;
        for (int i = 1; i < n; i++) {
            if (choose_big[edges[i].u] && choose_big[edges[i].v]) {
                cost += edges[i].w;
            }
        }
        ans = min(ans, cost);
        return;
    }

    if (u == 1) {
        choose_big[u] = 1;
        brute_many_heads(u + 1);
        return;
    }

    choose_big[u] = 0;
    brute_many_heads(u + 1);
    choose_big[u] = 1;
    brute_many_heads(u + 1);
    choose_big[u] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：直接按题意枚举小数据情况，用来对拍。
    cin >> n >> m >> k_need;
    for (int i = 1; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    ans = INF;
    if (m == 2) {
        memset(color, 0, sizeof(color));
        brute_two_heads(1);
    } else {
        memset(choose_big, 0, sizeof(choose_big));
        brute_many_heads(1);
    }
    cout << ans << '\n';
    return 0;
}
