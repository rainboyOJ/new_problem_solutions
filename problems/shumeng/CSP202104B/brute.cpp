/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:01
 */
// brute.cpp：枚举每个像素邻域中的全部格子，直接计算平均值。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, levels, radius, threshold;
    cin >> n >> levels >> radius >> threshold;
    vector<vector<int> > image(n, vector<int>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> image[i][j];
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int total = 0, count = 0;
            for (int x = max(0, i - radius); x <= min(n - 1, i + radius); x++) {
                for (int y = max(0, j - radius); y <= min(n - 1, j + radius); y++) {
                    total += image[x][y];
                    count++;
                }
            }
            if (total <= threshold * count) answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}
