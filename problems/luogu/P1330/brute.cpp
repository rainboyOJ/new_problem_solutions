#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v;
    }

    int best = INT_MAX;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        int cnt = __builtin_popcount((unsigned)mask);

        for (const auto &e : edges) {
            bool pick_u = (mask >> (e.u - 1)) & 1;
            bool pick_v = (mask >> (e.v - 1)) & 1;
            if (!pick_u && !pick_v) {
                ok = false;
                break;
            }
            if (pick_u && pick_v) {
                ok = false;
                break;
            }
        }

        if (ok) {
            best = min(best, cnt);
        }
    }

    if (best == INT_MAX) {
        cout << "Impossible\n";
    } else {
        cout << best << '\n';
    }
    return 0;
}
