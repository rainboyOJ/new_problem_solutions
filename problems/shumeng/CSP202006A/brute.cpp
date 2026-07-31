/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:32
 */
// brute.cpp：逐条查询、逐点检查两类点是否位于直线的两侧。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    char type;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, query_count;
    cin >> n >> query_count;
    vector<Point> point(n);
    for (int i = 0; i < n; i++) cin >> point[i].x >> point[i].y >> point[i].type;
    while (query_count--) {
        long long theta0, theta1, theta2;
        cin >> theta0 >> theta1 >> theta2;
        int sign_a = 0, sign_b = 0;
        for (int i = 0; i < n; i++) {
            long long value = theta0 + theta1 * point[i].x + theta2 * point[i].y;
            int sign = value > 0 ? 1 : -1;
            if (point[i].type == 'A' && sign_a == 0) sign_a = sign;
            if (point[i].type == 'B' && sign_b == 0) sign_b = sign;
        }
        bool correct = sign_a != sign_b;
        for (int i = 0; i < n; i++) {
            long long value = theta0 + theta1 * point[i].x + theta2 * point[i].y;
            int sign = value > 0 ? 1 : -1;
            if (point[i].type == 'A' && sign != sign_a) correct = false;
            if (point[i].type == 'B' && sign != sign_b) correct = false;
        }
        cout << (correct ? "Yes" : "No") << '\n';
    }

    return 0;
}
