// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

struct Cow {
    int min_spf;
    int max_spf;
};

int c, l;
Cow cows[MAXN];
vector<int> bottles;
vector<int> graph_edges[MAXN];
int match_to[MAXN];
bool vis[MAXN];

bool dfs_match(int u) {
    for (int i = 0; i < (int)graph_edges[u].size(); i++) {
        int v = graph_edges[u][i];
        if (vis[v]) {
            continue;
        }
        vis[v] = true;
        if (match_to[v] == 0 || dfs_match(match_to[v])) {
            match_to[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> c >> l;
    for (int i = 1; i <= c; i++) {
        cin >> cows[i].min_spf >> cows[i].max_spf;
    }
    for (int i = 1; i <= l; i++) {
        int spf, cover;
        cin >> spf >> cover;
        for (int j = 0; j < cover; j++) {
            bottles.push_back(spf);
        }
    }

    for (int i = 1; i <= c; i++) {
        for (int j = 0; j < (int)bottles.size(); j++) {
            if (cows[i].min_spf <= bottles[j] && bottles[j] <= cows[i].max_spf) {
                graph_edges[i].push_back(j + 1);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= c; i++) {
        memset(vis, false, sizeof(vis));
        if (dfs_match(i)) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
