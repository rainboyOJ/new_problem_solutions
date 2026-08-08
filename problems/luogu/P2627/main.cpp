#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, k;
long long e[MAXN];
long long prefix_sum[MAXN];
long long dp[MAXN]; // dp[i] 表示考虑前 i 只奶牛，合法选择的最大效率。
int que[MAXN];      // 单调队列存断点 j，按 dp[j-1]-prefix_sum[j] 从大到小维护。

long long value_of_break(int j) {
    long long left_best = 0;
    if (j > 0) {
        left_best = dp[j - 1];
    }
    return left_best - prefix_sum[j];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> e[i];
        prefix_sum[i] = prefix_sum[i - 1] + e[i];
    }

    int head = 1, tail = 1;
    que[1] = 0; // j=0 表示前面没有断点，可以从第 1 只开始连续选择。
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (head <= tail && value_of_break(que[tail]) <= value_of_break(j)) {
            tail--;
        }
        tail++;
        que[tail] = j;

        // 断点 j 必须满足 i-k <= j <= i，保证 j+1..i 连续选择不超过 k 只。
        while (head <= tail && que[head] < i - k) {
            head++;
        }

        dp[i] = prefix_sum[i] + value_of_break(que[head]);
    }

    cout << dp[n] << '\n';

    return 0;
}
