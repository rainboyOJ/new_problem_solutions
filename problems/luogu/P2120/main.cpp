#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

long long x[MAXN], p[MAXN], c[MAXN];
long long sum_p[MAXN], sum_px[MAXN];
long long dp[MAXN];
int q[MAXN];
int n;

long long X(int i) {
    return sum_p[i];
}

long long Y(int i) {
    return dp[i] + sum_px[i];
}

// 判断队头的后一个决策点是否已经在当前 x 下更优。
bool better_front(int a, int b, long long cur_x) {
    return (__int128) (Y(b) - Y(a)) <= (__int128) cur_x * (X(b) - X(a));
}

// 判断中间点 b 是否永远不会成为最优决策。
bool bad(int a, int b, int c) {
    return (__int128) (Y(b) - Y(a)) * (X(c) - X(b))
         >= (__int128) (Y(c) - Y(b)) * (X(b) - X(a));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> p[i] >> c[i];
        sum_p[i] = sum_p[i - 1] + p[i];
        sum_px[i] = sum_px[i - 1] + p[i] * x[i];
    }

    int head = 1, tail = 1;
    q[1] = 0;
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        while (head < tail && better_front(q[head], q[head + 1], x[i])) {
            head++;
        }

        int j = q[head];
        // j 表示最后一个仓库建在 j 之后，下一个仓库建在 i。
        // 那么 j+1..i-1 的产品都运到 i。
        dp[i] = dp[j]
              + c[i]
              + x[i] * (sum_p[i] - sum_p[j])
              - (sum_px[i] - sum_px[j]);

        // 若斜率相同，只保留截距更小的那个决策点。
        while (head <= tail && X(q[tail]) == X(i)) {
            if (Y(q[tail]) <= Y(i)) {
                break;
            }
            tail--;
        }
        if (head <= tail && X(q[tail]) == X(i) && Y(q[tail]) <= Y(i)) {
            continue;
        }

        while (head < tail && bad(q[tail - 1], q[tail], i)) {
            tail--;
        }
        q[++tail] = i;
    }

    cout << dp[n] << '\n';
    return 0;
}
