/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 09:46
 * update_at: 2026-07-19 10:29
 */
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;

double coefficient_a, coefficient_b, coefficient_c, coefficient_d;

double polynomial(double x) {
    return ((coefficient_a * x + coefficient_b) * x + coefficient_c) * x + coefficient_d;
}

bool is_zero_at(double x, double value) {
    double absolute_x = fabs(x);
    double scale = ((fabs(coefficient_a) * absolute_x + fabs(coefficient_b)) * absolute_x
                    + fabs(coefficient_c)) * absolute_x + fabs(coefficient_d);
    return fabs(value) <= EPS * scale;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> coefficient_a >> coefficient_b >> coefficient_c >> coefficient_d;

    vector<double> roots;

    for (int integer = -100; integer < 100; integer++) {
        double left = integer;
        double right = integer + 1;
        double left_value = polynomial(left);
        double right_value = polynomial(right);
        bool left_is_root = is_zero_at(left, left_value);
        bool right_is_root = is_zero_at(right, right_value);

        // 整数根只在它作为左端点时记录；右端点根留到下一轮。
        if (left_is_root) {
            roots.push_back(left);
        } else if (!right_is_root && left_value * right_value < 0) {
            for (int iteration = 1; iteration <= 80; iteration++) {
                double middle = (left + right) / 2;
                double middle_value = polynomial(middle);

                if (left_value * middle_value <= 0) {
                    right = middle;
                } else {
                    left = middle;
                    left_value = middle_value;
                }
            }
            roots.push_back((left + right) / 2);
        }
    }

    double right_endpoint_value = polynomial(100.0);
    if (is_zero_at(100.0, right_endpoint_value)) {
        roots.push_back(100.0);
    }

    cout << fixed << setprecision(2);
    for (int i = 0; i < 3; i++) {
        double root = roots[i];
        if (fabs(root) < 0.0005) root = 0.0;
        if (i > 0) cout << ' ';
        cout << root;
    }
    cout << '\n';

    return 0;
}
