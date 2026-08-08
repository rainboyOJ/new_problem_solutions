#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int a[MAXN]; // a[i] 表示 x^i 的系数

// 把一项追加到答案串末尾。
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

    // 指数大于 0 且系数绝对值为 1 时，不输出这个 1。
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

    for (int i = n; i >= 0; i--) {
        if (a[i] == 0) {
            continue;
        }
        append_term(ans, a[i], i, first_term);
        first_term = false;
    }

    cout << ans << '\n';
    return 0;
}
