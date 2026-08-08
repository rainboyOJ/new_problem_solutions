#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举小数据所有点集，检查是否连通。

const int MAXN = 22;

int n;
int beauty[MAXN];
bool edge_exists[MAXN][MAXN];

bool connected_subset(int mask) {
    int start = -1;
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) != 0) {
            start = i;
            break;
        }
    }
    if (start == -1) {
        return false;
    }

    queue<int> que;
    bool visited[MAXN] = {false};
    visited[start] = true;
    que.push(start);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v = 0; v < n; v++) {
            if ((mask & (1 << v)) != 0 && edge_exists[u + 1][v + 1] && !visited[v]) {
                visited[v] = true;
                que.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) != 0 && !visited[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> beauty[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edge_exists[u][v] = true;
        edge_exists[v][u] = true;
    }

    int answer = -1000000000;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (!connected_subset(mask)) {
            continue;
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) != 0) {
                sum += beauty[i + 1];
            }
        }
        answer = max(answer, sum);
    }
    cout << answer << '\n';

    return 0;
}
