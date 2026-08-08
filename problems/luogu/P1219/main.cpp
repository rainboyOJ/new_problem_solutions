#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXD = 40;

int n;
int pos[MAXN];          // pos[i]：第 i 行的皇后放在哪一列
int used_col[MAXN];     // 列是否已经被占用
int used_diag1[MAXD];   // 主对角线 row - col + n
int used_diag2[MAXD];   // 副对角线 row + col
long long total_ans;
int printed_cnt;

void print_solution() {
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << pos[i];
    }
    cout << '\n';
}

void dfs(int row) {
    if (row > n) {
        total_ans++;
        if (printed_cnt < 3) {
            print_solution();
            printed_cnt++;
        }
        return;
    }

    for (int col = 1; col <= n; col++) {
        int d1 = row - col + n;
        int d2 = row + col;
        if (used_col[col] || used_diag1[d1] || used_diag2[d2]) {
            continue;
        }

        pos[row] = col;
        used_col[col] = 1;
        used_diag1[d1] = 1;
        used_diag2[d2] = 1;

        dfs(row + 1);

        used_col[col] = 0;
        used_diag1[d1] = 0;
        used_diag2[d2] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    total_ans = 0;
    printed_cnt = 0;
    memset(used_col, 0, sizeof(used_col));
    memset(used_diag1, 0, sizeof(used_diag1));
    memset(used_diag2, 0, sizeof(used_diag2));

    dfs(1);
    cout << total_ans << '\n';

    return 0;
}
