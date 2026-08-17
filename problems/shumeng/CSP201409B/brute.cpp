/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:53
 */
// brute.cpp：小数据暴力解，逐个单位格检查是否被任意矩形覆盖。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int x1[105], y1[105], x2[105], y2[105];
    for (int i = 0; i < n; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    int answer = 0;
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            bool covered = false;
            for (int i = 0; i < n; i++) {
                if (x1[i] <= x && x < x2[i] && y1[i] <= y && y < y2[i]) {
                    covered = true;
                    break;
                }
            }
            answer += covered;
        }
    }

    cout << answer << '\n';
    return 0;
}
