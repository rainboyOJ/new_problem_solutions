// brute.cpp：这题本质就是按规则逐项模拟输出，作为教学版朴素解和对拍程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int a[MAXN]; // a[i] 表示 x^i 的系数

// 按题目要求把一项转成字符串并接到答案后面。
void append_term(string &ans, int coef, int exp, bool first_term) {
    if (coef == 0) {
        return;
    }

    if (first_term) {
        if (coef < 0) {
            ans += '-';
        }
    }
    else {
        if (coef > 0) {
            ans += '+';
        }
        else {
            ans += '-';
        }
    }

    int abs_coef = abs(coef);

    // 常数项一定要输出数字；非常数项只有绝对值不是 1 时才输出系数。
    if (exp == 0 || abs_coef != 1) {
        ans += to_string(abs_coef);
    }

    if (exp >= 1) {
        ans += 'x';
        if (exp >= 2) {
            ans += '^';
            ans += to_string(exp);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = n; i >= 0; i--) {
        cin >> a[i];
    }

    string ans;
    bool first_term = true;

    for (int exp = n; exp >= 0; exp--) {
        if (a[exp] == 0) {
            continue;
        }
        append_term(ans, a[exp], exp, first_term);
        first_term = false;
    }

    cout << ans << '\n';
    return 0;
}
