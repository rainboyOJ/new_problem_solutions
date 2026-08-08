#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int T;
int n;
int a[MAXN][MAXN];
vector<int> g[MAXN];
int match_col[MAXN];  // match_col[j] 表示第 j 列当前匹配了哪一行
int vis[MAXN];        // vis[j] 表示这一轮增广里，第 j 列是否已经尝试过

// 尝试给第 u 行找一个可用的列。
bool dfs(int u) {
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (vis[v]) {
            continue;
        }
        vis[v] = 1;

        // 如果这一列还没人占，或者原来占着它的那一行
        // 还能换到别的列，那么就把这一列分配给当前行。
        if (match_col[v] == 0 || dfs(match_col[v])) {
            match_col[v] = u;
            return true;
        }
    }
    return false;
}

void init_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 1) {
                g[i].push_back(j);
            }
        }
    }
}

bool solve_case() {
    memset(match_col, 0, sizeof(match_col));

    int match_cnt = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) {
            match_cnt++;
        }
    }
    return match_cnt == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        init_case();
        if (solve_case()) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
