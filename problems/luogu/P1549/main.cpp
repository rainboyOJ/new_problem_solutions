/**
 * Problem: luogu P1549 - [NOIP 1997 提高组] 棋盘问题
 * Author: rainboy
 * Date: 2026-11-11 00:30
 * Description: 首行首列定序启发式回溯 + 质数相邻剪枝
 */
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int n;
bool is_prime[205];
bool vis[105];
int board[15][15];
int ans_board[15][15];
int best_sum = INF;

struct Pos {
    int r, c;
};

vector<Pos> order;

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

void dfs(int idx, int cur_sum) {
    if (cur_sum >= best_sum) return;

    if (idx == n * n) {
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

    int r = order[idx].r;
    int c = order[idx].c;

    for (int v = 1; v <= n * n; ++v) {
        if (vis[v]) continue;

        // 检查与上方已填单元格之和是否为素数
        if (r > 1 && board[r - 1][c] != 0) {
            if (!is_prime[board[r - 1][c] + v]) continue;
        }
        // 检查与下方已填单元格之和是否为素数
        if (r < n && board[r + 1][c] != 0) {
            if (!is_prime[board[r + 1][c] + v]) continue;
        }
        // 检查与左方已填单元格之和是否为素数
        if (c > 1 && board[r][c - 1] != 0) {
            if (!is_prime[board[r][c - 1] + v]) continue;
        }
        // 检查与右方已填单元格之和是否为素数
        if (c < n && board[r][c + 1] != 0) {
            if (!is_prime[board[r][c + 1] + v]) continue;
        }

        board[r][c] = v;
        vis[v] = true;

        int add_cost = 0;
        if (r == 1) add_cost += v;
        if (c == 1) add_cost += v;

        dfs(idx + 1, cur_sum + add_cost);

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

    // 搜索顺序：优先填第一行，再填第一列，再填其余内部方格
    for (int j = 1; j <= n; ++j) order.push_back({1, j});
    for (int i = 2; i <= n; ++i) order.push_back({i, 1});
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            order.push_back({i, j});
        }
    }

    // 左上角固定为 1
    board[1][1] = 1;
    vis[1] = true;

    // 从 index 1 开始搜索
    dfs(1, 2); // board[1][1] 同时属于第一行和第一列，初始贡献为 1 + 1 = 2

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
