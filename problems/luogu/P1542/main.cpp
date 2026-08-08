#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

int n;
double l[MAXN], r[MAXN], s[MAXN];

// 判断最大速度 speed 是否可行。
bool check(double speed) {
    double low = l[1];
    double high = r[1];

    for (int i = 2; i <= n; i++) {
        double need = s[i] / speed;

        // 从上一站可行到达区间 [low, high] 出发，
        // 加上这一段行驶时间 need 后，到达当前站的可行时间区间是：
        // [low + need, +inf)
        //
        // 由于上一站可以等待到任意不超过 high 的时刻再出发，
        // 所以只要当前站签收区间与 [low + need, +inf) 有交集即可。
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

    double left = 0.0;
    double right = 1e8;

    for (int i = 0; i < 100; i++) {
        double mid = (left + right) / 2.0;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << fixed << setprecision(2) << right << '\n';
    return 0;
}
