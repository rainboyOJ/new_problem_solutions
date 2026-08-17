/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
// brute.cpp：小数据暴力解，对每个候选点扫描所有垃圾坐标，检查八个相邻位置。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
long long point_x[MAXN], point_y[MAXN];

// 线性扫描全部垃圾坐标，判断 (x, y) 处是否有垃圾。
bool has_point(long long x, long long y) {
    for (int i = 1; i <= n; i++) {
        if (point_x[i] == x && point_y[i] == y) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> point_x[i] >> point_y[i];
    }

    int answer[5] = {};
    for (int i = 1; i <= n; i++) {
        long long x = point_x[i], y = point_y[i];
        // 先确认四个正交邻居，再统计四个对角邻居作为得分。
        if (!has_point(x - 1, y) || !has_point(x + 1, y)
                || !has_point(x, y - 1) || !has_point(x, y + 1)) {
            continue;
        }
        int score = 0;
        score += has_point(x - 1, y - 1);
        score += has_point(x - 1, y + 1);
        score += has_point(x + 1, y - 1);
        score += has_point(x + 1, y + 1);
        answer[score]++;
    }
    for (int i = 0; i <= 4; i++) cout << answer[i] << '\n';

    return 0;
}