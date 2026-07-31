/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:30
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int> > matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    bool first = true;
    for (int sum = 0; sum <= 2 * n - 2; sum++) {
        int low = max(0, sum - n + 1);
        int high = min(n - 1, sum);
        if (sum % 2 == 0) {
            for (int row = high; row >= low; row--) {
                if (!first) cout << ' ';
                first = false;
                cout << matrix[row][sum - row];
            }
        } else {
            for (int row = low; row <= high; row++) {
                if (!first) cout << ' ';
                first = false;
                cout << matrix[row][sum - row];
            }
        }
    }
    cout << '\n';
    return 0;
}
