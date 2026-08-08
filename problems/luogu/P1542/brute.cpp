// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
double l[MAXN], r[MAXN], s[MAXN];

bool check(double speed) {
    double low = l[1];
    double high = r[1];

    for (int i = 2; i <= n; i++) {
        double need = s[i] / speed;
        low = max(l[i], low + need);
        high = r[i];
        if (low > high) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i] >> s[i];
    }

    // 小数据暴力版仍然直接二分答案。
    // 这题核心是可行性判定，不存在更自然的离散暴力。
    double left = 0.0;
    double right = 1e8;
    for (int i = 0; i < 100; i++) {
        double mid = (left + right) / 2.0;
        if (check(mid)) right = mid;
        else left = mid;
    }

    cout << fixed << setprecision(2) << right << '\n';
    return 0;
}
