#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> g;
static vector<int> color;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    color.assign(n + 1, -1);
    int ans = 0;

    for (int s = 1; s <= n; ++s) {
        if (color[s] != -1) {
            continue;
        }

        queue<int> q;
        q.push(s);
        color[s] = 0;
        int cnt[2] = {1, 0};
        bool ok = true;

        while (!q.empty() && ok) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    ++cnt[color[v]];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            cout << "Impossible\n";
            return 0;
        }

        ans += min(cnt[0], cnt[1]);
    }

    cout << ans << '\n';
    return 0;
}
