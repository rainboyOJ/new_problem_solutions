#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXM = 5005;

struct Train {
    int x, y, p, q;
} tr[MAXM];

int n, m;
long long A, B, C;
long long dp[MAXM];

long long wait_cost(long long t) {
    return A * t * t + B * t + C;
}

bool cmp_train(const Train &lhs, const Train &rhs) {
    if (lhs.q != rhs.q) {
        return lhs.q < rhs.q;
    }
    if (lhs.p != rhs.p) {
        return lhs.p < rhs.p;
    }
    if (lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    }
    return lhs.y < rhs.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力 DP。
    // 按到达时间排序，枚举所有能接上的前一班车。
    cin >> n >> m >> A >> B >> C;
    for (int i = 1; i <= m; i++) {
        cin >> tr[i].x >> tr[i].y >> tr[i].p >> tr[i].q;
    }

    sort(tr + 1, tr + m + 1, cmp_train);

    long long answer = INF;
    for (int i = 1; i <= m; i++) {
        dp[i] = INF;
        if (tr[i].x == 1) {
            dp[i] = min(dp[i], wait_cost(tr[i].p));
        }
        for (int j = 1; j < i; j++) {
            if (dp[j] >= INF / 2) {
                continue;
            }
            if (tr[j].y == tr[i].x && tr[j].q <= tr[i].p) {
                dp[i] = min(dp[i], dp[j] + wait_cost(tr[i].p - tr[j].q));
            }
        }
        if (tr[i].y == n) {
            answer = min(answer, dp[i] + tr[i].q);
        }
    }

    cout << answer << '\n';
    return 0;
}
