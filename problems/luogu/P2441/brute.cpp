#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    vector<vector<int>> tree(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    for (int i = 0; i < (int)order.size(); ++i) {
        int u = order[i];
        for (int v : tree[u]) {
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            order.push_back(v);
        }
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            int cur = parent[x];
            int ans = -1;

            // 直接沿父链向上找第一个 gcd 大于 1 的祖先。
            while (cur != 0) {
                if (std::gcd(value[cur], value[x]) > 1) {
                    ans = cur;
                    break;
                }
                cur = parent[cur];
            }
            cout << ans << '\n';
        } else {
            int x, y;
            cin >> x >> y;
            value[x] = y;
        }
    }
    return 0;
}
