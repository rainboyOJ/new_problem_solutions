// brute.cpp：每次在树上直接找两点间的唯一路径长度，然后顺着路线累加。
// 这个做法最贴近题意，但每次都重新搜索路径，只适合小数据验证。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
vector<int> g[MAXN];
int parent_arr[MAXN];

bool dfs_find(int u, int target, int fa) {
    if (u == target) {
        return true;
    }

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        parent_arr[v] = u;
        if (dfs_find(v, target, u)) {
            return true;
        }
    }
    return false;
}

int dist(int u, int v) {
    for (int i = 1; i <= n; i++) {
        parent_arr[i] = 0;
    }

    dfs_find(u, v, 0);

    int len = 0;
    int x = v;
    while (x != u) {
        len++;
        x = parent_arr[x];
    }
    return len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int m;
    cin >> m;

    long long answer = 0;
    int last = 1;

    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        answer += dist(last, x);
        last = x;
    }

    cout << answer << '\n';

    return 0;
}
