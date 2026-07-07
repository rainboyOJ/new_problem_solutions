// brute_01_style.cpp：01 序列风格暴力，按点编号依次决定选或不选。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
};

const int MAXN = 25;

int n, m;
vector<Edge> edges;
int chosen[MAXN]; // chosen[i] 表示第 i 个点是否被封锁。
int best;

bool check() {
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        // 每条边必须恰好有一个端点被选。
        if (chosen[u] == chosen[v]) {
            return false;
        }
    }
    return true;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (chosen[i] == 1) cnt++;
    }
    return cnt;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (best > value) best = value;
        }
        return;
    }

    // 第 dep 个点的 01 选择：0 不封锁，1 封锁。
    for (int i = 0; i <= 1; i++) {
        chosen[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v;
    }

    best = n + 1;
    dfs_choose(1);

    if (best == n + 1) {
        cout << "Impossible\n";
    } else {
        cout << best << '\n';
    }

    return 0;
}
