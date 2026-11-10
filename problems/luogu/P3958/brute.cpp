/**
 * Problem: luogu P3958 - [NOIP 2017 提高组] 奶酪 (Brute Force BFS)
 * Author: rainboy
 * Date: 2026-11-11 00:45
 * Description: 显式建图 + BFS 遍历连通性基准
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;
using int128 = __int128_t;

struct Hole {
    ll x, y, z;
};

int n;
ll h, r;
Hole holes[1005];
vector<int> g[1005];
bool vis[1005];

bool is_connected(const Hole &a, const Hole &b, ll radius) {
    int128 dx = a.x - b.x;
    int128 dy = a.y - b.y;
    int128 dz = a.z - b.z;
    int128 dist_sq = dx * dx + dy * dy + dz * dz;
    int128 limit = static_cast<int128>(2) * radius;
    int128 limit_sq = limit * limit;
    return dist_sq <= limit_sq;
}

void solve_bfs() {
    cin >> n >> h >> r;

    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        vis[i] = false;
        cin >> holes[i].x >> holes[i].y >> holes[i].z;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (holes[i].z <= r) {
            q.push(i);
            vis[i] = true;
        }
        for (int j = i + 1; j <= n; ++j) {
            if (is_connected(holes[i], holes[j], r)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    bool reach_top = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (holes[u].z + r >= h) {
            reach_top = true;
            break;
        }

        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    if (reach_top) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve_bfs();
        }
    }

    return 0;
}
