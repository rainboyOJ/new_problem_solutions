#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

struct Edge {
    int to;
    int w;
};

int n, k_need;
vector<Edge> g[MAXN];
int dista[MAXN][MAXN];
int choose_black[MAXN]; // choose_black[i] = 0/1，表示第 i 个点染白/染黑
long long ans;

void dfs_dist(int start, int u, int fa, int d) {
    dista[start][u] = d;
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        int w = g[u][i].w;
        if (v == fa) {
            continue;
        }
        dfs_dist(start, v, u, d + w);
    }
}

int calc_black_count() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_black[i] == 1) cnt++;
    }
    return cnt;
}

bool check() {
    return calc_black_count() == k_need;
}

long long calc_answer() {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (choose_black[i] == choose_black[j]) {
                sum += dista[i][j];
            }
        }
    }
    return sum;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            long long value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 第 dep 个点的 01 选择：0 染白，1 染黑。
    for (int i = 0; i <= 1; i++) {
        choose_black[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举哪些点染成黑色，直接统计黑黑点对和白白点对的距离和。
    cin >> n >> k_need;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    for (int i = 1; i <= n; i++) {
        dfs_dist(i, i, 0, 0);
    }

    ans = 0;
    dfs_choose(1);
    cout << ans << '\n';
    return 0;
}
