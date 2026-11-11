#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            // 转为 0-based 数值，方便索引
            a[i][j]--;
        }
    }

    // 暴力枚举两两配对
    for (int i = 0; i < n; ++i) {
        int max_beauty = 0;
        for (int j = 0; j < n; ++j) {
            int cur_beauty = 0;
            for (int k = 0; k < m; ++k) {
                // 根据乘法定义：第 k 个位置的值是 a[j][a[i][k]]
                if (a[j][a[i][k]] == k) {
                    cur_beauty++;
                } else {
                    break;
                }
            }
            max_beauty = max(max_beauty, cur_beauty);
        }
        cout << max_beauty << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
