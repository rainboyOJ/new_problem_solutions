// brute.cpp：小数据朴素解，直接枚举最短边和最长边后约分。
#include <bits/stdc++.h>
using namespace std;

long long gcd_ll(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd_ll(b, a % b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    cin >> a >> b >> c;

    long long mn = min(a, min(b, c));
    long long mx = max(a, max(b, c));
    long long g = gcd_ll(mn, mx);
    cout << mn / g << '/' << mx / g << '\n';
    return 0;
}
