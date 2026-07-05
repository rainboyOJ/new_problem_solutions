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

bool check_current() {
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

void dfs_choose(int pos, int count_chosen) {
    if (count_chosen >= best) {
        return;
    }
    if (pos == n + 1) {
        if (check_current()) {
            best = count_chosen;
        }
        return;
    }

    // 选择 0：不封锁第 pos 个点。
    chosen[pos] = 0;
    dfs_choose(pos + 1, count_chosen);

    // 选择 1：封锁第 pos 个点。
    chosen[pos] = 1;
    dfs_choose(pos + 1, count_chosen + 1);
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
    dfs_choose(1, 0);

    if (best == n + 1) {
        cout << "Impossible\n";
    } else {
        cout << best << '\n';
    }

    return 0;
}
