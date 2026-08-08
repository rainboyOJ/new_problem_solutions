#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int MAXN = 1005;

int n;
ull x_arr[MAXN];

// brute.cpp：小数据暴力版。
// 直接做试除分解，统计每个质因子的指数 e，
// 把 floor(e / 3) 部分乘回答案。

ull solve_one(ull x) {
    ull ans = 1;

    for (ull p = 2; p * p * p <= x; p++) {
        if (x % p != 0) {
            continue;
        }

        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }

        while (cnt >= 3) {
            ans *= p;
            cnt -= 3;
        }
    }

    // 剩下的部分如果还能贡献给答案，只可能本身就是一个完整立方数。
    ull l = 1, r = 1000000, cube_root = 0;
    while (l <= r) {
        ull mid = (l + r) >> 1;
        __int128 val = (__int128)mid * mid * mid;
        if (val <= x) {
            cube_root = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    if ((__int128)cube_root * cube_root * cube_root == x) {
        ans *= cube_root;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x_arr[i];
    }

    for (int i = 1; i <= n; i++) {
        cout << solve_one(x_arr[i]) << '\n';
    }

    return 0;
}
