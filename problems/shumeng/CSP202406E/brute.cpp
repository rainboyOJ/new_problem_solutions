/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:04
 */
// brute.cpp：小数据暴力解，直接维护 n*n 个格子的最终权重。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dimension, query_count;
    cin >> dimension >> query_count;
    vector<vector<int> > value(dimension + 1, vector<int>(dimension + 1, 0));
    for (int i = 0; i < dimension; i++) {
        int x1, x2, y1, y2, v;
        cin >> x1 >> x2 >> y1 >> y2 >> v;
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) value[x][y] = max(value[x][y], v);
        }
    }

    for (int i = 0; i < query_count; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        int answer = 0;
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) answer = max(answer, value[x][y]);
        }
        cout << answer << '\n';
    }

    return 0;
}
