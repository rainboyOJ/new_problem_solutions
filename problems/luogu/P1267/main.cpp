#include <bits/stdc++.h>
using namespace std;

const int MAX_FACE = 5;
const int MAXN = 20;
const int MAXPOS = 40;
const int MAXV = 1305;

int n;
int tot;
int mp[MAX_FACE][MAXN][MAXPOS];
int deg_cnt[MAXV];
int g[MAXV][4];
bool has_edge[MAXV][MAXV];

// memo[u][pi][bound]：
// 当前根为 u，父亲是 g[u][pi]，另一个边界值是 bound 时，
// 能形成的最大 BST 节点数。
int memo[MAXV][4][MAXV];

void add_edge(int u, int v) {
    if (has_edge[u][v]) {
        return;
    }
    has_edge[u][v] = true;
    has_edge[v][u] = true;
    g[u][deg_cnt[u]++] = v;
    g[v][deg_cnt[v]++] = u;
}

int find_parent_index(int u, int parent) {
    for (int i = 0; i < deg_cnt[u]; i++) {
        if (g[u][i] == parent) {
            return i;
        }
    }
    return -1;
}

int dp(int u, int bound, int parent) {
    int pi = find_parent_index(u, parent);
    if (memo[u][pi][bound] != 0) {
        return memo[u][pi][bound];
    }

    int left_limit, right_limit;
    if (bound < parent) {
        left_limit = bound;
        right_limit = parent - 1;
    } else {
        left_limit = parent + 1;
        right_limit = bound;
    }

    int best_left = 0;
    int best_right = 0;

    // 父亲已确定后，剩下的最多两个相邻点里，
    // 只需分别挑一个最优左儿子和一个最优右儿子。
    for (int i = 0; i < deg_cnt[u]; i++) {
        int v = g[u][i];
        if (v == parent) {
            continue;
        }
        if (v < left_limit || v > right_limit) {
            continue;
        }
        if (v < u) {
            best_left = max(best_left, dp(v, left_limit, u));
        } else {
            best_right = max(best_right, dp(v, right_limit, u));
        }
    }

    memo[u][pi][bound] = best_left + best_right + 1;
    return memo[u][pi][bound];
}

void build_graph() {
    // 每个面按行存：第 i 行有 2*i-1 个单位三角形。
    for (int face = 1; face <= 4; face++) {
        for (int row = 1; row <= n; row++) {
            for (int col = 1; col <= row * 2 - 1; col++) {
                cin >> mp[face][row][col];
            }
        }
    }

    // 面内相邻。
    for (int face = 1; face <= 4; face++) {
        for (int row = 2; row < n; row++) {
            for (int col = 2; col < row * 2 - 1; col++) {
                int u = mp[face][row][col];
                add_edge(u, mp[face][row][col - 1]);
                add_edge(u, mp[face][row][col + 1]);
                if (col & 1) {
                    add_edge(u, mp[face][row + 1][col + 1]);
                } else {
                    add_edge(u, mp[face][row - 1][col - 1]);
                }
            }
        }
    }

    // 最后一行的内部相邻。
    if (n >= 2) {
        for (int face = 1; face <= 4; face++) {
            for (int col = 2; col <= n * 2 - 1; col += 2) {
                int u = mp[face][n][col];
                add_edge(u, mp[face][n][col - 1]);
                add_edge(u, mp[face][n][col + 1]);
                add_edge(u, mp[face][n - 1][col - 1]);
            }
        }
    }

    // 三个侧面和底面的公共边。
    for (int col = 1; col <= n * 2 - 1; col++) {
        add_edge(mp[1][n][col], mp[4][n - col / 2][1]);
        add_edge(mp[2][n][col], mp[4][col / 2 + 1][(col / 2 + 1) * 2 - 1]);
        add_edge(mp[3][n][col], mp[4][n][n * 2 - col]);
    }

    // 三个侧面的公共棱。
    for (int row = 1; row <= n; row++) {
        add_edge(mp[1][row][1], mp[3][row][row * 2 - 1]);
        add_edge(mp[2][row][1], mp[1][row][row * 2 - 1]);
        add_edge(mp[3][row][1], mp[2][row][row * 2 - 1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    tot = 4 * n * n;

    build_graph();

    int ans = 0;

    // 枚举根节点。根最多选一个左儿子、一个右儿子。
    for (int root = 1; root <= tot; root++) {
        int best_left = 0;
        int best_right = 0;

        for (int i = 0; i < deg_cnt[root]; i++) {
            int v = g[root][i];
            if (v < root) {
                best_left = max(best_left, dp(v, 1, root));
            } else {
                best_right = max(best_right, dp(v, tot, root));
            }
        }

        ans = max(ans, best_left + best_right + 1);
    }

    cout << ans << '\n';
    return 0;
}
