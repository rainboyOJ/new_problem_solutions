// brute.cpp：小数据直接递归 + 记忆化，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

map<tuple<int, int, int>, long long> memo;

long long solve(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    if (a > 20 || b > 20 || c > 20) {
        return solve(20, 20, 20);
    }

    tuple<int, int, int> key = make_tuple(a, b, c);
    map<tuple<int, int, int>, long long>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    long long ret;
    if (a < b && b < c) {
        ret = solve(a, b, c - 1) + solve(a, b - 1, c - 1) - solve(a, b - 1, c);
    }
    else {
        ret = solve(a - 1, b, c) + solve(a - 1, b - 1, c) + solve(a - 1, b, c - 1) - solve(a - 1, b - 1, c - 1);
    }

    memo[key] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    while (cin >> a >> b >> c) {
        if (a == -1 && b == -1 && c == -1) {
            break;
        }
        cout << "w(" << a << ", " << b << ", " << c << ") = " << solve((int) a, (int) b, (int) c) << '\n';
    }

    return 0;
}
