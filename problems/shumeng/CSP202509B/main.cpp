/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:20
 */
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

    vector<int> difference(limit + 2, 0);
    for (int top = 0; top + 5 <= n; top++) {
        for (int left = 0; left + 9 <= n; left++) {
            int minimum_white = limit;
            int maximum_black = -1;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 9; j++) {
                    if (pattern[i][j] == 1) {
                        minimum_white = min(minimum_white, image[top + i][left + j]);
                    } else {
                        maximum_black = max(maximum_black, image[top + i][left + j]);
                    }
                }
            }
            int lower = maximum_black + 1;
            int upper = minimum_white;
            if (lower <= upper) {
                difference[lower]++;
                difference[upper + 1]--;
            }
        }
    }

    int active = 0;
    for (int k = 0; k < limit; k++) {
        active += difference[k];
        if (active > 0) cout << k << '\n';
    }
    return 0;
}
