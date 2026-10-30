#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005;

int n, q;
int fa[MAXN];
vector<int> children[MAXN];
int bfs_order[MAXN];
int sz[MAXN];
int heavy[MAXN];
int ans[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> q)) return 0;

    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
        children[fa[i]].push_back(i);
    }

    // BFS 遍历生成拓扑序，避免深层递归爆栈
    int head = 0, tail = 0;
    bfs_order[tail++] = 1;
    while (head < tail) {
        int u = bfs_order[head++];
        for (int v : children[u]) {
            bfs_order[tail++] = v;
        }
    }

    // 逆序处理（从叶子到根自底向上）
    for (int i = n - 1; i >= 0; --i) {
        int u = bfs_order[i];
        sz[u] = 1;
        heavy[u] = 0;
        for (int v : children[u]) {
            sz[u] += sz[v];
            if (sz[v] > sz[heavy[u]]) {
                heavy[u] = v;
            }
        }

        if (heavy[u] == 0) {
            ans[u] = u;
        } else {
            int c = ans[heavy[u]];
            // 只要上方连通块大小超过一半，即 2 * sz[c] < sz[u]，就往上跳
            while (2 * sz[c] < sz[u]) {
                c = fa[c];
            }
            ans[u] = c;
        }
    }

    while (q--) {
        int v;
        cin >> v;
        cout << ans[v] << "\n";
    }

    return 0;
}
