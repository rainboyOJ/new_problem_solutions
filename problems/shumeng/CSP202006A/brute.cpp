/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，两遍扫描先确定每类代表符号，再验证所有点。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, query_count;
long long x[MAXN], y[MAXN];   // 点的横坐标、纵坐标
char type[MAXN];              // 点的类别：A 或 B

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> query_count;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i] >> type[i];

    while (query_count--) {
        long long theta0, theta1, theta2;
        cin >> theta0 >> theta1 >> theta2;

        // 第一遍：确定 A、B 两类各自的代表符号
        int sign_a = 0, sign_b = 0;
        for (int i = 1; i <= n; i++) {
            long long value = theta0 + theta1 * x[i] + theta2 * y[i];
            int sign = value > 0 ? 1 : -1;
            if (type[i] == 'A' && sign_a == 0) sign_a = sign;
            if (type[i] == 'B' && sign_b == 0) sign_b = sign;
        }

        // 第二遍：验证所有点与各自类别代表符号一致，且两类符号相反
        bool correct = sign_a != sign_b;
        for (int i = 1; i <= n; i++) {
            long long value = theta0 + theta1 * x[i] + theta2 * y[i];
            int sign = value > 0 ? 1 : -1;
            if (type[i] == 'A' && sign != sign_a) correct = false;
            if (type[i] == 'B' && sign != sign_b) correct = false;
        }
        cout << (correct ? "Yes" : "No") << '\n';
    }

    return 0;
}