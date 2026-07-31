/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:35
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int> > code(n + 1, vector<int>(m));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) cin >> code[i][j];
    }

    for (int i = 1; i <= n; i++) {
        int parent = 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            bool greater = true;
            for (int k = 0; k < m; k++) {
                if (code[j][k] <= code[i][k]) {
                    greater = false;
                    break;
                }
            }
            if (greater) {
                parent = j;
                break;
            }
        }
        cout << parent << '\n';
    }

    return 0;
}
