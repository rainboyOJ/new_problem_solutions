#include <bits/stdc++.h>
using namespace std;

static long long N, A, X, Y;
unordered_map<long long, double> memo;

// dp(n) = 最小期望花费，使 n 变为 0
double dp(long long n) {
    if (n == 0) return 0.0;
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;

    // 操作1：付 X，n -> floor(n/A)
    double cost1 = (double)X + dp(n / A);

    // 操作2：付 Y 掷骰子，b=1 时 n 不变（等于重来一次）
    // dp = Y + (1/6)dp + (1/6)*sum_{b=2..6} dp(n/b)
    // => dp = (6Y + sum_{b=2..6} dp(n/b)) / 5
    double sum = 0.0;
    for (long long b = 2; b <= 6; ++b) sum += dp(n / b);
    double cost2 = (6.0 * (double)Y + sum) / 5.0;

    double res = min(cost1, cost2);
    memo[n] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> A >> X >> Y;

    printf("%.15f\n", dp(N));
    return 0;
}
