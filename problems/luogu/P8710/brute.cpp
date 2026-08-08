// brute.cpp：直接维护原图，每次发送消息都 BFS 整个连通块。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n, m;
vector<int> graph[MAXN];
long long answer[MAXN];
bool vis[MAXN];

void add_edge(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
}

void spread_message(int start, int value) {
    queue<int> q;
    memset(vis, 0, sizeof(vis));

    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        answer[u] += value;

        for (int v : graph[u]) {
            if (vis[v]) {
                continue;
            }
            vis[v] = true;
            q.push(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        answer[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            add_edge(x, y);
        } else {
            spread_message(x, y);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
