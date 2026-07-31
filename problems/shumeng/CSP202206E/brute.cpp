/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:21
 */
// brute.cpp：小数据暴力解，逐点执行每次仿射变换，用来辅助对拍。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

int n, query_count;
vector<Point> point;

void translate(int left, int right, long double x, long double y) {
    for (int i = left; i <= right; i++) {
        point[i].x += x;
        point[i].y += y;
    }
}

void rotate_point(int left, int right, long double x, long double y, long double theta) {
    long double c = cos(theta), s = sin(theta);
    for (int i = left; i <= right; i++) {
        long double old_x = point[i].x - x;
        long double old_y = point[i].y - y;
        point[i].x = c * old_x - s * old_y + x;
        point[i].y = s * old_x + c * old_y + y;
    }
}

void scale_point(int left, int right, long double x, long double y, long double lambda) {
    for (int i = left; i <= right; i++) {
        point[i].x = x + lambda * (point[i].x - x);
        point[i].y = y + lambda * (point[i].y - y);
    }
}

void line_transform(int left, int right, long double theta, long double y0, bool projection) {
    long double c = cos(theta), s = sin(theta);
    long double m00, m01, m10, m11;
    if (projection) {
        m00 = c * c;
        m01 = c * s;
        m10 = c * s;
        m11 = s * s;
    } else {
        m00 = c * c - s * s;
        m01 = 2 * c * s;
        m10 = 2 * c * s;
        m11 = s * s - c * c;
    }
    long double vx = -m01 * y0;
    long double vy = y0 - m11 * y0;
    for (int i = left; i <= right; i++) {
        long double old_x = point[i].x;
        long double old_y = point[i].y;
        point[i].x = m00 * old_x + m01 * old_y + vx;
        point[i].y = m10 * old_x + m11 * old_y + vy;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> query_count;
    point.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> point[i].x >> point[i].y;

    cout << fixed << setprecision(12);
    while (query_count--) {
        int type, left, right;
        cin >> type >> left >> right;
        if (type == 1) {
            long double a, b;
            cin >> a >> b;
            translate(left, right, a, b);
        } else if (type == 2) {
            long double a, b, theta;
            cin >> a >> b >> theta;
            rotate_point(left, right, a, b, theta);
        } else if (type == 3) {
            long double a, b, lambda;
            cin >> a >> b >> lambda;
            scale_point(left, right, a, b, lambda);
        } else if (type == 4 || type == 5) {
            long double theta, y0;
            cin >> theta >> y0;
            line_transform(left, right, theta, y0, type == 5);
        } else if (type == 6) {
            long double sx = 0, sy = 0;
            for (int i = left; i <= right; i++) {
                sx += point[i].x;
                sy += point[i].y;
            }
            long double count = right - left + 1;
            cout << sx / count << ' ' << sy / count << '\n';
        } else {
            long double a, b, answer = 0;
            cin >> a >> b;
            for (int i = left; i <= right; i++) {
                long double dx = point[i].x - a;
                long double dy = point[i].y - b;
                answer += dx * dx + dy * dy;
            }
            cout << answer << '\n';
        }
    }

    return 0;
}
