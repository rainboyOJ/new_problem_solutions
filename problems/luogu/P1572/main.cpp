#include <bits/stdc++.h>
using namespace std;

string s;
long long ans_num, ans_den = 1; // 当前答案为 ans_num / ans_den

long long gcd_ll(long long a, long long b) {
    if (a < 0) {
        a = -a;
    }
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void simplify() {
    long long g = gcd_ll(ans_num, ans_den);
    if (g != 0) {
        ans_num /= g;
        ans_den /= g;
    }
    if (ans_den < 0) {
        ans_den = -ans_den;
        ans_num = -ans_num;
    }
}

long long read_number(int &i) {
    long long value = 0;
    while (i < (int) s.size() && s[i] >= '0' && s[i] <= '9') {
        value = value * 10 + (s[i] - '0');
        i++;
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int i = 0;
    int sign = 1;

    while (i < (int) s.size()) {
        if (s[i] == '+') {
            sign = 1;
            i++;
        }
        else if (s[i] == '-') {
            sign = -1;
            i++;
        }

        long long a = read_number(i);
        i++; // 跳过 '/'
        long long b = read_number(i);

        ans_num = ans_num * b + sign * a * ans_den;
        ans_den = ans_den * b;
        simplify();
    }

    cout << ans_num << '/' << ans_den << '\n';
    return 0;
}
