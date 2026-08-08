#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> x, y;
vector<int> order;  // 0 表示横切，1 表示竖切
long long ans = (1LL << 62);

void dfs(int used_row, int used_col, long long row_piece, long long col_piece, long long cost) {
    if (used_row == n - 1 && used_col == m - 1) {
        ans = min(ans, cost);
        return;
    }

    if (used_row < n - 1) {
        dfs(used_row + 1, used_col, row_piece + 1, col_piece, cost + y[used_row] * col_piece);
    }
    if (used_col < m - 1) {
        dfs(used_row, used_col + 1, row_piece, col_piece + 1, cost + x[used_col] * row_piece);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    y.resize(max(0, n - 1));
    x.resize(max(0, m - 1));

    for (int i = 0; i < n - 1; i++) {
        cin >> y[i];
    }
    for (int i = 0; i < m - 1; i++) {
        cin >> x[i];
    }

    sort(y.begin(), y.end(), greater<long long>());
    sort(x.begin(), x.end(), greater<long long>());

    dfs(0, 0, 1, 1, 0);
    cout << ans << '\n';
    return 0;
}
