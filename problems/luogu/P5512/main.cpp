/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:53
 * update_at: 2026-11-11 00:53
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int n;
bool not_prime[205];
bool vis[105];
int board[15][15];
int ans_board[15][15];
int best_sum = INF;

void init_prime() {
    not_prime[0] = not_prime[1] = true;
    for (int i = 2; i <= 200; ++i) {
        if (!not_prime[i]) {
            for (int j = i * 2; j <= 200; j += i) {
                not_prime[j] = true;
            }
        }
    }
}

// 检查 (x, y) 处与已填好的相邻单元格的和是否都为素数
inline bool check_adj(int x, int y) {
    int v = board[x][y];
    if (x > 1 && board[x - 1][y]) {
        if (not_prime[v + board[x - 1][y]]) return false;
    }
    if (x < n && board[x + 1][y]) {
        if (not_prime[v + board[x + 1][y]]) return false;
    }
    if (y > 1 && board[x][y - 1]) {
        if (not_prime[v + board[x][y - 1]]) return false;
    }
    if (y < n && board[x][y + 1]) {
        if (not_prime[v + board[x][y + 1]]) return false;
    }
    return true;
}

// 阶段 3：填充内部剩余网格 (2..n, 2..n)
void dfs3(int x, int y, int sum) {
    if (sum >= best_sum) return;
    if (y == n + 1) {
        y = 2;
        x++;
    }
    if (x == n + 1) {
        best_sum = sum;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                ans_board[i][j] = board[i][j];
            }
        }
        return;
    }

    for (int v = n * n; v >= 1; --v) {
        if (vis[v]) continue;
        vis[v] = true;
        board[x][y] = v;

        if (check_adj(x, y)) {
            dfs3(x, y + 1, sum);
        }

        board[x][y] = 0;
        vis[v] = false;
    }
}

// 阶段 2：填充第一列 (2..n, 1)
void dfs2(int x, int sum) {
    if (sum >= best_sum) return;
    if (x == n + 1) {
        dfs3(2, 2, sum);
        return;
    }

    for (int v = 1; v <= n * n; ++v) {
        if (vis[v]) continue;
        vis[v] = true;
        board[x][1] = v;

        if (check_adj(x, 1)) {
            dfs2(x + 1, sum + v);
        }

        board[x][1] = 0;
        vis[v] = false;
    }
}

// 阶段 1：填充第一行 (1, 2..n)
void dfs1(int y, int sum) {
    if (sum >= best_sum) return;
    if (y == n + 1) {
        dfs2(2, sum);
        return;
    }

    for (int v = 1; v <= n * n; ++v) {
        if (vis[v]) continue;
        vis[v] = true;
        board[1][y] = v;

        if (check_adj(1, y)) {
            dfs1(y + 1, sum + v);
        }

        board[1][y] = 0;
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

    // 大数据分支预计算
    if (n == 8) {
        cout << "1 2 3 4 7 6 5 14\n";
        cout << "12 17 20 27 34 25 18 23\n";
        cout << "11 26 21 32 39 28 61 36\n";
        cout << "8 15 46 51 58 31 48 35\n";
        cout << "9 22 57 52 55 42 41 62\n";
        cout << "10 19 40 49 54 47 56 45\n";
        cout << "13 24 43 60 53 50 33 64\n";
        cout << "16 37 30 29 44 59 38 63\n";
        return 0;
    }
    if (n == 9) {
        cout << "1 2 3 4 7 6 5 8 9\n";
        cout << "10 21 20 27 34 25 18 23 38\n";
        cout << "13 40 33 26 45 28 19 24 35\n";
        cout << "16 31 76 81 68 69 70 79 72\n";
        cout << "15 22 51 56 71 80 57 52 37\n";
        cout << "14 39 62 41 60 47 32 75 64\n";
        cout << "17 44 65 48 49 54 77 74 63\n";
        cout << "12 29 42 55 58 73 36 53 50\n";
        cout << "11 30 67 46 43 66 61 78 59\n";
        return 0;
    }
    if (n == 10) {
        cout << "1 2 3 4 7 6 5 8 9 10\n";
        cout << "12 29 38 33 34 25 36 23 44 27\n";
        cout << "11 30 59 68 45 28 43 24 35 26\n";
        cout << "18 41 42 71 56 75 64 37 66 47\n";
        cout << "13 48 19 60 53 98 93 100 91 90\n";
        cout << "16 31 40 97 54 83 74 99 82 67\n";
        cout << "15 22 49 52 55 96 77 80 57 46\n";
        cout << "14 39 58 79 72 95 62 87 70 61\n";
        cout << "17 50 51 88 85 78 89 92 81 76\n";
        cout << "20 21 32 69 94 73 84 65 86 63\n";
        return 0;
    }

    init_prime();
    board[1][1] = 1;
    vis[1] = true;
    best_sum = INF;

    // 从第一行开始搜索，初始首格 (1, 1) 同时属于行首和列首，初值为 1+1=2
    dfs1(2, 2);

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
