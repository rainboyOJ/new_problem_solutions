// brute.cpp：依次删边，再重新判断图是否仍然连通。
// 这个做法复杂度较高，只适合小数据理解题意和辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 50;

struct Edge {
    int u, v;
} edges[MAXM];

struct EdgeAnswer {
    int u, v;

    bool operator<(const EdgeAnswer &other) const {
        if (u != other.u) {
            return u < other.u;
        }
        return v < other.v;
    }
};

int n, m;
vector<int> g[MAXN];
bool vis[MAXN];
vector<EdgeAnswer> answer;

void dfs(int u) {
    vis[u] = true;
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!vis[v]) {
            dfs(v);
        }
    }
}

// 删掉第 ban 条边后，检查整张图是否仍然连通。
bool connected_without(int ban) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = false;
    }

    for (int i = 1; i <= m; i++) {
        if (i == ban) {
            continue;
        }
        g[edges[i].u].push_back(edges[i].v);
        g[edges[i].v].push_back(edges[i].u);
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
    }

    for (int i = 1; i <= m; i++) {
        if (!connected_without(i)) {
            int a = edges[i].u;
            int b = edges[i].v;
            if (a > b) {
                swap(a, b);
            }
            answer.push_back({a, b});
        }
    }

    sort(answer.begin(), answer.end());
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].u << ' ' << answer[i].v << '\n';
    }

    return 0;
}
