/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:11
 */
// brute.cpp：对每个候选点扫描所有垃圾坐标，检查八个相邻位置。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

bool has_point(const vector<Point> &points, long long x, long long y) {
    for (int i = 0; i < (int)points.size(); i++) {
        if (points[i].x == x && points[i].y == y) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
    int answer[5] = {};
    for (int i = 0; i < n; i++) {
        long long x = points[i].x, y = points[i].y;
        if (!has_point(points, x - 1, y) || !has_point(points, x + 1, y)
                || !has_point(points, x, y - 1) || !has_point(points, x, y + 1)) continue;
        int score = 0;
        score += has_point(points, x - 1, y - 1);
        score += has_point(points, x - 1, y + 1);
        score += has_point(points, x + 1, y - 1);
        score += has_point(points, x + 1, y + 1);
        answer[score]++;
    }
    for (int i = 0; i <= 4; i++) cout << answer[i] << '\n';

    return 0;
}
