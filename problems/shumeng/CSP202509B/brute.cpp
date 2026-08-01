/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit;
    cin >> n >> limit;
    vector<vector<int> > image(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> image[i][j];
    }

    int pattern[5][9] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
    };
    for (int k = 0; k < limit; k++) {
        bool found = false;
        for (int top = 0; top + 5 <= n && !found; top++) {
            for (int left = 0; left + 9 <= n && !found; left++) {
                bool valid = true;
                for (int i = 0; i < 5 && valid; i++) {
                    for (int j = 0; j < 9; j++) {
                        bool white = image[top + i][left + j] >= k;
                        if ((int)white != pattern[i][j]) {
                            valid = false;
                            break;
                        }
                    }
                }
                if (valid) found = true;
            }
        }
        if (found) cout << k << '\n';
    }
    return 0;
}
