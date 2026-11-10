/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:53
 * update_at: 2026-11-11 00:53
 */
#include <iostream>
#include <vector>

using namespace std;

// 暴力版本：朴素从左到右、从上到下逐格递归搜索
int n;
int g[10][10];
bool vis[105];
int ans_g[10][10];
int best_val = 1e9;

bool is_p(int v) {
    if (v < 2) return false;
    for (int i = 2; i * i <= v; ++i) {
        if (v % i == 0) return false;
    }
    return true;
}

bool valid(int r, int c) {
    if (r > 1 && g[r - 1][c] && !is_p(g[r][c] + g[r - 1][c])) return false;
    if (c > 1 && g[r][c - 1] && !is_p(g[r][c] + g[r][c - 1])) return false;
    return true;
}

void dfs(int r, int c) {
    if (r == n + 1) {
        int sum_val = 0;
        for (int i = 1; i <= n; ++i) sum_val += g[1][i] + g[i][1];
        if (sum_val < best_val) {
            best_val = sum_val;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    ans_g[i][j] = g[i][j];
                }
            }
        }
        return;
    }

    int next_r = (c == n ? r + 1 : r);
    int next_c = (c == n ? 1 : c + 1);

    for (int v = 1; v <= n * n; ++v) {
        if (vis[v]) continue;
        g[r][c] = v;
        if (valid(r, c)) {
            vis[v] = true;
            dfs(next_r, next_c);
            vis[v] = false;
        }
        g[r][c] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    if (n == 1) {
        cout << "NO\n";
        return 0;
    }

    g[1][1] = 1;
    vis[1] = true;
    dfs(1, 2);

    if (best_val == 1e9) {
        cout << "NO\n";
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << ans_g[i][j] << (j == n ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}
