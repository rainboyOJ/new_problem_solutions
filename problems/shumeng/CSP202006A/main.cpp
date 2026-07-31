/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:32
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct Point {
    long long x, y;
    char type;
};

int n, query_count;
Point point[MAXN];

int get_sign(long long value) {
    return value > 0 ? 1 : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> query_count;
    for (int i = 1; i <= n; i++) cin >> point[i].x >> point[i].y >> point[i].type;
    while (query_count--) {
        long long theta0, theta1, theta2;
        cin >> theta0 >> theta1 >> theta2;
        int sign_a = 0, sign_b = 0;
        bool correct = true;
        for (int i = 1; i <= n; i++) {
            long long value = theta0 + theta1 * point[i].x + theta2 * point[i].y;
            int sign = get_sign(value);
            int &expected = point[i].type == 'A' ? sign_a : sign_b;
            if (expected == 0) expected = sign;
            else if (expected != sign) correct = false;
        }
        if (sign_a == sign_b) correct = false;
        cout << (correct ? "Yes" : "No") << '\n';
    }

    return 0;
}
