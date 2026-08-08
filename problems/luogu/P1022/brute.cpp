// brute.cpp：顺着等式扫描并分别统计未知数系数和常数项，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

string s;
char var_name;
double coef_sum;   // 所有未知数项移到左边后的总系数
double const_sum;  // 所有常数项移到左边后的总和

bool is_digit_char(char ch) {
    return ch >= '0' && ch <= '9';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int n = (int) s.size();
    int side = 1; // 左边是 +1，右边是 -1
    int sign = 1;
    int i = 0;

    while (i < n) {
        if (s[i] == '+') {
            sign = 1;
            i++;
            continue;
        }
        if (s[i] == '-') {
            sign = -1;
            i++;
            continue;
        }
        if (s[i] == '=') {
            side = -1;
            sign = 1;
            i++;
            continue;
        }

        int value = 0;
        bool has_number = false;
        while (i < n && is_digit_char(s[i])) {
            value = value * 10 + (s[i] - '0');
            i++;
            has_number = true;
        }

        if (i < n && s[i] >= 'a' && s[i] <= 'z') {
            var_name = s[i];
            if (!has_number) {
                value = 1;
            }
            coef_sum += side * sign * value;
            i++;
        }
        else {
            const_sum += side * sign * value;
        }
    }

    double ans = -const_sum / coef_sum;
    if (fabs(ans) < 0.0005) {
        ans = 0.0;
    }

    cout << var_name << '=';
    cout << fixed << setprecision(3) << ans << '\n';
    return 0;
}
