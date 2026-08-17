/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, query_count;
long long x[MAXN], y[MAXN];   // 点的横坐标、纵坐标
char type[MAXN];              // 点的类别：A 或 B

// 返回 value 的符号：正为 1，负为 -1（题目保证点不落在直线上）
int get_sign(long long value) {
    return value > 0 ? 1 : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> query_count;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i] >> type[i];

    while (query_count--) {
        long long theta0, theta1, theta2;
        cin >> theta0 >> theta1 >> theta2;

        int sign_a = 0, sign_b = 0;   // A 类与 B 类各自的代表符号
        bool correct = true;
        for (int i = 1; i <= n; i++) {
            // 代入直线方程，结果的正负表示点在直线的哪一侧
            long long value = theta0 + theta1 * x[i] + theta2 * y[i];
            int sign = get_sign(value);
            if (type[i] == 'A') {
                if (sign_a == 0) sign_a = sign;
                else if (sign_a != sign) correct = false;
            } else {
                if (sign_b == 0) sign_b = sign;
                else if (sign_b != sign) correct = false;
            }
        }
        // 两类点必须在直线两侧，即代表符号相反
        if (sign_a == sign_b) correct = false;
        cout << (correct ? "Yes" : "No") << '\n';
    }

    return 0;
}