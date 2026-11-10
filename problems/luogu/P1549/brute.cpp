/**
 * Problem: luogu P1549 - [NOIP 1997 提高组] 棋盘问题 (Brute Force)
 * Author: rainboy
 * Date: 2026-11-11 00:30
 * Description: 朴素行优先 DFS 基准实现
 */
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int n;
bool is_prime[205];
bool vis[105];
int board[15][15];
int ans_board[15][15];
int best_sum = INF;

void init_prime() {
    for (int i = 2; i <= 200; ++i) {
        bool prime = true;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                prime = false;
                break;
            }
        }
        is_prime[i] = prime;
    }
}

void dfs_brute(int r, int c) {
    if (r > n) {
        int sum_val = 0;
        for (int i = 1; i <= n; ++i) {
            sum_val += board[1][i] + board[i][1];
        }
        if (sum_val < best_sum) {
            best_sum = sum_val;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    ans_board[i][j] = board[i][j];
                }
            }
        }
        return;
    }

    int nr = (c == n ? r + 1 : r);
    int nc = (c == n ? 1 : c + 1);

    if (r == 1 && c == 1) {
        board[1][1] = 1;
        vis[1] = true;
        dfs_brute(nr, nc);
        vis[1] = false;
        board[1][1] = 0;
        return;
    }

    for (int v = 1; v <= n * n; ++v) {
        if (vis[v]) continue;

        if (r > 1 && !is_prime[board[r - 1][c] + v]) continue;
        if (c > 1 && !is_prime[board[r][c - 1] + v]) continue;

        board[r][c] = v;
        vis[v] = true;

        dfs_brute(nr, nc);

        board[r][c] = 0;
        vis[v] = false;
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

    init_prime();
    dfs_brute(1, 1);

    if (best_sum == INF) {
        cout << "NO\n";
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << ans_board[i][j] << (j == n ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}
