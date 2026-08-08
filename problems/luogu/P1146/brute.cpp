#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int all = (1 << n) - 1;
    vector<int> dist(1 << n, -1), pre(1 << n, -1), op(1 << n, -1);
    queue<int> q;
    q.push(0);
    dist[0] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == all) break;

        for (int keep = 0; keep < n; keep++) {
            int flip_mask = all ^ (1 << keep);
            int v = u ^ flip_mask;
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            pre[v] = u;
            op[v] = keep;
            q.push(v);
        }
    }

    vector<int> path;
    for (int cur = all; cur != 0; cur = pre[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    cout << path.size() << '\n';
    for (int state : path) {
        for (int i = 0; i < n; i++) {
            cout << ((state >> i) & 1);
        }
        cout << '\n';
    }

    return 0;
}
