#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举每个罪犯分到哪座监狱，只适合小数据对拍。

const int MAXN = 25;
const int MAXM = 405;

struct Edge {
    int u, v, w;
};

int n, m;
Edge edge[MAXM];
int belong[MAXN]; // belong[i] 表示第 i 个罪犯所在监狱，取 0 或 1。
int answer;

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
}

void dfs(int pos) {
    if (pos == n + 1) {
        int worst = 0;
        for (int i = 1; i <= m; i++) {
            if (belong[edge[i].u] == belong[edge[i].v]) {
                worst = max(worst, edge[i].w);
            }
        }
        answer = min(answer, worst);
        return;
    }

    belong[pos] = 0;
    dfs(pos + 1);
    belong[pos] = 1;
    dfs(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    answer = 1000000000;
    dfs(1);
    cout << answer << '\n';

    return 0;
}
