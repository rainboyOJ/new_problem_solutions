// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int T;
int n, m;
vector<int> graph[MAXN];
int indeg[MAXN];
bool used[MAXN];
int cur_order[MAXN], best_order[MAXN];
int best_pos[MAXN];
bool found;

bool better_than_best() {
    int cur_pos[MAXN];
    for (int i = 1; i <= n; i++) {
        cur_pos[cur_order[i]] = i;
    }

    if (!found) {
        return true;
    }

    for (int x = 1; x <= n; x++) {
        if (cur_pos[x] != best_pos[x]) {
            return cur_pos[x] < best_pos[x];
        }
    }
    return false;
}

// 直接枚举所有拓扑序，然后按题目要求比较哪个更优。
void dfs(int dep) {
    if (dep > n) {
        if (better_than_best()) {
            found = true;
            for (int i = 1; i <= n; i++) {
                best_order[i] = cur_order[i];
                best_pos[cur_order[i]] = i;
            }
        }
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (used[i] || indeg[i] != 0) {
            continue;
        }

        used[i] = true;
        cur_order[dep] = i;
        for (int v : graph[i]) {
            indeg[v]--;
        }

        dfs(dep + 1);

        for (int v : graph[i]) {
            indeg[v]++;
        }
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m;

        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            indeg[i] = 0;
            used[i] = false;
        }

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            indeg[v]++;
        }

        found = false;
        dfs(1);

        if (!found) {
            cout << "Impossible!\n";
        } else {
            for (int i = 1; i <= n; i++) {
                if (i > 1) {
                    cout << ' ';
                }
                cout << best_order[i];
            }
            cout << '\n';
        }
    }

    return 0;
}
