#include <bits/stdc++.h>
using namespace std;

const int MAX_FACE = 5;
const int MAXN = 8;
const int MAXPOS = 20;
const int MAXV = 150;

int n;
int tot;
int mp[MAX_FACE][MAXN][MAXPOS];
int deg_cnt[MAXV];
int g[MAXV][4];
bool has_edge[MAXV][MAXV];

unordered_map<unsigned long long, int> memo;

void add_edge(int u, int v) {
    if (has_edge[u][v]) {
        return;
    }
    has_edge[u][v] = true;
    has_edge[v][u] = true;
    g[u][deg_cnt[u]++] = v;
    g[v][deg_cnt[v]++] = u;
}

void build_graph() {
    for (int face = 1; face <= 4; face++) {
        for (int row = 1; row <= n; row++) {
            for (int col = 1; col <= row * 2 - 1; col++) {
                cin >> mp[face][row][col];
            }
        }
    }

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

    for (int col = 1; col <= n * 2 - 1; col++) {
        add_edge(mp[1][n][col], mp[4][n - col / 2][1]);
        add_edge(mp[2][n][col], mp[4][col / 2 + 1][(col / 2 + 1) * 2 - 1]);
        add_edge(mp[3][n][col], mp[4][n][n * 2 - col]);
    }

    for (int row = 1; row <= n; row++) {
        add_edge(mp[1][row][1], mp[3][row][row * 2 - 1]);
        add_edge(mp[2][row][1], mp[1][row][row * 2 - 1]);
        add_edge(mp[3][row][1], mp[2][row][row * 2 - 1]);
    }
}

unsigned long long encode_state(int u, int parent, int low, int high) {
    unsigned long long key = 0;
    key = (unsigned long long) u;
    key = key * 256ULL + (unsigned long long) parent;
    key = key * 256ULL + (unsigned long long) low;
    key = key * 256ULL + (unsigned long long) high;
    return key;
}

// brute.cpp：直接按 BST 定义搜索。
// 状态显式带上下界，写法更直观，但只适合小数据。
int dfs(int u, int parent, int low, int high) {
    unsigned long long key = encode_state(u, parent, low, high);
    unordered_map<unsigned long long, int>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    int best_left = 0;
    int best_right = 0;
    for (int i = 0; i < deg_cnt[u]; i++) {
        int v = g[u][i];
        if (v == parent) {
            continue;
        }
        if (v < low || v > high) {
            continue;
        }
        if (v < u) {
            best_left = max(best_left, dfs(v, u, low, u - 1));
        } else if (v > u) {
            best_right = max(best_right, dfs(v, u, u + 1, high));
        }
    }

    int res = best_left + best_right + 1;
    memo[key] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    tot = 4 * n * n;

    build_graph();

    int ans = 0;
    for (int root = 1; root <= tot; root++) {
        ans = max(ans, dfs(root, 0, 1, tot));
    }

    cout << ans << '\n';
    return 0;
}
