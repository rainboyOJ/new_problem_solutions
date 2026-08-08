// brute.cpp：依次删除每个点，重新数连通块，判断它是不是割点。
// 这个做法复杂度较高，只适合小数据理解和对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 50;

struct Edge {
    int u, v;
} edges[MAXM];

int n, m;
vector<int> g[MAXN];
bool vis[MAXN];

void build_graph(int ban) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = false;
    }

    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (u == ban || v == ban) {
            continue;
        }
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void dfs(int u, int ban) {
    vis[u] = true;
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == ban || vis[v]) {
            continue;
        }
        dfs(v, ban);
    }
}

int count_components(int ban) {
    build_graph(ban);

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == ban || vis[i]) {
            continue;
        }
        cnt++;
        dfs(i, ban);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
    }

    int base_cc = count_components(0);
    vector<int> answer;

    for (int i = 1; i <= n; i++) {
        int cc = count_components(i);
        if (cc > base_cc) {
            answer.push_back(i);
        }
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i] << ' ';
    }
    cout << '\n';

    return 0;
}
