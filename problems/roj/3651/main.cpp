/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:01
 * update_at: 2026-10-06 16:01
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // n <= 1000

struct Hole {
    ll x, y, z;
} a[MAXN]; // 按 z 排序后的球心

int fa[MAXN + 2]; // 并查集父节点，额外 2 个给下表面和上表面

int find_root(int x) {
    int r = x;
    while (fa[r] != r) r = fa[r];
    while (fa[x] != x) {
        int p = fa[x];
        fa[x] = r;
        x = p;
    }
    return r;
}

void unite(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx != ry) fa[ry] = rx;
}

bool cmp_z(const Hole &p, const Hole &q) {
    return p.z < q.z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        ll h, r;
        cin >> n >> h >> r;
        for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y >> a[i].z;

        sort(a, a + n, cmp_z); // 按 z 升序，用于 z 窗口剪枝

        int bottom = n;
        int top = n + 1;
        for (int i = 0; i < n + 2; i++) fa[i] = i;

        for (int i = 0; i < n; i++) {
            if (a[i].z <= r) unite(bottom, i);       // 与下表面相连
            if (a[i].z + r >= h) unite(top, i);        // 与上表面相连
        }

        ll reach = 2 * r;          // 球心 z 差超过 2r 不可能相交
        __int128 limit = (__int128)4 * r * r; // 球心距离平方上限
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[j].z - a[i].z > reach) break; // z 差已经太大，后面更大
                __int128 dx = a[j].x - a[i].x;
                __int128 dy = a[j].y - a[i].y;
                __int128 dz = a[j].z - a[i].z;
                __int128 dist2 = dx * dx + dy * dy + dz * dz;
                if (dist2 <= limit) unite(i, j);
            }
        }

        cout << (find_root(bottom) == find_root(top) ? "Yes" : "No") << '\n';
    }
    return 0;
}
