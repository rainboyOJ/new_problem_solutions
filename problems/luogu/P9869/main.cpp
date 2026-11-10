/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:10
 * update_at: 2026-11-10 23:10
 */
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// 拆点扩展域并查集
struct DSU {
    vector<int> fa;

    DSU(int n = 0) {
        init(n);
    }

    void init(int n) {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// 记录变量当前值的代数表达：
// id > 0: +x_{id}
// id < 0: -x_{|id|}
// id == 0: 常数，具体为 val
struct Value {
    int id;   // 依赖的变量编号（带正负号），0 表示常数
    char val; // 当 id == 0 时的常数取值：'T', 'F', 'U'
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // 初始时每个变量等于自身的初值 +x_i
    vector<Value> cur(n + 1);
    for (int i = 1; i <= n; ++i) {
        cur[i] = {i, ' '};
    }

    for (int k = 0; k < m; ++k) {
        char op;
        cin >> op;
        if (op == 'T' || op == 'F' || op == 'U') {
            int i;
            cin >> i;
            cur[i] = {0, op};
        } else if (op == '+') {
            int i, j;
            cin >> i >> j;
            cur[i] = cur[j];
        } else if (op == '-') {
            int i, j;
            cin >> i >> j;
            if (cur[j].id == 0) {
                char nxt = cur[j].val;
                if (nxt == 'T') nxt = 'F';
                else if (nxt == 'F') nxt = 'T';
                cur[i] = {0, nxt};
            } else {
                cur[i] = {-cur[j].id, ' '};
            }
        }
    }

    // 拆点并查集大小：
    // 1 ~ n: 正点
    // n + 1 ~ 2n: 负点
    // 2n + 1: 常数 U 集合
    // 2n + 2: 常数 T 集合
    // 2n + 3: 常数 F 集合
    int u_node = 2 * n + 1;
    int t_node = 2 * n + 2;
    int f_node = 2 * n + 3;

    DSU dsu(2 * n + 3);

    for (int i = 1; i <= n; ++i) {
        if (cur[i].id == 0) {
            if (cur[i].val == 'U') {
                dsu.unite(i, u_node);
                dsu.unite(i + n, u_node);
            } else if (cur[i].val == 'T') {
                dsu.unite(i, t_node);
                dsu.unite(i + n, f_node);
            } else if (cur[i].val == 'F') {
                dsu.unite(i, f_node);
                dsu.unite(i + n, t_node);
            }
        } else {
            int j = cur[i].id;
            if (j > 0) {
                // x_i = x_j
                dsu.unite(i, j);
                dsu.unite(i + n, j + n);
            } else {
                // x_i = -x_{|j|}
                int real_j = -j;
                dsu.unite(i, real_j + n);
                dsu.unite(i + n, real_j);
            }
        }
    }

    // 检测自相矛盾（正负点连通）或与 T, F 矛盾
    for (int i = 1; i <= n; ++i) {
        if (dsu.same(i, i + n)) {
            dsu.unite(i, u_node);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (dsu.same(i, u_node)) {
            ans++;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, t;
    if (cin >> c >> t) {
        while (t--) {
            solve();
        }
    }

    return 0;
}
