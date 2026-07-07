// brute_01_style.cpp：状态搜索风格暴力，枚举每一时刻走哪条边，只适合小数据。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int open;
};

const int MAXN = 105;
const int MAX_TIME = 500;
const long long INF = (1LL << 60);

int n, m, k;
vector<Edge> g[MAXN];
bool seen[MAXN][MAX_TIME + 5];
long long answer;

void dfs(int u, int time_now) {
    if (time_now > MAX_TIME || time_now >= answer) {
        return;
    }

    if (seen[u][time_now]) {
        return;
    }
    seen[u][time_now] = true;

    if (u == n && time_now % k == 0) {
        answer = min(answer, (long long)time_now);
        return;
    }

    // 当前层递归选择下一条要走的道路。不能等待，只能走已经开放的边。
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i].to;
        int open_time = g[u][i].open;
        if (time_now < open_time) {
            continue;
        }
        dfs(v, time_now + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, a;
        cin >> u >> v >> a;
        g[u].push_back({v, a});
    }

    answer = INF;

    // 枚举乘哪一班车到入口：出发时刻必须是 k 的倍数。
    for (int start = 0; start <= MAX_TIME; start += k) {
        memset(seen, 0, sizeof(seen));
        dfs(1, start);
    }

    if (answer == INF) {
        cout << -1 << '\n';
    } else {
        cout << answer << '\n';
    }

    return 0;
}
