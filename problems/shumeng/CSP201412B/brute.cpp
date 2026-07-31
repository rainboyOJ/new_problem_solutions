/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:30
 */
// brute.cpp：小数据暴力解，逐条副对角线收集元素后按方向输出。
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

    vector<int> answer;
    for (int sum = 0; sum <= 2 * n - 2; sum++) {
        vector<int> diagonal;
        for (int row = 0; row < n; row++) {
            int column = sum - row;
            if (0 <= column && column < n) {
                diagonal.push_back(matrix[row][column]);
            }
        }
        if (sum % 2 == 0) reverse(diagonal.begin(), diagonal.end());
        answer.insert(answer.end(), diagonal.begin(), diagonal.end());
    }

    for (int i = 0; i < (int)answer.size(); i++) {
        if (i > 0) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
