#include <bits/stdc++.h>
using namespace std;

int t, p;
int period_len;

// 预处理 Fibonacci 模 p 的周期长度。
void build_period() {
    if (p == 1) {
        period_len = 1;
        return;
    }

    int a = 0;
    int b = 1;
    period_len = 0;

    for (int i = 1; i <= 6 * p; i++) {
        int c = (a + b) % p;
        a = b;
        b = c;
        if (a == 0 && b == 1) {
            period_len = i;
            return;
        }
    }
}

// 返回 1 表示 x 先到 0，2 表示 y 先到 0，-1 表示平局。
int solve_one(int x, int y) {
    if (p == 1) {
        return 1;
    }

    x %= p;
    y %= p;

    // 令 a1 = x, a2 = y, 后面满足 a_n = a_{n-1} + a_{n-2} (mod p)。
    // 第 1 次操作得到 a3，对应 x；第 2 次操作得到 a4，对应 y。
    int a = x;
    int b = y;

    for (int step = 1; step <= period_len; step++) {
        int c = (a + b) % p;
        if (c == 0) {
            if (step & 1) {
                return 1;
            }
            return 2;
        }
        a = b;
        b = c;
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t >> p;
    build_period();

    while (t--) {
        int x, y;
        cin >> x >> y;
        int ret = solve_one(x, y);
        if (ret == -1) {
            cout << "error\n";
        }
        else {
            cout << ret << '\n';
        }
    }

    return 0;
}
