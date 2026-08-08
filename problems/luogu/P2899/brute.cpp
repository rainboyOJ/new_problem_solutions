#include <bits/stdc++.h>
using namespace std;

const int MAXN = 22;

int n;
vector<int> g[MAXN];
int choose_tower[MAXN]; // choose_tower[i] = 0/1，表示第 i 个点不放塔/放塔
int ans;

int calc_tower_count() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_tower[i] == 1) cnt++;
    }
    return cnt;
}

bool check() {
    for (int i = 1; i <= n; i++) {
        bool covered = choose_tower[i] == 1;
        for (size_t j = 0; j < g[i].size(); j++) {
            if (choose_tower[g[i][j]] == 1) {
                covered = true;
                break;
            }
        }
        if (!covered) {
            return false;
        }
    }
    return true;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_tower_count();
            if (ans > value) ans = value;
        }
        return;
    }

    // 第 dep 个点的 01 选择：0 不放塔，1 放塔。
    for (int i = 0; i <= 1; i++) {
        choose_tower[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举哪些点放塔，直接检查是否覆盖整棵树。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        choose_tower[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ans = n;
    dfs_choose(1);
    cout << ans << '\n';
    return 0;
}
