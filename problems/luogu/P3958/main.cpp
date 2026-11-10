/**
 * Problem: luogu P3958 - [NOIP 2017 提高组] 奶酪
 * Author: rainboy
 * Date: 2026-11-11 00:45
 * Description: 空间球相交几何模型 + 并查集连通性判定
 */
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

using ll = long long;
using int128 = __int128_t;

const int MAXN = 1005;

struct Hole {
    ll x, y, z;
};

int n;
ll h, r;
Hole holes[MAXN];
int fa[MAXN + 2];

int find_set(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find_set(fa[x]);
}

void union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fa[fx] = fy;
    }
}

// 检查两球是否相切或相交
bool is_connected(const Hole &a, const Hole &b, ll radius) {
    int128 dx = a.x - b.x;
    int128 dy = a.y - b.y;
    int128 dz = a.z - b.z;
    int128 dist_sq = dx * dx + dy * dy + dz * dz;
    int128 limit = static_cast<int128>(2) * radius;
    int128 limit_sq = limit * limit;
    return dist_sq <= limit_sq;
}

void solve() {
    cin >> n >> h >> r;

    int bottom = 0;
    int top = n + 1;

    for (int i = 0; i <= n + 1; ++i) {
        fa[i] = i;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> holes[i].x >> holes[i].y >> holes[i].z;

        // 与下表面相交或相切
        if (holes[i].z <= r) {
            union_set(i, bottom);
        }
        // 与上表面相交或相切
        if (holes[i].z + r >= h) {
            union_set(i, top);
        }
    }

    // 两两球之间连通性判定
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (is_connected(holes[i], holes[j], r)) {
                union_set(i, j);
            }
        }
    }

    if (find_set(bottom) == find_set(top)) {
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
            solve();
        }
    }

    return 0;
}
